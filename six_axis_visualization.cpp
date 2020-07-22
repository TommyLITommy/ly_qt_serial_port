#include "six_axis_visualization.h"
#include "ui_six_axis_visualization.h"
#include <QDebug>
#include <QTime>
#include <QMessageBox>

six_axis_visualization::six_axis_visualization(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::six_axis_visualization),
    chart(new QChart),
    timer(new QTimer),
    count(0)
{
    ui->setupUi(this);

    displayMaxPointsNumber = 200;

    initFontColor();

    for(int i = 0; i < AXIS_NUMBER; i++)
    {
        series[i] = new QLineSeries();
        series[i]->setColor(colorTable.at(i));//Set Line Color
        chart->addSeries(series[i]);
    }
#if 1
    initChart();
    initSlot();

    timer->setInterval(100);
    timer->start();
#endif
}

six_axis_visualization::~six_axis_visualization()
{
    delete ui;
}


void six_axis_visualization::closeEvent(QCloseEvent *event)
{
    auto temp = QMessageBox::information(this, "tootip","Do you want to close this window?", QMessageBox::Yes | QMessageBox::No);
    if(temp == QMessageBox::Yes)
    {
        timer->stop();
        emit destroyed();
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void six_axis_visualization::initChart()
{
    axisX = new QValueAxis();
    axisX->setTitleFont(QFont("Microsoft YaHei", 10, QFont::Normal, true));
    axisX->setTitleText("Time(s)");
    axisX->setGridLineVisible(true);
    chart->addAxis(axisX, Qt::AlignBottom);

    axisY = new QValueAxis();
    axisY->setTitleFont(QFont("Microsoft YaHei", 10, QFont::Normal, true));
    axisY->setTitleText("Dis(mm");
    axisY->setGridLineVisible(true);
    chart->addAxis(axisY, Qt::AlignLeft);

    for(int i = 0; i < AXIS_NUMBER; i++)
    {
        series[i]->attachAxis(axisX);
        series[i]->attachAxis(axisY);
    }

    chart->legend()->hide();
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);//How to comprehensive Render
    ui->verticalLayout->addWidget(chartView);
}

void six_axis_visualization::initSlot()
{
    connect(timer, SIGNAL(timeout()), this, SLOT(timerSlot()));

    for(int i = 0; i < AXIS_NUMBER; i++)
    {
        //connect(checkBoxVector.at(i), SIGNAL(toggled(bool)), this, SLOT(checkboxChanged()));
    }
}

void six_axis_visualization::initFontColor()
{
    colorTable.append(QColor(255, 0, 0));//red
    colorTable.append(QColor(0, 0, 255));//blue
    colorTable.append(QColor(0, 255, 0));//green
#if 0
    colorTable.append(QColor(139, 0, 0));//dark red
    colorTable.append(QColor(255, 255, 0));//yellow
    colorTable.append(QColor(0, 0, 0));//black
#endif

    strColor[0] = "QCheckBox{color:rgb(255, 0, 0)}";//What is the use of strColor?
    strColor[1] = "QCheckBox{color:rgb(0, 0, 255)}";
    strColor[2] = "QCheckBox{color:rgb(0, 255, 0)}";
#if 0
    strColor[3] = "QCheckBox{color:rgb(139, 0, 0)}";
    strColor[4] = "QCheckBox{color:rgb(255, 255, 0)}";
    strColor[5] = "QCheckBox{color:rgb(0, 0, 0)}";
#endif
}


//AxisArray[0]-->x, AxisArray[1]-->y, AxisArray[2]-->z,
void six_axis_visualization::addChartData(float time, float *AxisArray)
{
    float globalMinX = time;
    float globalMaxX = time;
    float globalMinY = AxisArray[0];
    float globalMaxY = AxisArray[0];

    for(int i = 0; i < AXIS_NUMBER; i++)
    {
        QVector<QPointF> oldData = series[i]->pointsVector();
        QVector<QPointF> newData;

        if(oldData.size() < displayMaxPointsNumber)
        {
            newData = oldData;
        }
        else
        {
            oldData.removeFirst();
            newData = oldData;
        }

        newData.append(QPointF(time, AxisArray[i]));

        float minX = newData.at(0).x();
        float maxX = newData.at(0).x();
        float minY = newData.at(0).y();
        float maxY = newData.at(0).y();

        for(int j = 0; j < newData.size(); j++)
        {
            if(minY > newData.at(j).y())
            {
                minY = newData.at(j).y();
            }

            if(maxY < newData.at(j).y())
            {
                maxY = newData.at(j).y();
            }
        }

        if(i == 0)
        {
            for(int j = 0; j < newData.size(); j++)
            {
                if(minX > newData.at(j).x())
                {
                    minX = newData.at(j).x();
                }

                if(maxX < newData.at(j).x())
                {
                    maxX = newData.at(j).x();
                }
            }

            globalMinX = minX;
            globalMaxX = maxX;
        }

        globalMinY = globalMinY < minY ? globalMinY:minY;
        globalMaxY = globalMaxY > maxY ? globalMaxY:maxY;

        series[i]->replace(newData);
    }

    //What is the use of following statements
    //Pay more attention to the following two statement
    axisX->setRange(globalMinX, globalMaxX);
    axisY->setRange(globalMinY - (globalMaxY - globalMinY) * 0.1, globalMaxY + (globalMaxY - globalMinY) * 0.1);
}

void six_axis_visualization::selectAll()
{
    for(int i = 0; i < checkBoxVector.size(); i++)
    {
        checkBoxVector.at(i)->setChecked(true);
    }
}

void six_axis_visualization::invertSelect()
{
    for(int i = 0; i < checkBoxVector.size(); i++)
    {
        if(checkBoxVector.at(i)->checkState())
        {
            checkBoxVector.at(i)->setChecked(false);
        }
        else
        {
            checkBoxVector.at(i)->setChecked(true);
        }
    }
}

void six_axis_visualization::checkboxChanged()
{
    for(int i = 0; i < AXIS_NUMBER; i++)
    {
        if(checkBoxVector.at(i)->checkState())
        {
            series[i]->setVisible(true);
        }
        else
        {
            series[i]->setVisible(false);
        }
    }
}

int get_rand()
{
    QTime time;
    time = QTime::currentTime();
    qsrand(time.msec() + time.second() * 1000);
    int n = qrand() % 8;
    return n;
}

void six_axis_visualization::timerSlot()
{
    qDebug()<<"timerSlot,count:"<<count;
    float AxisBuffer[3];
    AxisBuffer[0] = get_rand() + 1;
    AxisBuffer[1] = get_rand() + 2;
    AxisBuffer[2] = get_rand() + 3;

    if(QObject::sender() == timer)
    {
        addChartData(count++, AxisBuffer);
    }
}


