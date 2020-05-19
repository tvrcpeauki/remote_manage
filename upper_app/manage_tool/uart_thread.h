#ifndef UART_THREAD_H_H
#define UART_THREAD_H_H

#include <QThread>
#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "protocol.h"

class uart_protocol_info:public protocol_info
{
public:
    uart_protocol_info(uint8_t *p_rx, uint8_t *p_tx):
        protocol_info(p_rx, p_tx){

    }
    ~uart_protocol_info(){}

    int device_read(uint8_t *ptr, uint16_t max_size);
    int device_write(uint8_t *ptr, uint16_t size);
    uint16_t get_id(void){
        return id;
    }
    void set_id(uint16_t cur_id){
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
