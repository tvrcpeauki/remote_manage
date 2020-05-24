
#include "socketclient.h"


static uint8_t rx_buffer[BUFF_CACHE_SIZE];
static uint8_t tx_buffer[BUFF_CACHE_SIZE];
CTcpClientSocket *pCTcpClientSocket;
static uint8_t beep_on_cmd[] = {
    0x02, 0x00, 0x00, 0x00, 0x03, 0x05, 0x00, 0x02
};

CTcpClientSocket::CTcpClientSocket(QObject *parent, uint8_t *pRxBuffer, uint8_t *pTxBuffer):QObject(parent), CProtocolInfo(pRxBuffer, pTxBuffer)
{
    status = false;
    port = 8000;
    ipAddr = QString("192.168.1.251");
    serverIP = new QHostAddress();

    if(!serverIP->setAddress(ipAddr)){
        qDebug()<<"SetAddress error\n";
    }

    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, SIGNAL(connected()), this, SLOT(slotConnected()));
    connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(slotDisconnected()));
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(dataReceived()));
}

CTcpClientSocket::~CTcpClientSocket()
{
    tcpSocket->deleteLater();
    delete  serverIP;
}

void CTcpClientSocket::slotConnected()
{
    int nLen;
    qDebug()<<"socket connect\n";
    SSendBuffer *pSendBuffer = new SSendBuffer(sizeof(beep_on_cmd), beep_on_cmd, false);
    nLen = CreateSendBuffer(pCTcpClientSocket->GetId(), pSendBuffer->m_nSize, pSendBuffer->m_pBuffer, pSendBuffer->m_IsWriteThrough);
    delete pSendBuffer;
    DeviceWrite(tx_buffer, nLen);
}


void CTcpClientSocket::slotDisconnected()
{
    qDebug()<<"退出网络连接\n";
}

int CTcpClientSocket::CheckReceiveData(void)
{
  return 0;
}

//接收数据
void CTcpClientSocket::dataReceived()
{
    while(tcpSocket->bytesAvailable() > 0)
    {
        QByteArray datagram;
        datagram.resize(tcpSocket->bytesAvailable());

        DeviceRead((uint8_t *)datagram.data(), datagram.size());

        QString msg = datagram.data();
        qDebug()<<"socket recv:"<<msg<<"\n";
    }
    tcpSocket->disconnectFromHost();
}

void CTcpClientSocket::SocketProcess(SSendBuffer *pSendBuffer)
{
    if(tcpSocket->isOpen() == false)
    {
         tcpSocket->disconnectFromHost();
    }
    tcpSocket->connectToHost(*serverIP, port);
}

void CTcpClientSocketInit(void)
{
    pCTcpClientSocket = new CTcpClientSocket((QObject *)0, rx_buffer, tx_buffer);
}

CTcpClientSocket *GetTcpClientSocket()
{
    return pCTcpClientSocket;
}
