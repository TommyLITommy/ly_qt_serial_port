#-------------------------------------------------
#
# Project created by QtCreator 2017-07-12T19:45:41
#
#-------------------------------------------------

QT       += core gui charts
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Qt-SerialPort
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        blecentral.cpp \
        childwindow.cpp \
        lcd.cpp \
        lcddisplay.cpp \
        mainwindow.cpp \
        mythread.cpp \
        nine_axis_visualization.cpp \
        protocol.cpp \
        qcustomplot.cpp \
        six_axis_visualization.cpp \
        three_axis_visualization.cpp

HEADERS  += mainwindow.h \
    analog_clock.h \
    bind_success.h \
    blecentral.h \
    blood_pressure.h \
    car_bind.h \
    car_tire_pressure..h \
    charging.h \
    childwindow.h \
    clock_01.h \
    heart_rate.h \
    incoming_call.h \
    is_binding.h \
    lcd.h \
    lcddisplay.h \
    motor_bind.h \
    motor_tire_pressure.h \
    mythread.h \
    nine_axis_visualization.h \
    protocol.h \
    qcustomplot.h \
    qq.h \
    select.h \
    setup.h \
    six_axis_visualization.h \
    suv_bind.h \
    suv_tire_pressure.h \
    text.h \
    three_axis_visualization.h \
    tire_pressure.h \
    type.h \
    wechat.h

FORMS    += mainwindow.ui \
    blecentral.ui \
    childwindow.ui \
    lcddisplay.ui \
    nine_axis_visualization.ui \
    six_axis_visualization.ui

#Change logo
RC_ICONS += com.ico
