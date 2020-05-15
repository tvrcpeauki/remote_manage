/*
 * File      : uart_task.h
 * uart task interface
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
#include "protocol.h"

/**************************************************************************
* Global Macro Definition
***************************************************************************/

#define BUFFER_SIZE     		1200
/**************************************************************************
* Global Type Definition
***************************************************************************/
class uart_protocol_info:public protocol_info
{
public:
	uart_protocol_info(uint8_t *p_rx, uint8_t *p_tx, uint8_t *p_rxd, uint16_t max_bs):
		protocol_info(p_rx, p_tx, p_rxd, max_bs){

	}
	~uart_protocol_info(){}

	int device_read(int fd, uint8_t *ptr, uint16_t size){
		return read(fd, ptr, size);
	}
	int device_write(int fd, uint8_t *ptr, uint16_t size){
		return write(fd, ptr, size);
	}
};

/**************************************************************************
* Global Variable Declaration
***************************************************************************/

/**************************************************************************
* Global Functon Declaration
***************************************************************************/
void uart_task_init(void);
void uart_module_test(void);

#endif
