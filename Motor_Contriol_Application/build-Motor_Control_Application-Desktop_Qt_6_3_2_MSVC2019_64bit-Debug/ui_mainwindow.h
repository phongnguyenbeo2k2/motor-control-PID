/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAAk;
    QWidget *centralwidget;
    QFrame *frame;
    QPushButton *send_pid_btn;
    QLineEdit *lineEdit;
    QLabel *label_4;
    QLabel *label_3;
    QLineEdit *lineEdit_3;
    QLabel *Kp_label;
    QLineEdit *lineEdit_2;
    QLabel *PID_label;
    QFrame *frame_2;
    QComboBox *Com_comboBox;
    QComboBox *Baud_rate_comboBox;
    QPushButton *connect_btn;
    QPushButton *refresh_btn;
    QLabel *PID_label_2;
    QLabel *PID_label_3;
    QLabel *PID_label_4;
    QFrame *frame_3;
    QPushButton *position_mode_btn;
    QPushButton *velocity_mode_btn;
    QLabel *PID_label_5;
    QTextEdit *textEdit;
    QLabel *label;
    QFrame *frame_4;
    QPushButton *run_btn;
    QPushButton *reset_btn;
    QPushButton *stop_btn;
    QLabel *PID_label_6;
    QFrame *frame_6;
    QTextEdit *notification_textEdit;
    QPushButton *clear_notice_table_btn;
    QLabel *label_2;
    QFrame *frame_5;
    QTextEdit *received_data_textEdit;
    QPushButton *clear_received_data_tabel_btn;
    QLabel *label_5;
    QTabWidget *tabWidget;
    QWidget *tab;
    QCustomPlot *graph;
    QWidget *tab_2;
    QStatusBar *statusbar;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1540, 820);
        actionAAk = new QAction(MainWindow);
        actionAAk->setObjectName(QString::fromUtf8("actionAAk"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(10, 570, 371, 201));
        QFont font;
        font.setUnderline(false);
        frame->setFont(font);
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);
        frame->setLineWidth(2);
        frame->setMidLineWidth(0);
        send_pid_btn = new QPushButton(frame);
        send_pid_btn->setObjectName(QString::fromUtf8("send_pid_btn"));
        send_pid_btn->setGeometry(QRect(260, 60, 80, 31));
        lineEdit = new QLineEdit(frame);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(100, 60, 113, 24));
        label_4 = new QLabel(frame);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(40, 160, 49, 16));
        label_4->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(frame);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(40, 110, 49, 16));
        label_3->setAlignment(Qt::AlignCenter);
        lineEdit_3 = new QLineEdit(frame);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(100, 160, 113, 24));
        Kp_label = new QLabel(frame);
        Kp_label->setObjectName(QString::fromUtf8("Kp_label"));
        Kp_label->setGeometry(QRect(40, 60, 49, 16));
        Kp_label->setAlignment(Qt::AlignCenter);
        lineEdit_2 = new QLineEdit(frame);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(100, 110, 113, 24));
        PID_label = new QLabel(frame);
        PID_label->setObjectName(QString::fromUtf8("PID_label"));
        PID_label->setGeometry(QRect(20, 10, 111, 16));
        PID_label->setAlignment(Qt::AlignCenter);
        frame_2 = new QFrame(centralwidget);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setGeometry(QRect(410, 570, 371, 201));
        frame_2->setFrameShape(QFrame::Panel);
        frame_2->setFrameShadow(QFrame::Sunken);
        frame_2->setLineWidth(2);
        Com_comboBox = new QComboBox(frame_2);
        Com_comboBox->addItem(QString());
        Com_comboBox->setObjectName(QString::fromUtf8("Com_comboBox"));
        Com_comboBox->setGeometry(QRect(80, 60, 101, 24));
        Baud_rate_comboBox = new QComboBox(frame_2);
        Baud_rate_comboBox->addItem(QString());
        Baud_rate_comboBox->setObjectName(QString::fromUtf8("Baud_rate_comboBox"));
        Baud_rate_comboBox->setGeometry(QRect(80, 110, 101, 24));
        connect_btn = new QPushButton(frame_2);
        connect_btn->setObjectName(QString::fromUtf8("connect_btn"));
        connect_btn->setGeometry(QRect(230, 50, 111, 41));
        QFont font1;
        font1.setPointSize(11);
        font1.setBold(true);
        connect_btn->setFont(font1);
        connect_btn->setStyleSheet(QString::fromUtf8("color: rgb(0, 255, 0);"));
        refresh_btn = new QPushButton(frame_2);
        refresh_btn->setObjectName(QString::fromUtf8("refresh_btn"));
        refresh_btn->setGeometry(QRect(230, 110, 111, 41));
        PID_label_2 = new QLabel(frame_2);
        PID_label_2->setObjectName(QString::fromUtf8("PID_label_2"));
        PID_label_2->setGeometry(QRect(30, 10, 111, 16));
        PID_label_2->setAlignment(Qt::AlignCenter);
        PID_label_3 = new QLabel(frame_2);
        PID_label_3->setObjectName(QString::fromUtf8("PID_label_3"));
        PID_label_3->setGeometry(QRect(-20, 60, 111, 16));
        PID_label_3->setAlignment(Qt::AlignCenter);
        PID_label_4 = new QLabel(frame_2);
        PID_label_4->setObjectName(QString::fromUtf8("PID_label_4"));
        PID_label_4->setGeometry(QRect(-10, 110, 111, 16));
        PID_label_4->setAlignment(Qt::AlignCenter);
        frame_3 = new QFrame(centralwidget);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setGeometry(QRect(820, 570, 371, 201));
        frame_3->setFrameShape(QFrame::Panel);
        frame_3->setFrameShadow(QFrame::Sunken);
        frame_3->setLineWidth(2);
        position_mode_btn = new QPushButton(frame_3);
        position_mode_btn->setObjectName(QString::fromUtf8("position_mode_btn"));
        position_mode_btn->setGeometry(QRect(220, 30, 121, 61));
        velocity_mode_btn = new QPushButton(frame_3);
        velocity_mode_btn->setObjectName(QString::fromUtf8("velocity_mode_btn"));
        velocity_mode_btn->setGeometry(QRect(220, 120, 121, 61));
        PID_label_5 = new QLabel(frame_3);
        PID_label_5->setObjectName(QString::fromUtf8("PID_label_5"));
        PID_label_5->setGeometry(QRect(20, 10, 111, 16));
        PID_label_5->setAlignment(Qt::AlignCenter);
        textEdit = new QTextEdit(frame_3);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(50, 90, 104, 31));
        label = new QLabel(frame_3);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(50, 70, 91, 16));
        label->setAlignment(Qt::AlignCenter);
        frame_4 = new QFrame(centralwidget);
        frame_4->setObjectName(QString::fromUtf8("frame_4"));
        frame_4->setGeometry(QRect(1210, 570, 311, 201));
        frame_4->setFrameShape(QFrame::Panel);
        frame_4->setFrameShadow(QFrame::Sunken);
        frame_4->setLineWidth(2);
        run_btn = new QPushButton(frame_4);
        run_btn->setObjectName(QString::fromUtf8("run_btn"));
        run_btn->setGeometry(QRect(30, 50, 111, 61));
        reset_btn = new QPushButton(frame_4);
        reset_btn->setObjectName(QString::fromUtf8("reset_btn"));
        reset_btn->setGeometry(QRect(180, 50, 111, 61));
        stop_btn = new QPushButton(frame_4);
        stop_btn->setObjectName(QString::fromUtf8("stop_btn"));
        stop_btn->setGeometry(QRect(110, 130, 111, 61));
        PID_label_6 = new QLabel(frame_4);
        PID_label_6->setObjectName(QString::fromUtf8("PID_label_6"));
        PID_label_6->setGeometry(QRect(20, 10, 111, 16));
        PID_label_6->setAlignment(Qt::AlignCenter);
        frame_6 = new QFrame(centralwidget);
        frame_6->setObjectName(QString::fromUtf8("frame_6"));
        frame_6->setGeometry(QRect(1210, 70, 301, 361));
        frame_6->setFrameShape(QFrame::StyledPanel);
        frame_6->setFrameShadow(QFrame::Raised);
        frame_6->setLineWidth(2);
        notification_textEdit = new QTextEdit(frame_6);
        notification_textEdit->setObjectName(QString::fromUtf8("notification_textEdit"));
        notification_textEdit->setGeometry(QRect(40, 30, 241, 261));
        clear_notice_table_btn = new QPushButton(frame_6);
        clear_notice_table_btn->setObjectName(QString::fromUtf8("clear_notice_table_btn"));
        clear_notice_table_btn->setGeometry(QRect(200, 310, 80, 24));
        label_2 = new QLabel(frame_6);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 10, 131, 16));
        label_2->setAlignment(Qt::AlignCenter);
        frame_5 = new QFrame(centralwidget);
        frame_5->setObjectName(QString::fromUtf8("frame_5"));
        frame_5->setGeometry(QRect(880, 70, 301, 361));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Raised);
        received_data_textEdit = new QTextEdit(frame_5);
        received_data_textEdit->setObjectName(QString::fromUtf8("received_data_textEdit"));
        received_data_textEdit->setGeometry(QRect(40, 30, 241, 261));
        clear_received_data_tabel_btn = new QPushButton(frame_5);
        clear_received_data_tabel_btn->setObjectName(QString::fromUtf8("clear_received_data_tabel_btn"));
        clear_received_data_tabel_btn->setGeometry(QRect(190, 310, 80, 24));
        label_5 = new QLabel(frame_5);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(20, 10, 131, 16));
        label_5->setAlignment(Qt::AlignCenter);
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(10, 30, 811, 511));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        graph = new QCustomPlot(tab);
        graph->setObjectName(QString::fromUtf8("graph"));
        graph->setGeometry(QRect(30, 20, 751, 441));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tabWidget->addTab(tab_2, QString());
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1540, 21));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionAAk->setText(QCoreApplication::translate("MainWindow", "AAk", nullptr));
        send_pid_btn->setText(QCoreApplication::translate("MainWindow", "SEND PID", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Kd", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Ki", nullptr));
        Kp_label->setText(QCoreApplication::translate("MainWindow", "Kp", nullptr));
        PID_label->setText(QCoreApplication::translate("MainWindow", "PID PARAMETERS", nullptr));
        Com_comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "SELECT COM", nullptr));

        Baud_rate_comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "BAUD RATE", nullptr));

        connect_btn->setText(QCoreApplication::translate("MainWindow", "CONNECT", nullptr));
        refresh_btn->setText(QCoreApplication::translate("MainWindow", "REFRESH", nullptr));
        PID_label_2->setText(QCoreApplication::translate("MainWindow", "SERIAL ", nullptr));
        PID_label_3->setText(QCoreApplication::translate("MainWindow", "COM", nullptr));
        PID_label_4->setText(QCoreApplication::translate("MainWindow", "Baund rate", nullptr));
        position_mode_btn->setText(QCoreApplication::translate("MainWindow", "POSITION", nullptr));
        velocity_mode_btn->setText(QCoreApplication::translate("MainWindow", "VELOCITY", nullptr));
        PID_label_5->setText(QCoreApplication::translate("MainWindow", "MODE CONTROL", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Set point", nullptr));
        run_btn->setText(QCoreApplication::translate("MainWindow", "RUN", nullptr));
        reset_btn->setText(QCoreApplication::translate("MainWindow", "RESET", nullptr));
        stop_btn->setText(QCoreApplication::translate("MainWindow", "STOP", nullptr));
        PID_label_6->setText(QCoreApplication::translate("MainWindow", "CONTROL MOTOR", nullptr));
        clear_notice_table_btn->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "NOTFICATION", nullptr));
        clear_received_data_tabel_btn->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "RECEIVED DATA", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "Tab 1", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Tab 2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
