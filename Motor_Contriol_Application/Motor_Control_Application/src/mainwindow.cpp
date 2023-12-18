#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include "frame_data.h"

/*Initialize global variables*/
QByteArray test_frame;
uint8_t test_frame_buff[20] = {0};
uint16_t test_frame_buff_length;
frame_data frame_data_motor;
uint8_t length_data_rx = 0;
uint8_t is_select_mode = 0;
uint8_t is_send_pid = 0;
/*--------------------------*/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer_receive = new QTimer(this);
    init_main_window();
    connect(&com_serial,SIGNAL(readyRead()),this,SLOT(received_data_from_STM32()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init_main_window()
{
//  setFixedSize(width(),height()); /*fix size of application */
    setWindowTitle("Motor Control App");
    ui->Kp_lineEdit->setValidator(new QDoubleValidator);
    ui->Ki_lineEdit->setValidator(new QDoubleValidator);
    ui->Kd_lineEdit->setValidator(new QDoubleValidator);
    ui->setPoint_lineEdit->setValidator(new QDoubleValidator);
    /*find all available com is existing on my computer*/
    QList<QSerialPortInfo> com_list = com_info.availablePorts();
    QList<QString> com_str;
    for (int i = 0; i < com_list.size(); i++)
    {
//        qDebug() << com_list.at(i).portName() << "\n";
        com_str.append(com_list.at(i).portName());
//        qDebug() << "1";
    }
//    qDebug() << com_str;
    ui->Com_comboBox->addItems(com_str);
    /*find all available baud rate that computer can use for serial protocol*/
    QList<qint32> baud_rate_list = com_info.standardBaudRates();
    QList<QString> baud_rate_str;
    for (int i = 0; i < baud_rate_list.size(); i++)
    {
        baud_rate_str.append(QString::number(baud_rate_list.at(i)));
    }
    ui->Baud_rate_comboBox->addItems(baud_rate_str);
}


void MainWindow::on_refresh_btn_clicked()
{
    QList<QSerialPortInfo> com_list = com_info.availablePorts();
    QList<QString> com_str;
    for (int i = 0; i < com_list.size(); i++)
    {
        com_str.append(com_list.at(i).portName());
    }
    ui->Com_comboBox->clear();
    ui->Com_comboBox->addItem("SELECT COM");
    ui->Com_comboBox->addItems(com_str);
}

void MainWindow::show_notice(const QString mess, const Qt::GlobalColor textColor)
{
    ui->notification_textEdit->setTextColor(textColor);
    ui->notification_textEdit->append(mess);
    ui->notification_textEdit->setTextColor(textColor);
}

void MainWindow::received_data_from_STM32()
{
    uint8_t length_raw_data_rx;
    if (com_serial.isOpen())
    {
        frame_data_motor.read_data = com_serial.readAll();
        qDebug() << frame_data_motor.read_data;
        qDebug() << com_serial.bytesAvailable();
        length_data_rx = frame_data_motor.read_data.size();
        qDebug() << length_data_rx;
        if (length_data_rx == 10)
        {
                uint8_t check = frame_data_motor.decode_received_frame_data(reinterpret_cast<uint8_t *>(frame_data_motor.read_data.data()),&length_data_rx,frame_data_motor.frame_data_rx,&length_raw_data_rx);
            if (check == 0)
            {
                show_notice("Data is true",Qt::black);
                uint8_t *raw_data = frame_data_motor.frame_data_rx;
                float *velocity_data = reinterpret_cast<float *>(raw_data + 2);
                qDebug() << *velocity_data;
                QString velocity_str = QString("Velocity is %1").arg(*(velocity_data));
                qDebug() << velocity_str;
            show_notice(velocity_str,Qt::black);
            }else
            {
            show_notice("Data is wrong",Qt::red);
            }
        }
//        frame_data_motor.read_data = com_serial.readAll();
//        qDebug() << frame_data_motor.read_data;
//        qDebug() << com_serial.bytesAvailable();
    }

}

void MainWindow::on_connect_btn_clicked()
{
    if (ui->connect_btn->text() == "CONNECT")
    {
        QString selected_com = ui->Com_comboBox->currentText();
        if (!(selected_com == "SELECT COM"))
        {
        com_serial.setPortName(selected_com);
        /*create connection between computer and STM32F1 blue pill*/
        com_serial.open(QIODevice::ReadWrite);
        if (!com_serial.isOpen())
        {
            /*Connect failed*/
            show_notice("Connect unsucessfully !",Qt::red);
        }else
        {
            /*Connect sucessfully*/
            /*Step 1: set baudrate for interacting between computer and microcontroller*/
            QString current_baudrate_str = ui->Baud_rate_comboBox->currentText();
            if (!(current_baudrate_str == "BAUD RATE"))
            {
            com_serial.setBaudRate(current_baudrate_str.toInt());

            /*Step 2: set data bits for frame data to communicate*/
            com_serial.setDataBits(QSerialPort::Data8);
            /*Step 3: set stop bits for frame data*/
            com_serial.setStopBits(QSerialPort::OneStop);
            /*Step 4: set parity bit for frame data*/
            com_serial.setParity(QSerialPort::NoParity);
            show_notice("Connect sucessfully !",Qt::black);

            /*when port is connect successfully, i need to disable the things which can config param of serial */
//            ui->send_pid_btn->setDisabled(true);
//            ui->position_mode_btn->setDisabled(true);
//            ui->velocity_mode_btn->setDisabled(true);
//            ui->refresh_btn->setDisabled(true);
            ui->connect_btn->setText("DISCONNECT");
            ui->connect_btn->setStyleSheet("QPushButton {color: rgb(255, 0, 0);}");
            }else
            {
                QMessageBox::warning(this,"Warning","You have to select baud rate before starting !");
                com_serial.close();
            }
        }
        }else
        {
        QMessageBox::warning(this,"Warning","You have to select COM before starting !");
        }

    }else
    {
        com_serial.close();
        show_notice("Disconnect sucessfully !",Qt::black);
        ui->send_pid_btn->setDisabled(false);
        ui->position_mode_btn->setDisabled(false);
        ui->velocity_mode_btn->setDisabled(false);
        ui->refresh_btn->setDisabled(false);
        ui->connect_btn->setText("CONNECT");
        ui->connect_btn->setStyleSheet("QPushButton {color: rgb(0, 255, 0);}");
    }
}


void MainWindow::on_send_pid_btn_clicked()
{
    if (is_select_mode == 1)
    {
    char mode = 0x01;
    float Kp = ui->Kp_lineEdit->text().toFloat();
    float Ki = ui->Ki_lineEdit->text().toFloat();
    float Kd = ui->Kd_lineEdit->text().toFloat();
    /*Create raw frame transmit*/
    frame_data_motor.write_data.clear();
    frame_data_motor.write_data.append(mode);
    frame_data_motor.write_data.append(reinterpret_cast<char *>(&Kp),sizeof(Kp));
    frame_data_motor.write_data.append(reinterpret_cast<char *>(&Ki),sizeof(Ki));
    frame_data_motor.write_data.append(reinterpret_cast<char *>(&Kd),sizeof(Kd));

    /*create frame that sended to STM32 */
    uint8_t length_frame_to_STM32 = frame_data_motor.create_frame_data(reinterpret_cast<uint8_t *>(frame_data_motor.write_data.data()),frame_data_motor.write_data.size(),frame_data_motor.frame_data_tx);
    qDebug() << frame_data_motor.write_data;
    qDebug() << "----------------------------------";
    qDebug() << length_frame_to_STM32;
    qDebug() << "----------------------------------";
    for (int i = 0; i < length_frame_to_STM32; i++)
    {
        qDebug() << frame_data_motor.frame_data_tx[i];
    }

    QByteArray frame_to_STM32 = QByteArray(reinterpret_cast<char *>(frame_data_motor.frame_data_tx),length_frame_to_STM32);
    if (com_serial.isOpen())
    {
        show_notice("---------------------------",Qt::black);
        show_notice("Send PID param to STM32",Qt::black);
        show_notice("Data is transmitted",Qt::black);
        com_serial.write(frame_to_STM32);
        is_send_pid = 1;
    }else
    {
        show_notice("---------------------------",Qt::black);
        show_notice("Don't set position control mode",Qt::red);
        show_notice("Data isn't transmitted",Qt::red);
    }
    }else
    {
        QMessageBox::warning(this,"Warning","You have to select mode before send PID params !");
    }
}


void MainWindow::on_position_mode_btn_clicked()
{
    char mode = 0x05;
    float set_point_position = ui->setPoint_lineEdit->text().toFloat();
    QString setpoint = "Hello";
    qDebug() << setpoint;
    /*Create raw frame to transmit*/
    frame_data_motor.write_data.clear();
    frame_data_motor.write_data.append(mode);
    frame_data_motor.write_data.append(reinterpret_cast<char *>(&set_point_position),sizeof(set_point_position));
    /*create frame that needed to STM32 by frame data layer*/
    uint8_t length_frame_to_STM32 = frame_data_motor.create_frame_data(reinterpret_cast<uint8_t *>(frame_data_motor.write_data.data()),frame_data_motor.write_data.size(),frame_data_motor.frame_data_tx);
    qDebug() << frame_data_motor.write_data;
    qDebug() << "----------------------------------";
    qDebug() << length_frame_to_STM32;
    qDebug() << "----------------------------------";
    for (int i = 0; i < length_frame_to_STM32; i++)
    {
        qDebug() << frame_data_motor.frame_data_tx[i];
    }
    QByteArray frame_to_STM32 = QByteArray(reinterpret_cast<char *>(frame_data_motor.frame_data_tx),length_frame_to_STM32);
    /*transmit to STM32*/
    if (com_serial.isOpen())
    {
        show_notice("---------------------------",Qt::black);
        show_notice("Setting position control mode",Qt::black);
        show_notice(setpoint,Qt::black);
        show_notice("Data is transmitted",Qt::black);
        com_serial.write(frame_to_STM32);
        is_select_mode = 1;
    }else
    {
        show_notice("---------------------------",Qt::black);
        show_notice("Don't set position control mode",Qt::red);
        show_notice("Data isn't transmitted",Qt::red);
    }
}


void MainWindow::on_velocity_mode_btn_clicked()
{
    /*clear buffer for transmitting frame data*/
    frame_data_motor.clear_frame_tx();
    /*start*/
    char mode = 0x03;
    float set_point_velocity = ui->setPoint_lineEdit->text().toFloat();
    /*Create raw frame to transmit*/
    frame_data_motor.write_data.clear();
    frame_data_motor.write_data.append(mode);
    frame_data_motor.write_data.append(reinterpret_cast<char *>(&set_point_velocity),sizeof(set_point_velocity));
    /*create frame that needed to STM32 by frame data layer*/
    uint8_t length_frame_to_STM32 = frame_data_motor.create_frame_data(reinterpret_cast<uint8_t *>(frame_data_motor.write_data.data()),frame_data_motor.write_data.size(),frame_data_motor.frame_data_tx);
    qDebug() << frame_data_motor.write_data;
    qDebug() << "----------------------------------";
    qDebug() << length_frame_to_STM32;
    qDebug() << "----------------------------------";
    for (int i = 0; i < length_frame_to_STM32; i++)
    {
        qDebug() << frame_data_motor.frame_data_tx[i];
    }
    QByteArray frame_to_STM32 = QByteArray(reinterpret_cast<char *>(frame_data_motor.frame_data_tx),length_frame_to_STM32);
    /*transmit to STM32*/
    if (com_serial.isOpen())
    {
        show_notice("---------------------------",Qt::black);
        show_notice("Setting velocity control mode",Qt::black);
        show_notice("Data is transmitted",Qt::black);
        com_serial.write(frame_to_STM32);
        is_select_mode = 1;
    }else
    {
        show_notice("---------------------------",Qt::black);
        show_notice("Don't set velocity control mode",Qt::red);
        show_notice("Data isn't transmitted",Qt::red);
    }
}


void MainWindow::on_run_btn_clicked()
{
    if ((is_send_pid == 1) && (is_select_mode == 1))
    {
    /*clear buffer for transmitting frame data*/
    frame_data_motor.clear_frame_tx();
    /*start*/
    char mode = 0x07;
    /*Create raw frame to transmit*/
    frame_data_motor.write_data.clear();
    frame_data_motor.write_data.append(mode);
    /*create frame that needed to STM32 by frame data layer*/
    uint8_t length_frame_to_STM32 = frame_data_motor.create_frame_data(reinterpret_cast<uint8_t *>(frame_data_motor.write_data.data()),frame_data_motor.write_data.size(),frame_data_motor.frame_data_tx);
    qDebug() << frame_data_motor.write_data;
    qDebug() << "----------------------------------";
    qDebug() << length_frame_to_STM32;
    qDebug() << "----------------------------------";
    for (int i = 0; i < length_frame_to_STM32; i++)
    {
        qDebug() << frame_data_motor.frame_data_tx[i];
    }
    QByteArray frame_to_STM32 = QByteArray(reinterpret_cast<char *>(frame_data_motor.frame_data_tx),length_frame_to_STM32);
    /*transmit to STM32*/
    if (com_serial.isOpen())
    {
        show_notice("---------------------------",Qt::black);
        show_notice("Run motor",Qt::black);
        show_notice("Data is transmitted",Qt::black);
        com_serial.write(frame_to_STM32);
    }else
    {
        show_notice("---------------------------",Qt::black);
        show_notice("Don't run motor",Qt::red);
        show_notice("Data isn't transmitted",Qt::red);
    }
    }else
    {
        QMessageBox::warning(this,"Warning","You have to select mode and send PID params before RUN motor!");
    }
}


void MainWindow::on_stop_btn_clicked()
{
    /*clear buffer for transmitting frame data*/
    frame_data_motor.clear_frame_tx();
    /*start*/
    char mode = 0x09;
    /*Create raw frame to transmit*/
    frame_data_motor.write_data.clear();
    frame_data_motor.write_data.append(mode);
    /*create frame that needed to STM32 by frame data layer*/
    uint8_t length_frame_to_STM32 = frame_data_motor.create_frame_data(reinterpret_cast<uint8_t *>(frame_data_motor.write_data.data()),frame_data_motor.write_data.size(),frame_data_motor.frame_data_tx);
    qDebug() << frame_data_motor.write_data;
    qDebug() << "----------------------------------";
    qDebug() << length_frame_to_STM32;
    qDebug() << "----------------------------------";
    for (int i = 0; i < length_frame_to_STM32; i++)
    {
        qDebug() << frame_data_motor.frame_data_tx[i];
    }
    QByteArray frame_to_STM32 = QByteArray(reinterpret_cast<char *>(frame_data_motor.frame_data_tx),length_frame_to_STM32);
    /*transmit to STM32*/
    if (com_serial.isOpen())
    {
        show_notice("---------------------------",Qt::black);
        show_notice("Stop motor",Qt::black);
        show_notice("Data is transmitted",Qt::black);
        com_serial.write(frame_to_STM32);
    }else
    {
        show_notice("---------------------------",Qt::black);
        show_notice("Don't stop motor",Qt::red);
        show_notice("Data isn't transmitted",Qt::red);
    }
}


void MainWindow::on_reset_btn_clicked()
{
    /*clear buffer for transmitting frame data*/
    frame_data_motor.clear_frame_tx();
    /*start*/
    char mode = 0x15;
    /*Create raw frame to transmit*/
    frame_data_motor.write_data.clear();
    frame_data_motor.write_data.append(mode);
    /*create frame that needed to STM32 by frame data layer*/
    uint8_t length_frame_to_STM32 = frame_data_motor.create_frame_data(reinterpret_cast<uint8_t *>(frame_data_motor.write_data.data()),frame_data_motor.write_data.size(),frame_data_motor.frame_data_tx);
    qDebug() << frame_data_motor.write_data;
    qDebug() << "----------------------------------";
    qDebug() << length_frame_to_STM32;
    qDebug() << "----------------------------------";
    for (int i = 0; i < length_frame_to_STM32; i++)
    {
        qDebug() << frame_data_motor.frame_data_tx[i];
    }
    QByteArray frame_to_STM32 = QByteArray(reinterpret_cast<char *>(frame_data_motor.frame_data_tx),length_frame_to_STM32);
    /*transmit to STM32*/
    if (com_serial.isOpen())
    {
        show_notice("---------------------------",Qt::black);
        show_notice("Reset motor",Qt::black);
        show_notice("Data is transmitted",Qt::black);
        com_serial.write(frame_to_STM32);
        is_select_mode = 0;
        is_send_pid = 0;
    }else
    {
        show_notice("---------------------------",Qt::black);
        show_notice("Don't reset motor",Qt::red);
        show_notice("Data isn't transmitted",Qt::red);
    }
}

