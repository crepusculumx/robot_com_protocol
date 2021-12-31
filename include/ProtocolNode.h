//
// Created by crepusculumx on 2021/12/28.
//

#ifndef SRC_ROBOT_COM_PROTOCOL_INCLUDE_PROTOCOLNODE_H_
#define SRC_ROBOT_COM_PROTOCOL_INCLUDE_PROTOCOLNODE_H_

#include <deque>
#include <string>

#include "ros/ros.h"
#include "std_msgs/Char.h"

#include "robot_com_protocol/AxleCmds.h"

#include "ComProtocol.h"
#include "TypeChanger.h"
#include "CrcCheck.h"

class ProtocolNode {
 private:
  ros::NodeHandle &nh;
  ros::Publisher tx_pub;
  ros::Subscriber axle_cmds_sub;
  void axle_cmds_callback(const robot_com_protocol::AxleCmds &axle_cmds);

 public:
  ProtocolNode(ros::NodeHandle &nh);
};

std::string protocol_dump(robot_com_protocol::AxleCmds axle_cmds);
#endif //SRC_ROBOT_COM_PROTOCOL_INCLUDE_PROTOCOLNODE_H_
