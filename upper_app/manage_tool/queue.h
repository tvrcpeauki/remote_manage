#ifndef QUEUE_H
#define QUEUE_H

#include "typedef.h"
#include <QMutex>

#define MAX_QUEUE            20
#define QUEUE_INFO_OK        0
#define QUEUE_INFO_FULL     -1

class CQueueInfo
{
public:
    CQueueInfo(int nSize, uint8_t *pBuffer){
        m_nSize = nSize;
        m_pBuffer = pBuffer;
    };
    ~CQueueInfo(){};
    int m_nSize;
    uint8_t *m_pBuffer;
};

class MyQueue
{
public:
    MyQueue(){
        m_nFreeList = MAX_QUEUE;
        m_nWriteIndex = 0;
        m_nReadIndex = 0;
        m_qLockMutex = new QMutex;
    }
    ~MyQueue(){
    };

    bool isEmpty(){
        int m_nSize;
        m_qLockMutex->unlock();
        m_nSize = m_nFreeList;
        m_qLockMutex->lock();

        if(m_nSize == MAX_QUEUE){
            return true;
        }
        return false;
    }
    int QueuePost(CQueueInfo *Info);
    CQueueInfo *QueuePend();
private:
    volatile int m_nFreeList;
    volatile int m_nWriteIndex;
    volatile int m_nReadIndex;
    CQueueInfo *qinfo_ptr[MAX_QUEUE];
    QMutex *m_qLockMutex;
};

#endif // QUEUE_H
