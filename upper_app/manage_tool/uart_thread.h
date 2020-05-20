#ifndef UART_THREAD_H_H
#define UART_THREAD_H_H

#include <QThread>
#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "protocol.h"

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
        return id;
    }
    void SetId(uint16_t cur_id){
        id = cur_id;
    }

private:
    uint16_t id;
};

class uart_thread:public QThread
{
    Q_OBJECT

public:
    explicit uart_thread(QObject *parent = 0);
    void closeThread();

protected:
    virtual void run();

signals:
    void send_edit_recv(QString);
    void send_edit_test(QString);

private:
    volatile bool isStop;
};


void uart_thread_init(void);

#endif // UART_THREAD_H_H
