#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "typedef.h"

#define PROTOCOL_SEND_HEAD  0x5A

#define BUFF_CACHE_SIZE     1200

class protocol_info
{
public:
    protocol_info(uint8_t *p_rx, uint8_t *p_tx);
        ~protocol_info();
    int check_receive_data(void);
    int create_send_buf(uint8_t id, uint16_t size, uint8_t *pdata);
    uint16_t crc_calculate(uint8_t *ptr, int len);

    virtual int device_read(uint8_t *ptr, uint16_t size) = 0;
    virtual int device_write(uint8_t *ptr, uint16_t size) = 0;
private:
    uint8_t *rx_ptr;
    uint8_t *tx_ptr;
    uint16_t packet_id;
};

#endif // PROTOCOL_H
