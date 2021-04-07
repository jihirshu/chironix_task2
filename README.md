# Chironix Task 2


### Ros Details
Assuming that your system has ros melodic installed on your system. <strong>If not installed</strong>, please go to this [link](http://wiki.ros.org/melodic/Installation/Ubuntu), follow the instructions and install melodic full desktop version using the following command :

	sudo apt install ros-melodic-desktop-full

The implementation also requires the installation of "timed_roslaunch". If it is not installed on your system, please use the following command to install the same : 

	sudo apt install ros-melodic-timed-roslaunch

### Husky Installation
Assuming that your system has the husky simulation package, husky navigation package and husky visualization package installed. <strong>If not installed</strong>, please use the following commands : 

	sudo apt-get update
	sudo apt-get install ros-melodic-husky-simulator
	export HUSKY_GAZEBO_DESCRIPTION=$(rospack find husky_gazebo)/urdf/description.gazebo.xacro
	sudo apt-get install ros-melodic-husky-navigation
	sudo apt-get install ros-melodic-husky-viz

Please make sure that everything is in order by running these four commands in separate terminals : 

	roslaunch husky_gazebo husky_empty_world.launch
	roslaunch husky_gazebo husky_playpen.launch
	roslaunch husky_viz view_robot.launch
	roslaunch husky_navigation amcl_demo.launch

If any of the above commands repeatedly fail, make sure that the instructions on this [tutorial](http://wiki.ros.org/Robots/Husky) has been followed.		


# Task 2 Installation:
If all previously mentioned requirements have been fulfilled, we can proceed with the package installation for task 2. Clone the repo into a desired location. In this example we will use the local Desktop and install the module.

    cd ~/Desktop
    git clone https://github.com/jihirshu/chironix_task2.git
    cd chironix_task2
    catkin_make

## Usage

To launch task 2 cpp node, open a terminal and execute the following commands : 

    source ~/Desktop/chironix_task2/devel/setup.bash
    roslaunch task2_cpp task2_cpp.launch
    
To launch task 2 python node, open a terminal and execute the following commands : 

    source ~/Desktop/chironix_task2/devel/setup.bash
    roslaunch task2_python task2_python.launch
    
Please wait when the launch files are executing as some time delay has been added between internal node launches.
