# WRSemaphore

## Overview

WRSemaphore is a semaphore class designed to allow multiple simultaneous reads while giving priority to write operations. Threads calling `attempt_write()` will be prioritized over incoming read attempts and will wait for current readers to finish.

## Features

- **Multiple Reads**: Allows multiple threads to read simultaneously.
- **Write Priority**: Prioritizes write operations over read operations.
- **Thread-Safe**: Ensures that only one thread can write to the shared memory at a time.

## Usage

### Basic Use Case

The class is used in a manner similar to the basic mutex `lock_guard`, but with some additional steps. Here's a basic example:

```cpp
WRSemaphore shared_semaphore;
```

#### Thread 1 (Write Operation)

```cpp
// Non-cross-thread code
shared_semaphore_pointer->attempt_write();
// Write to shared memory
shared_semaphore_pointer->done_write();
```

#### Thread 2 (Read Operation)

```cpp
// Non-cross-thread code
shared_semaphore_pointer->attempt_read();
// Read shared memory
shared_semaphore_pointer->done_read();
```

#### Thread 3 (Read Operation)

```cpp
// Non-cross-thread code
shared_semaphore_pointer->attempt_read();
// Read shared memory
shared_semaphore_pointer->done_read();
```

### Notes

- Threads 2 and 3 can read simultaneously; this is by design.
- This form of mutual exclusion is intended for applications with frequent reads and *in*frequent writes.

### Write Priority

If a reading thread is still within the critical region and a write thread calls `attempt_write()`, any further read attempts will be blocked until the write is complete. This ensures that write operations are not starved and can access the data even in a high-read environment.