#include "flash_operation.h"
#include "ui_flash_operation.h"
#include <qDebug>
#include <QMessageBox>
#include <QFileDialog>

flash_operation::flash_operation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::flash_operation)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);// 禁止最大化按钮
    setFixedSize(this->width(),this->height());//禁止拖拽窗口大小

//    QStringList list;
//    list<<"A"<<"B"<<"C"<<"D"<<"E";
//    ui->comboBox->addItems(list);
//    ui->comboBox->addItem("F");

    QStringList list;
    list<<"0"<<"1";
    ui->comboBox->addItems(list);
    ui->lineEdit_address->setText("0x202000");
    ui->lineEdit_length->setText("0x1F4000");
}

flash_operation::~flash_operation()
{
    delete ui;
}

void flash_operation::closeEvent(QCloseEvent *event)
{
    auto temp = QMessageBox::information(this, "tootip","Do you want to close this window?", QMessageBox::Yes | QMessageBox::No);
    if(temp == QMessageBox::Yes)
    {
        emit destroyed();
    }
    else
    {
        event->ignore();
    }
}
//#include "ble_protocol.h"
//ble_device_info_t ble_device_info;
void flash_operation::on_pushButton_erase_clicked()
{
    qDebug()<<"on_pushButton_erase_clicked";
    qDebug()<<"address:"<<ui->lineEdit_address->text();
    qDebug()<<"length:"<<ui->lineEdit_length->text();

    qDebug()<<"address to int:"<<ui->lineEdit_address->text().toInt(NULL, 16);//Attention Please
    qDebug()<<"length to int:"<<ui->lineEdit_length->text().toInt(NULL, 16);

//    ble_device_info.conn_handle = 0x16;
//    ble_device_info.mac_address[0] = 0x11;
//    ble_device_info.mac_address[1] = 0x22;
//    ble_device_info.mac_address[2] = 0x33;
//    ble_device_info.mac_address[3] = 0x44;
//    ble_device_info.mac_address[4] = 0x55;
//    ble_device_info.mac_address[5] = 0x66;
    emit send_flash_operation_id(1, NULL, NULL);
}
void flash_operation::on_pushButton_read_clicked()
{
    qDebug()<<"on_pushButton_read_clicked";
    emit send_flash_operation_id(2, NULL, NULL);
}
void flash_operation::on_pushButton_write_clicked()
{
    qDebug()<<"on_pushButton_write_clicked";
    QString file_path = ui->lineEdit_file->text();
    qDebug()<<"file_path"<<file_path;
    if(file_path.length() > 0)
    {
        emit send_flash_operation_id(3, file_path, NULL);
        QFile file(file_path);
        //file.open(QIODevice::ReadOnly | QIODevice::Text);
        file.open(QIODevice::ReadOnly);
        QFileInfo info(file);
        qDebug()<<"file size:"<<info.size();
        file.close();
    }
}
void flash_operation::on_pushButton_browse_clicked()
{
    qDebug()<<"on_pushButton_browse_clicked";
    QString file_path = QFileDialog::getOpenFileName(this, "please choose file");
    if (file_path.length() > 0) {
        ui->lineEdit_file->setText(file_path);
    }
    //emit send_flash_operation_id(4, file_path, NULL);
}
