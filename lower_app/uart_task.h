/*
 * File      : uart_task.h
 * This file is uart task interface
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
#ifndef _INCLUDE_UART_TASK_H
#define _INCLUDE_UART_TASK_H

/***************************************************************************
* Include Header Files
***************************************************************************/
#include "typedef.h"

/**************************************************************************
* Global Macro Definition
***************************************************************************/
/*协议数据格式*/
#define FRAME_HEAD_SIZE			6
#define CRC_SIZE				2

#define PROTO_REQ_HEAD  		0x5A	/*协议数据头*/
#define PROTO_ID      			0x01	/*设备ID*/
#define PROTO_ACK_HEAD			0x5B	/*应答数据头*/

/*返回状态*/
#define RT_OK               	0x00
#define RT_FAIL             	0x01
#define RT_EMPTY            	0x02

/*设备操作指令*/
#define CMD_REG_READ 			0x01    /*读寄存器*/
#define CMD_REG_WRITE			0x02	/*写寄存器*/
#define CMD_UPLOAD_CMD			0x03	/*上传指令*/
#define CMD_UPLOAD_DATA			0x04	/*上传数据*/

/*设备应答指令*/
#define ACK_OK					0x00
#define ACK_INVALID_CMD			0x01
#define ACK_OTHER_ERR			0xff


#define BUFFER_SIZE     		1200
#define BIG_ENDING         		0
#if BIG_ENDING	
#define LENGTH_CONVERT(val)	(val)
#else
#define LENGTH_CONVERT(val) (((val)<<8) |((val)>>8))
#endif

/**************************************************************************
* Global Type Definition
***************************************************************************/


/*协议包格式*/
#pragma pack(push, 1)
struct req_frame
{
	uint8_t head;
	uint8_t id;
	uint16_t packet_id;
	uint16_t length;
};
#pragma pack(pop)


/**************************************************************************
* Global Variable Declaration
***************************************************************************/

/**************************************************************************
* Global Functon Declaration
***************************************************************************/
void uart_init(void);
void *uart_loop_task(void *arg);
void uart_module_test(void);

#endif
