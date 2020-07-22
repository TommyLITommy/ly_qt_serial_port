#include "nine_axis_visualization.h"
#include "ui_nine_axis_visualization.h"

nine_axis_visualization::nine_axis_visualization(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::nine_axis_visualization)
{
    ui->setupUi(this);
}

nine_axis_visualization::~nine_axis_visualization()
{
    delete ui;
}
