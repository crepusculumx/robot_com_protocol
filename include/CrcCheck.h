//
// Created by crepusculumx on 2021/12/21.
//

#ifndef ROBOTMOTORCONTROL_USER_SRC_CRCCHECK_H_
#define ROBOTMOTORCONTROL_USER_SRC_CRCCHECK_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "TypeChanger.h"

#ifdef __cplusplus
extern "C" {
#endif

uint16_t CRC_crunch(char x, uint16_t g_accum);

uint16_t CRC16_check(const uint8_t data[], size_t length);

#ifdef __cplusplus
}
#endif
#endif //ROBOTMOTORCONTROL_USER_SRC_CRCCHECK_H_
