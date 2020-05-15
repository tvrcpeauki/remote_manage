/*
 * File      : uart_task.cpp
 * This file is uart protoco task
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
struct PROTOCOL_INFO
{
	uint8_t *rx_ptr;       //接收数据首指针
	uint8_t *tx_ptr;	   //发送数据首指针
	uint8_t *rx_data_ptr;  //接收数据数据段首指针
	uint16_t packet_id;	   //数据包的编号,用于数据校验同步
	uint16_t rx_size;	   //接收数据长度
	uint16_t tx_size;      //发送数据长度
	uint16_t rx_data_size; //接收数据数据段长度
};

/**************************************************************************
* Local static Variable Declaration
***************************************************************************/
static uint8_t 	rx_buffer[BUFFER_SIZE];
static uint8_t  tx_buffer[BUFFER_SIZE];
static app_reg  *app_reg_ptr;
static uint8_t com_fd;

static const char DeviceList[][20] = {
	TTY_DEVICE,
};

struct PROTOCOL_INFO proto_info = {
	rx_buffer,
	tx_buffer,
	&rx_buffer[FRAME_HEAD_SIZE],
	0,
    0,
	0,
	0,
};

/**************************************************************************
* Global Variable Declaration
***************************************************************************/

/**************************************************************************
* Function
***************************************************************************/
int ReceiveCheckData(int);
static int set_opt(int, int, int, char, int);
static uint16_t  CrcCalculate(uint8_t *, int);
int protocol_do_cmd(void);
static int create_output_buf(uint8_t ack, uint16_t size, uint8_t *pdata);

/**
 * uart模块初始化
 * 
 * @param argc
 * @param argv
 *  
 * @return the error code, 0 on initialization successfully.
 */
void uart_init(void)
{
	const char *pDevice;

	pDevice =  DeviceList[0];
	if((com_fd = open(pDevice, O_RDWR|O_NOCTTY|O_NDELAY))<0){	
		USR_DEBUG("open %s is failed\n", pDevice);
	}
	else{
		set_opt(com_fd, 115200, 8, 'N', 1);
		USR_DEBUG("open %s success!\t\n", pDevice);
	}
}

/**
 * uart主循环流程
 * 
 * @param arg
 *  
 * @return the error code, 0 on initialization successfully.
 */
void *uart_loop_task(void *arg)
{
	int flag;
	app_reg_ptr = get_app_reg();

	USR_DEBUG("Uart Main Task Start\n");
	write(com_fd, "Uart Start OK!\n", strlen("Uart Start OK!\n"));

	for(;;){	   
		flag = ReceiveCheckData(com_fd);     
        if(flag == RT_OK){
			if(protocol_do_cmd() == RT_OK)
			{
				/*将数据提交上位机*/
				write(com_fd, proto_info.tx_ptr, proto_info.tx_size);
			}
            proto_info.rx_size = 0;
		}
	}
}

/**
 * 协议具体指令执行
 * 
 * @param fd
 *  
 * @return NULL
 */
int protocol_do_cmd(void)
{
	uint8_t cmd;
	uint16_t reg_index, size;
	uint8_t *cache_ptr;

	cmd = proto_info.rx_data_ptr[0];
	reg_index = proto_info.rx_data_ptr[1]<<8 | proto_info.rx_data_ptr[2];
	size = proto_info.rx_data_ptr[3]<<8 | proto_info.rx_data_ptr[4];
	cache_ptr = (uint8_t *)malloc(BUFFER_SIZE);
	proto_info.tx_size = 0;
	
	switch (cmd)
	{
		case CMD_REG_READ:
			app_reg_ptr->get_multiple_val(reg_index, size, cache_ptr);
			proto_info.tx_size = create_output_buf(ACK_OK, size, cache_ptr);
			break;
		case CMD_REG_WRITE:	
			memcpy(cache_ptr, &proto_info.rx_data_ptr[5], size);
			app_reg_ptr->set_multiple_val(reg_index, size, cache_ptr);	
			proto_info.tx_size = create_output_buf(ACK_OK, 0, NULL);
			break;
		case CMD_UPLOAD_CMD:		
			break;
		case CMD_UPLOAD_DATA:
			break;
		default:
			break;
	}

	free(cache_ptr);
	//log_array(proto_info.rx_data_ptr, proto_info.rx_data_size);
	return RT_OK;
}

/**
 * 生成发生的数据包
 * 
 * @param ack
 * @param size
 * @param pdata 
 *  
 * @return the error code, 0 on initialization successfully.
 */
