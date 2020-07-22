#ifndef NINE_AXIS_VISUALIZATION_H
#define NINE_AXIS_VISUALIZATION_H

#include <QWidget>

namespace Ui {
class nine_axis_visualization;
}

class nine_axis_visualization : public QWidget
{
    Q_OBJECT

public:
    explicit nine_axis_visualization(QWidget *parent = nullptr);
    ~nine_axis_visualization();

private:
    Ui::nine_axis_visualization *ui;
};

#endif // NINE_AXIS_VISUALIZATION_H
