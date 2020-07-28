#ifndef LY_UTIL_H
#define LY_UTIL_H

#include "type.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint8_t uint16_encode(uint16_t value, uint8_t * p_encoded_data);
uint8_t uint24_encode(uint32_t value, uint8_t * p_encoded_data);
uint8_t uint32_encode(uint32_t value, uint8_t * p_encoded_data);
uint8_t uint40_encode(uint64_t value, uint8_t * p_encoded_data);
uint8_t uint48_encode(uint64_t value, uint8_t * p_encoded_data);
uint16_t uint16_decode(const uint8_t * p_encoded_data);
uint16_t uint16_big_decode(const uint8_t * p_encoded_data);
uint32_t uint24_decode(const uint8_t * p_encoded_data);
uint32_t uint32_decode(const uint8_t * p_encoded_data);
uint32_t uint32_big_decode(const uint8_t * p_encoded_data);
uint8_t uint16_big_encode(uint16_t value, uint8_t * p_encoded_data);
uint8_t uint32_big_encode(uint32_t value, uint8_t * p_encoded_data);
uint64_t uint40_decode(const uint8_t * p_encoded_data);
uint64_t uint48_decode(const uint8_t * p_encoded_data);
uint16_t crc16_checksum(uint8_t const *p_data, uint32_t size, uint16_t const *p_crc);

#endif // LY_UTIL_H
