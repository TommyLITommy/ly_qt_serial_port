#ifndef PROTOCOL_H
#define PROTOCOL_H

#define COMMAND_HEADER_OFFSET           0
#define COMMAND_SEQUENCE_OFFSET         2
#define COMMAND_GROUP_ID_OFFSET         3
#define COMMAND_COMMAND_ID_OFFSET       4
#define COMMAND_PAYLOAD_LENGTH_OFFSET   5
#define COMMAND_PAYLOAD_OFFSET          7

#define WORKING_BUFFER_LENGTH 1024

#define PC_TO_DEVICE_HEADER 0xAA55
#define DEVICE_TO_PC_HEADER 0x55AA

#include "type.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <string>
#include <QTextCodec>
#include <QByteArray>

typedef enum
{
    GROUP_ID_HARDWARE,//下位机硬件外设控制Group命令
    GROUP_ID_BLE,
    GROUP_ID_BLE_P,     //BLE Peripheral
    GROUP_ID_BLE_C,     //BLE Central
    GROUP_ID_BLE_MESH,
    GROUP_ID_BLE_AUDIO,
    GROUP_ID_ACK,
    GROUP_ID_DEBUG,   //调试log输出
}group_id;

typedef enum
{
    GID_HARDWARE_CID_PTD_LCD_FILL,
    GID_HARDWARE_CID_PTD_LCD_DRAW_POINT,
    GID_HARDWARE_CID_PTD_LCD_DRAW_LINE,
    GID_HARDWARE_CID_PTD_LCD_DRAW_RECTANGLE,
    GID_HARDWARE_CID_PTD_LCD_DRAW_PICTURE,
    GID_HARDWARE_CID_PTD_MEMS_CALIBRATION,
    GID_HARDWARE_CID_PTD_FLASH_OPERATION,//erase, flash, read
}gid_hardware_cid_ptd_t;//ptd-->pc to device

typedef enum
{
    GID_HARDWARE_CID_DTP_NONE,
    GID_HARDWARE_CID_DTP_3_AXIS_RAW_DATA_REPORT,
    GID_HARDWARE_CID_DTP_6_AXIS_RAW_DATA_REPORT,
    GID_HARDWARE_CID_DTP_9_AXIS_RAW_DATA_REPORT,
    GID_HARDWARE_CID_DTP_PITCH_YAW_ROLL_REPORT,
    GID_HARDWARE_CID_DTP_ECG_RAW_DATA_REPORT,
    GID_HARDWARE_CID_DTP_PPG_RAW_DATA_REPORT,
}gid_hardware_cid_dtp_t;//dtp-->device to pc

//不管哪一端收到一条完整命令，都要回复一个ack，ack里面包含了收到命令的group id和command id

typedef enum
{
    GID_BLE_P_CID_PTD_BLE_PERIPHERAL_MODE_SET,
    GID_BLE_P_CID_PTD_SET_ADV_PARAMETER,
    GID_BLE_P_CID_PTD_ACQUIRE_ADV_PARAMETER,
    GID_BLE_P_CID_PTD_SET_CONNECTION_PARAMETER,
    GID_BLE_P_CID_PTD_ACQUIRE_CONNECTION_PARAMETER
}gid_ble_p_cid_ptd_t;

typedef enum
{
    GID_BLE_P_CID_DTP_ACQUIRE_ADV_PARAMETER_RESPONSE,
    GID_BLE_P_CID_DTP_ACQUIRE_CONNECTION_PARAMETER_RESPONSE,
    GID_BLE_P_CID_DTP_BLE_PERIPHERAL_EVENT
}gid_ble_p_cid_dtp_t;

typedef enum
{
    GID_BLE_C_CID_PTD_BLE_CENTRAL_MODE_SET,
    GID_BLE_C_CID_PTD_SET_SCAN_PARAMETER,
    GID_BLE_C_CID_PTD_ACQUIRE_SCAN_PARAMETER,
    GID_BLE_C_GID_CONNECT,
    GID_BLE_C_GID_DISCONNECT,
    GID_BLE_C_GID_WRITE_CHAR
}gid_ble_c_cid_ptd_t;

typedef enum
{
    GID_BLE_P_CID_DTP_ACQUIRE_SCAN_PARAMETER_RESPONSE,
    GID_BLE_P_CID_DTP_BLE_CENTTRAL_EVENT
}gid_ble_c_cid_dtp_t;

typedef enum
{
    COMMAND_ID_SET_WORK_MODE,
    COMMAND_ID_ACQUIRE_WORK_MODE,
    COMMAND_ID_SET_ADV_PARAMETER,
    COMMAND_ID_ACQUIRE_ADV_PARAMETER,
    COMMAND_ID_SET_SCAN_PARAMETER,
    COMMAND_ID_ACQUIRE_SCAN_PARAMETER,
    COMMAND_ID_START_SCAN,
    COMMAND_ID_STOP_SCAN,
    COMMAND_ID_CONNECT,
    COMMAND_ID_DISCONNECT,
    COMMAND_ID_ACQUIRE_CONNECTED_DEVICE,
    COMMAND_ID_HARDWARE_COMMAND_START,
    COMMAND_ID_LCD_DRAW_POINT,
    COMMAND_ID_LCD_DRAW_LINE,
    COMMAND_ID_LCD_DRAW_RECTANGLE,
    COMMAND_ID_LCD_FILL,
    //COMMAND_ID_BLE_CENTRAL_EVENT,
    //COMMAND_ID_BLE_PERIPHERAL_EVENT,
    COMMAND_ID_ACK_FROM_PC_TO_DEVICE,
}gropu_id_ble_command_id_pc_to_device_t;

typedef enum
{
    COMMAND_ID_XXX_RESPONSE,
    COMMAND_ID_MAX,
    COMMAND_ID_BLE_CENTRAL_EVENT,
    COMMAND_ID_BLE_PERIPHERAL_EVENT,
    COMMAND_ID_ACK_FROM_DEVICE_TO_PC,
}command_id_device_to_pc_t;

class protocol
{
private:
    uint8_t sequence;
    QSerialPort *serial;

public:
    protocol();
    protocol(QSerialPort *serial);

    void uart_rx_handler(uint8_t *p_data, uint16_t length);
    void uart_tx_handler(uint8_t *p_data, uint16_t length);
    uint16_t crc16_checksum(uint8_t const *p_data, uint32_t size, uint16_t const *p_crc);
    void assemble_command_and_send(uint8_t group_id, uint8_t command_id, uint8_t *p_payload, uint16_t payload_length);
    void group_id_hardware_handler(uint8_t *p_data, uint16_t length);
    void group_id_ble_handler(uint8_t *p_data, uint16_t length);
    void group_id_ack_handler(uint8_t *p_data, uint16_t length);
    void group_id_debug_handler(uint8_t *p_data,uint16_t length);
};

#endif // PROTOCOL_H
