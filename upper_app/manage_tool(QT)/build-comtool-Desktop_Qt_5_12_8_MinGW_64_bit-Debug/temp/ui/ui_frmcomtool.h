/********************************************************************************
** Form generated from reading UI file 'frmcomtool.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMCOMTOOL_H
#define UI_FRMCOMTOOL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frmComTool
{
public:
    QGridLayout *gridLayout_6;
    QTextEdit *txtMain;
    QWidget *widgetRight;
    QVBoxLayout *verticalLayout;
    QFrame *frameTop;
    QGridLayout *gridLayout_3;
    QLabel *labPortName;
    QComboBox *cboxPortName;
    QLabel *labBaudRate;
    QComboBox *cboxBaudRate;
    QLabel *labDataBit;
    QComboBox *cboxDataBit;
    QLabel *labParity;
    QComboBox *cboxParity;
    QLabel *labStopBit;
    QComboBox *cboxStopBit;
    QPushButton *btnOpen;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_5;
    QPushButton *btnReceiveCount;
    QCheckBox *ckHexReceive;
    QPushButton *btnStopShow;
    QSpacerItem *verticalSpacer;
    QPushButton *btnClear;
    QCheckBox *ckAutoClear;
    QPushButton *btnSendCount;
    QPushButton *btnSave;
    QPushButton *btnData;
    QCheckBox *ckHexSend;
    QCheckBox *ckDebug;
    QGridLayout *gridLayout;
    QCheckBox *ckAutoSend;
    QComboBox *cboxSendInterval;
    QCheckBox *ckAutoSave;
    QComboBox *cboxSaveInterval;
    QWidget *tab_2;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout_4;
    QLabel *labListenPort;
    QLabel *labServerIP;
    QComboBox *cboxSleepTime;
    QLineEdit *txtServerIP;
    QLabel *labServerPort;
    QLineEdit *txtServerPort;
    QLabel *labSleepTime;
    QLineEdit *txtListenPort;
    QLabel *labMode;
    QComboBox *cboxMode;
    QPushButton *btnStart;
    QSpacerItem *verticalSpacer_2;
    QCheckBox *ckAutoConnect;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QComboBox *cboxData;
    QPushButton *btnSend;

    void setupUi(QWidget *frmComTool)
    {
        if (frmComTool->objectName().isEmpty())
            frmComTool->setObjectName(QString::fromUtf8("frmComTool"));
        frmComTool->resize(800, 600);
        gridLayout_6 = new QGridLayout(frmComTool);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        txtMain = new QTextEdit(frmComTool);
        txtMain->setObjectName(QString::fromUtf8("txtMain"));
        txtMain->setEnabled(true);
        txtMain->setFrameShape(QFrame::StyledPanel);
        txtMain->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        txtMain->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        txtMain->setReadOnly(true);

        gridLayout_6->addWidget(txtMain, 0, 0, 1, 1);

        widgetRight = new QWidget(frmComTool);
        widgetRight->setObjectName(QString::fromUtf8("widgetRight"));
        widgetRight->setMaximumSize(QSize(200, 16777215));
        verticalLayout = new QVBoxLayout(widgetRight);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        frameTop = new QFrame(widgetRight);
        frameTop->setObjectName(QString::fromUtf8("frameTop"));
        frameTop->setFrameShape(QFrame::Box);
        frameTop->setFrameShadow(QFrame::Sunken);
        gridLayout_3 = new QGridLayout(frameTop);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        labPortName = new QLabel(frameTop);
        labPortName->setObjectName(QString::fromUtf8("labPortName"));

        gridLayout_3->addWidget(labPortName, 0, 0, 1, 1);

        cboxPortName = new QComboBox(frameTop);
        cboxPortName->setObjectName(QString::fromUtf8("cboxPortName"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(cboxPortName->sizePolicy().hasHeightForWidth());
        cboxPortName->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(cboxPortName, 0, 1, 1, 1);

        labBaudRate = new QLabel(frameTop);
        labBaudRate->setObjectName(QString::fromUtf8("labBaudRate"));

        gridLayout_3->addWidget(labBaudRate, 1, 0, 1, 1);

        cboxBaudRate = new QComboBox(frameTop);
        cboxBaudRate->setObjectName(QString::fromUtf8("cboxBaudRate"));
        sizePolicy.setHeightForWidth(cboxBaudRate->sizePolicy().hasHeightForWidth());
        cboxBaudRate->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(cboxBaudRate, 1, 1, 1, 1);

        labDataBit = new QLabel(frameTop);
        labDataBit->setObjectName(QString::fromUtf8("labDataBit"));

        gridLayout_3->addWidget(labDataBit, 2, 0, 1, 1);

        cboxDataBit = new QComboBox(frameTop);
        cboxDataBit->setObjectName(QString::fromUtf8("cboxDataBit"));
        sizePolicy.setHeightForWidth(cboxDataBit->sizePolicy().hasHeightForWidth());
        cboxDataBit->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(cboxDataBit, 2, 1, 1, 1);

        labParity = new QLabel(frameTop);
        labParity->setObjectName(QString::fromUtf8("labParity"));

        gridLayout_3->addWidget(labParity, 3, 0, 1, 1);

        cboxParity = new QComboBox(frameTop);
        cboxParity->setObjectName(QString::fromUtf8("cboxParity"));
        sizePolicy.setHeightForWidth(cboxParity->sizePolicy().hasHeightForWidth());
        cboxParity->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(cboxParity, 3, 1, 1, 1);

        labStopBit = new QLabel(frameTop);
        labStopBit->setObjectName(QString::fromUtf8("labStopBit"));

        gridLayout_3->addWidget(labStopBit, 4, 0, 1, 1);

        cboxStopBit = new QComboBox(frameTop);
        cboxStopBit->setObjectName(QString::fromUtf8("cboxStopBit"));
        sizePolicy.setHeightForWidth(cboxStopBit->sizePolicy().hasHeightForWidth());
        cboxStopBit->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(cboxStopBit, 4, 1, 1, 1);

        btnOpen = new QPushButton(frameTop);
        btnOpen->setObjectName(QString::fromUtf8("btnOpen"));

        gridLayout_3->addWidget(btnOpen, 5, 0, 1, 2);


        verticalLayout->addWidget(frameTop);

        tabWidget = new QTabWidget(widgetRight);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setTabPosition(QTabWidget::South);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout_5 = new QGridLayout(tab);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        btnReceiveCount = new QPushButton(tab);
        btnReceiveCount->setObjectName(QString::fromUtf8("btnReceiveCount"));

        gridLayout_5->addWidget(btnReceiveCount, 4, 0, 1, 2);

        ckHexReceive = new QCheckBox(tab);
        ckHexReceive->setObjectName(QString::fromUtf8("ckHexReceive"));

        gridLayout_5->addWidget(ckHexReceive, 0, 1, 1, 1);

        btnStopShow = new QPushButton(tab);
        btnStopShow->setObjectName(QString::fromUtf8("btnStopShow"));

        gridLayout_5->addWidget(btnStopShow, 5, 0, 1, 2);

        verticalSpacer = new QSpacerItem(20, 2, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_5->addItem(verticalSpacer, 9, 0, 1, 2);

        btnClear = new QPushButton(tab);
        btnClear->setObjectName(QString::fromUtf8("btnClear"));

        gridLayout_5->addWidget(btnClear, 8, 0, 1, 2);

        ckAutoClear = new QCheckBox(tab);
        ckAutoClear->setObjectName(QString::fromUtf8("ckAutoClear"));

        gridLayout_5->addWidget(ckAutoClear, 1, 1, 1, 1);

        btnSendCount = new QPushButton(tab);
        btnSendCount->setObjectName(QString::fromUtf8("btnSendCount"));

        gridLayout_5->addWidget(btnSendCount, 3, 0, 1, 2);

        btnSave = new QPushButton(tab);
        btnSave->setObjectName(QString::fromUtf8("btnSave"));

        gridLayout_5->addWidget(btnSave, 6, 0, 1, 2);

        btnData = new QPushButton(tab);
        btnData->setObjectName(QString::fromUtf8("btnData"));

        gridLayout_5->addWidget(btnData, 7, 0, 1, 2);

        ckHexSend = new QCheckBox(tab);
        ckHexSend->setObjectName(QString::fromUtf8("ckHexSend"));

        gridLayout_5->addWidget(ckHexSend, 0, 0, 1, 1);

        ckDebug = new QCheckBox(tab);
        ckDebug->setObjectName(QString::fromUtf8("ckDebug"));

        gridLayout_5->addWidget(ckDebug, 1, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        ckAutoSend = new QCheckBox(tab);
        ckAutoSend->setObjectName(QString::fromUtf8("ckAutoSend"));

        gridLayout->addWidget(ckAutoSend, 0, 0, 1, 1);

        cboxSendInterval = new QComboBox(tab);
        cboxSendInterval->setObjectName(QString::fromUtf8("cboxSendInterval"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(cboxSendInterval->sizePolicy().hasHeightForWidth());
        cboxSendInterval->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(cboxSendInterval, 0, 1, 1, 1);

        ckAutoSave = new QCheckBox(tab);
        ckAutoSave->setObjectName(QString::fromUtf8("ckAutoSave"));

        gridLayout->addWidget(ckAutoSave, 1, 0, 1, 1);

        cboxSaveInterval = new QComboBox(tab);
        cboxSaveInterval->setObjectName(QString::fromUtf8("cboxSaveInterval"));
        sizePolicy1.setHeightForWidth(cboxSaveInterval->sizePolicy().hasHeightForWidth());
        cboxSaveInterval->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(cboxSaveInterval, 1, 1, 1, 1);


        gridLayout_5->addLayout(gridLayout, 2, 0, 1, 2);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        gridLayout_2 = new QGridLayout(tab_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        labListenPort = new QLabel(tab_2);
        labListenPort->setObjectName(QString::fromUtf8("labListenPort"));

        gridLayout_4->addWidget(labListenPort, 3, 0, 1, 1);

        labServerIP = new QLabel(tab_2);
        labServerIP->setObjectName(QString::fromUtf8("labServerIP"));

        gridLayout_4->addWidget(labServerIP, 1, 0, 1, 1);

        cboxSleepTime = new QComboBox(tab_2);
        cboxSleepTime->setObjectName(QString::fromUtf8("cboxSleepTime"));

        gridLayout_4->addWidget(cboxSleepTime, 4, 1, 1, 1);

        txtServerIP = new QLineEdit(tab_2);
        txtServerIP->setObjectName(QString::fromUtf8("txtServerIP"));

        gridLayout_4->addWidget(txtServerIP, 1, 1, 1, 1);

        labServerPort = new QLabel(tab_2);
        labServerPort->setObjectName(QString::fromUtf8("labServerPort"));

        gridLayout_4->addWidget(labServerPort, 2, 0, 1, 1);

        txtServerPort = new QLineEdit(tab_2);
        txtServerPort->setObjectName(QString::fromUtf8("txtServerPort"));

        gridLayout_4->addWidget(txtServerPort, 2, 1, 1, 1);

        labSleepTime = new QLabel(tab_2);
        labSleepTime->setObjectName(QString::fromUtf8("labSleepTime"));

        gridLayout_4->addWidget(labSleepTime, 4, 0, 1, 1);

        txtListenPort = new QLineEdit(tab_2);
        txtListenPort->setObjectName(QString::fromUtf8("txtListenPort"));

        gridLayout_4->addWidget(txtListenPort, 3, 1, 1, 1);

        labMode = new QLabel(tab_2);
        labMode->setObjectName(QString::fromUtf8("labMode"));

        gridLayout_4->addWidget(labMode, 0, 0, 1, 1);

        cboxMode = new QComboBox(tab_2);
        cboxMode->addItem(QString());
        cboxMode->addItem(QString());
        cboxMode->addItem(QString());
        cboxMode->addItem(QString());
        cboxMode->setObjectName(QString::fromUtf8("cboxMode"));

        gridLayout_4->addWidget(cboxMode, 0, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout_4, 0, 0, 1, 2);

        btnStart = new QPushButton(tab_2);
        btnStart->setObjectName(QString::fromUtf8("btnStart"));

        gridLayout_2->addWidget(btnStart, 2, 0, 1, 2);

        verticalSpacer_2 = new QSpacerItem(20, 59, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 3, 0, 1, 2);

        ckAutoConnect = new QCheckBox(tab_2);
        ckAutoConnect->setObjectName(QString::fromUtf8("ckAutoConnect"));

        gridLayout_2->addWidget(ckAutoConnect, 1, 0, 1, 2);

        tabWidget->addTab(tab_2, QString());

        verticalLayout->addWidget(tabWidget);


        gridLayout_6->addWidget(widgetRight, 0, 1, 2, 1);

        widget = new QWidget(frmComTool);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        cboxData = new QComboBox(widget);
        cboxData->setObjectName(QString::fromUtf8("cboxData"));
        QSizePolicy sizePolicy2(QSizePolicy::Ignored, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(cboxData->sizePolicy().hasHeightForWidth());
        cboxData->setSizePolicy(sizePolicy2);
        cboxData->setEditable(true);
        cboxData->setDuplicatesEnabled(false);

        horizontalLayout->addWidget(cboxData);

        btnSend = new QPushButton(widget);
        btnSend->setObjectName(QString::fromUtf8("btnSend"));
        btnSend->setMinimumSize(QSize(80, 0));
        btnSend->setMaximumSize(QSize(80, 16777215));

        horizontalLayout->addWidget(btnSend);


        gridLayout_6->addWidget(widget, 1, 0, 1, 1);


        retranslateUi(frmComTool);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(frmComTool);
    } // setupUi

    void retranslateUi(QWidget *frmComTool)
    {
        labPortName->setText(QApplication::translate("frmComTool", "\344\270\262\345\217\243\345\217\267", nullptr));
        labBaudRate->setText(QApplication::translate("frmComTool", "\346\263\242\347\211\271\347\216\207", nullptr));
        labDataBit->setText(QApplication::translate("frmComTool", "\346\225\260\346\215\256\344\275\215", nullptr));
        labParity->setText(QApplication::translate("frmComTool", "\346\240\241\351\252\214\344\275\215", nullptr));
        labStopBit->setText(QApplication::translate("frmComTool", "\345\201\234\346\255\242\344\275\215", nullptr));
        btnOpen->setText(QApplication::translate("frmComTool", "\346\211\223\345\274\200\344\270\262\345\217\243", nullptr));
        btnReceiveCount->setText(QApplication::translate("frmComTool", "\346\216\245\346\224\266 : 0 \345\255\227\350\212\202", nullptr));
        ckHexReceive->setText(QApplication::translate("frmComTool", "Hex\346\216\245\346\224\266", nullptr));
        btnStopShow->setText(QApplication::translate("frmComTool", "\345\201\234\346\255\242\346\230\276\347\244\272", nullptr));
        btnClear->setText(QApplication::translate("frmComTool", "\346\270\205\347\251\272\346\225\260\346\215\256", nullptr));
        ckAutoClear->setText(QApplication::translate("frmComTool", "\350\207\252\345\212\250\346\270\205\347\251\272", nullptr));
        btnSendCount->setText(QApplication::translate("frmComTool", "\345\217\221\351\200\201 : 0 \345\255\227\350\212\202", nullptr));
        btnSave->setText(QApplication::translate("frmComTool", "\344\277\235\345\255\230\346\225\260\346\215\256", nullptr));
        btnData->setText(QApplication::translate("frmComTool", "\347\256\241\347\220\206\346\225\260\346\215\256", nullptr));
        ckHexSend->setText(QApplication::translate("frmComTool", "Hex\345\217\221\351\200\201", nullptr));
        ckDebug->setText(QApplication::translate("frmComTool", "\346\250\241\346\213\237\350\256\276\345\244\207", nullptr));
        ckAutoSend->setText(QApplication::translate("frmComTool", "\350\207\252\345\212\250\345\217\221\351\200\201", nullptr));
        ckAutoSave->setText(QApplication::translate("frmComTool", "\350\207\252\345\212\250\344\277\235\345\255\230", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("frmComTool", "\344\270\262\345\217\243\351\205\215\347\275\256", nullptr));
        labListenPort->setText(QApplication::translate("frmComTool", "\347\233\221\345\220\254\347\253\257\345\217\243", nullptr));
        labServerIP->setText(QApplication::translate("frmComTool", "\350\277\234\347\250\213\345\234\260\345\235\200", nullptr));
        txtServerIP->setText(QString());
        labServerPort->setText(QApplication::translate("frmComTool", "\350\277\234\347\250\213\347\253\257\345\217\243", nullptr));
        txtServerPort->setText(QString());
        labSleepTime->setText(QApplication::translate("frmComTool", "\345\273\266\346\227\266\346\227\266\351\227\264", nullptr));
        labMode->setText(QApplication::translate("frmComTool", "\350\275\254\346\215\242\346\250\241\345\274\217", nullptr));
        cboxMode->setItemText(0, QApplication::translate("frmComTool", "Tcp_Client", nullptr));
        cboxMode->setItemText(1, QApplication::translate("frmComTool", "Tcp_Server", nullptr));
        cboxMode->setItemText(2, QApplication::translate("frmComTool", "Udp_Client", nullptr));
        cboxMode->setItemText(3, QApplication::translate("frmComTool", "Udp_Server", nullptr));

        btnStart->setText(QApplication::translate("frmComTool", "\345\220\257\345\212\250", nullptr));
        ckAutoConnect->setText(QApplication::translate("frmComTool", "\350\207\252\345\212\250\351\207\215\350\277\236\347\275\221\347\273\234", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("frmComTool", "\347\275\221\347\273\234\351\205\215\347\275\256", nullptr));
        btnSend->setText(QApplication::translate("frmComTool", "\345\217\221\351\200\201", nullptr));
        Q_UNUSED(frmComTool);
    } // retranslateUi

};

namespace Ui {
    class frmComTool: public Ui_frmComTool {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMCOMTOOL_H
