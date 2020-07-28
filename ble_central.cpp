#include "ble_central.h"
#include "ui_ble_central.h"

ble_central::ble_central(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ble_central)
{
    ui->setupUi(this);
}

ble_central::~ble_central()
{
    delete ui;
}
