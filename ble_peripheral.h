#ifndef BLE_PERIPHERAL_H
#define BLE_PERIPHERAL_H

#include <QWidget>

namespace Ui {
class ble_peripheral;
}

class ble_peripheral : public QWidget
{
    Q_OBJECT

public:
    explicit ble_peripheral(QWidget *parent = nullptr);
    ~ble_peripheral();

private:
    Ui::ble_peripheral *ui;
};

#endif // BLE_PERIPHERAL_H
