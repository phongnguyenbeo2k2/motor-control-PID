/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Motor_Control_Application/inc/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    uint offsetsAndSizes[32];
    char stringdata0[11];
    char stringdata1[17];
    char stringdata2[1];
    char stringdata3[23];
    char stringdata4[12];
    char stringdata5[5];
    char stringdata6[16];
    char stringdata7[10];
    char stringdata8[25];
    char stringdata9[23];
    char stringdata10[24];
    char stringdata11[29];
    char stringdata12[29];
    char stringdata13[19];
    char stringdata14[20];
    char stringdata15[21];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_MainWindow_t::offsetsAndSizes) + ofs), len 
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
        QT_MOC_LITERAL(0, 10),  // "MainWindow"
        QT_MOC_LITERAL(11, 16),  // "init_main_window"
        QT_MOC_LITERAL(28, 0),  // ""
        QT_MOC_LITERAL(29, 22),  // "on_refresh_btn_clicked"
        QT_MOC_LITERAL(52, 11),  // "show_notice"
        QT_MOC_LITERAL(64, 4),  // "mess"
        QT_MOC_LITERAL(69, 15),  // "Qt::GlobalColor"
        QT_MOC_LITERAL(85, 9),  // "textColor"
        QT_MOC_LITERAL(95, 24),  // "received_data_from_STM32"
        QT_MOC_LITERAL(120, 22),  // "on_connect_btn_clicked"
        QT_MOC_LITERAL(143, 23),  // "on_send_pid_btn_clicked"
        QT_MOC_LITERAL(167, 28),  // "on_position_mode_btn_clicked"
        QT_MOC_LITERAL(196, 28),  // "on_velocity_mode_btn_clicked"
        QT_MOC_LITERAL(225, 18),  // "on_run_btn_clicked"
        QT_MOC_LITERAL(244, 19),  // "on_stop_btn_clicked"
        QT_MOC_LITERAL(264, 20)   // "on_reset_btn_clicked"
    },
    "MainWindow",
    "init_main_window",
    "",
    "on_refresh_btn_clicked",
    "show_notice",
    "mess",
    "Qt::GlobalColor",
    "textColor",
    "received_data_from_STM32",
    "on_connect_btn_clicked",
    "on_send_pid_btn_clicked",
    "on_position_mode_btn_clicked",
    "on_velocity_mode_btn_clicked",
    "on_run_btn_clicked",
    "on_stop_btn_clicked",
    "on_reset_btn_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   80,    2, 0x08,    1 /* Private */,
       3,    0,   81,    2, 0x08,    2 /* Private */,
       4,    2,   82,    2, 0x08,    3 /* Private */,
       8,    0,   87,    2, 0x08,    6 /* Private */,
       9,    0,   88,    2, 0x08,    7 /* Private */,
      10,    0,   89,    2, 0x08,    8 /* Private */,
      11,    0,   90,    2, 0x08,    9 /* Private */,
      12,    0,   91,    2, 0x08,   10 /* Private */,
      13,    0,   92,    2, 0x08,   11 /* Private */,
      14,    0,   93,    2, 0x08,   12 /* Private */,
      15,    0,   94,    2, 0x08,   13 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 6,    5,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->init_main_window(); break;
        case 1: _t->on_refresh_btn_clicked(); break;
        case 2: _t->show_notice((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<Qt::GlobalColor>>(_a[2]))); break;
        case 3: _t->received_data_from_STM32(); break;
        case 4: _t->on_connect_btn_clicked(); break;
        case 5: _t->on_send_pid_btn_clicked(); break;
        case 6: _t->on_position_mode_btn_clicked(); break;
        case 7: _t->on_velocity_mode_btn_clicked(); break;
        case 8: _t->on_run_btn_clicked(); break;
        case 9: _t->on_stop_btn_clicked(); break;
        case 10: _t->on_reset_btn_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.offsetsAndSizes,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_MainWindow_t
, QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString, std::false_type>, QtPrivate::TypeAndForceComplete<const Qt::GlobalColor, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
