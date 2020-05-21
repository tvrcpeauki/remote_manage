//环形队列，线程间的消息通讯
#include "queue.h"
#include <QEventLoop>
#include <QTime>
#include <QThread>

int CUserQueue::QueuePost(CQueueInfo *info)
{
    if(m_nFreeList == 0)
    {
        return QUEUE_INFO_FULL;
    }

    m_qLockMutex->lock();
    qinfo_ptr[m_nWriteIndex] = info;
    m_nWriteIndex++;

    //队列循环
    if(m_nWriteIndex == MAX_QUEUE){
        m_nWriteIndex = 0;
    }
    m_nFreeList--;
    m_qLockMutex->unlock();

    return QUEUE_INFO_OK;
}

CQueueInfo *CUserQueue::QueuePend()
{
    CQueueInfo *info = nullptr;

    if(m_nFreeList < MAX_QUEUE)
    {
        m_qLockMutex->lock();
        info = qinfo_ptr[m_nReadIndex];
        m_nReadIndex++;

        //队列循环
        if(m_nReadIndex == MAX_QUEUE){
            m_nReadIndex = 0;
        }
        m_nFreeList++;
        m_qLockMutex->unlock();
    }
    else{
        xtime time;
        time.sec = 1;
        _Thrd_sleep(&time);
    }
    return info;
}
