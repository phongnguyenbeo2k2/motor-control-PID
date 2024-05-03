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
uint8_t is_select_velcity_mode = 0;
uint8_t is_select_position_mode = 0;
uint8_t is_send_pid = 0;
uint8_t is_connect = 0;
uint8_t is_start = 0;
uint8_t is_stop = 0;
uint8_t pressed_plot_realtime = 0, pressed_plot_response = 0;
float setpoint_value;
uint32_t countRealtime = 0;
static int checkSizeDataVector, checkSizeMotorData;
uint8_t checkFirst = 0, checkContinue = 0;
double value_motor;
uint8_t checkConRead = 0;
uint8_t read_data_click = 0;
/*--------------------------*/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer_receive = new QTimer(this);
    timer_updategraph = new QTimer(this);
    timer_plotrealtime = new QTimer(this);
    init_main_window();
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
        com_str.append(com_list.at(i).portName());
    }
    ui->Com_comboBox->addItems(com_str);
    /*find all available baud rate that computer can use for serial protocol*/
    QList<qint32> baud_rate_list = com_info.standardBaudRates();
    QList<QString> baud_rate_str;
    for (int i = 0; i < baud_rate_list.size(); i++)
    {
        baud_rate_str.append(QString::number(baud_rate_list.at(i)));
    }
    ui->Baud_rate_comboBox->addItems(baud_rate_str);

    /*Initialize plot graph*/
    ui->plot_response_graph->addGraph();
    ui->plot_response_graph->graph(0)->setPen(QPen(Qt::blue, 2)); /*this graph is for ploting response of motor*/
    ui->plot_response_graph->xAxis->setRange(0, 20);
    ui->plot_response_graph->yAxis->setRange(-100,100);
    ui->plot_response_graph->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables); /*set feature interaction with plot graph zoom out zoom in graph*/
    ui->plot_response_graph->addGraph();
    ui->plot_response_graph->graph(1)->setPen(QPen(Qt::red,2));
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

void MainWindow::test_plot_graph()
{
    QVector<double> x = {1,2,3,4,5,6,7,8,9}, y = {4,5,6,3,2,7,3,8,9};
    ui->plot_response_graph->graph(0)->setData(x,y);
    ui->plot_response_graph->rescaleAxes(); /*tự động scales lại để hiển thị rõ đồ thị*/
    /*replot and update is come together*/
    ui->plot_response_graph->replot();
    ui->plot_response_graph->update();
}

void MainWindow::show_notice(const QString mess, const Qt::GlobalColor textColor)
{
    ui->notification_textEdit->setTextColor(textColor);
    ui->notification_textEdit->append(mess);
    ui->notification_textEdit->setTextColor(Qt::black);
}

void MainWindow::show_received_data(const QString mess, const Qt::GlobalColor textColor)
{
    ui->received_data_textEdit->setTextColor(textColor);
    ui->received_data_textEdit->append(mess);
}

