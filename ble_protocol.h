#ifndef BLE_PROTOCOL_H
#define BLE_PROTOCOL_H

#include "type.h"
#include "protocol.h"

class ble_protocol
{
public:
    ble_protocol();
    ble_protocol(protocol *p);
    void ble_command_assemble(uint8_t group_id, uint8_t command_id, uint8_t *p_payload, uint16_t payload_length, void *parameter);
public:
    uint8_t sequence;
private:
    protocol *p_protocol;
};

#define BLE_PROTOCOL_MIN_SIZE						7

#define BLE_PROTOCOL_SEQUENCE_FIELD_OFFSET 			0
#define BLE_PROTOCOL_GROUP_ID_FIELD_OFFSET			1
#define BLE_PROTOCOL_COMMAND_ID_FIELD_OFFSET		2
#define BLE_PROTOCOL_PAYLOAD_LENGTH_FIELD_OFFSET	3
#define BLE_PROTOCOL_PAYLOAD_OFFSET					5

typedef enum
{
    BLE_GROUP_ID_DEBUG = 0x06,
    BLE_GROUP_ID_FLASH = 0x07,
}ble_group_id_t;

typedef enum
{
    BLE_GID_DEBUG_CID_SHORT_PRESS,
    BLE_GID_DEBUG_CID_LONG_PRESS,
    BLE_GID_DEBUG_CID_SYSTEM_RESET,
    BLE_GID_DEBUG_CID_DATABASE_DISCOVERY,
}ble_group_debug_cid_t;

typedef enum
{
    BLE_GID_FLASH_CID_ERASE,
    BLE_GID_FLASH_CID_WRITE,
    BLE_GID_FLASH_CID_READ,
}ble_group_flash_cid_t;

enum
{
    FLASH_ID_INTERNAL = 0,
    FLASH_ID_EXTERNAL，
};

typedef struct
{
    uint16_t conn_handle;
    uint8_t mac_address[6];
}ble_device_info_t;

#endif // BLE_PROTOCOL_H
