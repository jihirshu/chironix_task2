#!/usr/bin/env python
import rospy
import actionlib
from move_base_msgs.msg import MoveBaseAction, MoveBaseGoal
import csv


def moveToLoc(x,y):
    
    client = actionlib.SimpleActionClient('move_base',MoveBaseAction)
    client.wait_for_server()

    goal = MoveBaseGoal()

    # set frame id to map to convey that co-ordinates are with respect to map 
    # and not the robot base itself

    goal.target_pose.header.frame_id = "map"
    goal.target_pose.header.stamp = rospy.Time.now()
    goal.target_pose.pose.position.x = x
    goal.target_pose.pose.position.y = y
    goal.target_pose.pose.orientation.w = 1.0

    client.send_goal(goal)
    wait = client.wait_for_result()
    if not wait:
        rospy.logerr("Action server not available!")
        rospy.signal_shutdown("Action server not available!")
    else:
        return client.get_result()




if __name__ == '__main__':
    try:
        rospy.init_node('task2_python', anonymous=True)

        # fetches the absolute path of the csv file
        csvPath = rospy.get_param('/task2_python/CoordsCSVFile', 'io.csv')
        x = None
        y = None
        with open(csvPath) as file:
            lines = csv.reader(file, delimiter=',')
            for line in lines:
                x = line[0]
                y = line[1]
                break;
        x = float(x.replace(" ",""))
        y = float(y.replace(" ",""))
        result = moveToLoc(x,y)

        if result:
            with open(csvPath, mode='a') as wfile:
                writer = csv.writer(wfile, delimiter=',', lineterminator='\n')
                writer.writerow(["Husky has moved to the desired location"])
            rospy.loginfo("Husky has moved to the desired location")
    except rospy.ROSInterruptException:
        with open(csvPath, mode='a') as wfile:
            writer = csv.writer(wfile, delimiter=',', lineterminator='\n')
            writer.writerow(["There was a problem moving Husky to the desired location"])
        rospy.loginfo("There was a problem moving Husky to the desired location")
        