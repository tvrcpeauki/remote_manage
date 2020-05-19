/*
 * File      : protocol.h
 * protocol layer interface
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
#ifndef _INCLUDE_PROTOCOL_H
#define _INCLUDE_PROTOCOL_H

/***************************************************************************
* Include Header Files
***************************************************************************/
#include "typedef.h"

/**************************************************************************
* Global Macro Definition
***************************************************************************/
/*协议数据长度*/
#define FRAME_HEAD_SIZE			6   //协议头数据的宽度
#define CRC_SIZE				2   //CRC数据的长度 

/*协议数据格式*/
#define PROTOCOL_REQ_HEAD  		0x5A	/*协议数据头*/
#define PROTOCOL_DEVICE_ID      0x01	/*设备ID*/
#define PROTOCOL_ACK_HEAD		0x5B	/*应答数据头*/

/*设备操作指令*/
#define CMD_REG_READ 			0x01    /*读寄存器*/
#define CMD_REG_WRITE			0x02	/*写寄存器*/
#define CMD_UPLOAD_CMD			0x03	/*上传指令*/
#define CMD_UPLOAD_DATA			0x04	/*上传数据*/

/*设备应答指令*/
#define ACK_OK					0x00
#define ACK_INVALID_CMD			0x01
#define ACK_OTHER_ERR			0xff

#define BIG_ENDING         		0
#if BIG_ENDING	
#define LENGTH_CONVERT(val)	(val)
#else
#define LENGTH_CONVERT(val) (((val)<<8) |((val)>>8))
#endif

/**************************************************************************
* Global Type Definition
***************************************************************************/
/*协议文件头格式*/
#pragma pack(push, 1)
struct req_frame
{
	uint8_t head;
	uint8_t id;
	uint16_t packet_id;
	uint16_t length;
};
#pragma pack(pop)

class protocol_info
{
public:  
    protocol_info(uint8_t *p_rx, uint8_t *p_tx, uint8_t *p_rxd, uint16_t max_bs);
        ~protocol_info(void){};

    int execute_command(int fd);                                  //数据处理和执行
    int check_receive_data(int fd);                             //接收数据分析
    int create_send_buf(uint8_t ack, uint16_t size, uint8_t *pdata);

	/*设备读写函数，因为不同设备的实现可能不同，用纯虚函数*/
	virtual int device_read(int fd, uint8_t *ptr, uint16_t size) = 0;   
	virtual int device_write(int fd, uint8_t *ptr, uint16_t size) = 0;
private:
    uint8_t *rx_ptr;       //接收数据首指针
	uint8_t *tx_ptr;	   //发送数据首指针
	uint8_t *rx_data_ptr;  //接收数据数据段首指针
	uint16_t packet_id;	   //数据包的编号,用于数据校验同步
	uint16_t rx_size;	   //接收数据长度
	uint16_t tx_size;      //发送数据长度
	uint16_t rx_data_size; //接收数据数据段长度
    uint16_t max_buf_size;  //最大的数据长度
	uint32_t timeout; //超时时间
    uint16_t crc_calculate(uint8_t *ptr, int len);
};
/**************************************************************************
* Global Variable Declaration
***************************************************************************/

/**************************************************************************
* Global Functon Declaration
***************************************************************************/
#endif
