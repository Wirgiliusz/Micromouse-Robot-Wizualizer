#!usr/bin/env python
import sys
import bluetooth
import rospy
from std_msgs.msg import String

target_name = "KiM_BT"
target_address = "98:D3:91:FD:71:CE"
passKey = "1235"


if __name__ == "__main__":
    # Creating ros node
    pub = rospy.Publisher("sender", String, queue_size=1)
    rospy.init_node("sender_node", anonymous=True)

    # Connecting with robot bluetooth
    print("Type:")
    print("[r] - to connect to robot and start live visualization")
    print("[m] - to start writing commands for manual visualization")
    choice = input()
    if choice == "r":
        client_socket = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
        client_socket.connect(("98:D3:91:FD:71:CE",1))
        print("Connected to the robot. Press enter to start")
        input()

        # Starting robot
        client_socket.send('1')

        # Reading and sending data
        while(True):
            try:
                data = client_socket.recv(1)
                data = str(data).replace("b", "").replace("'", "")
                if data == '0':
                    messege = "NORTH"
                elif data == '1':
                    messege = "WEST"
                elif data == '2':
                    messege = "SOUTH"
                elif data == '3':
                    messege = "EAST"
                else:
                    messege = "UKNOWN COMMAND"
                print("Received massege: ", messege)

                rospy.loginfo(messege)
                pub.publish(messege)

            except rospy.ROSInterruptException:
                client_socket.send('0')
                client_socket.close()
    elif choice == "m":
        print("Type commands [0-NORTH, 1-WEST, 2-SOUTH, 3-EAST")
        while(True):
            data = input()
            if data == '0':
                messege = "NORTH"
            elif data == '1':
                messege = "WEST"
            elif data == '2':
                messege = "SOUTH"
            elif data == '3':
                messege = "EAST"
            elif data == 'q':
                break
            else:
                messege = "UKNOWN COMMAND"
            print("Received massege: ", messege)
            rospy.loginfo(messege)
            pub.publish(messege)
    else:
        print("Unknown command! Exiting..")
        sys.exit()

    
