#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "clock_01.h"
#include "tire_pressure.h"
#include "wechat.h"
#include "blood_pressure.h"
#include "heart_rate.h"
#include "charging.h"
#include "analog_clock.h"
#include "suv_tire_pressure.h"
#include "bind_success.h"
#include "is_binding.h"
#include "car_bind.h"
#include "motor_bind.h"
#include "select.h"
#include "setup.h"
#include "motor_tire_pressure.h"
#include "car_tire_pressure..h"
#include "incoming_call.h"
#include "text.h"
#include "qq.h"
#include "suv_bind.h"
#include <QChartView>
#include <QLineSeries>
#include <QValueAxis>
#include <six_axis_visualization.h>

using namespace QtCharts;

ChildWindow *MainWindow::cw = NULL;
nine_axis_visualization *MainWindow::nine_axis = NULL;
six_axis_visualization *MainWindow::six_axis = NULL;
LcdDisplay *MainWindow::lcd_display = NULL;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //find usable serialport
    QSerialPortInfo serialinfo;
    QList<QSerialPortInfo> infos = serialinfo.availablePorts();

    //QList<QSerialPortInfo> infos = QSerialPortInfo::availablePorts();
    if (infos.empty())
    {
        ui->PortBox->addItem("None");
        infos = serialinfo.availablePorts();
    }
    foreach(QSerialPortInfo info, infos)
    {
        ui->PortBox->addItem(info.portName());
    }

    //setup menu display
    ui->BaudBox->setCurrentIndex(10); // 默认显示第10项
    ui->BitNumBox->setCurrentIndex(3); // 默认显示第3项
    ui->ParityBox->setCurrentIndex(0); // 默认显示第0项
    ui->StopBox->setCurrentIndex(0); // 默认显示第0项

    //turn on sendButton
    ui->sendButton->setEnabled(true);

    qDebug()<<"MainWindow Constructor";

    p_protocol = new protocol(serial);
    p_lcd = new lcd(p_protocol);
    p_thread = new mythread(p_lcd);

    for(uint8_t m = 0; m < 240; m++)
    {
        line_color[2 * m + 0] = 0xF8;
        line_color[2 * m + 1] = 0x00;
    }

#if 1
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timer_timeout_handler()));
    //timer->start(1000);

    timer2 = new QTimer(this);
    //connect(timer, SIGNAL(timeout()), this, SLOT(timer2_timeout_handler()));
#endif
}

MainWindow::~MainWindow()
{
    delete ui;
    qDebug()<<"MainWindow deConstructor";
}

void MainWindow::on_clearButton_clicked()
{
    ui->textBrowser->clear();
    ui->textEdit_2->clear();
    //setup_charts();
}

char convert_char_to_hex(char ch)
{
    if((ch >= '0') && (ch <= '9'))
    {
        return ch - '0';
    }
    else if((ch >= 'A') && (ch <= 'F'))
    {
        return ch - 'A' + 10;
    }
    else if((ch > 'a') && (ch <= 'f'))
    {
        return ch - 'a' + 10;
    }
    else
    {
        return (-1);
    }

}

void string_to_hex_array(QString str, QByteArray &array)//What the fuck, the & is a reference!!!
{
    char hex_data, hex_data_low, hex_data_high;
    int len = str.length();
    int index = 0;
    char ch;
    array.resize(len / 2);
    for(int i = 0; i < str.length(); i++)
    {
        ch = str[2 * i].toLatin1();
        if(ch == ' ')
        {
            continue;
        }

        hex_data_high = convert_char_to_hex(ch);

        ch = str[2 * i + 1].toLatin1();
        if(ch == ' ')
        {
            continue;
        }

        hex_data_low = convert_char_to_hex(ch);

        hex_data = (char)(hex_data_high * 16) + (char)(hex_data_low << 0);

        array[index++] = hex_data;
        qDebug("%02x", hex_data);
    }

    //array.resize(index);//Pay more attention here
}


