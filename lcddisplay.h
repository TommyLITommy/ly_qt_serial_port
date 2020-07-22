#ifndef LCDDISPLAY_H
#define LCDDISPLAY_H

#include <QWidget>

#include <QCloseEvent>

namespace Ui {
class LcdDisplay;
}

class LcdDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit LcdDisplay(QWidget *parent = nullptr);
    ~LcdDisplay();

private:
    Ui::LcdDisplay *ui;

protected:
    void closeEvent(QCloseEvent *event);

signals:
    void destroyed();
    void send_lcd_picture_id(int id);

public slots:
    void on_pushButton_clicked();
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_10_clicked();
    void on_pushButton_11_clicked();
    void on_pushButton_12_clicked();
    void on_pushButton_13_clicked();
    void on_pushButton_14_clicked();
    void on_pushButton_15_clicked();
    void on_pushButton_16_clicked();
    void on_pushButton_17_clicked();
    void on_pushButton_18_clicked();
    void on_pushButton_19_clicked();
    void on_pushButton_20_clicked();
    void on_pushButton_21_clicked();

private:
    void send_picture_id(int id);
};

#endif // LCDDISPLAY_H
