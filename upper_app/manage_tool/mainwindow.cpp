#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "protocol.h"

protocol_info *sys_protocol_ptr;
uint8_t rx_buffer[BUFF_CACHE_SIZE];
uint8_t tx_buffer[BUFF_CACHE_SIZE];

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

    sys_protocol_ptr = new protocol_info(rx_buffer, tx_buffer);
}

QString byteArrayToHexString(uint8_t* str, uint16_t size)
{
    QString result = "";
    QString s;

    for(int i = 0; i < size; ++i)
    {
        s = QString("%1").arg(str[i], 0, 16);
        if(s.length() == 1)
            result.append("0x");
        result.append(s.toUpper());
        result.append(' ');
    }
    result.chop(1);
    return result;
}

QString do_cmd_send_info(uint8_t *cmd, uint8_t size)
{
    int len;
    QString Sendbuf = "";
    len = sys_protocol_ptr->create_send_buf(0x0001, size, cmd);

    Sendbuf += "Sendbuf: ";
    Sendbuf += byteArrayToHexString(tx_buffer, len);
    return Sendbuf;
}

//清理接收数据框
void MainWindow::on_btn_clear_clicked()
{
    ui->text_edit_test->clear();
    ui->text_edit_recv->clear();
}

//打开LED
void MainWindow::on_btn_led_on_clicked()
{
    QString Strbuf;
    uint8_t led_open_cmd[] = {
        0x02, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x01
    };

    Strbuf = do_cmd_send_info(led_open_cmd, sizeof(led_open_cmd));
    ui->text_edit_test->append(Strbuf);
}

//关闭LED
void MainWindow::on_btn_led_off_clicked()
{
    QString Strbuf;
    uint8_t led_close_cmd[] = {
        0x02, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00
    };

    Strbuf = do_cmd_send_info(led_close_cmd, sizeof(led_close_cmd));
    ui->text_edit_test->append(Strbuf);
}

//打开蜂鸣器
void MainWindow::on_btn_beep_on_clicked()
{
    QString Strbuf;
    uint8_t beep_open_cmd[] = {
        0x02, 0x00, 0x00, 0x00, 0x03, 0x05, 0x00, 0x02
    };

    Strbuf = do_cmd_send_info(beep_open_cmd, sizeof(beep_open_cmd));
    ui->text_edit_test->append(Strbuf);
}

//关闭蜂鸣器
void MainWindow::on_btn_beep_off_clicked()
{
    QString Strbuf;
    uint8_t beep_close_cmd[] = {
        0x02, 0x00, 0x00, 0x00, 0x03, 0x05, 0x00, 0x00
    };

    Strbuf = do_cmd_send_info(beep_close_cmd, sizeof(beep_close_cmd));
    ui->text_edit_test->append(Strbuf);
}
