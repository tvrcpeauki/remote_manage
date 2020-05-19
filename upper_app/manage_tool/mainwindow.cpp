#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "protocol.h"
#include "uart_thread.h"
#include "queue.h"

extern MyQueue *uart_queue;
ComInfo *com_info;

uint8_t led_on_cmd[] = {
    0x02, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x01
};
uint8_t led_off_cmd[] = {
    0x02, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00
};
uint8_t beep_on_cmd[] = {
    0x02, 0x00, 0x00, 0x00, 0x03, 0x05, 0x00, 0x02
};
uint8_t beep_off_cmd[] = {
    0x02, 0x00, 0x00, 0x00, 0x03, 0x05, 0x00, 0x00
};

//函数声明
void init_btn_disable(Ui::MainWindow *ui);
void init_btn_enable(Ui::MainWindow *ui);

//类的实现
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    //添加COM口
    QStringList comList;
    for (int i = 1; i <= 20; i++) {
        comList << QString("COM%1").arg(i);
    }
    ui->combo_box_com->addItems(comList);

    //波特率选项
    QStringList BaudList;
    BaudList <<"9600"<<"38400"<<"76800"<<"115200"<<"230400";
    ui->combo_box_baud->addItems(BaudList);
    ui->combo_box_baud->setCurrentIndex(3);

    //数据位选项
    QStringList dataBitsList;
    dataBitsList <<"6" << "7" << "8"<<"9";
    ui->combo_box_data->addItems(dataBitsList);
    ui->combo_box_data->setCurrentIndex(2);

    //停止位选项
    QStringList StopBitsList;
    StopBitsList<<"1"<<"2";
    ui->combo_box_stop->addItems(StopBitsList);
    ui->combo_box_stop->setCurrentIndex(0);

    //校验位
    QStringList ParityList;
    ParityList<<"N"<<"Odd"<<"Even";
    ui->combo_box_parity->addItems(ParityList);
    ui->combo_box_parity->setCurrentIndex(0);

    //正则限制部分输入需要为数据
    QRegExp regx("[0-9]+$");
    QValidator *validator_time = new QRegExpValidator(regx,  ui->line_edit_time);
    ui->line_edit_time->setValidator( validator_time );
    QValidator *validator_id = new QRegExpValidator(regx,  ui->line_edit_dev_id);
    ui->line_edit_dev_id->setValidator( validator_id );

    //启动应用相关的处理
    com_info = new ComInfo();
    uart_thread_init();

    //默认按键配置不可操作
    init_btn_disable(ui);
    ui->btn_uart_close->setDisabled(true);

    uart_thread *mythread = new uart_thread();

    //信号槽通讯连接
    connect(mythread, SIGNAL(send_edit_recv(QString)), this, SLOT(append_text_edit_recv(QString)));
    connect(mythread, SIGNAL(send_edit_test(QString)), this, SLOT(append_text_edit_test(QString)));
    mythread->start();
}

void MainWindow::append_text_edit_recv(QString s)
{
    ui->text_edit_recv->append(s);
}

void MainWindow::append_text_edit_test(QString s)
{
    ui->text_edit_test->append(s);
}

//功能函数
void init_btn_disable(Ui::MainWindow *ui)
{
    ui->btn_led_on->setDisabled(true);
    ui->btn_led_off->setDisabled(true);
    ui->btn_reboot->setDisabled(true);
    ui->btn_beep_on->setDisabled(true);
    ui->btn_beep_off->setDisabled(true);
    ui->btn_refresh->setDisabled(true);
    ui->btn_send_cmd->setDisabled(true);
}

void init_btn_enable(Ui::MainWindow *ui)
{
    ui->btn_led_on->setEnabled(true);
    ui->btn_led_off->setEnabled(true);
    ui->btn_reboot->setEnabled(true);
    ui->btn_beep_on->setEnabled(true);
    ui->btn_beep_off->setEnabled(true);
    ui->btn_refresh->setEnabled(true);
    ui->btn_send_cmd->setEnabled(true);
}

//打开LED
void MainWindow::on_btn_led_on_clicked()
{
    QString Strbuf;
    MyQInfo *info = new MyQInfo(sizeof(led_on_cmd), led_on_cmd);

    uart_queue->QueuePost(info);
}

//关闭LED
void MainWindow::on_btn_led_off_clicked()
{
    QString Strbuf;
    MyQInfo *info = new MyQInfo(sizeof(led_off_cmd), led_off_cmd);

    uart_queue->QueuePost(info);
}

//打开蜂鸣器
void MainWindow::on_btn_beep_on_clicked()
{
    QString Strbuf;
    MyQInfo *info = new MyQInfo(sizeof(beep_on_cmd), beep_on_cmd);

    uart_queue->QueuePost(info);
}

//关闭蜂鸣器
void MainWindow::on_btn_beep_off_clicked()
{
    QString Strbuf;
    MyQInfo *info = new MyQInfo(sizeof(beep_off_cmd), beep_off_cmd);

    uart_queue->QueuePost(info);
}

//关闭串口
void MainWindow::on_btn_uart_close_clicked()
{
    init_btn_disable(ui);
    com_info->com->close();
    com_info->com->deleteLater();
    ui->btn_uart_close->setDisabled(true);
    ui->btn_uart_open->setEnabled(true);
    ui->text_edit_test->append("串口关闭");
}

//开启串口
void MainWindow::on_btn_uart_open_clicked()
{
    com_info->com = new QextSerialPort(ui->combo_box_com->currentText(), QextSerialPort::Polling);
    com_info->com_status = com_info->com->open(QIODevice::ReadWrite);

    if(com_info->com_status)
    {
        //清除缓存区
        com_info->com->flush();
        //设置波特率
        com_info->com->setBaudRate((BaudRateType)ui->combo_box_baud->currentText().toInt());
        //设置数据位
        com_info->com->setDataBits((DataBitsType)ui->combo_box_data->currentText().toInt());
        //设置校验位
        com_info->com->setParity((ParityType)ui->combo_box_parity->currentText().toInt());
        //设置停止位
        com_info->com->setStopBits((StopBitsType)ui->combo_box_stop->currentText().toInt());
        com_info->com->setFlowControl(FLOW_OFF);
        com_info->com->setTimeout(10);
        init_btn_enable(ui);
        ui->btn_uart_close->setEnabled(true);
        ui->btn_uart_open->setDisabled(true);
        ui->text_edit_test->append(QString("串口打开成功"));
    }
    else
    {
        com_info->com->deleteLater();
        ui->text_edit_test->append("串口打开失败");
        com_info->com_status = false;
    }
}

//清理接收数据框
void MainWindow::on_btn_clear_clicked()
{
    ui->text_edit_test->clear();
    ui->text_edit_recv->clear();
}

//数组转换成指针发送
QString byteArrayToHexString(QString head, uint8_t* str, uint16_t size, QString tail)
{
    QString result = head;
    QString s;

    for(int i = 0; i < size; ++i)
    {
        s = QString("%1").arg(str[i], 0, 16);
        if(s.length() == 1)
            result.append("0x");
        result.append(s.toUpper());
        result.append(' ');
    }
    result += tail;
    result.chop(1);
    return result;
}
