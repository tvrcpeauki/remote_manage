#ifndef PROTOCOL_H
#define PROTOCOL_H

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

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
private:
    uint8_t *rx_ptr;
    uint8_t *tx_ptr;
    uint16_t packet_id;
};

#endif // PROTOCOL_H
