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
};

class uart_thread:public QThread
{
public:
    uart_thread(Ui::MainWindow *);
    void closeThread();
protected:
    virtual void run();

private:
    volatile bool isStop;
    Ui::MainWindow *ui;
};


void uart_thread_init(Ui::MainWindow *ui);

#endif // UART_THREAD_H_H
