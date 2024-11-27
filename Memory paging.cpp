#include <iostream>
#include <vector>
using namespace std;

const int pageSize = 1024;
const int numPage = 8; 
const int physicalFrames = 4;


struct Process {
    int pid; // Process ID
    int virtualAddress; // Virtual memory address
};

int main() {
    
    vector<int> pageTable(numPage, -1);

    for (int i = 0; i < physicalFrames; ++i) {
        pageTable[i] = i;
    }

    Process process;
    process.pid = 1;
    process.virtualAddress = 3203; 

    //  gets virtual page number and offset
    int virtualPageNumber = process.virtualAddress / pageSize;
    int offset = process.virtualAddress % pageSize;

    cout << "Process ID: " << process.pid << endl;
    cout << "Virtual Address: " << process.virtualAddress << endl;
    cout << "Virtual Page Number: " << virtualPageNumber << endl;
    cout << "Offset: " << offset << endl;

    // converts virtual address to physical address
    if (virtualPageNumber < numPage && pageTable[virtualPageNumber] != -1) {
        int physicalFrameNumber = pageTable[virtualPageNumber];
        int physicalAddress = physicalFrameNumber * pageSize + offset;

        cout << "Mapped to physical frame: " << physicalFrameNumber << endl;
        cout << "Physical Address: " << physicalAddress << endl;
    } else {
        cout << "Error" << endl;
    }

    return 0;
}
