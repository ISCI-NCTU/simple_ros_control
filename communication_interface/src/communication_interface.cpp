#include <communication_interface/communication_interface.h>
#include <iostream>

extern "C" {
	#include <ethercat_igh/ethercat_igh.h>
}

#define IGH_DOF 3

void communication_interface::init()
{
	igh_configure();
	igh_start();
}

void communication_interface::terminate()
{
	igh_cleanup();
}

void communication_interface::write_cmd_pos(std::vector<double>)
{
}

std::vector<double> communication_interface::get_home_pos()
{
	int *home_pos_temp_;
	std::vector<double> home_pos_temp_vec_;
	home_pos_temp_ = igh_get_home_pos();
	
	// Because now I only have 2 controller (while the dof or robot is 3), 
	// so the third joint I just initialize as zero.
	// This step shouldn't be done if the number of controllers is correct.
	for(int i = 0; i < IGH_DOF - 1; i++)
		home_pos_temp_vec_.push_back(*(home_pos_temp_ + i));
	home_pos_temp_vec_.push_back(0);

	return home_pos_temp_vec_;
}

std::vector<double> communication_interface::update(std::vector<double> act_cmd_pos_)
{
	int cmd_pos_temp_[IGH_DOF];	
	int *curr_pos_temp_;
	std::vector<double> curr_pos_temp_vec_;

	// For the same reason that I only have two controllers, 
	// so I only update the first two joints, 
	// and keep the third joint returning same value as the command value.
	for(int i = 0; i < act_cmd_pos_.size() - 1; i++)
		cmd_pos_temp_[i] = act_cmd_pos_[i];
	cmd_pos_temp_[IGH_DOF - 1] = 0;

	curr_pos_temp_ = igh_update(cmd_pos_temp_);
	
	for(int i = 0; i < act_cmd_pos_.size() - 1; i++)
		curr_pos_temp_vec_.push_back(*(curr_pos_temp_ + i));

	curr_pos_temp_vec_.push_back(act_cmd_pos_[IGH_DOF - 1]);

	return curr_pos_temp_vec_;
}
