#ifndef FLASH_OPERATION_H
#define FLASH_OPERATION_H

#include <QWidget>
#include <QCloseEvent>

namespace Ui {
class flash_operation;
}

class flash_operation : public QWidget
{
    Q_OBJECT

public:
    explicit flash_operation(QWidget *parent = nullptr);
    ~flash_operation();

private:
    Ui::flash_operation *ui;

protected:
    void closeEvent(QCloseEvent *event);

public slots:
    void on_pushButton_browse_clicked();
    void on_pushButton_erase_clicked();
    void on_pushButton_read_clicked();
    void on_pushButton_write_clicked();

signals:
    void destroyed();
    void send_flash_operation_id(int id, QString str, void*);
};

#endif // FLASH_OPERATION_H
