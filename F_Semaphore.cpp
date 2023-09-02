#include "WRSemaphore.h"

// Constructor initializes the atomic variables counter and writer_waiting to 0.
WRSemaphore::WRSemaphore() {
    counter.store(0);          // Initialize reader counter to 0.
    writer_waiting.store(0);   // Initialize writer waiting counter to 0.
}

// Function for a thread to attempt to read.
void WRSemaphore::attempt_read() {
    std::unique_lock<std::mutex> lk(cv_m);  // Acquire a unique lock on the mutex for the condition variable.
    // Wait until no writer is waiting and no writer is in the critical section.
    cv.wait(lk, [this] { return writer_waiting.load() == 0 && counter.load() >= 0; });
    counter++;  // Increment the reader counter to indicate a new reader in the critical section.
}

// Function for a thread to indicate it has finished reading.
void WRSemaphore::done_read(){
    counter--;  // Decrement the reader counter to indicate a reader has left the critical section.
    cv.notify_all();  // Notify all waiting threads (likely writers) that they can attempt to acquire the lock.
}

// Function for a thread to attempt to write.
void WRSemaphore::attempt_write() {
    std::unique_lock<std::mutex> lk(cv_m);  // Acquire a unique lock on the mutex for the condition variable.
    writer_waiting++;  // Increment the writer waiting counter to give priority to writers.
    // Wait until no readers or writers are in the critical section.
    cv.wait(lk, [this] { return counter.load() <= 0; });
    mtx.lock();  // Acquire the mutex lock for the critical section.
    counter.store(-1);  // Set the counter to -1 to indicate a writer is in the critical section.
    writer_waiting--;  // Decrement the writer waiting counter as the writer has acquired the lock.
}

// Function for a thread to indicate it has finished writing.
void WRSemaphore::done_write() {
    counter.store(0);  // Reset the counter to 0 to allow other threads to enter the critical section.
    mtx.unlock();  // Release the mutex lock for the critical section.
    cv.notify_all();  // Notify all waiting threads (readers and writers) that they can attempt to acquire the lock.
}
