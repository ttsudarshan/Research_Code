#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MEMORY_SIZE_GB 7
#define PAGE_SIZE 4096

using namespace std;

int main(int argc, char **argv)
{
    int i, j;
    int success = 0;
    int fail = 0;
    int num_pages;

    // Convert the input argument to integer
    if (argc < 2) {
        printf("no memory defined");
        return -1;
    }

    num_pages = 256 * 1024 * atoi(argv[1]); // Total number of pages to access

    // Print the requested memory size
    printf("Accessing pages for: %d GB\n", atoi(argv[1]));

    // Allocate memory pages
    char *ptr[num_pages];
    for (i = 0; i < num_pages; i++) {
        ptr[i] = (char *)malloc(PAGE_SIZE);
        if (ptr[i] == NULL) {
            printf("Memory allocation failed at page %d\n", i);
            fail++;
        } else {
            // Initialize the page with a value to ensure it is not optimized away
            for (j = 0; j < PAGE_SIZE; j++) {
                ptr[i][j] = 'a';
            }
            success++;
        }
    }

    printf("Successfully allocated pages: %d, Allocation failures: %d\n", success, fail);

    // Repeatedly access the memory pages until the program is killed
    while (1) {
        for (i = 0; i < num_pages; i++) {
            // Access each page (simple read operation)
            char temp = ptr[i][0];
        }
    }

    return 0;
}
