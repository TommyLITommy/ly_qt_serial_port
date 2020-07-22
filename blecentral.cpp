#include "blecentral.h"
#include "ui_blecentral.h"

BleCentral::BleCentral(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BleCentral)
{
    ui->setupUi(this);
}

BleCentral::~BleCentral()
{
    delete ui;
}
