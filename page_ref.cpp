#include <iostream>
#include <queue>
#include <unordered_set>
using namespace std;

int main() {
    int pages[] = {1, 3, 0, 3, 5, 6, 3};
    int n = sizeof(pages) / sizeof(pages[0]);
    int capacity = 3;

    unordered_set<int> pageSet;     // To check if a page is in memory
    queue<int> pageQueue;           // To maintain the order of pages (FIFO)

    int pageFaults = 0;

    for (int i = 0; i < n; i++) {
        int page = pages[i];

        // If page is not present in memory
        if (pageSet.find(page) == pageSet.end()) {
            // If memory is full, remove the oldest page
            if (pageQueue.size() == capacity) {
                int oldest = pageQueue.front();
                pageQueue.pop();
                pageSet.erase(oldest);
            }

            // Add the new page
            pageQueue.push(page);
            pageSet.insert(page);
            pageFaults++;
        }
        // If page is already in memory, do nothing (no page fault)
    }

    cout << "Total Page Faults: " << pageFaults << endl;

    return 0;
}

