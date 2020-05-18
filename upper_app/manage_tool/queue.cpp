//环形队列，线程间的消息通讯
#include "queue.h"
#include <QEventLoop>
#include <QTime>
#include <QThread>

int MyQueue::QueuePost(MyQInfo *info)
{
    if(this->freelist == 0)
    {
        return QUEUE_INFO_FULL;
    }

    this->lock_mutex->lock();
    this->qinfo_ptr[write_index] = info;
    this->write_index++;

    //队列循环
    if(this->write_index == MAX_QUEUE){
        this->write_index = 0;
    }
    this->freelist--;
    this->lock_mutex->unlock();

    return QUEUE_INFO_OK;
}

MyQInfo *MyQueue::QueuePend()
{
    MyQInfo *info = nullptr;

    if(this->freelist < MAX_QUEUE)
    {
        this->lock_mutex->lock();
        info = this->qinfo_ptr[read_index];
        this->read_index++;

        //队列循环
        if(this->read_index == MAX_QUEUE){
            this->read_index = 0;
        }
        this->freelist++;
        this->lock_mutex->unlock();
    }
    else{
        xtime time;
        time.sec = 1;
        _Thrd_sleep(&time);
    }
    return info;
}
