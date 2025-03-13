#include <iostream>
#include <unordered_map>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

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

            this_thread::sleep_for(chrono::milliseconds(50)); // Simulate delay (100ms)
        }
    }

    void displayAccessCounts() {
        while (true) {
            cout << "\nPage Access Counts (Updated):\n";
            for (const auto &entry : page_access_count) {
                cout << "Page " << entry.first << " was accessed " << entry.second << " times" << std::endl;
            }

            // Sleep for 5 seconds before updating the display again
            this_thread::sleep_for(chrono::seconds(5));
        }
    }

private:
    unordered_map<int, int> page_access_count;
};

int main() {
    Page_access_tracker tracker;

    // Start the page access simulation in a separate thread
    thread access_thread(&Page_access_tracker::simulatePageAccess, &tracker, 10); // Simulating 10 pages

    // Start displaying the access counts in the main thread
    tracker.displayAccessCounts();

    // Join the access thread (although it runs forever, the program will keep running)
    access_thread.join();
    
    return 0;
}
