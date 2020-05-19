/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QFrame *fram_uart;
    QLabel *label_comid;
    QComboBox *combo_box_com;
    QLabel *label_baud;
    QComboBox *combo_box_baud;
    QLabel *label_data;
    QComboBox *combo_box_data;
    QLabel *label_stop;
    QComboBox *combo_box_stop;
    QLabel *label_parity;
    QComboBox *combo_box_parity;
    QPushButton *btn_uart_open;
    QPushButton *btn_uart_close;
    QFrame *frame_info;
    QLabel *label_led;
    QPushButton *btn_led_on;
    QPushButton *btn_led_off;
    QLabel *label_beep;
    QPushButton *btn_beep_on;
    QPushButton *btn_beep_off;
    QTextEdit *text_edit_recv;
    QLabel *label_stauts;
    QPushButton *btn_refresh;
    QCheckBox *check_box_time;
    QLineEdit *line_edit_time;
    QLabel *label_time;
    QLabel *label_reboot;
    QPushButton *btn_reboot;
    QFrame *frame_dev;
    QLabel *label_dev_id;
    QLineEdit *line_edit_dev_id;
    QFrame *frame_test;
    QLabel *label_cmd;
    QLineEdit *line_edit_cmd;
    QPushButton *btn_send_cmd;
    QLabel *label_test;
    QTextEdit *text_edit_test;
    QPushButton *btn_clear;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(710, 720);
        MainWindow->setMinimumSize(QSize(710, 720));
        MainWindow->setMaximumSize(QSize(710, 720));
        MainWindow->setAutoFillBackground(false);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        fram_uart = new QFrame(centralwidget);
        fram_uart->setObjectName(QString::fromUtf8("fram_uart"));
        fram_uart->setGeometry(QRect(500, 10, 201, 191));
        fram_uart->setMinimumSize(QSize(100, 100));
        fram_uart->setFrameShape(QFrame::StyledPanel);
        fram_uart->setFrameShadow(QFrame::Raised);
        label_comid = new QLabel(fram_uart);
        label_comid->setObjectName(QString::fromUtf8("label_comid"));
        label_comid->setGeometry(QRect(10, 10, 61, 16));
        combo_box_com = new QComboBox(fram_uart);
        combo_box_com->setObjectName(QString::fromUtf8("combo_box_com"));
        combo_box_com->setGeometry(QRect(80, 10, 111, 21));
        label_baud = new QLabel(fram_uart);
        label_baud->setObjectName(QString::fromUtf8("label_baud"));
        label_baud->setGeometry(QRect(10, 40, 61, 20));
        combo_box_baud = new QComboBox(fram_uart);
        combo_box_baud->setObjectName(QString::fromUtf8("combo_box_baud"));
        combo_box_baud->setGeometry(QRect(80, 40, 111, 21));
        label_data = new QLabel(fram_uart);
        label_data->setObjectName(QString::fromUtf8("label_data"));
        label_data->setGeometry(QRect(10, 70, 61, 20));
        combo_box_data = new QComboBox(fram_uart);
        combo_box_data->setObjectName(QString::fromUtf8("combo_box_data"));
        combo_box_data->setGeometry(QRect(80, 70, 111, 21));
        label_stop = new QLabel(fram_uart);
        label_stop->setObjectName(QString::fromUtf8("label_stop"));
        label_stop->setGeometry(QRect(10, 100, 61, 20));
        combo_box_stop = new QComboBox(fram_uart);
        combo_box_stop->setObjectName(QString::fromUtf8("combo_box_stop"));
        combo_box_stop->setGeometry(QRect(80, 100, 111, 21));
        label_parity = new QLabel(fram_uart);
        label_parity->setObjectName(QString::fromUtf8("label_parity"));
        label_parity->setGeometry(QRect(10, 130, 51, 20));
        combo_box_parity = new QComboBox(fram_uart);
        combo_box_parity->setObjectName(QString::fromUtf8("combo_box_parity"));
        combo_box_parity->setGeometry(QRect(80, 130, 111, 21));
        btn_uart_open = new QPushButton(fram_uart);
        btn_uart_open->setObjectName(QString::fromUtf8("btn_uart_open"));
        btn_uart_open->setGeometry(QRect(10, 160, 71, 23));
        btn_uart_close = new QPushButton(fram_uart);
        btn_uart_close->setObjectName(QString::fromUtf8("btn_uart_close"));
        btn_uart_close->setGeometry(QRect(110, 160, 81, 23));
        frame_info = new QFrame(centralwidget);
        frame_info->setObjectName(QString::fromUtf8("frame_info"));
        frame_info->setGeometry(QRect(10, 10, 481, 301));
        frame_info->setFrameShape(QFrame::StyledPanel);
        frame_info->setFrameShadow(QFrame::Raised);
        label_led = new QLabel(frame_info);
        label_led->setObjectName(QString::fromUtf8("label_led"));
        label_led->setGeometry(QRect(10, 2, 71, 16));
        btn_led_on = new QPushButton(frame_info);
        btn_led_on->setObjectName(QString::fromUtf8("btn_led_on"));
        btn_led_on->setGeometry(QRect(90, 0, 91, 23));
        btn_led_off = new QPushButton(frame_info);
        btn_led_off->setObjectName(QString::fromUtf8("btn_led_off"));
        btn_led_off->setGeometry(QRect(200, 0, 91, 23));
        label_beep = new QLabel(frame_info);
        label_beep->setObjectName(QString::fromUtf8("label_beep"));
        label_beep->setGeometry(QRect(10, 30, 71, 21));
        btn_beep_on = new QPushButton(frame_info);
        btn_beep_on->setObjectName(QString::fromUtf8("btn_beep_on"));
        btn_beep_on->setGeometry(QRect(90, 30, 91, 23));
        btn_beep_off = new QPushButton(frame_info);
        btn_beep_off->setObjectName(QString::fromUtf8("btn_beep_off"));
        btn_beep_off->setGeometry(QRect(200, 30, 91, 23));
        text_edit_recv = new QTextEdit(frame_info);
        text_edit_recv->setObjectName(QString::fromUtf8("text_edit_recv"));
        text_edit_recv->setGeometry(QRect(0, 120, 481, 181));
        text_edit_recv->setReadOnly(true);
        label_stauts = new QLabel(frame_info);
        label_stauts->setObjectName(QString::fromUtf8("label_stauts"));
        label_stauts->setGeometry(QRect(10, 90, 81, 21));
        btn_refresh = new QPushButton(frame_info);
        btn_refresh->setObjectName(QString::fromUtf8("btn_refresh"));
        btn_refresh->setGeometry(QRect(90, 90, 91, 21));
        check_box_time = new QCheckBox(frame_info);
        check_box_time->setObjectName(QString::fromUtf8("check_box_time"));
        check_box_time->setGeometry(QRect(200, 90, 51, 21));
        line_edit_time = new QLineEdit(frame_info);
        line_edit_time->setObjectName(QString::fromUtf8("line_edit_time"));
        line_edit_time->setGeometry(QRect(260, 90, 71, 21));
        label_time = new QLabel(frame_info);
        label_time->setObjectName(QString::fromUtf8("label_time"));
        label_time->setGeometry(QRect(340, 90, 41, 21));
        label_reboot = new QLabel(frame_info);
        label_reboot->setObjectName(QString::fromUtf8("label_reboot"));
        label_reboot->setGeometry(QRect(10, 60, 71, 21));
        btn_reboot = new QPushButton(frame_info);
        btn_reboot->setObjectName(QString::fromUtf8("btn_reboot"));
        btn_reboot->setGeometry(QRect(90, 60, 91, 23));
        frame_dev = new QFrame(centralwidget);
        frame_dev->setObjectName(QString::fromUtf8("frame_dev"));
        frame_dev->setGeometry(QRect(500, 210, 201, 91));
        frame_dev->setFrameShape(QFrame::StyledPanel);
        frame_dev->setFrameShadow(QFrame::Raised);
        label_dev_id = new QLabel(frame_dev);
        label_dev_id->setObjectName(QString::fromUtf8("label_dev_id"));
        label_dev_id->setGeometry(QRect(10, 10, 71, 16));
        line_edit_dev_id = new QLineEdit(frame_dev);
        line_edit_dev_id->setObjectName(QString::fromUtf8("line_edit_dev_id"));
        line_edit_dev_id->setGeometry(QRect(80, 10, 101, 21));
        frame_test = new QFrame(centralwidget);
        frame_test->setObjectName(QString::fromUtf8("frame_test"));
        frame_test->setGeometry(QRect(10, 320, 481, 391));
        frame_test->setFrameShape(QFrame::StyledPanel);
        frame_test->setFrameShadow(QFrame::Raised);
        label_cmd = new QLabel(frame_test);
        label_cmd->setObjectName(QString::fromUtf8("label_cmd"));
        label_cmd->setGeometry(QRect(0, 0, 101, 16));
        line_edit_cmd = new QLineEdit(frame_test);
        line_edit_cmd->setObjectName(QString::fromUtf8("line_edit_cmd"));
        line_edit_cmd->setGeometry(QRect(0, 30, 401, 31));
        btn_send_cmd = new QPushButton(frame_test);
        btn_send_cmd->setObjectName(QString::fromUtf8("btn_send_cmd"));
        btn_send_cmd->setGeometry(QRect(410, 30, 71, 31));
        label_test = new QLabel(frame_test);
        label_test->setObjectName(QString::fromUtf8("label_test"));
        label_test->setGeometry(QRect(0, 70, 121, 16));
        text_edit_test = new QTextEdit(frame_test);
        text_edit_test->setObjectName(QString::fromUtf8("text_edit_test"));
        text_edit_test->setGeometry(QRect(0, 90, 481, 261));
        text_edit_test->setReadOnly(true);
        btn_clear = new QPushButton(centralwidget);
        btn_clear->setObjectName(QString::fromUtf8("btn_clear"));
        btn_clear->setGeometry(QRect(10, 680, 92, 28));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 710, 23));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        label_comid->setText(QApplication::translate("MainWindow", "\344\270\262\345\217\243\345\217\267", nullptr));
        label_baud->setText(QApplication::translate("MainWindow", "\346\263\242\347\211\271\347\216\207", nullptr));
        label_data->setText(QApplication::translate("MainWindow", "\346\225\260\346\215\256\344\275\215", nullptr));
        label_stop->setText(QApplication::translate("MainWindow", "\345\201\234\346\255\242\344\275\215", nullptr));
        label_parity->setText(QApplication::translate("MainWindow", "\346\240\241\351\252\214\344\275\215", nullptr));
        btn_uart_open->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\344\270\262\345\217\243", nullptr));
        btn_uart_close->setText(QApplication::translate("MainWindow", "\345\205\263\351\227\255\344\270\262\345\217\243", nullptr));
        label_led->setText(QApplication::translate("MainWindow", "LED\346\216\247\345\210\266", nullptr));
        btn_led_on->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200LED", nullptr));
        btn_led_off->setText(QApplication::translate("MainWindow", "\345\205\263\351\227\255LED", nullptr));
        label_beep->setText(QApplication::translate("MainWindow", "BEEP\346\216\247\345\210\266", nullptr));
        btn_beep_on->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\350\234\202\351\270\243\345\231\250", nullptr));
        btn_beep_off->setText(QApplication::translate("MainWindow", "\345\205\263\351\227\255\350\234\202\351\270\243\345\231\250", nullptr));
        label_stauts->setText(QApplication::translate("MainWindow", "\345\206\205\351\203\250\347\212\266\346\200\201\345\214\272", nullptr));
        btn_refresh->setText(QApplication::translate("MainWindow", "\345\210\267\346\226\260\347\212\266\346\200\201", nullptr));
        check_box_time->setText(QApplication::translate("MainWindow", "\345\256\232\346\227\266", nullptr));
        label_time->setText(QApplication::translate("MainWindow", "s", nullptr));
        label_reboot->setText(QApplication::translate("MainWindow", "\345\244\215\344\275\215", nullptr));
        btn_reboot->setText(QApplication::translate("MainWindow", "\345\244\215\344\275\215", nullptr));
        label_dev_id->setText(QApplication::translate("MainWindow", "\350\256\276\345\244\207ID", nullptr));
        line_edit_dev_id->setText(QApplication::translate("MainWindow", "1", nullptr));
        label_cmd->setText(QApplication::translate("MainWindow", "\350\207\252\345\256\232\344\271\211\346\214\207\344\273\244", nullptr));
        btn_send_cmd->setText(QApplication::translate("MainWindow", "\346\214\207\344\273\244\345\217\221\351\200\201", nullptr));
        label_test->setText(QApplication::translate("MainWindow", "\350\260\203\350\257\225\347\252\227\345\217\243", nullptr));
        btn_clear->setText(QApplication::translate("MainWindow", "\346\270\205\347\251\272\346\225\260\346\215\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
