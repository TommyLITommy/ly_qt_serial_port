#ifndef BLECENTRAL_H
#define BLECENTRAL_H

#include <QWidget>

namespace Ui {
class BleCentral;
}

class BleCentral : public QWidget
{
    Q_OBJECT

public:
    explicit BleCentral(QWidget *parent = nullptr);
    ~BleCentral();

private:
    Ui::BleCentral *ui;
};

#endif // BLECENTRAL_H
