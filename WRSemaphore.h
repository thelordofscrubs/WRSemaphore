#ifndef MYCLASS_H
#define MYCLASS_H

#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif

#include <mutex>
#include <atomic>
#include <thread>
#include <vector>


class DLL_EXPORT WRSemaphore {

    protected:
    std::atomic<int> counter;
    std::atomic<int> writer_waiting;
    std::mutex mtx;
    void start_read();
    void start_write();

    public:
    WRSemaphore();

    void attempt_read();
    void done_read();

    void attempt_write();
    void done_write();
};

#endif