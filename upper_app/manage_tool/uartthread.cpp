//uart任务处理
#include "uartthread.h"
#include "mainwindow.h"

static CUserQueue *pUartQueue;
static CUartProtocolInfo *pUartProtocolInfo;
static uint8_t rx_buffer[BUFF_CACHE_SIZE];
static uint8_t tx_buffer[BUFF_CACHE_SIZE];


CUartThread::CUartThread(QObject *parent):QThread(parent)
{
   m_nIsStop = 0;
}

//关闭任务
void CUartThread::CloseThread()
{
    m_nIsStop = 1;
}

//任务执行函数
void CUartThread::run()
{
    CQueueInfo *pQueueInfo;
    int nLen;
    QString Sendbuf = "";
    CComInfo *pComInfo;

    forever{
        if(m_nIsStop)
            return;

        pQueueInfo  = pUartQueue->QueuePend();
        if(pQueueInfo != nullptr)
        {
            pComInfo = GetComInfo();
            if(pComInfo->com_status)
            {
                nLen = pUartProtocolInfo->CreateSendBuffer(pUartProtocolInfo->GetId(), pQueueInfo->m_nSize, pQueueInfo->m_pBuffer);
                Sendbuf += byteArrayToHexString("Sendbuf:", tx_buffer, nLen, "\n");
                pUartProtocolInfo->DeviceWrite(tx_buffer, nLen);

                //通知主线程更新窗口
                emit send_edit_test(Sendbuf);
                Sendbuf.clear();
                while(1)
                {
                    nLen = pUartProtocolInfo->DeviceRead(rx_buffer, BUFF_CACHE_SIZE);
                    if(nLen != 0)
                        break;
                }

                Sendbuf += byteArrayToHexString("Recvbuf:", rx_buffer, nLen, "\n");
                //通知主线程更新窗口
                emit send_edit_test(Sendbuf);
                //qDebug()<<Sendbuf;
                Sendbuf.clear();
            }

            qDebug()<<"thread queue test OK\n";
            delete pQueueInfo;
        }
    }
}

//设备写数据
int CUartProtocolInfo::DeviceWrite(uint8_t *pStart, uint16_t nSize)
{
    CComInfo *pComInfo;
    pComInfo = GetComInfo();
    pComInfo->com->write((char *)pStart, nSize);
    return nSize;
}

//设备读数据
int CUartProtocolInfo::DeviceRead(uint8_t *pStart, uint16_t nMaxSize)
{
    CComInfo *pComInfo;
    pComInfo = GetComInfo();
    return pComInfo->com->read((char *)pStart, nMaxSize);
}

//任务初始化
void UartThreadInit(void)
{
    pUartProtocolInfo = new CUartProtocolInfo(rx_buffer, tx_buffer);
    pUartQueue = new CUserQueue();
}

CUserQueue *GetUartQueue(void)
{
    return pUartQueue;
}

CUartProtocolInfo *GetUartProtocolInfo(void)
{
    return pUartProtocolInfo;
}
