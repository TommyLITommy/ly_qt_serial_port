#include "lcd.h"

lcd::lcd()
{

}

lcd::lcd(protocol *p)
{
    p_protocol = p;
}

void lcd::lcd_fill(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
    uint8_t buffer[24];
    uint16_t index = 0;
    buffer[index++] = (uint8_t)((x1 >> 0) & 0xFF);
    buffer[index++] = (uint8_t)((x1 >> 8) & 0xFF);

    buffer[index++] = (uint8_t)((y1 >> 0) & 0xFF);
    buffer[index++] = (uint8_t)((y1 >> 8) & 0xFF);

    buffer[index++] = (uint8_t)((x2 >> 0) & 0xFF);
    buffer[index++] = (uint8_t)((x2 >> 8) & 0xFF);

    buffer[index++] = (uint8_t)((y2 >> 0) & 0xFF);
    buffer[index++] = (uint8_t)((y2 >> 8) & 0xFF);

    buffer[index++] = (uint8_t)((color >> 0) & 0xFF);
    buffer[index++] = (uint8_t)((color >> 8) & 0xFF);

    p_protocol->assemble_command_and_send(GROUP_ID_HARDWARE, GID_HARDWARE_CID_PTD_LCD_FILL, buffer, index);
}

void lcd::lcd_draw_point(uint16_t x, uint16_t y, uint16_t color)
{

}

void lcd::lcd_draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{

}

void lcd::lcd_draw_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{

}

void lcd::lcd_draw_picture(uint16_t x, uint16_t y, uint16_t length, uint16_t width, const uint8_t pic[])
{
    uint8_t buffer[1024];
    uint16_t index = 0;
    buffer[index++] = (uint8_t)((x >> 0) & 0xFF);
    buffer[index++] = (uint8_t)((x >> 8) & 0xFF);

    buffer[index++] = (uint8_t)((y >> 0) & 0xFF);
    buffer[index++] = (uint8_t)((y >> 8) & 0xFF);

    buffer[index++] = (uint8_t)((length >> 0) & 0xFF);
    buffer[index++] = (uint8_t)((length >> 8) & 0xFF);

    buffer[index++] = (uint8_t)((width >> 0) & 0xFF);
    buffer[index++] = (uint8_t)((width >> 8) & 0xFF);

    memcpy(&buffer[index], pic, length * width * 2);
    index += length * width * 2;
    p_protocol->assemble_command_and_send(GROUP_ID_HARDWARE, GID_HARDWARE_CID_PTD_LCD_DRAW_PICTURE, buffer, index);
}
