#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#define PAGE_SIZE 4096  // 4KB pages
#define NUM_TRACKED_PAGES 10  // Track 10 randomly chosen pages

void displayPageAccessInfo(char *memory, size_t total_pages, size_t *tracked_pages, int *access_count) {
    unsigned char *vec = (unsigned char *)calloc(total_pages, sizeof(unsigned char));
    if (!vec) {
        perror("calloc failed");
        return;
    }

    while (1) {
        if (mincore(memory, total_pages * PAGE_SIZE, vec) == 0) {
            printf("\n=== Page Access Summary (Every 5 sec) ===\n");
            for (size_t i = 0; i < NUM_TRACKED_PAGES; i++) {
                size_t page_index = tracked_pages[i];
                if (vec[page_index] & 1) {
                    access_count[i]++;
                    printf("Page %zu (Real Address: %p) Accessed %d times\n",
                           page_index, (void *)&memory[page_index * PAGE_SIZE], access_count[i]);
                }
            }
        } else {
            perror("mincore failed");
        }
        sleep(5);
    }
    free(vec);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s <memory_size_in_GB>\n", argv[0]);
        return 1;
    }

    int mem_size_gb = atoi(argv[1]);
    if (mem_size_gb <= 0) {
        printf("Invalid memory size.\n");
        return 1;
    }

    printf("Allocating %d GB of memory...\n", mem_size_gb);
    
    size_t total_pages = (mem_size_gb * 256 * 1024);
    char *memory = (char *)mmap(NULL, total_pages * PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (memory == MAP_FAILED) {
        perror("Memory allocation failed");
        return 1;
    }

    int success = 0, fail = 0;

    // Access all allocated pages
    for (size_t i = 0; i < total_pages; i++) {
        char *ptr = &memory[i * PAGE_SIZE];
        if (!ptr) {
            fail++;
        } else {
            memset(ptr, 'a', PAGE_SIZE);  // Access memory to bring it into RAM
            success++;
        }
    }

    printf("Success: %d, Failed: %d\n", success, fail);

    // Randomly select 10 pages to track
    srand(time(NULL));
    size_t tracked_pages[NUM_TRACKED_PAGES];
    int access_count[NUM_TRACKED_PAGES] = {0};  // Initialize access counts to zero
    for (size_t i = 0; i < NUM_TRACKED_PAGES; i++) {
        tracked_pages[i] = rand() % total_pages;
    }

    printf("\nTracking %d Random Pages for Access Frequency:\n", NUM_TRACKED_PAGES);
    for (size_t i = 0; i < NUM_TRACKED_PAGES; i++) {
        printf("Tracking Page %zu (Address: %p)\n", tracked_pages[i], (void *)&memory[tracked_pages[i] * PAGE_SIZE]);
    }

    // Start tracking accessed pages
    displayPageAccessInfo(memory, total_pages, tracked_pages, access_count);

    // Cleanup (this point will never be reached in the infinite loop)
    munmap(memory, total_pages * PAGE_SIZE);
    return 0;
}