void MainWindow::received_data_from_STM32()
{
    qDebug() << "received_data_from_STM32";
    if (com_serial.isOpen() && com_serial.bytesAvailable())
    {

//    qDebug() << "received_data_from_STM32 1";
        frame_data_motor.read_data.clear();
//    qDebug() << "received_data_from_STM32 1.1";
        frame_data_motor.read_data = com_serial.readAll();
//    qDebug() << "received_data_from_STM32 1.2";/**/
        int8_t check_frame = frame_data_motor.decode_received_frame_data(reinterpret_cast<uint8_t *>(frame_data_motor.read_data.data()),frame_data_motor.read_data.size(),frame_data_motor.decoded_data,&frame_data_motor.length_decded_data);
//    qDebug() << "received_data_from_STM32 1.3";
        if (checkConRead == 1)
        {
//    qDebug() << "received_data_from_STM32 2";
            if (is_select_velcity_mode == 1)
{
            if (frame_data_motor.decoded_data[0] == 0x0F && check_frame == TRUE_FRAME)
            {
/*old method*/
                quint64 current_time = timer_plot.elapsed() + preTime;
                double change_current_time = (double)(current_time) / 1000;
//                if(pressed_plot_realtime == 1)
//                {
//                    while (timeX.size() >= 800)
//                    {
//                        timeX.removeFirst();
//                    }
//                }
//                timeX.append(change_current_time);
                preTime = current_time;
//                if (change_current_time >= 15)
//                {
                /*old method*/
//                    timer_updategraph->stop();
//                    checkConRead = 0;
//                }
                timer_plot.start();
                qDebug() << "received_data_from_STM32 3";
                float velocity = (*(float *)(frame_data_motor.decoded_data + 1));
                QString data = QString::number(velocity);
                show_notice("Velocity is true",Qt::black);
                QString received_data_str = QString("Velocity is %1").arg(velocity);
                show_received_data(received_data_str,Qt::blue);
    /*try new method*/
                if (pressed_plot_realtime == 1)
                {
                    while(motor_data_Y.size() >= 250)
                    {
                        /*delete data*/
                        qDebug() << "delete data";
                        motor_data_Y.removeFirst();
                        timeX.removeFirst();
                        setpoint_Y.removeFirst();
                    }
                }
//                motor_data.append(data);
                motor_data_Y.append(velocity);
                setpoint_Y.append(setpoint_value);
                timeX.append(change_current_time);
            }else if (is_select_velcity_mode == 1)
            {
                show_notice("Received velocity is wrong",Qt::red);
            }
 }
            if (is_select_position_mode == 1)
 {
            if (frame_data_motor.decoded_data[0] == 0x11 && check_frame == TRUE_FRAME)
            {
                quint64 current_time = timer_plot.elapsed() + preTime;
                double change_current_time = (double)(current_time) / 1000;
                //                if(pressed_plot_realtime == 1)
                //                {
                //                    while (timeX.size() >= 800)
                //                    {
                //                        timeX.removeFirst();
                //                    }
                //                }
                //                timeX.append(change_current_time);
                preTime = current_time;
                //                if (change_current_time >= 15)
                //                {
                /*old method*/
                //                    timer_updategraph->stop();
                //                    checkConRead = 0;
                //                }
                timer_plot.start();
                qDebug() << "received_data_from_STM32 3";
                float position = (*(float *)(frame_data_motor.decoded_data + 1));
                QString data = QString::number(position);
                show_notice("position is true",Qt::black);
                QString received_data_str = QString("position is %1 degrees").arg(position);
                show_received_data(received_data_str,Qt::blue);
                /*try new method*/
                if (pressed_plot_realtime == 1)
                {
                    while(motor_data_Y.size() >= 180)
                    {
                        /*delete data*/
                        qDebug() << "delete data";
                        motor_data_Y.removeFirst();
                        timeX.removeFirst();
                        setpoint_Y.removeFirst();
                    }
                }
                //                motor_data.append(data);
                motor_data_Y.append(position);
                setpoint_Y.append(setpoint_value);
                timeX.append(change_current_time);
            }else if (is_select_velcity_mode == 1)
            {
                show_notice("position velocity is wrong",Qt::red);
            }
}
        }
        if (is_send_pid == 0 || is_select_position_mode == 0 || is_select_velcity_mode == 0)
        {
            if (frame_data_motor.decoded_data[0] == 0x02 && check_frame == TRUE_FRAME)
            {
                show_notice("Setting wrong, frame true",Qt::red);
                if ((is_select_velcity_mode == 1 || is_select_position_mode == 1) && (is_send_pid == 0))
                {
                    show_notice("Setting mode fail, frame true",Qt::red);
                    is_select_velcity_mode = 0;
                    is_select_position_mode = 0;
                }else if ((is_select_velcity_mode == 1 || is_select_position_mode == 1) && (is_send_pid == 1))
                {
                    show_notice("Setting pid fail, frame true",Qt::red);
                    is_send_pid = 0;
                }
            }
        }
    }
}

