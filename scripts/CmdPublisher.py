import rospy
from robot_com_protocol.msg import AxleCmds

if __name__ == '__main__':
    rospy.init_node('CmdPublisher', anonymous=True)
    pub = rospy.Publisher('axle_cmds', AxleCmds, queue_size=10)

    rate = rospy.Rate(10)  # 10hz
    while not rospy.is_shutdown():
        axle_cmds = AxleCmds()
        for i in range(18):
            axle_cmds.axle_cmd[i].mode = 2
            axle_cmds.axle_cmd[i].velocity = 10
        pub.publish(axle_cmds)

        rate.sleep()
