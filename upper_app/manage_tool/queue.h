#ifndef QUEUE_H
#define QUEUE_H

#include "typedef.h"
#include <QMutex>

#define MAX_QUEUE            20

#define QUEUE_INFO_OK        0
#define QUEUE_INFO_FULL     -1

class MyQInfo
{
public:
    MyQInfo(int s, uint8_t *b){
        this->size = s;
        this->buf = b;
    };
    ~MyQInfo(){};
    int size;
    uint8_t *buf;
};

class MyQueue
{
public:
    MyQueue(){
        this->freelist = MAX_QUEUE;
        this->write_index = 0;
        this->read_index = 0;
        this->lock_mutex = new QMutex;
    }
    ~MyQueue(){
    };

    bool isEmpty(){
        int size;
        lock_mutex->unlock();
        size = this->freelist;
        lock_mutex->lock();

        if(size == MAX_QUEUE){
            return true;
        }
        return false;
    }
    int QueuePost(MyQInfo *Info);
    MyQInfo *QueuePend();
private:
    volatile int freelist;
    volatile int write_index;
    volatile int read_index;
    MyQInfo *qinfo_ptr[MAX_QUEUE];
    QMutex *lock_mutex;
};

#endif // QUEUE_H
