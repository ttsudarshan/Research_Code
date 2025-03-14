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

    if (argc < 2) {
        printf("no memory definedn\n");
        return -1;
    }

    num_pages = 256 * 1024 * atoi(argv[1]); // Total number of pages to access

    // Print the requested memory size
    printf("received: %d GB\n", atoi(argv[1]));

    // Allocate memory pages
    char *ptr[num_pages];
    for (i = 0; i < num_pages; i++) {
        ptr[i] = (char *)malloc(PAGE_SIZE);
        if (!ptr[i]) {
            printf("Memory allocation failed at page %d\n", i);
            fail++;
        } else {
    
            for (j = 0; j < PAGE_SIZE; j++) {
                ptr[i][j] = 'a';
            }
            success++;
        }
    }

    printf("Sucess %d, failed: %d\n", success, fail);

  
    while (1) {
      int random_page = rand() % num_pages;  // randomly access those pages
        char temp = ptr[random_page][0];

        //for (i = 0; i < num_pages; i++) {
         //   // Access each page and read only
          //  char temp = ptr[i][0];
        //}
    }

    return 0;
}
