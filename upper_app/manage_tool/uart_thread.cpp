//uart任务处理
#include "uart_thread.h"
#include "queue.h"
#include "mainwindow.h"

MyQueue *uart_queue;
CUartProtocolInfo *uart_protocol_ptr;
ComInfo *com_info;
uint8_t rx_buffer[BUFF_CACHE_SIZE];
uint8_t tx_buffer[BUFF_CACHE_SIZE];

uart_thread::uart_thread(QObject *parent):QThread(parent)
{
    this->isStop = 0;
}

//关闭任务
void uart_thread::closeThread()
{
    this->isStop = 1;
}

//任务执行函数
void uart_thread::run()
{
    CQueueInfo *info;
    int len;
    QString Sendbuf = "";

    forever
    {
        if(isStop)
            return;

        info  = uart_queue->QueuePend();
        if(info != nullptr)
        {
            if(com_info->com_status)
            {
                len = uart_protocol_ptr->CreateSendBuffer(uart_protocol_ptr->GetId(), info->m_nSize, info->m_pBuffer);
                Sendbuf += byteArrayToHexString("Sendbuf:", tx_buffer, len, "\n");
                uart_protocol_ptr->DeviceWrite(tx_buffer, len);

                //通知主线程更新窗口
                emit send_edit_test(Sendbuf);
                Sendbuf.clear();
                while(1)
                {
                    len = uart_protocol_ptr->DeviceRead(rx_buffer, BUFF_CACHE_SIZE);
                    if(len != 0)
                        break;
                }

                Sendbuf += byteArrayToHexString("Recvbuf:", rx_buffer, len, "\n");
                //通知主线程更新窗口
                emit send_edit_test(Sendbuf);
                //qDebug()<<Sendbuf;
                Sendbuf.clear();
            }

            qDebug()<<"thread queue test OK\n";
            delete info;
        }
    }
}

//设备写数据
int CUartProtocolInfo::DeviceWrite(uint8_t *pStart, uint16_t nSize)
{
    com_info->com->write((char *)pStart, nSize);
    return nSize;
}

//设备读数据
int CUartProtocolInfo::DeviceRead(uint8_t *pStart, uint16_t nMaxSize)
{
    return com_info->com->read((char *)pStart, nMaxSize);
}

//任务初始化
void uart_thread_init(void)
{
    uart_protocol_ptr = new CUartProtocolInfo(rx_buffer, tx_buffer);
    uart_queue = new MyQueue();
}

