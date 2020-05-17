#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    ui->ComBaudBox->addItems(BaudList);
    ui->ComBaudBox->setCurrentIndex(3);

    //数据位选项
    QStringList dataBitsList;
    dataBitsList <<"6" << "7" << "8"<<"9";
    ui->ComDataBox->addItems(dataBitsList);
    ui->ComDataBox->setCurrentIndex(2);

    //停止位选项
    QStringList StopBitsList;
    StopBitsList<<"1"<<"2";
    ui->ComStopBox->addItems(StopBitsList);
    ui->ComStopBox->setCurrentIndex(0);

    //校验位
    QStringList ParityList;
    ParityList<<"N"<<"Odd"<<"Even";
    ui->ComParityBox->addItems(ParityList);
    ui->ComParityBox->setCurrentIndex(0);
}

void MainWindow::on_open_btn_clicked()
{
    ui->ReceiveEdit->append("打开串口");
}
