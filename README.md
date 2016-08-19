# Disclaimer
This project isn't complete, and also not general enough. It only works for my own dirver now.
However, the project can still be modified to your own usage if you understand this project enough.

# Introduction
This project is dedicated to create a ROS Control tool that you can control your physical robot with ease. 
If you have multiple robots, with different motors, degree of freedom ..., etc. All of them can use this project.
For example, I have a simple robot arm and a differential drive platform robot. Both of them can share the same code with their own settings. This will be shown later.

# Package Explaination
- **simple_ros_control**: 
Just for metapackage informations.
- **simple_ros_control_main**:
The main package for ROS control, including hardware_interface, transmission_interface..., etc. This package is responsible for registering joints to ROS controller manager and updating motor commands. Your robots will share this package.
- **communication_interface**:
You have to implement your communication functions here to fit your robots. Notice that all the functions defined here, such as **init()** and **update_pp()**, will be called by **simple_ros_control_main** package. So please don't add or delete functions. Just implement the what the function wants. (This is beacuse I want to make **simple_ros_control_main** independent. More clearly, whenever **simple_ros_control_main** updates, different robots don't have to modify the motor communication functions. If you have better ideas, please tell me. Thanks!)
- **simple_robot_description**:
You have to put your urdf here, with their names "simple_diff_robot.xacro"(if a differential drive platform) or "simple_robot.urdf"(if a robot arm). I will change these names to make more sense in the future.
- **simple_robot_moveit_config**:
If you use a robot arm, please put your moveit config here. Please DON'T change the package name (namely, **simple_robot_moveit_config**) because the package will be called by **simple_ros_control_main**.
- **simple_robot_config**: 
There are two .yaml here now: **arm_ros_control.yaml** and **diff_ros_control.yaml**. Modify the content, including degree of freedom, gear ratios, update frequency..., etc. to fit your robots.

You can change the \*.yaml in **simple_robot_config** to fit your own robot, 
including degree of freedom, gear ratios, update frequency..., etc.
And also implement your motor communication functions in **communication_interface**.

I use a metapackage for this project. There are mainly two parts. 
The main part is **simple_ros_control_main** package, which I use a submodule in this project.
Other packages can be treated as another part.

The main idea is that all the ROS control works are done in the **simple_ros_control_main**, 
while all the custom settings are in the remaining packages.
More clearly, whenever **simple_ros_control_main** updates, you don't have to change the custom settings.



