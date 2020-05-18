#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void init();    

private slots:
    void on_btn_clear_clicked();
    void on_btn_led_off_clicked();
    void on_btn_led_on_clicked();

    void on_btn_beep_on_clicked();

    void on_btn_beep_off_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
