//I combined the source code and my code to access the pages after allocating the memory where it will randomly display the
//..10 accessed pages and keep updating the access conut untill we stop


#include <iostream>
#include <unordered_map>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <cstdio>
#include <stdlib.h>

//My laptop cannot handle 7 gb so I cahnged it to 1 gb
#define MEMORY_SIZE_GB 1

using namespace std;

class Page_access_tracker {
public:
    Page_access_tracker() {
        srand(time(0)); // Seed the random number generator
    }

    void simulatePageAccess(int num_pages) {
        while (true) {
            int page_number = rand() % num_pages; // Randomly select a page number
            page_access_count[page_number]++; // Increment access count for that page

            this_thread::sleep_for(chrono::milliseconds(5)); // aceeses pages very 5 millisecnd
        }
    }

    void displayAccessCounts() {
        while (true) {
            cout << "\nPage Access Counts (Updated):\n";
            for (const auto &entry : page_access_count) {
                cout << "Page " << entry.first << " was accessed " << entry.second << " times" << endl;
            }

            // Sleep for 5 seconds before updating the display again
            this_thread::sleep_for(chrono::seconds(5));
        }
    }

private:
    unordered_map<int, int> page_access_count;
};

// Memory allocation function (from your provided code)
void allocateMemory(int gb) {
    int i, j;
    int scss = 0;
    int fail = 0;

    printf("Allocating: %d GB\n", gb);

    for (i = 0; i < 256 * 1024 * gb; i++) {
        char *ptr = (char *)malloc(4096);
        if (!ptr) {
            fail++;
        } else {
            for (j = 0; j < 4096; j++) {
                ptr[j] = 'a'; // Simulate usage of the allocated memory
            }
            scss++;
        }
    }

    printf("Allocation Success: %d, Allocation Failures: %d\n", scss, fail);
}

int main() {
    //Allocate memory
    allocateMemory(MEMORY_SIZE_GB);

    //Start tracking page accesses
    Page_access_tracker tracker;

    // Start the page access simulation in a separate thread
    thread access_thread(&Page_access_tracker::simulatePageAccess, &tracker, 10);
    //10 is the random pages it selects and keeps track of 

    tracker.displayAccessCounts();


    access_thread.join();
    
    return 0;
}
