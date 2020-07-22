#include "mythread.h"
#include <QDebug.h>

#if 0
mythread::mythread()
{

}

mythread::mythread(lcd *p)
{
    p_lcd = p;
}

void mythread::run()
{
    while(true)
    {
        if(start_draw_picture)
        {
            for(uint8_t i = 0; i < 240; i++)
            {
                p_lcd->lcd_draw_picture(0, i, 240, 1, &gImage_image_01[240*i*2]);
                msleep(100);
            }
        }
    }
}
#endif

mythread::mythread()
{

}

mythread::mythread(lcd *p)
{
    p_lcd = p;
    start_draw_picture = false;
}

void mythread::run()
{
    while(1)
    {
        if(start_draw_picture)
        {
            for(uint8_t i = 0; i < 1; i++)
            {
                qDebug()<<"draw "<<i<<" line";
                //p_lcd->lcd_draw_picture(0, i, 240, 1, &gImage_image_01[240*i*2]);
                //qDebug()<<&gImage_image_01[240*i*2];
                sleep(2);
            }
        }
        qDebug()<<"Exit thread";
    }
}
