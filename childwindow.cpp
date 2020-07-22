#include "childwindow.h"
#include "ui_childwindow.h"
#include <QChartView>
#include <QLineSeries>
#include <QValueAxis>

using namespace QtCharts;

ChildWindow::ChildWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChildWindow)
{
    ui->setupUi(this);
    QObject::connect(parent, SIGNAL(sendSerialDataToChild(QString)), this, SLOT(readData(QString)));//readData does not need to specify
    setup_charts();
}

ChildWindow::~ChildWindow()
{
    delete ui;
}

void ChildWindow::readData(QString str)
{
    ui->textBrowser->setText(ui->textBrowser->toPlainText()+str);
    //ui->textBrowser->append(buf.toHex()); //16进制输出
}

void ChildWindow::setup_charts()
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
