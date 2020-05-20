//协议层的实现
#include "protocol.h"
#include <QTime>

CProtocolInfo::CProtocolInfo(uint8_t *pRxBuffer, uint8_t *pTxBuffer)
{
    m_pRxBuffer = pRxBuffer;
    m_pTxBuffer = pTxBuffer;
}

int CProtocolInfo::CreateSendBuffer(uint8_t nId, uint16_t nSize, uint8_t *pStart)
{
    if(m_pTxBuffer != nullptr)
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
