QT       += core gui serialport network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += inc/
VPATH += src/

SOURCES += \
    src/frame_data.cpp \
    main.cpp \
    src/crc16.cpp \
    src/mainwindow.cpp \
    src/qcustomplot.cpp

HEADERS += \
    inc/frame_data.h \
    inc/crc16.h \
    inc/mainwindow.h \
    inc/qcustomplot.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
