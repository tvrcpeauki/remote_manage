//uart任务处理
#include "uart_thread.h"
#include "queue.h"
#include "mainwindow.h"

MyQueue *uart_queue;
uart_protocol_info *uart_protocol_ptr;
extern ComInfo *com_info;
uint8_t rx_buffer[BUFF_CACHE_SIZE];
uint8_t tx_buffer[BUFF_CACHE_SIZE];

uart_thread::uart_thread(Ui::MainWindow *ui)
{
    this->isStop = 0;
    this->ui = ui;
}

void uart_thread::closeThread()
{
    this->isStop = 1;
}

//清理接收数据框
void MainWindow::on_btn_clear_clicked()
{
    ui->text_edit_test->clear();
    ui->text_edit_recv->clear();
}

//任务执行函数
void uart_thread::run()
{
    MyQInfo *info;
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
                len = uart_protocol_ptr->create_send_buf(0x0001, info->size, info->buf);
                Sendbuf += byteArrayToHexString("Sendbuf:", tx_buffer, len, "\n");
                uart_protocol_ptr->device_write(tx_buffer, len);
                //ui->text_edit_test->setText(Sendbuf);
               //qDebug()<<Sendbuf;
                Sendbuf.clear();
                while(1)
                {
                    len = uart_protocol_ptr->device_read(rx_buffer, BUFF_CACHE_SIZE);
                    if(len != 0)
                        break;
                }

                Sendbuf += byteArrayToHexString("Recvbuf:", rx_buffer, len, "\n");
                //qDebug()<<Sendbuf;
                //ui->text_edit_test->append(Sendbuf);
                Sendbuf.clear();
            }

            qDebug()<<"thread queue test OK\n";
            delete info;
        }
    }
}


int uart_protocol_info::device_write(uint8_t *ptr, uint16_t size)
{
    com_info->com->write((char *)ptr, size);
    return size;
}

int uart_protocol_info::device_read(uint8_t *ptr, uint16_t max_size)
{
    return com_info->com->read((char *)ptr, max_size);
}

int device_write(uint8_t *ptr, uint16_t size);

//任务初始化
void uart_thread_init(Ui::MainWindow *ui)
{
    uart_protocol_ptr = new uart_protocol_info(rx_buffer, tx_buffer);
    uart_queue = new MyQueue();
    uart_thread *mythread = new uart_thread(ui);
    mythread->start();
}
