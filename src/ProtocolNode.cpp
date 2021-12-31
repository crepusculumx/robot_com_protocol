//
// Created by crepusculumx on 2021/12/25.
//
#include "ProtocolNode.h"

ProtocolNode::ProtocolNode(ros::NodeHandle &nh) : nh(nh) {
  this->tx_pub = nh.advertise<std_msgs::Char>("com_tx", 1000);
  this->axle_cmds_sub = nh.subscribe("axle_cmds", 1000, &ProtocolNode::axle_cmds_callback, this);
}

void ProtocolNode::axle_cmds_callback(const robot_com_protocol::AxleCmds &axle_cmds) {
  std::string s = protocol_dump(axle_cmds);
  for (char c : s) {
    std_msgs::Char pub_data;
    pub_data.data = c;
    this->tx_pub.publish(pub_data);
  }
}

std::string protocol_dump(robot_com_protocol::AxleCmds axle_cmds) {
  uint8_t buffer[MAX_PACKET_LENGTH];
  memset(buffer, 0, MAX_PACKET_LENGTH);
  buffer[0] = HD_NUM;
  buffer[1] = ID_NUM;

  buffer[3] = PRE;
  buffer[4] = BID;
  size_t it = 17; //2 + 1 + 14

  for (size_t i = 0; i < AXLE_NUM; i++) {
    data_int16_to_int8(axle_cmds.axle_cmd[i].mode, buffer, &it);
    data_int16_to_int8(axle_cmds.axle_cmd[i].current, buffer, &it);
    data_int16_to_int8(axle_cmds.axle_cmd[i].velocity, buffer, &it);
    data_int16_to_int8(axle_cmds.axle_cmd[i].position, buffer, &it);
  }

  //todo 透传

  buffer[2] = it + 2;// +crc

  uint16_t crc = CRC16_check(buffer, it);
  buffer[it] = (crc & 0xff00) >> 8;
  buffer[it + 1] = (crc & 0x00ff);

  it += 2;
  std::string res;
  for (size_t i = 0; i < it; i++) {
    res.push_back((char) buffer[i]);
  }
  return res;
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "ProtocolNode");
  ros::NodeHandle n;
  ProtocolNode protocol_node(n);
  ros::spin();
  return 0;
}