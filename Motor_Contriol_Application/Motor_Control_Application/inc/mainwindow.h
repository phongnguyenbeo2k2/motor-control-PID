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
#include <QElapsedTimer>

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
    void test_plot_graph();
    void show_notice(const QString mess, const Qt::GlobalColor textColor);
    void show_received_data(const QString mess, const Qt::GlobalColor textColor);
    void received_data_from_STM32();
    void plot_response();
    void plot_real_time_graph();
    /*That function is defined defalut by Qt*/
    void on_connect_btn_clicked();

    void on_send_pid_btn_clicked();

    void on_position_mode_btn_clicked();

    void on_velocity_mode_btn_clicked();

    void on_run_btn_clicked();

    void on_stop_btn_clicked();

    void on_reset_btn_clicked();

    void on_clear_graph_btn_clicked();

    void on_clear_received_data_tabel_btn_clicked();

    void on_clear_notice_table_btn_clicked();

    void on_plot_realtime_graph_btn_clicked();

    void on_clear_realtimegraph_btn_clicked();

    void on_clear_response_graph_btn_clicked();

    void on_plot_response_graph_btn_clicked();

    void on_Read_data_STM_btn_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPortInfo com_info;
    QSerialPort com_serial;
    QTimer *timer_receive;
    QTimer *timer_updategraph;
    QTimer *timer_plotrealtime;
    QElapsedTimer timer_plot; /*return type variable is quint64*/
    QVector<double> timeX, motor_data_Y, setpoint_Y;
    quint64 preTime = 0;
    QStringList motor_data;
    QList<double> dataPoints;
    QVector<double> dataPoints_vec;
};
#endif // MAINWINDOW_H
