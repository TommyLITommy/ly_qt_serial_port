#include "ble_peripheral.h"
#include "ui_ble_peripheral.h"

ble_peripheral::ble_peripheral(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ble_peripheral)
{
    ui->setupUi(this);
}

ble_peripheral::~ble_peripheral()
{
    delete ui;
}
