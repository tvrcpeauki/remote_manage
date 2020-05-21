#ifndef CUartThread_H_H
#define CUartThread_H_H

#include <QThread>
#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "protocol.h"
#include "queue.h"

class CUartProtocolInfo:public CProtocolInfo
{
public:
    CUartProtocolInfo(uint8_t *pRxBuffer, uint8_t *pTxBuffer):
        CProtocolInfo(pRxBuffer, pTxBuffer){

    }
    ~CUartProtocolInfo(){}

    int DeviceRead(uint8_t *pStart, uint16_t nMaxSize);
    int DeviceWrite(uint8_t *pStart, uint16_t nSize);
    uint16_t GetId(void){
        return m_nId;
    }
    void SetId(uint16_t nCurId){
        m_nId = nCurId;
    }

private:
    uint16_t m_nId;
};

class CUartThread:public QThread
{
    Q_OBJECT

public:
    explicit CUartThread(QObject *parent = 0);
    void CloseThread();

protected:
    virtual void run();

signals:
    void send_edit_recv(QString);
    void send_edit_test(QString);

private:
    volatile bool m_nIsStop;
};

void UartThreadInit(void);
CUserQueue *GetUartQueue(void);
CUartProtocolInfo *GetUartProtocolInfo(void);
#endif // CUartThread_H_H
