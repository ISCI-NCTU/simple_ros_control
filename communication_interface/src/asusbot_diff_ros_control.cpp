#include <asusbot_diff_ros_control/asusbot_diff_hardware_interface.h>
#include <asusbot_diff_ros_control/asusbot_diff_serial.h>

void serialInitialize(SerialHandle *my_port)
{
	//port settings
	my_port->set_baudRate(9600);
	my_port->set_dataBits(8);
	my_port->set_stopBit(1);
	my_port->set_parity(false);
	my_port->set_hardwareFlowControl(true);

	//initial Faulhaber motor
	my_port->writeData("en\r");
}

int main(int argc, char **argv)
{
  //initialize ros
  ros::init(argc, argv, "asusbot_diff_ros_control");
  ros::NodeHandle nh;

  MyRobot robot;
  controller_manager::ControllerManager cm(&robot, nh);
  
  //port setting
  SerialHandle my_port("/dev/ttyUSB0");
  serialInitialize(&my_port);

  //start loop
  ros::Rate rate(1.0 / robot.getPeriod().toSec());
  ros::AsyncSpinner spinner(1);
  spinner.start();

  while (ros::ok())
  {
     robot.read(&my_port);
     robot.write(&my_port);
	 
     cm.update(robot.getTime(), robot.getPeriod());
	 rate.sleep();
  }
  spinner.stop();

  return 0;
}