void MainWindow::plot_response()
{
    qDebug()<< "Data size" << timeX.size();
    qDebug() << "Data size datapoint " << motor_data_Y.size();
    qDebug() << "Data size setpoint" << setpoint_Y.size();
//    if (motor_data_Y.size() > 1000)
//    {
//        timer_updategraph->stop();
//        checkConRead = 0;
//    }
    ui->plot_response_graph->graph(0)->addData(timeX,motor_data_Y);
    ui->plot_response_graph->graph(1)->addData(timeX, setpoint_Y);
    ui->plot_response_graph->rescaleAxes(true);
    ui->plot_response_graph->replot();
    ui->plot_response_graph->update();
    /*try new method */
//    qDebug() << "plot_response";
//    static QVector<double> response_x_axis;
//    if (pressed_plot_response == 1)
//    {
//        pressed_plot_realtime = 0;
//        if (checkFirst == 0)
//        {
//        checkFirst = 1;
//        checkContinue = 1;
//        for (int i = 0; i < motor_data.size(); i++)
//            {
//            value_motor = motor_data[i].toDouble();
//            dataPoints.append(value_motor);
//            }
//        checkSizeMotorData = motor_data.size();
//        dataPoints_vec = QVector<double>::fromList(dataPoints);
//        response_x_axis.resize(dataPoints_vec.size());
//        checkSizeDataVector = dataPoints_vec.size();
//        for (int i = 0; i < response_x_axis.size(); i++)
//        {
//            response_x_axis[i] = i;
//        }

//        }

//        if (checkContinue == 1)
//        {
//            for (int i = checkSizeMotorData; i < motor_data.size(); i++)
//            {
//                value_motor = motor_data[i].toDouble();
//                dataPoints.append(value_motor);
//            }
//            checkSizeMotorData = motor_data.size();
//            dataPoints_vec = QVector<double>::fromList(dataPoints);
//            response_x_axis.resize(dataPoints_vec.size());
//            for (int i = checkSizeDataVector; i < dataPoints_vec.size(); i++)
//            {
//                response_x_axis[i] = i;
//                if (dataPoints_vec.size() > 1000)
//                {
//                pressed_plot_response = 0;
//                checkConRead = 0;
//                timer_updategraph->stop();
//                }
//            }
//            checkSizeDataVector = dataPoints_vec.size();
//        }
//        ui->plot_response_graph->graph(0)->addData(response_x_axis,dataPoints_vec);
//        ui->plot_response_graph->graph(1)->addData(response_x_axis,setPoint_vec);

//        ui->plot_response_graph->rescaleAxes();
//        ui->plot_response_graph->replot();
//        ui->plot_response_graph->update();
//    }
}

