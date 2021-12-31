from collections import deque
from ctypes import c_uint8
import rospy
import serial
from std_msgs.msg import Char

tx_queue = deque()
rx_queue = deque()


def tx_callback(data):
    tx_queue.append(c_uint8(data.data))


if __name__ == '__main__':
    rospy.init_node('ComNode', anonymous=True)

    rx_pub = rospy.Publisher('com_rx', Char, queue_size=200)
    tx_sub = rospy.Subscriber("com_tx", Char, tx_callback, queue_size=1000)

    ser = serial.Serial("/dev/ttyUSB0", 230400, timeout=0.5)
    print(ser.name)  # 设备名字
    print(ser.port)  # 读或者写端口
    print(ser.baudrate)  # 波特率
    print(ser.bytesize)  # 字节大小
    print(ser.parity)  # 校验位
    print(ser.stopbits)  # 停止位
    print(ser.timeout)  # 读超时设置
    print(ser.writeTimeout)  # 写超时
    print(ser.xonxoff)  # 软件流控
    print(ser.rtscts)  # 软件流控
    print(ser.dsrdtr)  # 硬件流控
    print(ser.interCharTimeout)  # 字符间隔超时
    while not rospy.is_shutdown():
        # send
        while len(tx_queue) != 0:
            s = tx_queue.popleft()
            ser.write(s)

        # read
        # if com.inWaiting() != 0:
        #     s = com.read(com.inWaiting())
        #     for c in s:
        #         rx_pub.publish(c)

    rospy.spin()
