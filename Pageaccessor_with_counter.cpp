#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

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
        printf("No memory defined\n");
        return -1;
    }

    num_pages = 256 * 1024 * atoi(argv[1]); 

    
    printf("Received: %d GB\n", atoi(argv[1]));

    
    char *ptr[num_pages];
    int access_count[num_pages]; 
    for (i = 0; i < num_pages; i++) {
        ptr[i] = (char *)malloc(PAGE_SIZE);
        access_count[i] = 0; 
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

    printf("Success %d, Failed: %d\n", success, fail);

    
    srand(time(NULL));

    while (1) {
        // Randomly access pages
        int random_page = rand() % num_pages;  
        char temp = ptr[random_page][0];       

        
        access_count[random_page]++;


        printf("Accessing page %d (access count: %d)\n", random_page, access_count[random_page]);
    }

    return 0;
}
