# WRSemaphore

WRSemaphore is a semaphore class designed to allow multiple simultaneous reads while giving priority to write operations. Threads calling `attempt_write()` will be prioritized over incoming read attempts and will wait for current readers to finish.

## Installation

### Prerequisites

- Make sure you have a C++ compiler installed (e.g., g++, MSVC).
- Ensure that your development environment is set up (e.g., Visual Studio Code, Visual Studio, etc.).

### Steps

1. **Clone the Repository or Download the ZIP**

    Clone the repository to your local machine using git:

    ```bash
    git clone https://github.com/yourusername/WRSemaphore.git
    ```

    Or download the ZIP file from the repository and extract it.

2. **Locate the DLL and Header File**

    Navigate to the repository folder and locate the following files:

    - `WRSemaphore.dll`: The pre-compiled dynamic link library.
    - `WRSemaphore.h`: The header file containing the class definition.

3. **Copy Files to Your Project**

    Copy `WRSemaphore.dll` and `WRSemaphore.h` into your project's working directory.

4. **Link the DLL**

    - **For g++**: Use the `-L` flag to specify the directory containing `WRSemaphore.dll` and `-lWRSemaphore` to link the library.

        ```bash
        g++ your_file.cpp -L. -lWRSemaphore
        ```

    - **For MSVC**: Add the directory containing `WRSemaphore.dll` to the list of directories to be searched for libraries. Then, add `WRSemaphore.lib` to the list of additional dependencies.

5. **Include the Header**

    In your C++ source files, include the header file as follows:

    ```cpp
    #include "WRSemaphore.h"
    ```

6. **Compile and Run**

    Compile your project. Make sure that `WRSemaphore.dll` is either in the same directory as your executable or in a directory listed in your system's PATH.


## Features

- **Multiple Reads**: Allows multiple threads to read simultaneously.
- **Write Priority**: Prioritizes write operations over read operations.
- **Thread-Safe**: Ensures that only one thread can write to the shared memory at a time.

### API Reference

#### `void attempt_read()`

Initiates a read attempt. Blocks if a write operation is in progress or waiting.

#### `void done_read()`

Signals the completion of a read operation, allowing waiting write operations to proceed.

#### `void attempt_write()`

Initiates a write attempt. Blocks until all read operations are complete.

#### `void done_write()`

Signals the completion of a write operation, allowing other read or write operations to proceed.


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