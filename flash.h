#ifndef FLASH_H
#define FLASH_H

#include "protocol.h"
#include "ble_protocol.h"

enum
{
    DESTINATION_LOCAL_DEVICE = 0,
    DESTINATION_REMOTE_DEVICE
};

class flash
{
public:
    flash();
    flash(ble_protocol *p);
    void flash_erase(uint8_t flash_id, uint32_t start_address, uint32_t length, uint8_t destination, void *parameter);
    void flash_read(uint8_t flash_id, uint32_t start_address, uint32_t length, uint8_t destination, void *parameter);
    void flash_write(uint8_t flash_id, uint32_t start_address, uint32_t length, uint8_t *p_write_data, uint8_t destination, void *parameter);
private:
    ble_protocol *p_ble_protocol;
};

#endif // FLASH_H