uint8_t xx1 = 50, yy1 = 50, xx2 = 100, yy2 = 100;
uint8_t index = 0;

uint8_t i = 0, j = 0;

void MainWindow::on_sendButton_clicked()
{
    //uint16_t i = 20;
    qDebug()<<"on_sendButton_clicked";

    i = 0;
    j = 0;
    timer_id = 1;
    timer->stop();
    timer->start(50);
#if 0
    if(index++ % 2 == 0)
    {
        p_lcd->lcd_fill(xx1 , yy1, xx2, yy2, WHITE);
    }
    else
    {
        xx1 += 10;
        xx2 += 10;
        p_lcd->lcd_fill(xx1 , yy1, xx2, yy2, BRED);
    }
#endif

    //p_lcd->lcd_draw_picture(0, i, 240, 1, line_color);
    //p_lcd->lcd_draw_picture(0, i, 240, 1, &gImage_image_01[240*i*2]);

    /*
    if(p_thread->start_draw_picture == false)
    {
        p_thread->start_draw_picture = true;
        p_thread->start();
    }
    else
    {
        p_thread->exit();
    }
    */


    /*

    QString str = ui->textEdit_2->toPlainText();
    QByteArray data;
    qDebug()<<"Data To Be Send:"<<str;

    #if 1
    data = QByteArray::fromHex(str.toLatin1());
    qDebug()<<"data:"<<data;
    serial->write(data);
    #else
    string_to_hex_array(str, data);
    qDebug()<<"data:"<<data;
    serial->write(data);
    #endif
    */
}

uint8_t serial_open_button_status = 0;

void MainWindow::on_openButton_clicked()
{
    //if (ui->openButton->text() == tr("打开串口"))
    if(ui->openButton->text() == "Open Serial")
    //if(serial_open_button_status == 0)
    {
        serial_open_button_status = 1;
        qDebug()<<"open serial";
        serial->setPortName(ui->PortBox->currentText()); // 设置串口名
        serial->open(QIODevice::ReadWrite); // 打开串口
        serial->setBaudRate(ui->BaudBox->currentText().toInt()); // 设置波特率
        switch(ui->BitNumBox->currentText().toInt()) // 设置数据位数
        {
        case 5:
            serial->setDataBits(QSerialPort::Data5);
            break;
        case 6:
            serial->setDataBits(QSerialPort::Data6);
            break;
        case 7:
            serial->setDataBits(QSerialPort::Data7);
            break;
        case 8:
            serial->setDataBits(QSerialPort::Data8);
            break;
        default:
            break;
        }
        switch(ui->ParityBox->currentText().toInt()) // 设置奇偶校验
        {
        case 0:
            serial->setParity(QSerialPort::NoParity);
            break;
        case 2:
            serial->setParity(QSerialPort::EvenParity);
            break;
        case 3:
            serial->setParity(QSerialPort::OddParity);
            break;
        case 4:
            serial->setParity(QSerialPort::SpaceParity);
            break;
        case 5:
            serial->setParity(QSerialPort::MarkParity);
            break;
        default:
            break;
        }
        switch(ui->StopBox->currentText().toInt()) // 设置停止位
        {
        case 1:
            serial->setStopBits(QSerialPort::OneStop);
            break;
        case 2:
            serial->setStopBits(QSerialPort::TwoStop);
            break;
        default:
            break;
        }
        serial->setFlowControl(QSerialPort::NoFlowControl); // 设置流控制
        // 关闭参数选择使能
        ui->PortBox->setEnabled(false);
        ui->BaudBox->setEnabled(false);
        ui->BitNumBox->setEnabled(false);
        ui->ParityBox->setEnabled(false);
        ui->StopBox->setEnabled(false);
        //ui->openButton->setText(tr("关闭串口"));
        ui->openButton->setText("Close Serial");
        ui->sendButton->setEnabled(true);
        // 连接信号槽
        QObject::connect(serial, &QSerialPort::readyRead, this, &MainWindow::Read_Data);
    }
    else
    {
        serial_open_button_status = 0;
        qDebug()<<"close serial";
        // 关闭串口
        serial->clear();
        serial->close();

        // 打开参数选择使能
        ui->PortBox->setEnabled(true);
        ui->BaudBox->setEnabled(true);
        ui->BitNumBox->setEnabled(true);
        ui->ParityBox->setEnabled(true);
        ui->StopBox->setEnabled(true);
        //ui->openButton->setText(tr("打开串口"));
        ui->openButton->setText(tr("Open Serial"));
        ui->sendButton->setEnabled(false);
    }
}

