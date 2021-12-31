//
// Created by crepusculumx on 2021/12/20.
//

#include "ComProtocol.h"

int8_t parse_msg(uint8_t data[], size_t length, ProtocolInner *inner_msg) {
  if (length != MSG_LENGTH) {
    return -1;
  }

  inner_msg->head[0] = data[0];
  inner_msg->head[1] = data[1];

  if (inner_msg->head[0] != PRE || inner_msg->head[1] != BID) {
    return -2;
  }

  size_t it = 2;
  inner_msg->cur = data_int8_to_int16(data, &it);

  it += 10;//轴指令前位置

  for (size_t i = 0; i < AXLE_NUM; i++) {
    inner_msg->axle_cmd[i].mode = data_int8_to_int16(data, &it);
    inner_msg->axle_cmd[i].current = data_int8_to_int16(data, &it);
    inner_msg->axle_cmd[i].velocity = data_int8_to_int16(data, &it);
    inner_msg->axle_cmd[i].position = data_int8_to_int16(data, &it);
  }
  return 0;
}

int8_t parse_packet(const uint8_t data[], const size_t length, ProtocolPacket *data_packet) {
  data_packet->head[0] = data[0];
  data_packet->head[1] = data[1];

  // 包头错误
  if (data_packet->head[0] != HD_NUM || data_packet->head[1] != ID_NUM) {
    return -1;
  }

  data_packet->length = data[2];

  // 包长错误
  if (data_packet->length >= MAX_PACKET_LENGTH || data_packet->length > length) {
    return -2;
  }

  //CRC校验
  uint16_t crc_res = data_packet->crc = CRC16_check(data, length - 2);
  if ((data[length - 2]) != ((crc_res & 0xff00) >> 8) || (data[length - 1] != (crc_res & 0x00ff))) {
    return -3;
  }

  // 移除透传,并且只保留msg
  uint8_t msg_data[MAX_PACKET_LENGTH + 10];
  size_t msg_data_it = 0;
  //开头跳过HD_NUM ID_NUM length，后面不包括crc
  for (size_t i = 3; i < length - 2; i++) {
    msg_data[msg_data_it] = data[i];
    msg_data_it++;

    if (data[i - 2] == HD_NUM && data[i - 1] == 0 && data[i] == ID_NUM) {
      msg_data[msg_data_it - 2] = msg_data[msg_data_it - 1];
      msg_data_it--;
    }
  }

  // 解析内容
  uint8_t parse_msg_res = parse_msg(msg_data, msg_data_it, &(data_packet->inner_msg));
  if (parse_msg_res != 0) {
    return -4;
  }

  return 0;
}