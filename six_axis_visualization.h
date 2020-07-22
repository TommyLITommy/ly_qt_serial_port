#ifndef SIX_AXIS_VISUALIZATION_H
#define SIX_AXIS_VISUALIZATION_H

#include <QWidget>
#include <QChart>
#include <QLineSeries>
#include <QVector>
#include <QTimer>
#include <QStandardItemModel>
#include <QCheckBox>
#include <QValueAxis>
#include <QChartView>

QT_CHARTS_USE_NAMESPACE

#define AXIS_NUMBER 3

namespace Ui {
class six_axis_visualization;
}

class six_axis_visualization : public QWidget
{
    Q_OBJECT

public:
    explicit six_axis_visualization(QWidget *parent = nullptr);
    ~six_axis_visualization();

private:
    Ui::six_axis_visualization *ui;

protected:
    void closeEvent(QCloseEvent *event);

public:
    void addChartData(float time, float *AxisArray);
private:
    void initUI();
    void initChart();
    void initSlot();
    void initFontColor();

    QChartView *chartView;
    QChart *chart;
    QLineSeries *series[AXIS_NUMBER];
    int displayMaxPointsNumber;//used for draw curve line

    QTimer *timer;
    quint16 count;

private slots:
    void selectAll();
    void invertSelect();
    void checkboxChanged();
    void timerSlot();

private:
    QVector<QCheckBox*>checkBoxVector;
    QString strColor[AXIS_NUMBER];
    QVector<QColor> colorTable;
    QStandardItemModel *model;

    QValueAxis *axisX;
    QValueAxis *axisY;

signals:
    void destroyed();

};

#endif // SIX_AXIS_VISUALIZATION_H
