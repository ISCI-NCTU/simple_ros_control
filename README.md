# Disclaimer
This project isn't complete, and also not general enough. It only works for my own dirver now.
However, the project can still be modified to your own usage if you understand this project enough.

# Package Explaination
- **simple_ros_control**: 
Just for metapackage informations.
- **simple_ros_control_main**:
The main package for ROS control, including hardware_interface, transmission_interface..., etc. This package is responsible for registering joints to ROS controller manager and updating motor commands. Your robots will share this package.
- **communication_interface**(\*1):
Implement your communication functions here to fit your robots. Notice that all the functions defined here, such as **init()** and **update_pp()**, will be called by **simple_ros_control_main** package. So please don't add or delete functions. Just implement the what the function wants. 
- **simple_robot_description**:
Put your urdf here, with their names "simple_diff_robot.xacro"(if a differential drive platform) or "simple_robot.urdf"(if a robot arm). I will change these names to make more sense in the future.
- **simple_robot_moveit_config**:
If you use a robot arm, please put your moveit config here. Please DON'T change the package name (namely, **simple_robot_moveit_config**) because the package will be called by **simple_ros_control_main**.
- **simple_robot_config**: 
There are two .yaml here now: **arm_ros_control.yaml** and **diff_ros_control.yaml**. Modify the content, including degree of freedom, gear ratios, update frequency..., etc. to fit your robots.

\*1:This is beacuse I want to make **simple_ros_control_main** independent. More clearly, whenever **simple_ros_control_main** updates, different robots don't have to modify the motor communication functions. If you have better ideas, please tell me. Thanks!

# Hardwares
 - Faulhaber Controller
 - Panasonic MBDHT2510BA1 driver

# Prequest
Install [LibSerial](https://sourceforge.net/projects/libserial/files/?source=navbar) first, and here is the [documentation](http://libserial.sourceforge.net/). Also, install [IGH](http://www.etherlab.org/en/ethercat/) (see github wiki).
(Please run **$sudo ldconfig** after installation, or there may be some errors while starting the iceira_diff_control node)

#Installation
Do the followings in your ros workspace.
Clone this metapackage:
```
git clone https://github.com/willie5588912/simple_ros_control.git -b own-usage
```
Clone submodule:
```
cd simple_ros_control
git submodule init
git submodule update
```
Back to workspace:
```
cd ..
```
Clone **uart_faulhaber**:
```
https://github.com/willie5588912/uart_faulhaber.git
```
Clone **ethercat_igh**:
```
https://github.com/willie5588912/ethercat_igh.git
```
Compile:
```
cd ..
catkin_make
```


# Demo 1: Fake Update
Edit the config file:
```
rosed simple_robot_config arm_ros_control.yaml
```
Change the **control_type** to **fake**, namely:
```
control_type: fake
```
Launch controllers and some other things:
```
roslaunch simple_ros_control_main arm_ros_control.launch
```
Run the main control node:
```
rosrun simple_ros_control_main simple_ros_control_main
```
Launch moveit:
```
roslaunch simple_ros_control_main moveit_bringup.launch
```

Drag the robot arm, and then press **plan and execuate**, you can see the joints and actuators value change in the terminal running **simple_ros_control_main** node. The actuator values shown will be passed to the **communication_interface**. So you can use these values to write into your motors.

# Demo 2: EtherCAT
Come to my seat and turn on the Panasonic A5B drivers, plug the ethercat line in your computer.
Edit the config file:
```
rosed simple_robot_config arm_ros_control.yaml
```
Change the **control_type** to **pp**, namely:
```
control_type: pp
```
Launch IGH:
```
sudo /etc/init.d/ethercat start
```
```
sudo chmod a+w /dev/EtherCAT0
```
Launch controllers and some other things:
```
roslaunch simple_ros_control_main arm_ros_control.launch
```
Run the ROS control node:
```
rosrun simple_ros_control_main simple_ros_control_main
```
Now you should hear the sound "click" of the driver servo on.
Then launch moveit:
```
roslaunch simple_ros_control_main moveit_bringup.launch
```
Drag the robot arm, and then press **plan and execuate**, you can see the motor rotates, too. The joints and actuators values also show in the terminal running **simple_ros_control_main** node. The actuator values will be written to the dirver via the **communication_interface**.
