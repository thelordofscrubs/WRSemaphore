# WRSemaphore
WRSemaphore is a semaphore class that allows multiple simultaneous reads, while also preferring writes.
Any thread that calls the attempt_write() function will be given priority over any incoming read attempts, and will wait for current readers to finish reading.
Any thread calling attempt_read() will be given instant access in the event that no other thread is in the critical region, or in the event that only readers are currently granted access (and that no writers are waiting)

# Usage

The class is used somewhat similarly to the basic mutex lock_guard, albeit with some additional steps.

The basic use case is as follows:

WRSemaphore shared_semaphore;

Thread 1:
    //non cross thread code
    shared_semaphore_pointer->attempt_write()
    //write to memory shared between threads ---- When this thread is in the critical region, no other thread can read or write using the same semaphore
    shared_semaphore_pointer->done_write()

Thread 2:
    //non cross thread code
    shared_semaphore_pointer->attempt_read()
    //read memory that other threads write to
    shared_semaphore_pointer->done_read()

Thread 3:
    //non cross thread code
    shared_semaphore_pointer->attempt_read()
    //read memory that other threads write to
    shared_semaphore_pointer->done_read()


Note that Threads 2 and 3 can read simoultaneously, this is by design. This form of mutual exclusion is intended for applications where you have frequent reads, and *in*frequent writes.

In the event that a reading thread is still within the critical region, and a write thread calls attempt_write(), any further read attempts will be blocked until the write is finished. This way, in the event of a continuous stream of read attempts, write attempts are still able (and given priority) to access the data.





# Credit
Eli Kaituri and Conner Sutton