# Disclaimer
This project isn't complete, and also not general enough. It only works for my own dirver now.
However, the project can still be modified to your own usage if you understand this project enough.

# Introduction
This project is dedicated to create a ROS Control tool that you can control your physical robot with ease. 
If you have multiple robots, with different motors, degree of freedom ..., etc. All of them can use this project.

# Package Explaination
- **simple_ros_control**: 
Just for metapackage informations.
- **simple_ros_control_main**:
The main package for ROS control, including hardware_interface, transmission_interface..., etc. This package is responsible for registering joints to ROS controller manager and updating motor commands. Your robots will share this package.

You can change the \*.yaml in **simple_robot_config** to fit your own robot, 
including degree of freedom, gear ratios, update frequency..., etc.
And also implement your motor communication functions in **communication_interface**.

I use a metapackage for this project. There are mainly two parts. 
The main part is **simple_ros_control_main** package, which I use a submodule in this project.
Other packages can be treated as another part.

The main idea is that all the ROS control works are done in the **simple_ros_control_main**, 
while all the custom settings are in the remaining packages.
More clearly, whenever **simple_ros_control_main** updates, you don't have to change the custom settings.



