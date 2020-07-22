#include "lcddisplay.h"
#include "ui_lcddisplay.h"
#include <QMessageBox>
#include <QDebug>

LcdDisplay::LcdDisplay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LcdDisplay)
{
    ui->setupUi(this);

    setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);    // 禁止最大化按钮
    setFixedSize(this->width(),this->height());                     // 禁止拖动窗口大小
}

LcdDisplay::~LcdDisplay()
{
    delete ui;
}

void LcdDisplay::closeEvent(QCloseEvent *event)
{
    auto temp = QMessageBox::information(this, "tootip","Do you want to close this window?", QMessageBox::Yes | QMessageBox::No);
    if(temp == QMessageBox::Yes)
    {
        emit destroyed();
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void LcdDisplay::send_picture_id(int id)
{
    emit send_lcd_picture_id(id);
}

void LcdDisplay::on_pushButton_clicked()
{
    qDebug()<<"on_pushButton_clicked";
    send_picture_id(17);
}
void LcdDisplay::on_pushButton_1_clicked()
{
    qDebug()<<"on_pushButton_1_clicked";
    send_picture_id(1);
}
void LcdDisplay::on_pushButton_2_clicked()
{
    qDebug()<<"on_pushButton_2_clicked";
    send_picture_id(0);
}
void LcdDisplay::on_pushButton_3_clicked()
{
    qDebug()<<"on_pushButton_3_clicked";
    send_picture_id(3);
}
void LcdDisplay::on_pushButton_4_clicked()
{
    qDebug()<<"on_pushButton_4_clicked";
    send_picture_id(14);
}
void LcdDisplay::on_pushButton_5_clicked()
{
    qDebug()<<"on_pushButton_5_clicked";
    send_picture_id(6);
}
void LcdDisplay::on_pushButton_6_clicked()
{
    qDebug()<<"on_pushButton_6_clicked";
    send_picture_id(11);
}
void LcdDisplay::on_pushButton_7_clicked()
{
    qDebug()<<"on_pushButton_7_clicked";
    send_picture_id(7);
}
void LcdDisplay::on_pushButton_8_clicked()
{
    qDebug()<<"on_pushButton_8_clicked";
    send_picture_id(1);
}
void LcdDisplay::on_pushButton_9_clicked()
{
    qDebug()<<"on_pushButton_9_clicked";
    send_picture_id(4);
}
void LcdDisplay::on_pushButton_10_clicked()
{
    qDebug()<<"on_pushButton_10_clicked";
    send_picture_id(7);
}
void LcdDisplay::on_pushButton_11_clicked()
{
    qDebug()<<"on_pushButton_11_clicked";
    send_picture_id(9);
}
void LcdDisplay::on_pushButton_12_clicked()
{
    qDebug()<<"on_pushButton_12_clicked";
    send_picture_id(12);
}
void LcdDisplay::on_pushButton_13_clicked()
{
    qDebug()<<"on_pushButton_13_clicked";
    send_picture_id(15);
}
void LcdDisplay::on_pushButton_14_clicked()
{
    qDebug()<<"on_pushButton_14_clicked";
    send_picture_id(18);
}
void LcdDisplay::on_pushButton_15_clicked()
{
    qDebug()<<"on_pushButton_15_clicked";
    send_picture_id(2);
}
void LcdDisplay::on_pushButton_16_clicked()
{
    qDebug()<<"on_pushButton_16_clicked";
    send_picture_id(5);
}
void LcdDisplay::on_pushButton_17_clicked()
{
    qDebug()<<"on_pushButton_17_clicked";
    send_picture_id(8);
}
void LcdDisplay::on_pushButton_18_clicked()
{
    qDebug()<<"on_pushButton_18_clicked";
    send_picture_id(10);
}
void LcdDisplay::on_pushButton_19_clicked()
{
    qDebug()<<"on_pushButton_19_clicked";
    send_picture_id(13);
}
void LcdDisplay::on_pushButton_20_clicked()
{
    qDebug()<<"on_pushButton_20_clicked";
    send_picture_id(16);
}
void LcdDisplay::on_pushButton_21_clicked()
{
    qDebug()<<"on_pushButton_21_clicked";
}