void MainWindow::plot_real_time_graph()
{
    qDebug()<< "Data size" << timeX.size();
    qDebug() << "Data size datapoint " << motor_data_Y.size();
    qDebug() << "Data size setpoint" << setpoint_Y.size();
    ui->realtime_plot_graph->graph(0)->setData(timeX,motor_data_Y);
    ui->realtime_plot_graph->graph(1)->setData(timeX,setpoint_Y);
    if (is_select_velcity_mode == 1)
    { /*velocity*/
    ui->realtime_plot_graph->xAxis->rescale();
    ui->realtime_plot_graph->yAxis->setRange(0,50);
    }else
    { /*position*/
    ui->realtime_plot_graph->xAxis->rescale();
    ui->realtime_plot_graph->yAxis->setRange(-100,1000);
    }
//    ui->realtime_plot_graph->rescaleAxes();
    ui->realtime_plot_graph->replot();
    ui->realtime_plot_graph->update();
    ui->realtime_plot_graph->graph(0)->data()->clear();
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

            ui->connect_btn->setText("DISCONNECT");
            ui->connect_btn->setStyleSheet("QPushButton {color: rgb(255, 0, 0);}");
            is_connect = 1;
            /*set timer for receive data*/
//            timer_receive->setTimerType(Qt::PreciseTimer); /*higher priority*/
//            connect(timer_receive,SIGNAL(timeout()),this,SLOT(received_data_from_STM32()));
//            timer_receive->start(20);

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
    if ((is_select_position_mode == 1) || (is_select_velcity_mode == 1))
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
    qDebug() << frame_data_motor.write_data;
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
    int check_frame = frame_data_motor.decode_received_frame_data(frame_data_motor.frame_data_tx,length_frame_to_STM32,frame_data_motor.decoded_data,&frame_data_motor.length_decded_data);
    float test_velocity = *((float *)(frame_data_motor.decoded_data + 1));
    qDebug() << "---------------------------";
    qDebug() << test_velocity;
    for (int i = 0; i < frame_data_motor.length_decded_data; i++)
    {
        qDebug() << "123";
        qDebug() << frame_data_motor.decoded_data[i];
    }
    qDebug() << check_frame;
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
    if (is_connect == 1)
    {
    frame_data_motor.clear_frame_tx();
    char mode = 0x05;
    float set_point_position = ui->setPoint_lineEdit->text().toFloat();
    setpoint_value = set_point_position;
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
        show_notice("Data is transmitted",Qt::black);
        com_serial.write(frame_to_STM32);
        is_select_position_mode = 1;
        ui->plot_response_graph->xAxis->setLabel("Time (s)");
        ui->plot_response_graph->yAxis->setLabel("Position (degrees)");
    }else
    {
        show_notice("---------------------------",Qt::black);
        show_notice("Don't set position control mode",Qt::red);
        show_notice("Data isn't transmitted",Qt::red);
    }
    }else
    {
        QMessageBox::warning(this,"Warning","You have to connect to STM32 before selecting mode for motor!");
    }
}


void MainWindow::on_velocity_mode_btn_clicked()
{
    if (is_connect == 1)
    {
    /*clear buffer for transmitting frame data*/
    frame_data_motor.clear_frame_tx();
    /*start*/
    char mode = 0x03;
    float set_point_velocity = ui->setPoint_lineEdit->text().toFloat();
    setpoint_value = set_point_velocity;
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
        is_select_velcity_mode = 1;
        ui->plot_response_graph->xAxis->setLabel("Time (s)");
        ui->plot_response_graph->yAxis->setLabel("Velocity (rpm)");
    }else
    {
        show_notice("---------------------------",Qt::black);
        show_notice("Don't set velocity control mode",Qt::red);
        show_notice("Data isn't transmitted",Qt::red);
    }
    }else
    {
        QMessageBox::warning(this,"Warning","You have to connect to STM32 before selecting mode for motor!");
    }
}


void MainWindow::on_run_btn_clicked()
{
    if ((is_send_pid == 1) && ((is_select_position_mode == 1) || (is_select_velcity_mode == 1)))
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
    QByteArray frame_to_STM32 = QByteArray(reinterpret_cast<char *>(frame_data_motor.frame_data_tx),length_frame_to_STM32);
    /*transmit to STM32*/
    if (com_serial.isOpen())
    {
        show_notice("---------------------------",Qt::black);
        show_notice("Run motor",Qt::black);
        show_notice("Data is transmitted",Qt::black);
        com_serial.write(frame_to_STM32);
        is_start = 1;
        is_stop = 0;
        checkConRead = 1;
        motor_data_Y.append(0.0);
        timeX.append(0.0);
        timer_plot.start();
        preTime = 0;
//        timer_updategraph->setTimerType(Qt::CoarseTimer);
//        timer_updategraph->start(22);

        //        setPoint_vec.fill(setpoint_value);
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
        is_start = 0;
        is_stop = 1;
//        timer_receive->stop();
        timer_plot.elapsed();
        qDebug() <<"Stop" << timeX.size();
        qDebug() <<"Stop" << motor_data_Y.size();
        timeX.clear();
        motor_data_Y.clear();
        setpoint_Y.clear();
        timer_updategraph->stop();
        timer_plotrealtime->stop();
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
        is_select_position_mode = 0;
        is_select_velcity_mode = 0;
        is_send_pid = 0;
        is_start = 0;
        is_stop = 0;
        setpoint_value = 0;
        checkFirst = 0;
        checkContinue = 0;
        motor_data.clear();
        dataPoints.clear();
        checkConRead = 0;
        checkSizeDataVector = 0;
        checkSizeMotorData = 0;
        timeX.clear();
        motor_data_Y.clear();
        setpoint_Y.clear();
        qDebug() << "size of timeX "<< timeX.size();
        qDebug() << "size of motor_data_Y" <<motor_data_Y.size();
/*new method*/
        pressed_plot_realtime = 0;
    }else
    {
        show_notice("---------------------------",Qt::black);
        show_notice("Don't reset motor",Qt::red);
        show_notice("Data isn't transmitted",Qt::red);
    }
}


