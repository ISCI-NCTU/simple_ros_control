#include <iostream>
#include <sstream>
#include <communication_interface/communication_interface.h>
#include <uart_faulhaber/uart_faulhaber.h>

extern "C" {
	#include <ethercat_igh/ethercat_igh.h>
}

void communication_interface::init(std::string m_control_type_, int m_n_dof_)
{
	control_type_ = m_control_type_;
	n_dof_ = m_n_dof_;

	if(control_type_ == "ethercat")
	{
	  igh_configure();
	  igh_start();
	}
	else if(control_type_ == "uart")
	{
	  my_port.set_port("/dev/ttyUSB0");
	  my_port.set_baudRate(9600);
	  my_port.set_dataBits(8);
	  my_port.set_stopBit(1);
	  my_port.set_parity(false);
	  my_port.set_hardwareFlowControl(false);
	}
}

void communication_interface::terminate()
{
	if(control_type_ == "ethercat")
		igh_cleanup();
	else if(control_type_ == "uart")
	{
		//TODO
	}
}

void communication_interface::write_cmd_pos(std::vector<double>)
{
	if(control_type_ == "ethercat")
	{
		//TODO
	}
	else if(control_type_ == "uart")
	{
		//TODO
	}
}

std::vector<double> communication_interface::get_home_pos()
{
	if(control_type_ == "ethercat")
	{
		int *home_pos_temp_;
		std::vector<double> home_pos_temp_vec_;
		home_pos_temp_ = igh_get_home_pos();

		// Because now I only have 2 controller (while the dof or robot is 3), 
		// so the third joint I just initialize as zero.
		// This step shouldn't be done if the number of controllers is correct.
		for(int i = 0; i < n_dof_ - 1; i++)
		home_pos_temp_vec_.push_back(*(home_pos_temp_ + i));
		home_pos_temp_vec_.push_back(0);

		return home_pos_temp_vec_;
	}
	else if(control_type_ == "uart")
	{
		//TODO
	}
}

// Update pos and return pos
std::vector<double> communication_interface::update_pp(std::vector<double> act_cmd_pos_)
{
	if(control_type_ == "ethercat")
	{
		int cmd_pos_temp_[n_dof_];	
		int *curr_pos_temp_;
		std::vector<double> curr_pos_temp_vec_;

		// For the same reason that I only have two controllers, 
		// so I only update the first two joints, 
		// and keep the third joint returning same value as the command value.
		for(int i = 0; i < act_cmd_pos_.size() - 1; i++)
			cmd_pos_temp_[i] = act_cmd_pos_[i];
		cmd_pos_temp_[n_dof_ - 1] = 0;

		curr_pos_temp_ = igh_update(cmd_pos_temp_);
		
		for(int i = 0; i < act_cmd_pos_.size() - 1; i++)
			curr_pos_temp_vec_.push_back(*(curr_pos_temp_ + i));

		curr_pos_temp_vec_.push_back(act_cmd_pos_[n_dof_ - 1]);

		return curr_pos_temp_vec_;
	}
	else if(control_type_ == "uart")
	{
		//TODO
	}

}

// Update pos and return velocity
std::vector<double> communication_interface::update_pv(std::vector<double> act_cmd_pos_)
{
	if(control_type_ == "ethercat")
	{
		//TODO
	}
	else if(control_type_ == "uart")
	{
		//TODO
	}
}

// Update velocity and return velocity
std::vector<double> communication_interface::update_vv(std::vector<double> act_cmd_vel_)
{
	if(control_type_ == "ethercat")
	{
		//TODO
	}
	else if(control_type_ == "uart")
	{
		// Read command velocity 
		// (Fake, just show on the terminal, not updating)
		std::stringstream ss_curr_vel_;
		for(int i = 0; i < act_cmd_vel_.size(); i++)
		{
			ss_curr_vel_.str("");
			ss_curr_vel_ << i + 1 << "pos\r";
			my_port.writeData(ss_curr_vel_.str());
			std::cout << my_port.readData() << std::endl;
		}

		// Write command velocity
		std::stringstream ss_cmd_vel_;
		for(int i = 0; i < act_cmd_vel_.size(); i++)
		{
			ss_cmd_vel_.str("");
			if(i % 2 == 0)
			{
				ss_cmd_vel_ << i + 1 << "v" << -act_cmd_vel_[i] << "\r";
				my_port.writeData(ss_cmd_vel_.str());
			}
			else
			{
				ss_cmd_vel_ << i + 1 << "v" << act_cmd_vel_[i] << "\r";
				my_port.writeData(ss_cmd_vel_.str());
			}
		}

		return act_cmd_vel_;
	}
}

// Update velocity and return pos
std::vector<double> communication_interface::update_vp(std::vector<double> act_cmd_vel_)
{
	if(control_type_ == "ethercat")
	{
		//TODO
	}
	else if(control_type_ == "uart")
	{
		//TODO
	}
}
