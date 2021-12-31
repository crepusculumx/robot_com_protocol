//
// Created by crepusculumx on 2021/12/20.
//

#ifndef ROBOTMOTORCONTROL_USER_SRC_COMPROTOCOL_H_
#define ROBOTMOTORCONTROL_USER_SRC_COMPROTOCOL_H_

#include <stdbool.h>
#include <string.h>

#include "TypeChanger.h"
#include "CrcCheck.h"


#define AXLE_NUM 18

#define MAX_PACKET_LENGTH 170

// 包头标识
#define HD_NUM 0xFA
#define ID_NUM 0x01

// 数据头标识
#define PRE 0xFB
#define BID 0x00

#define MSG_LENGTH 158

typedef struct AxleCmd {
  int16_t mode;
  int16_t current;
  int16_t velocity;
  int16_t position;
} AxleCmd;

// 通信协议
typedef struct ProtocolInner {
  uint8_t head[2];
  uint16_t cur;
  uint8_t temp[10];
  AxleCmd axle_cmd[AXLE_NUM];
} ProtocolInner;

// 包结构
typedef struct ProtocolPacket {
  uint8_t head[2];
  uint8_t length;
  ProtocolInner inner_msg;
  uint16_t crc;
} ProtocolPacket;

#ifdef __cplusplus
extern "C" {
#endif

/*
 * 解析通信协议
 * 根据data[0]-data[length - 1]内容，将解析完成内容写入*inner_msg
 */
int8_t parse_msg(uint8_t data[], size_t length, ProtocolInner *inner_msg);

/*
 * 解析通信包
 * 根据data[0]-data[length - 1]内容，将解析完成内容写入*data_packet
 */
int8_t parse_packet(const uint8_t data[], size_t length, ProtocolPacket *data_packet);

#ifdef __cplusplus
}
#endif

#endif //ROBOTMOTORCONTROL_USER_SRC_COMPROTOCOL_H_
