/*
 * File      : main.cpp
 * This file is uart protocolw work
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

#include "uart_task.h"
#include "app_task.h"

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
 * 代码执行入口函数
 * 
 * @param argc
 * @param argv
 *  
 * @return the error code, 0 on initialization successfully.
 */
int main(int argc, char* argv[])
{
    int result = 0;
	pid_t pid;
	pthread_t tid1, tid2;

    result = daemon(1, 1);
	if(result < 0){
		perror("daemon\n");
		return result;
	}
	
	uart_init();
	app_init();

#if __SYSTEM_DEBUG == 0

	pthread_create(&tid1, NULL, uart_loop_task, NULL);
	pthread_create(&tid1, NULL, app_loop_task, NULL);	
	
	for(;;){
	}
#else
	uart_module_test();
	app_module_test();
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