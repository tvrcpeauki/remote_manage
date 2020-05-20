#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "typedef.h"

#define PROTOCOL_SEND_HEAD  0x5A

#define BUFF_CACHE_SIZE     1200

class CProtocolInfo
{
public:
    CProtocolInfo(uint8_t *pRxBuffer, uint8_t *pTxBuffer);
        ~CProtocolInfo();
    int CheckReceiveData(void);
    int CreateSendBuffer(uint8_t nId, uint16_t nSize, uint8_t *pStart);
    uint16_t CaclcuCrcVal(uint8_t *pStart, int nSize);

    virtual int DeviceRead(uint8_t *pStart, uint16_t nMaxSize) = 0;
    virtual int DeviceWrite(uint8_t *pStart, uint16_t nSize) = 0;
private:
    uint8_t *m_pRxBuffer;
    uint8_t *m_pTxBuffer;
    uint16_t m_nPacketId;
};

#endif // PROTOCOL_H
