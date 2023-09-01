#include "WRSemaphore.h"

WRSemaphore::WRSemaphore() {
    counter.store(0);
    writer_waiting.store(0);
}

void WRSemaphore::attempt_read() {
    while(writer_waiting.load() > 0 || counter.load() < 0);

    counter++;
    return;

}

void WRSemaphore::done_read(){
    counter--;
}

void WRSemaphore::attempt_write() {
    writer_waiting++;
    while (counter > 0);
    mtx.lock();
    counter.store(-1);
    writer_waiting--;
    return;
}

void WRSemaphore::done_write() {
    counter.store(0);
    mtx.unlock();
    return;
}