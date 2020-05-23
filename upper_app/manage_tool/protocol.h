#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "typedef.h"
#include <QMutex>

#define PROTOCOL_SEND_HEAD  0x5A
#define BUFF_CACHE_SIZE     1200

#define PROTOCOL_RECV_HEAD  0x5B


#define MAX_QUEUE            20
#define QUEUE_INFO_OK        0
#define QUEUE_INFO_FULL     -1

class SSendBuffer
{
public:
    SSendBuffer(int nSize, uint8_t *pBuffer, bool bWriteThrough){
        m_nSize = nSize;
        m_pBuffer = pBuffer;
        m_IsWriteThrough = bWriteThrough;
    }
    ~SSendBuffer(){

    }

    int m_nSize;
    uint8_t m_IsWriteThrough;
    uint8_t *m_pBuffer;
};

class CUserQueue
{
public:
    CUserQueue(){
        m_nFreeList = MAX_QUEUE;
        m_nWriteIndex = 0;
        m_nReadIndex = 0;
        m_qLockMutex = new QMutex;
    }
    ~CUserQueue(){
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
    int QueuePost(SSendBuffer *Info);
    SSendBuffer *QueuePend();
private:
    volatile int m_nFreeList;
    volatile int m_nWriteIndex;
    volatile int m_nReadIndex;
    SSendBuffer *qinfo_ptr[MAX_QUEUE];
    QMutex *m_qLockMutex;
};

class CProtocolInfo
{
public:
    CProtocolInfo(uint8_t *pRxBuffer, uint8_t *pTxBuffer);
        ~CProtocolInfo();

    int CreateSendBuffer(uint8_t nId, uint16_t nSize, uint8_t *pStart, bool bWriteThrough);
    uint16_t CaclcuCrcVal(uint8_t *pStart, int nSize);

    virtual int DeviceRead(uint8_t *pStart, uint16_t nMaxSize) = 0;
    virtual int DeviceWrite(uint8_t *pStart, uint16_t nSize) = 0;
    virtual int CheckReceiveData(void) = 0;
private:
    uint8_t *m_pRxBuffer;
    uint8_t *m_pTxBuffer;  
    uint16_t m_nPacketId;
};

#endif // PROTOCOL_H
