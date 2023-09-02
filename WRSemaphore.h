// Preprocessor directive to prevent multiple inclusions of the header file.
#ifndef MYCLASS_H
#define MYCLASS_H

// Macro to export or import classes and functions when building or using a DLL.
#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)  // Exporting the class if building a DLL.
#else
    #define DLL_EXPORT __declspec(dllimport)  // Importing the class if using the DLL.
#endif

// Include necessary header files for multithreading and synchronization.
#include <mutex>
#include <atomic>
#include <thread>
#include <vector>
#include <condition_variable>  // Include for condition variables.

// Class definition for WRSemaphore.
class DLL_EXPORT WRSemaphore {

    protected:
    std::atomic<int> counter;         // Atomic counter for the number of readers.
    std::atomic<int> writer_waiting;  // Atomic counter for the number of waiting writers.
    std::mutex mtx;                   // Mutex for synchronizing write operations.
    std::condition_variable cv;       // Condition variable for efficient thread waiting.
    std::mutex cv_m;                  // Mutex for the condition variable.

    // Placeholder functions for future use or subclassing.
    void start_read();
    void start_write();

    public:
    // Constructor to initialize the WRSemaphore object.
    WRSemaphore();

    // Public methods for read and write operations.
    void attempt_read();  // Method for a thread to attempt to read.
    void done_read();     // Method for a thread to indicate it has finished reading.

    void attempt_write(); // Method for a thread to attempt to write.
    void done_write();    // Method for a thread to indicate it has finished writing.
};

// End of preprocessor directive for multiple inclusions.
#endif
