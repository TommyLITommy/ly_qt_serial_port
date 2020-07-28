#include "flash.h"
#include "ly_util.h"
#include "ble_protocol.h"

flash::flash()
{

}

flash::flash(ble_protocol *p)
{
    p_ble_protocol = p;
}

//conn_handle, mac_address, ble+(flash_id, start_address, length);
void flash::flash_erase(uint8_t flash_id, uint32_t start_address, uint32_t length, uint8_t destination, void *parameter)
{
    uint8_t buffer[200];
    uint16_t index = 0;

    switch(destination)
    {
        case DESTINATION_LOCAL_DEVICE:
            break;
        case DESTINATION_REMOTE_DEVICE:
            buffer[index++] = flash_id;
            uint32_encode(start_address, &buffer[index]);
            index += 4;
            uint32_encode(length, &buffer[index]);
            index += 4;

            p_ble_protocol->ble_command_assemble(BLE_GROUP_ID_FLASH, BLE_GID_FLASH_CID_ERASE, buffer, index, parameter);
            break;
        default:
            break;
    }
}

void flash::flash_read(uint8_t flash_id, uint32_t start_address, uint32_t length, uint8_t destination, void *parameter)
{
    uint8_t buffer[200];
    uint16_t index = 0;

    switch(destination)
    {
        case DESTINATION_LOCAL_DEVICE:
            break;
        case DESTINATION_REMOTE_DEVICE:
            buffer[index++] = flash_id;
            uint32_encode(start_address, &buffer[index]);
            index += 4;
            uint32_encode(length, &buffer[index]);
            index += 4;

            p_ble_protocol->ble_command_assemble(BLE_GROUP_ID_FLASH, BLE_GID_FLASH_CID_READ, buffer, index, parameter);
            break;
        default:
            break;
    }
}

void flash::flash_write(uint8_t flash_id, uint32_t start_address, uint32_t length, uint8_t *p_write_data, uint8_t destination, void *parameter)
{
    uint8_t buffer[250];
    uint16_t index = 0;

    switch(destination)
    {
        case DESTINATION_LOCAL_DEVICE:
            break;
        case DESTINATION_REMOTE_DEVICE:
            buffer[index++] = flash_id;
            uint32_encode(start_address, &buffer[index]);
            index += 4;
            uint32_encode(length, &buffer[index]);
            index += 4;

            memcpy(&buffer[index], p_write_data, length);
            index += length;

            p_ble_protocol->ble_command_assemble(BLE_GROUP_ID_FLASH, BLE_GID_FLASH_CID_WRITE, buffer, index, parameter);
            break;
        default:
            break;
    }
}
