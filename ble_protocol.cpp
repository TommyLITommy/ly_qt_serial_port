#include <string>
#include "ble_protocol.h"
#include "ly_util.h"

ble_protocol::ble_protocol()
{

}

ble_protocol::ble_protocol(protocol *p)
{
    p_protocol = p;
}

void ble_protocol::ble_command_assemble(uint8_t group_id, uint8_t command_id, uint8_t *p_payload, uint16_t payload_length, void *parameter)
{
    uint16_t index;
    uint16_t crc16;
    uint8_t buffer[256];
    ble_device_info_t *ble_device_info;
    ble_device_info = (ble_device_info_t*)parameter;
    uint16_encode(ble_device_info->conn_handle, &buffer[index]);
    index += 2;
    memcpy(&buffer[index], ble_device_info->mac_address, 6);
    index += 6;

    buffer[index++] = sequence++;
    buffer[index++] = group_id;
    buffer[index++] = command_id;
    uint16_encode(payload_length, &buffer[index]);
    index += 2;
    memcpy(&buffer[index], p_payload, payload_length);
    index += payload_length;
    crc16 = crc16_checksum(&buffer[8], index - 8, NULL);
    uint16_encode(crc16, &buffer[index]);
    index += 2;

    p_protocol->assemble_command_and_send(GROUP_ID_BLE_C, GID_BLE_C_CID_PTD_WRITE_CHAR, buffer, index);
}
