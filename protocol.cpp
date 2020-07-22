#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <QDebug>
#include "protocol.h"

protocol::protocol()
{

}

protocol::protocol(QSerialPort *s)
{
    serial = s;
}

uint16_t protocol::crc16_checksum(uint8_t const *p_data, uint32_t size, uint16_t const *p_crc)
{
    uint16_t crc = (p_crc == NULL) ? 0xFFFF : *p_crc;

    for (uint32_t i = 0; i < size; i++)
    {
        crc  = (uint8_t)(crc >> 8) | (crc << 8);
        crc ^= p_data[i];
        crc ^= (uint8_t)(crc & 0xFF) >> 4;
        crc ^= (crc << 8) << 4;
        crc ^= ((crc & 0xFF) << 4) << 1;
    }

    return crc;
}

void protocol::assemble_command_and_send(uint8_t group_id, uint8_t command_id, uint8_t *p_payload, uint16_t payload_length)
{
     uint8_t buffer[WORKING_BUFFER_LENGTH];
     uint16_t index = 0;
     uint16_t crc16;
     buffer[index++] = (uint8_t)((PC_TO_DEVICE_HEADER >> 0) & 0xFF);
     buffer[index++] = (uint8_t)((PC_TO_DEVICE_HEADER >> 8) & 0xFF);
     buffer[index++] = sequence++;
     buffer[index++] = group_id;
     buffer[index++] = command_id;
     buffer[index++] = (uint8_t)((payload_length >> 0) & 0xFF);
     buffer[index++] = (uint8_t)((payload_length >> 8) & 0xFF);
     memcpy(&buffer[index], p_payload, payload_length);
     index += payload_length;
     crc16 = crc16_checksum(&buffer[2], index - 2, NULL);
     buffer[index++] = (uint8_t)((crc16 >> 0) & 0xFF);
     buffer[index++] = (uint8_t)((crc16 >> 8) & 0xFF);

     qDebug()<<"Total Length:"<<index;
     QByteArray array;
     array.resize(index);
     memcpy(array.data(), buffer, index);
     qDebug()<<"serial->write start";
     //qDebug()<<"array:"<<array;
     qint64 ret;
     ret = serial->write(array);
     qDebug()<<"serial->write end, ret:"<<ret;
}

void protocol::group_id_hardware_handler(uint8_t *p_data, uint16_t length)
{
    switch(p_data[COMMAND_COMMAND_ID_OFFSET])
    {
        case 0x01:
            break;
        default:
            break;
    }
}

void protocol::group_id_ble_handler(uint8_t *p_data, uint16_t length)
{
    switch(p_data[COMMAND_COMMAND_ID_OFFSET])
    {
        case 0x01:
            break;
        default:
            break;
    }
}

void protocol::group_id_ack_handler(uint8_t *p_data, uint16_t length)
{
    switch(p_data[COMMAND_COMMAND_ID_OFFSET])
    {
        case 0x01:
            break;
        default:
            break;
    }
}

void protocol::group_id_debug_handler(uint8_t *p_data,uint16_t length)
{
    switch(p_data[COMMAND_COMMAND_ID_OFFSET])
    {
        case 0x01:
            //byte array to string!
            break;
        default:
            break;
    }
}

void protocol::uart_rx_handler(uint8_t *p_data, uint16_t length)
{
    //First do crc16 checksum
    uint16_t crc16_01, crc16_02;
    crc16_01 = (p_data[length - 2] << 0) + (p_data[length - 1] << 8);
    crc16_02 = crc16_checksum(p_data, length - 2, NULL);
    qDebug()<<"crc16_01:"<<crc16_01<<" crc16_02:"<<crc16_02;
    if(crc16_01 != crc16_02)
    {
        qDebug()<<"crc16 checksum error!";
        return;
    }

    switch(p_data[COMMAND_GROUP_ID_OFFSET])
    {
        case GROUP_ID_HARDWARE:
            group_id_hardware_handler(p_data, length);
            break;
        case GROUP_ID_BLE:
            group_id_ble_handler(p_data, length);
            break;
        case GROUP_ID_ACK:
            group_id_ack_handler(p_data, length);
            break;
        case GROUP_ID_DEBUG:
            group_id_debug_handler(p_data, length);
            break;
        default:
            break;
    }
}