void MainWindow::on_clear_graph_btn_clicked()
{
    ui->plot_response_graph->graph(0)->data()->clear();
    ui->plot_response_graph->graph(1)->data()->clear();
    ui->plot_response_graph->replot();
    ui->plot_response_graph->update();
}


void MainWindow::on_clear_received_data_tabel_btn_clicked()
{
    ui->received_data_textEdit->clear();
}


void MainWindow::on_clear_notice_table_btn_clicked()
{
    ui->notification_textEdit->clear();
}


void MainWindow::on_plot_realtime_graph_btn_clicked()
{
    pressed_plot_realtime = 1;
    ui->realtime_plot_graph->addGraph();
    ui->realtime_plot_graph->graph(0)->setPen(QPen(Qt::blue, 2)); /*this graph is for ploting response of motor*/
    ui->realtime_plot_graph->xAxis->setRange(0, 1000);
    ui->realtime_plot_graph->yAxis->setRange(-100,1000);
    ui->realtime_plot_graph->addGraph();
    ui->realtime_plot_graph->graph(1)->setPen(QPen(Qt::red,2)); /*graph for setpoint*/
    connect(timer_plotrealtime,SIGNAL(timeout()),this,SLOT(plot_real_time_graph()));
    timer_plotrealtime->setTimerType(Qt::CoarseTimer);
    timer_plotrealtime->start(19);
}


void MainWindow::on_clear_realtimegraph_btn_clicked()
{
    ui->realtime_plot_graph->graph(0)->data()->clear();
    ui->realtime_plot_graph->graph(1)->data()->clear();
    ui->realtime_plot_graph->replot();
    ui->realtime_plot_graph->update();
}

void MainWindow::on_clear_response_graph_btn_clicked()
{
    ui->plot_response_graph->graph(0)->data()->clear();
    ui->plot_response_graph->graph(1)->data()->clear();
    ui->plot_response_graph->replot();
    ui->plot_response_graph->update();
}


void MainWindow::on_plot_response_graph_btn_clicked()
{
    connect(timer_updategraph,SIGNAL(timeout()),this,SLOT(plot_response()));
    timer_updategraph->setTimerType(Qt::CoarseTimer);
    timer_updategraph->start(18);
    pressed_plot_response = 1;
}


void MainWindow::on_Read_data_STM_btn_clicked()
{
    if (ui->Read_data_STM_btn->text() == "Read_data")
    {
    timer_receive->setTimerType(Qt::PreciseTimer); /*higher priority*/
    connect(timer_receive,SIGNAL(timeout()),this,SLOT(received_data_from_STM32()));
    timer_receive->start(7);
    ui->Read_data_STM_btn->setText("Stop");
    qDebug() << "1";
    }else
    {
    timer_receive->stop();
    ui->Read_data_STM_btn->setText("Read_data");
    }
}

