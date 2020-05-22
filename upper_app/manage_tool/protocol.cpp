//协议层的实现
#include "protocol.h"
#include <QTime>
#include <QEventLoop>
#include <QThread>

CProtocolInfo::CProtocolInfo(uint8_t *pRxBuffer, uint8_t *pTxBuffer)
{
    m_pRxBuffer = pRxBuffer;
    m_pTxBuffer = pTxBuffer;
}

int CProtocolInfo::CreateSendBuffer(uint8_t nId, uint16_t nSize, uint8_t *pStart, bool bWriteThrough)
{
    if(m_pTxBuffer != nullptr)
    {
        if(bWriteThrough == false)
        {
            uint8_t nTotalSize, nIndex;
            uint16_t nCrcVal;
            uint16_t random;

            //生成随机数
            qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
            random = qrand()%65536;
            m_nPacketId = random;

            nTotalSize = 0;
            m_pTxBuffer[nTotalSize++] = PROTOCOL_SEND_HEAD;
            m_pTxBuffer[nTotalSize++] = nId;
            m_pTxBuffer[nTotalSize++] = (uint8_t)(random>>8);
            m_pTxBuffer[nTotalSize++] = (uint8_t)(random&0xff);
            m_pTxBuffer[nTotalSize++] = (uint8_t)(nSize>>8);
            m_pTxBuffer[nTotalSize++] = (uint8_t)(nSize&0xff);

            if(nSize != 0 && pStart != NULL)
            {
                for(nIndex=0; nIndex<nSize; nIndex++)
                {
                    m_pTxBuffer[nTotalSize++] = *(pStart+nIndex);
                }
            }

            nCrcVal = CaclcuCrcVal(&m_pTxBuffer[1], nTotalSize-1);
            m_pTxBuffer[nTotalSize++] = (uint8_t)(nCrcVal>>8);
            m_pTxBuffer[nTotalSize++] = (uint8_t)(nCrcVal&0xff);

            return nTotalSize;
         }
         else
         {
            memcpy(m_pTxBuffer, pStart, nSize);
            return nSize;
         }
    }
    else
        return 0;
}

//crc校验实现
uint16_t CProtocolInfo::CaclcuCrcVal(uint8_t *pStart, int nSize)
{
    if(pStart == NULL || nSize == 0)
    {
        return 0;
    }
    return 0xffff;
}

int CUserQueue::QueuePost(SSendBuffer *info)
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

SSendBuffer *CUserQueue::QueuePend()
{
    SSendBuffer *info = nullptr;

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


