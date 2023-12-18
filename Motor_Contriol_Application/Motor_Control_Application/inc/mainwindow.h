#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDoubleValidator>
#include <QDebug>
#include <QSerialPortInfo>
#include <QString>
#include <QTimer>
#include <QSerialPort>
#include <QIODevice>
#include <stdint.h>
#include <QMessageBox>
#include "crc16.h"
#include <QByteArray>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:

    /*That function is defined by user*/
    void init_main_window();
    void on_refresh_btn_clicked();
    void show_notice(const QString mess, const Qt::GlobalColor textColor);
    void received_data_from_STM32();
    /*That function is defined defalut by Qt*/
    void on_connect_btn_clicked();

    void on_send_pid_btn_clicked();

    void on_position_mode_btn_clicked();

    void on_velocity_mode_btn_clicked();

    void on_run_btn_clicked();

    void on_stop_btn_clicked();

    void on_reset_btn_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPortInfo com_info;
    QSerialPort com_serial;
    QTimer *timer_receive;
};
#endif // MAINWINDOW_H