static int create_output_buf(uint8_t ack, uint16_t size, uint8_t *pdata)
{
	uint8_t out_size, index;
	uint16_t crc_calc;

	out_size = 0;
	proto_info.tx_ptr[out_size++] = PROTO_ACK_HEAD;
	proto_info.tx_ptr[out_size++] = PROTO_ID;
	proto_info.tx_ptr[out_size++] = (uint8_t)(proto_info.packet_id>>8);
	proto_info.tx_ptr[out_size++] = (uint8_t)(proto_info.packet_id&0xff);
	proto_info.tx_ptr[out_size++] = ack;
	proto_info.tx_ptr[out_size++] = (uint8_t)(size>>8);
	proto_info.tx_ptr[out_size++] = (uint8_t)(size&0xff);	
	
	if(size != 0 && pdata != NULL)
	{
		for(index=0; index<size; index++)
		{
			proto_info.tx_ptr[out_size++] = *(pdata+index);
		}
	}

	crc_calc = CrcCalculate(&proto_info.tx_ptr[1], out_size-1);
	proto_info.tx_ptr[out_size++] = (uint8_t)(crc_calc>>8);
	proto_info.tx_ptr[out_size++] = (uint8_t)(crc_calc&0xff);	
	
	return out_size;
}

/**
 * 数据读取和解析
 * 
 * @param fd
 *  
 * @return NULL
 */
int ReceiveCheckData(int fd)
{
    int nread;
    int CrcRecv, CrcCacl;
	struct req_frame *frame_ptr; 

	/*从串口中读取数据*/
	frame_ptr = (struct req_frame *)rx_buffer;
    nread = read(fd, &rx_buffer[proto_info.rx_size], (BUFFER_SIZE-proto_info.rx_size));
    if(nread > 0)
    {        
       proto_info.rx_size += nread;

	   /*接收到头不符合预期*/
       if(frame_ptr->head != PROTO_REQ_HEAD) {
            USR_DEBUG("No Valid Head\n");
	    	proto_info.rx_size = 0;
            return RT_FAIL;
       }

	   /*已经接收到长度数据*/
       else if(proto_info.rx_size > 5){
		    int nLen;

		    /*设备ID检测*/
            if(frame_ptr->id != PROTO_ID)
            {
                proto_info.rx_size = 0;
				USR_DEBUG("Valid ID\n");
                return RT_FAIL;
            }

			/*获取接收数据的总长度*/
			proto_info.rx_data_size = LENGTH_CONVERT(frame_ptr->length);

			/*crc冗余校验*/
            nLen = proto_info.rx_data_size+FRAME_HEAD_SIZE+CRC_SIZE;
            if(proto_info.rx_size >= nLen)
            {
				/*计算head后到CRC尾之前的所有数据的CRC值*/
                CrcRecv = (rx_buffer[nLen-2]<<8) + rx_buffer[nLen-1];
                CrcCacl = CrcCalculate(&rx_buffer[1], nLen-CRC_SIZE-1);
                if(CrcRecv == CrcCacl){
					proto_info.packet_id = LENGTH_CONVERT(frame_ptr->packet_id);
                    return RT_OK;
                }
                else{
					proto_info.rx_size = 0;
                    USR_DEBUG("CRC Check ERROR!. rx_data:%d, r:%d, c:%d\n", proto_info.rx_data_size, CrcRecv, CrcCacl);
                    return RT_FAIL;
                }
            }  
       }           
    }
    return RT_EMPTY;
}

/**
 * CRC16计算实现
 * 
 * @param ptr
 * @param len
 *  
 * @return NULL
 */
static uint16_t CrcCalculate(uint8_t *ptr, int len)
{
    return 0xffff;    
}

/**
 * 设置uart的信息
 * 
 * @param ptr
 * @param len
 *  
 * @return NULL
 */
static int set_opt(int fd, int nSpeed, int nBits, char nEvent, int nStop)
{
	struct termios newtio;
	struct termios oldtio;

	if  ( tcgetattr( fd,&oldtio)  !=  0) { 
		perror("SetupSerial 1");
		return -1;
	}
	bzero( &newtio, sizeof( newtio ) );
	newtio.c_cflag  |=  CLOCAL | CREAD;
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

	switch( nEvent )
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
	tcflush(fd,TCIFLUSH);
	if((tcsetattr(fd,TCSANOW,&newtio))!=0)
	{
		perror("com set error");
		return -1;
	}
//	printf("set done!\n\r");
	return 0;
}

void uart_module_test(void)
{
	app_reg_ptr = get_app_reg();
	proto_info.rx_data_ptr[0] = 0x02; //指令
	proto_info.rx_data_ptr[1] = 0x00;
	proto_info.rx_data_ptr[2] = 0x00; //寄存器
	proto_info.rx_data_ptr[3] = 0x00;
	proto_info.rx_data_ptr[4] = 0x03; //长度
	proto_info.rx_data_ptr[5] = 0x03; 
	proto_info.rx_data_ptr[6] = 0x00; //设置状态字段
	proto_info.rx_data_ptr[7] = 0x01; //配置
	protocol_do_cmd();
}

