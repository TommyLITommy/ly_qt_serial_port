#ifndef BLE_CENTRAL_H
#define BLE_CENTRAL_H

#include <QWidget>

namespace Ui {
class ble_central;
}

class ble_central : public QWidget
{
    Q_OBJECT

public:
    explicit ble_central(QWidget *parent = nullptr);
    ~ble_central();

private:
    Ui::ble_central *ui;
};

#endif // BLE_CENTRAL_H
