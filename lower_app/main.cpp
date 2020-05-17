/*
 * File      : main.cpp
 * main frame process
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

#include "include/uart_task.h"
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
static void system_test(void);

/**************************************************************************
* Function
***************************************************************************/
/**
 * 代码执行入口函数
 * 
 * @param argc 输入的字符串长度
 * @param argv 输入的字符串数组
 *  
 * @return the error code, 0 on initialization successfully.
 */
int main(int argc, char* argv[])
{
    int result = 0;

    result = daemon(1, 1);
	if(result < 0){
		perror("daemon\n");
		return result;
	}
	
	/*任务创建*/
#if __SYSTEM_DEBUG == 0
	uart_task_init();
	app_task_init();
	for(;;){
	}
#else
	system_test();
#endif	

	return result;
}

/**
 * 打印调试信息接口
 * 
 * @param ptr 打印数据信息首指针
 * @param size 打印数据长度
 *  
 * @return NULL
 */
void log_array(uint8_t *ptr, uint16_t size)
{
	uint16_t index;
	for(index=0; index<size; index++)
	{
		printf("0x%x ", (int)ptr[index]);
	}
	printf("\n");
}

#if __SYSTEM_DEBUG == 1
static uint8_t 	rx_buffer[BUFFER_SIZE];
static uint8_t  tx_buffer[BUFFER_SIZE];
const uint8_t test_command[] = {
	0x5a, 0x01, 0x32, 0x23, 0x00, 0x08, 0x02, 0x00, 
	0x00, 0x00, 0x03, 0x07, 0x00, 0x01, 0xFF, 0xFF
};
class test_protocol_info:public protocol_info
{
public:
	test_protocol_info(uint8_t *p_rx, uint8_t *p_tx, uint8_t *p_rxd, uint16_t max_bs):
		protocol_info(p_rx, p_tx, p_rxd, max_bs){
	}
	~test_protocol_info(){}

	int device_read(int fd, uint8_t *ptr, uint16_t size){
		memcpy(ptr, test_command, sizeof(test_command));
		return sizeof(test_command);
	}
	int device_write(int fd, uint8_t *ptr, uint16_t size){
		printf("send array:");
		log_array(ptr, size);
		return size;
	}
};

/**
 * 模块的测试代码
 * 
 * @param NULL
 *  
 * @return NULL
 */
static void system_test(void)
{
	int fd = 0;
	app_reg *arp_ptr;
	test_protocol_info *upi_ptr;
	int flag;

	arp_ptr = new app_reg();
	upi_ptr = new test_protocol_info(rx_buffer, tx_buffer, 
								&rx_buffer[FRAME_HEAD_SIZE], BUFFER_SIZE);
	/*更新设备处理指针*/
	set_app_reg(arp_ptr);

	/*执行接收数据的处理指令*/
	flag = upi_ptr->check_receive_data(fd);
	if(flag == RT_OK){
		upi_ptr->execute_command(fd);
		arp_ptr->hardware_refresh();
	}

	delete arp_ptr;
	delete upi_ptr;
	arp_ptr = NULL;	
	upi_ptr = NULL;
}
#endif