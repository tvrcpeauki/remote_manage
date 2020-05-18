
#include "protocol.h"
#include <QTime>

protocol_info::protocol_info(uint8_t *p_rx, uint8_t *p_tx)
{
    this->rx_ptr = p_rx;
    this->tx_ptr = p_tx;
}

int protocol_info::create_send_buf(uint8_t id, uint16_t size, uint8_t *pdata)
{
    if(this->tx_ptr != nullptr)
    {
        uint8_t out_size, index;
        uint16_t crc_calc;
        uint16_t random;

        //生成随机数
        qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
        random = qrand()%65536;
        this->packet_id = random;

        out_size = 0;
        this->tx_ptr[out_size++] = PROTOCOL_SEND_HEAD;
        this->tx_ptr[out_size++] = id;
        this->tx_ptr[out_size++] = (uint8_t)(random>>8);
        this->tx_ptr[out_size++] = (uint8_t)(random&0xff);
        this->tx_ptr[out_size++] = (uint8_t)(size>>8);
        this->tx_ptr[out_size++] = (uint8_t)(size&0xff);

        if(size != 0 && pdata != NULL)
        {
            for(index=0; index<size; index++)
            {
                this->tx_ptr[out_size++] = *(pdata+index);
            }
        }

        crc_calc = this->crc_calculate(&this->tx_ptr[1], out_size-1);
        this->tx_ptr[out_size++] = (uint8_t)(crc_calc>>8);
        this->tx_ptr[out_size++] = (uint8_t)(crc_calc&0xff);

        return out_size;
    }
    else
        return 0;
}

//crc校验实现
uint16_t protocol_info::crc_calculate(uint8_t *ptr, int len)
{
    if(ptr == NULL || len == 0)
    {
        return 0;
    }
    return 0xffff;
}
