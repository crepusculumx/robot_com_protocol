//
// Created by crepusculumx on 2021/12/28.
//

#include "SerialNode.h"
#include "ros/ros.h"
#include <serial/serial.h>

int main(int argc, char **argv) {
  ros::init(argc, argv, "ProtocolNode");
  ros::NodeHandle n;
  ros::spin();
  return 0;
}