void MainWindow::on_pushButton_clicked()
{
    if(cw == NULL){
        cw = new ChildWindow(this);
        cw->show();
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    if(nine_axis == NULL)
    {
        nine_axis = new nine_axis_visualization();
        nine_axis->show();
    }
}

void MainWindow::on_six_visualization_window_closed()
{
    qDebug()<<"on_six_virualizaiton_window_close";
    six_axis = NULL;
}

void MainWindow::on_pushButton_5_clicked()
{
    qDebug()<<"on_pushButton_5_clicked";
    if(six_axis == NULL)
    {
        six_axis = new six_axis_visualization();
        connect(six_axis, SIGNAL(destroyed()), this, SLOT(on_six_visualization_window_closed()));
        six_axis->show();
    }
}

void MainWindow::on_checkBox_clicked()
{
    qDebug()<<"on_checkBox_clicked";
}

QString convertToPrint(QByteArray hex, bool isHex)
{
    if (isHex) {
        return hex.toHex(' ').toUpper().data();
    } else {
        return QString(hex).replace("\r", "\\r");
    }
}

enum
{
    UART_RX_STATE_WAITING_FOR_HEADER = 0,
    UART_RX_STATE_WAITING_FOR_LENGTH,
    UART_RX_STATE_WAITING_FOR_MORE_DATA,
};

#define UART_COMMAND_HEADER_OFFSET			0
#define UART_COMMAND_SEQUENCE_OFFSET		2
#define UART_COMMAND_GROUP_ID_OFFSET		3
#define UART_COMMAND_CMD_ID_OFFSET			4
#define UART_COMMAND_PAYLOAD_LENGTH_OFFSET 	5
#define UART_COMMAND_PAYLOAD_OFFSET			7

#define UART_COMMAND_MIN_SIZE				9

#define UART_RX_WORKING_BUFFER_SIZE 1024

uint8_t uart_rx_working_buffer[UART_RX_WORKING_BUFFER_SIZE] = {0};
uint8_t uart_rx_current_state = UART_RX_STATE_WAITING_FOR_HEADER;
uint16_t uart_rx_working_buffer_index;
uint16_t uart_rx_command_length;

void uart_receive(uint8_t data)
{

    if(uart_rx_working_buffer_index >= UART_RX_WORKING_BUFFER_SIZE)
    {
        uart_rx_working_buffer_index = 0;
        uart_rx_current_state = UART_RX_STATE_WAITING_FOR_HEADER;
    }

    uart_rx_working_buffer[uart_rx_working_buffer_index++] = data;

    qDebug("index :%d", uart_rx_working_buffer_index);

    for(uint16_t m = 0; m < uart_rx_working_buffer_index; m++)
    {
        //qDebug()<<"rx_working_buffer["<<m<<"]:"<<uart_rx_working_buffer[m];
        qDebug("uart_rx_working_buffer[%d]:%02x", m, uart_rx_working_buffer[m]);
    }

    switch(uart_rx_current_state)
    {
        case UART_RX_STATE_WAITING_FOR_HEADER:
            if(0xAA == uart_rx_working_buffer[0])
            {
                if(0x02 == uart_rx_working_buffer_index)
                {
                    if(0x55 == uart_rx_working_buffer[1])
                    {
                        uart_rx_current_state = UART_RX_STATE_WAITING_FOR_LENGTH;
                    }
                    else
                    {
                        uart_rx_working_buffer_index = 0;
                    }
                }
            }
            else
            {
                uart_rx_working_buffer_index = 0;
            }
            break;
        case UART_RX_STATE_WAITING_FOR_LENGTH:
            if(UART_COMMAND_PAYLOAD_OFFSET == uart_rx_working_buffer_index)
            {
                uart_rx_command_length = UART_COMMAND_MIN_SIZE + (uint16_t)(uart_rx_working_buffer[UART_COMMAND_PAYLOAD_LENGTH_OFFSET] << 0) + (uart_rx_working_buffer[UART_COMMAND_PAYLOAD_LENGTH_OFFSET + 1] << 8);
                if(uart_rx_command_length >= UART_RX_WORKING_BUFFER_SIZE)
                {
                    uart_rx_working_buffer_index = 0;
                    uart_rx_current_state = UART_RX_STATE_WAITING_FOR_HEADER;
                }
                else
                {
                    uart_rx_current_state = UART_RX_STATE_WAITING_FOR_MORE_DATA;
                }
            }
            break;
        case UART_RX_STATE_WAITING_FOR_MORE_DATA:
            if(uart_rx_working_buffer_index == uart_rx_command_length)
            {
                //Do crc16 check here?
                //Handle command
                //uart_rx_command_handler(uart_rx_working_buffer, uart_rx_command_length);
                qDebug()<<"Received Command:";
                for(uint16_t i = 0; i < uart_rx_working_buffer_index; i++)
                {
                    qDebug("%x ", uart_rx_working_buffer[i]);
                }
                uart_rx_working_buffer_index = 0;
                uart_rx_command_length = 0;
                uart_rx_current_state = UART_RX_STATE_WAITING_FOR_HEADER;
            }
            break;
        default:
            break;
    }
}


void MainWindow::Read_Data()
{
    uint8_t temp_buffer[1024];
    QByteArray buf = NULL;
    buf = serial->readAll();
    if (!buf.isEmpty())
    {

        qDebug()<<"buf.length:"<<buf.length();

        for(uint16_t i = 0; i < buf.length(); i++)
        {
            //qDebug()<<"buf["<<i<<"]:"<<temp_buffer[i];
            //qDebug("buf[%d]:%02x", i, (uint8_t)buf[i]);
            uart_receive((uint8_t)buf[i]);
        }

        QString   qstr;
        qstr = convertToPrint(buf, true);
        qstr.append(" ");
        qDebug()<<"qstr:"<<qstr;
        ui->textBrowser->setText(ui->textBrowser->toPlainText() + qstr);
        //QString qstr = QString(buf);
        //ui->textBrowser->setText(ui->textBrowser->toPlainText()+qstr);
        //ui->textBrowser->append(buf.toHex()); //16进制输出

        if(cw != NULL){
            emit sendSerialDataToChild(qstr);
        }
    }

    buf.clear();
}

//uint8_t i = 0, j = 0;

void MainWindow::timer_timeout_handler()
{
    qDebug()<<"timer_timeout_handler";

    if(timer_id == 1)
    {
        if(i < 240)
        {
            qDebug()<<"Picure:"<<j<<",draw:"<<i<<"line";
            switch(j)
            {
                case 0:
                    p_lcd->lcd_draw_picture(0, i, 240, 1, &gImage_clock_01[240*i*2]);
                    break;
                case 1:
                    p_lcd->lcd_draw_picture(0, i, 240, 1, &gImage_analog_clock[240*i*2]);
                    break;
                case 2:
                    p_lcd->lcd_draw_picture(0, i, 240, 1, &gImage_blood_pressure[240*i*2]);
                    break;
                case 3:
                    p_lcd->lcd_draw_picture(0, i, 240, 1, &gImage_charging[240*i*2]);
                    break;
                case 4:
                    p_lcd->lcd_draw_picture(0, i, 240, 1, &gImage_heart_rate[240*i*2]);
                    break;
                case 5:
                    p_lcd->lcd_draw_picture(0, i, 240, 1, &gImage_wechat[240*i*2]);
                    break;
                case 6:
                    p_lcd->lcd_draw_picture(0, i, 240, 1, &gImage_tire_pressure[240*i*2]);
                default:
                    break;
            }
        }
        else
        {
            i = 0;
            j++;
            if(j >= 7)
            {
                j = 0;
                qDebug()<<"Stop Timer";
                timer->stop();
            }
        }


    #if 0
        for(uint8_t i = 0; i < 240; i++)
        {
            qDebug()<<"draw "<<i<<" line";
            p_lcd->lcd_draw_picture(0, i, 240, 1, &gImage_image_01[240*i*2]);
        }
    #endif
        i++;
    }

    if(timer_id == 2)
    {
        timer2_timeout_handler();
    }

}

void MainWindow::setup_charts()
{
    QChartView * chart_view = new QChartView;

    this->setCentralWidget(chart_view);

    QLineSeries *series_x = new QLineSeries();

    for(int i = 0; i < 10; i++)
    {
        series_x->append(i, i * 1.0);
    }

    chart_view->chart()->addSeries(series_x);

    chart_view->chart()->setTheme(QChart::ChartThemeDark);
    series_x->setName("test data");
    chart_view->chart()->setTitle("chart for test");
    QValueAxis *axisx = new QValueAxis;
    axisx->setTitleText("sample time(s)");
    chart_view->chart()->setAxisX(axisx, series_x);

    QValueAxis *axisy = new QValueAxis;
    axisy->setTitleText("height(meter");
    chart_view->chart()->setAxisY(axisy, series_x);
    chart_view->chart()->legend()->setVisible(true);
    chart_view->chart()->legend()->setAlignment(Qt::AlignBottom);
}

void MainWindow::keyPressEvent (QKeyEvent *e)
{
    qDebug()<<"button pressed:"<<e;
}


void MainWindow::on_pushButton_6_clicked()
{
    if(lcd_display == NULL)
    {
        lcd_display = new LcdDisplay();
        //destroy()的作用域！！！
        connect(lcd_display, SIGNAL(destroyed()), this, SLOT(on_lcd_display_window_closed()));
        connect(lcd_display, SIGNAL(send_lcd_picture_id(int)), this, SLOT(on_lcd_picture_id_received(int)));
        lcd_display->show();
    }
}

void MainWindow::on_lcd_display_window_closed()
{
    qDebug()<<"on_lcd_display_window_closed";
    lcd_display = NULL;
}

int picture_id, line;

void MainWindow::on_lcd_picture_id_received(int id)
{
    qDebug()<<"on_lcd_picture_id_received:"<<id;
#if 1
    picture_id = id;
    line = 0;

    timer_id = 2;
    timer->stop();
    timer->start(50);
#endif
}

const uint8_t *picture_array[21] =
{
    gImage_clock_01,
    gImage_analog_clock,
    gImage_charging,
    gImage_heart_rate,
    gImage_blood_pressure,
    gImage_wechat,
    gImage_qq,
    gImage_text,
    gImage_incoming_call,
    gImage_motor_tire_pressure,
    gImage_car_tire_pressure,
    gImage_suv_tire_pressure,
    gImage_setup,
    gImage_select,
    gImage_motor_bind,
    gImage_car_bind,
    gImage_suv_bind,
    gImage_is_binding,
    gImage_bind_success,
};

void MainWindow::timer2_timeout_handler()
{
    qDebug()<<"line:"<<line;
    if(line < 240)
    {
        //p_lcd->lcd_draw_picture(0, i, 240, 1, &gImage_clock_01[240*i*2]);
        p_lcd->lcd_draw_picture(0, line, 240, 1, &picture_array[picture_id][240*line*2]);
        line++;
    }
    else
    {
        qDebug()<<"Stop Timer_id 2";
        timer->stop();
        //timer2->stop();
    }
}

//定位到textBrowser的底部
void MainWindow::on_textBrowser_textChanged()
{
    ui->textBrowser->moveCursor(QTextCursor::End);
}
