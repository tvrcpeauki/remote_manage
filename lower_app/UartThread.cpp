/*
 * File      : uart_task.cpp
 * uart hardware process task
 * COPYRIGHT (C) 2020, zc
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-5-4      zc           the first version
 * 2020-5-20     zc           Code standardization 
 */

/**
 * @addtogroup IMX6ULL
 */
/*@{*/

#include "include/UartThread.h"
#include "include/ApplicationThread.h"

/**************************************************************************
* Local Macro Definition
***************************************************************************/

/**************************************************************************
* Local Type Definition
***************************************************************************/

/**************************************************************************
* Local static Variable Declaration
***************************************************************************/
static CUartProtocolInfo *pUartProtocolInfo; //uart模块管理信息指针

static uint8_t 	nRxCacheBuffer[BUFFER_SIZE];
static uint8_t  nTxCacheBuffer[BUFFER_SIZE];
static uint8_t 	nComFd;

static const char DeviceList[][20] = {
	TTY_DEVICE,
};

/**************************************************************************
* Global Variable Declaration
***************************************************************************/

/**************************************************************************
* Local Function
***************************************************************************/
static void *UartLoopThread(void *arg);
static int set_opt(int, int, int, char, int);

/**************************************************************************
* Function
***************************************************************************/
/**
 * uart模块任务初始化
 * 
 * @param NULL
 *  
 * @return NULL
 */
void UartThreadInit(void)
{
	int nErr;
	pthread_t tid1;
	const char *pDevice;

	pDevice =  DeviceList[0];
	if((nComFd = open(pDevice, O_RDWR|O_NOCTTY|O_NDELAY))<0){	
		USR_DEBUG("open %s is failed\n", pDevice);
		return;
	}
	else{
		set_opt(nComFd, 115200, 8, 'N', 1);
		USR_DEBUG("open %s success!\t\n", pDevice);
	}

	//创建UART协议管理对象
	pUartProtocolInfo = new CUartProtocolInfo(nRxCacheBuffer, nTxCacheBuffer, &nRxCacheBuffer[FRAME_HEAD_SIZE], BUFSIZ);

	nErr = pthread_create(&tid1, NULL, UartLoopThread, NULL);
	if(nErr != 0){
		USR_DEBUG("uart task thread create nErr, %d\n", nErr);
	}
}

/**
 * uart主任务执行流程
 * 
 * @param arg 线程传递的参数
 *  
 * @return NULL
 */
static void *UartLoopThread(void *arg)
{
	int nFlag;

	USR_DEBUG("Uart Main Task Start\n");
	write(nComFd, "Uart Start OK!\n", strlen("Uart Start OK!\n"));

	for(;;){	   
		nFlag = pUartProtocolInfo->CheckRxBuffer(nComFd);
		if(nFlag == RT_OK){
			pUartProtocolInfo->ExecuteCommand(nComFd);
		}
		else{
			usleep(100); //通讯结束让出线程
		}
	}
}

/**
 * 配置Uart硬件的功能
 * 
 * @param fd 	 设置的串口设备ID
 * @param nSpeed 波特率
 * @param nBits  数据位
 * @param nEvent 奇偶校验位
 * @param nStop  停止位
 *  
 * @return NULL
 */
static int set_opt(int nFd, int nSpeed, int nBits, char nEvent, int nStop)
{
	struct termios newtio;
	struct termios oldtio;

	if  (tcgetattr(nFd, &oldtio)  !=  0) { 
		perror("SetupSerial 1");
		return -1;
	}
	bzero( &newtio, sizeof(newtio));
	newtio.c_cflag |=  CLOCAL | CREAD;
	newtio.c_cflag &= ~CSIZE;

	switch( nBits )
	{
		case 7:
			newtio.c_cflag |= CS7;
			break;
		case 8:
			newtio.c_cflag |= CS8;
			break;
		default:
			break;
	}

	switch(nEvent)
	{
	case 'O':
		newtio.c_cflag |= PARENB;
		newtio.c_cflag |= PARODD;
		newtio.c_iflag |= (INPCK | ISTRIP);
		break;
	case 'E': 
		newtio.c_iflag |= (INPCK | ISTRIP);
		newtio.c_cflag |= PARENB;
		newtio.c_cflag &= ~PARODD;
		break;
	case 'N':  
		newtio.c_cflag &= ~PARENB;
		break;
	}

	switch( nSpeed )
	{
	case 2400:
		cfsetispeed(&newtio, B2400);
		cfsetospeed(&newtio, B2400);
		break;
	case 4800:
		cfsetispeed(&newtio, B4800);
		cfsetospeed(&newtio, B4800);
		break;
	case 9600:
		cfsetispeed(&newtio, B9600);
		cfsetospeed(&newtio, B9600);
		break;
	case 115200:
		cfsetispeed(&newtio, B115200);
		cfsetospeed(&newtio, B115200);
		break;
	case 460800:
		cfsetispeed(&newtio, B460800);
		cfsetospeed(&newtio, B460800);
		break;
	case 921600:
		printf("B921600\n");
		cfsetispeed(&newtio, B921600);
        cfsetospeed(&newtio, B921600);
		break;
	default:
		cfsetispeed(&newtio, B9600);
		cfsetospeed(&newtio, B9600);
		break;
	}
	if( nStop == 1 )
		newtio.c_cflag &=  ~CSTOPB;
	else if ( nStop == 2 )
	newtio.c_cflag |=  CSTOPB;
	newtio.c_cc[VTIME]  = 0;
	newtio.c_cc[VMIN] = 0;
	tcflush(nFd, TCIFLUSH);
	if((tcsetattr(nFd, TCSANOW,&newtio))!=0)
	{
		perror("com set error");
		return -1;
	}
//	printf("set done!\n\r");
	return 0;
}

