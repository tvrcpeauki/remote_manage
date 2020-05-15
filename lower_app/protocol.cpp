/*
 * File      : protocol.cpp
 * 协议层文件,符合解析的结构
 * COPYRIGHT (C) 2020, zc
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-5-4      zc           the first version
 */

/**
 * @addtogroup IMX6ULL
 */
/*@{*/

#include "include/protocol.h"
#include "include/app_task.h"

/**************************************************************************
* Local Macro Definition
***************************************************************************/

/**************************************************************************
* Local Type Definition
***************************************************************************/

/**************************************************************************
* Local static Variable Declaration
***************************************************************************/

/**************************************************************************
* Global Variable Declaration
***************************************************************************/

/**************************************************************************
* Local Function Declaration
***************************************************************************/

/**************************************************************************
* Function
***************************************************************************/
/**
 * 内部数据构造函数
 * 
 * @param p_rx  接收数据首地址指针
 * @param p_tx  发送数据首地址指针
 * @param p_rxd 接收到有效数据首地址
 *  
 * @return NULL
 */
protocol_info::protocol_info(uint8_t *p_rx, uint8_t *p_tx, uint8_t *p_rxd, uint16_t max_bs)
{
    this->rx_ptr = p_rx;
    this->tx_ptr = p_tx;
    this->rx_data_ptr = p_rxd;
    this->rx_size = 0;
    this->tx_size = 0;
    this->packet_id = 0;
    this->rx_data_size = 0;
    this->max_buf_size = max_bs;
}

/**
 * 接收数据以及校验
 * 
 * @param fd 访问设备的ID
 *  
 * @return 接收数据和校验的结果
 */
int protocol_info::check_receive_data(int fd)
{
    int nread;
    int CrcRecv, CrcCacl;
	struct req_frame *frame_ptr; 

	/*从设备中读取数据*/
    nread = this->device_read(fd, &this->rx_ptr[this->rx_size], 
                             (this->max_buf_size-this->rx_size));
    if(nread > 0)
    {        
       this->rx_size += nread;
       frame_ptr = (struct req_frame *)this->rx_ptr;

	   /*接收到头不符合预期*/
       if(frame_ptr->head != PROTOCOL_REQ_HEAD) {
            USR_DEBUG("No Valid Head\n");
	    	this->rx_size = 0;
            return RT_FAIL;
       }

	   /*已经接收到长度数据*/
       else if(this->rx_size > 5){
		    int nLen;

		    /*设备ID检测*/
            if(frame_ptr->id != PROTOCOL_DEVICE_ID)
            {
                this->rx_size = 0;
				USR_DEBUG("Valid ID\n");
                return RT_FAIL;
            }

			/*获取接收数据的总长度*/
			this->rx_data_size = LENGTH_CONVERT(frame_ptr->length);

			/*crc冗余校验*/
            nLen = this->rx_data_size+FRAME_HEAD_SIZE+CRC_SIZE;
            if(this->rx_size >= nLen)
            {
				/*计算head后到CRC尾之前的所有数据的CRC值*/
                CrcRecv = (this->rx_ptr[nLen-2]<<8) + this->rx_ptr[nLen-1];
                CrcCacl = this->crc_calculate(&this->rx_ptr[1], nLen-CRC_SIZE-1);
                if(CrcRecv == CrcCacl){
					this->packet_id = LENGTH_CONVERT(frame_ptr->packet_id);
                    return RT_OK;
                }
                else{
					this->rx_size = 0;
                    USR_DEBUG("CRC Check ERROR!. rx_data:%d, r:%d, c:%d\n", this->rx_data_size, CrcRecv, CrcCacl);
                    return RT_FAIL;
                }
            }  
       }           
    }
    return RT_EMPTY;
}

/**
 * 执行具体的指令, 并提交数据到上位机
 * 
 * @param fd 执行的设备ID号
 *  
 * @return 执行执行的结果
 */
int protocol_info::execute_command(int fd)
{
	uint8_t cmd;
	uint16_t reg_index, size;
	uint8_t *cache_ptr;
    app_reg  *app_reg_ptr;

	cmd = this->rx_data_ptr[0];
	reg_index = this->rx_data_ptr[1]<<8 | this->rx_data_ptr[2];
	size = this->rx_data_ptr[3]<<8 | this->rx_data_ptr[4];
	cache_ptr = (uint8_t *)malloc(this->max_buf_size);
	this->tx_size = 0;
	app_reg_ptr = get_app_reg();
    
	switch (cmd)
	{
		case CMD_REG_READ:
			app_reg_ptr->get_multiple_val(reg_index, size, cache_ptr);
			this->tx_size = this->create_send_buf(ACK_OK, size, cache_ptr);
			break;
		case CMD_REG_WRITE:	
			memcpy(cache_ptr, &this->rx_data_ptr[5], size);
			app_reg_ptr->set_multiple_val(reg_index, size, cache_ptr);	
			this->tx_size = this->create_send_buf(ACK_OK, 0, NULL);
			break;
		case CMD_UPLOAD_CMD:		
			break;
		case CMD_UPLOAD_DATA:
			break;
		default:
			break;
	}
	free(cache_ptr);

    this->device_write(fd, this->tx_ptr, this->tx_size);
	return RT_OK;
}

/**
 * 生成发送的数据包格式
 * 
 * @param ack 应答数据的状态
 * @param size 应答有效数据的长度
 * @param pdata 应答有效数据的首指针
 *  
 * @return 执行执行的结果
 */
int protocol_info::create_send_buf(uint8_t ack, uint16_t size, uint8_t *pdata)
{
    uint8_t out_size, index;
    uint16_t crc_calc;

    out_size = 0;
    this->tx_ptr[out_size++] = PROTOCOL_ACK_HEAD;
    this->tx_ptr[out_size++] = PROTOCOL_DEVICE_ID;
    this->tx_ptr[out_size++] = (uint8_t)(this->packet_id>>8);
    this->tx_ptr[out_size++] = (uint8_t)(this->packet_id&0xff);
    this->tx_ptr[out_size++] = ack;
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

/**
 * CRC16计算实现
 * 
 * @param ptr 计算CRC数据的首地址
 * @param len   计算CRC数据的长度
 *  
 * @return NULL
 */
uint16_t protocol_info::crc_calculate(uint8_t *ptr, int len)
{
    return 0xFFFF;
}
