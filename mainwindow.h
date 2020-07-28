#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <string>
#include <QTextCodec>
#include <QByteArray>
#include <childwindow.h>
#include <QTimer>
#include <six_axis_visualization.h>
#include <nine_axis_visualization.h>
#include <lcddisplay.h>

#include "lcd.h"
#include "protocol.h"
#include "mythread.h"
#include "flash_operation.h"
#include "flash.h"
#include "ble_protocol.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QSerialPort *serial = new QSerialPort;

public slots:
    void on_clearButton_clicked(); // clear
    void on_sendButton_clicked(); // send data
    void on_openButton_clicked(); // open serialport
    void on_pushButton_clicked();
    void on_checkBox_clicked();
    void Read_Data(); // read data
    void timer_timeout_handler();
    void setup_charts();
    void on_pushButton_2_clicked();
    void on_pushButton_5_clicked();
    void on_six_visualization_window_closed();
    void on_pushButton_6_clicked();
    void on_lcd_display_window_closed();
    void on_lcd_picture_id_received(int id);
    void timer2_timeout_handler();
    void on_pushButton_7_clicked();
    void on_flash_operation_closed();
    void on_flash_operation_id_received(int id, QString str, void*);
    void write_flash_timer_timeout_handler();

private:
    Ui::MainWindow *ui;

private:
    static ChildWindow *cw;//Singleton

private:
    lcd *p_lcd;
    protocol *p_protocol;
    mythread *p_thread;
    uint8_t line_color[240 * 2];
    QTimer *timer;
    QTimer *timer2;
    int timer_id;
    flash *p_flash;
    ble_protocol *p_ble_protocol;
    QTimer *write_flash_timer;


private:
    static nine_axis_visualization *nine_axis;
    static six_axis_visualization *six_axis;
    static LcdDisplay *lcd_display;
    //static flash_operation *m_flash_operation;

protected:
    void keyPressEvent (QKeyEvent *e);

signals:
    void sendSerialDataToChild(QString str);
private slots:
    void on_textBrowser_textChanged();

private:
    QByteArray flash_data;
    int send_index;
};

#endif // MAINWINDOW_H
