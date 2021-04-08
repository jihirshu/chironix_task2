 #include <ros/ros.h>
 #include <move_base_msgs/MoveBaseAction.h>
 #include <actionlib/client/simple_action_client.h>
 #include <iostream>
 #include <fstream>
 #include <sstream>
 #include <string>
 typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
 

 int main(int argc, char** argv)
 {
   ros::init(argc, argv, "task2_cpp");
   std::string csv_path;
   // fetches the absolute path of the csv file through the param set in launch file
   ros::param::param<std::string>("/task2_cpp/CoordsCSVFile", csv_path, "io.csv");
   std::vector<double> coords;
   std::ifstream csvfile(csv_path);
   std::string line, csvItem;
   
   // reads the first line of the csv file and converts them to double type
   if (csvfile.is_open())
   { 
     while(getline(csvfile, line))
     {
        std::istringstream myline(line);
        while(getline(myline, csvItem, ',')) 
        {   csvItem.erase(std::remove(csvItem.begin(),csvItem.end(),' '),csvItem.end());
            coords.push_back(stod(csvItem));

        }

        break;
     }
   }
   MoveBaseClient ac("move_base", true);
 
   //wait for the action server to come up
   while(!ac.waitForServer(ros::Duration(10.0))){
     ROS_INFO("Waiting for the move_base action server to come up");
   }
 
   move_base_msgs::MoveBaseGoal goal;

   // sets the frame id to map so that the nodes understand 
   // that the coordinates are with respect to the map and not the robot base itself

   goal.target_pose.header.frame_id = "map";
   goal.target_pose.header.stamp = ros::Time::now();
 
   goal.target_pose.pose.position.x = coords[0];
   goal.target_pose.pose.position.y = coords[1];
   goal.target_pose.pose.orientation.w = 1.0;
   ROS_INFO("Sending goal");
   ac.sendGoal(goal);
 
  ac.waitForResult();
  std::ofstream myfile(csv_path, std::ios::app | std::ios::binary);
   if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    {
      ROS_INFO("Husky has moved to the desired location");
      myfile <<std::endl;
      myfile << "Husky has moved to the desired location" <<std::endl;
    }   
   else
   {
     ROS_INFO("Husky movement not possible");
     myfile <<std::endl;
     myfile << "Husky movement not possible"<< std::endl;
   }
  
  myfile.close();

 
 return 0;
}