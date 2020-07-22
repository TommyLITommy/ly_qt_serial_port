#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include "lcd.h"

class mythread: public QThread
{
public:
    mythread();
    mythread(lcd *p);
    void run();

public:
    bool start_draw_picture;

private:
    lcd *p_lcd;
};

#endif // MYTHREAD_H
