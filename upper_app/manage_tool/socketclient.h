#ifndef SOCKETCLIENT_H
#define SOCKETCLIENT_H

#include <QDebug>
#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "protocol.h"

class CTcpClientSocket:public QObject, public CProtocolInfo
{
    Q_OBJECT

public:
    CTcpClientSocket(QObject *parent = 0, uint8_t *pRxBuffer = nullptr, uint8_t *pTxBuffer = nullptr);
    ~CTcpClientSocket();
    void SocketProcess(SSendBuffer *buf);
    int DeviceRead(uint8_t *pStart, uint16_t nMaxSize){
        return tcpSocket->read((char *)pStart, nMaxSize);
    };
    int DeviceWrite(uint8_t *pStart, uint16_t nSize){
        return tcpSocket->write((char *)pStart, nSize);
    };
    int CheckReceiveData(void);

private:
    bool status;
    int port;
    QHostAddress *serverIP;
    QTcpSocket *tcpSocket;
    QString ipAddr;

public slots:
    void slotConnected();
    void slotDisconnected();
    void dataReceived();
};


void CTcpClientSocketInit(void);
CTcpClientSocket *GetTcpClientSocket();

#endif // SOCKETCLIENT_H
