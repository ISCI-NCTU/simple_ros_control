#include <iostream>
#include <sstream>
#include <communication_interface/communication_interface.h>

void communication_interface::init(std::string m_control_type_, int m_n_dof_)
{
}

void communication_interface::terminate()
{
}

void communication_interface::write_cmd_pos(std::vector<double>)
{
}

std::vector<double> communication_interface::get_home_pos()
{
}

// Update pos and return pos
std::vector<double> communication_interface::update_pp(std::vector<double> act_cmd_pos_)
{
}

// Update pos and return velocity
std::vector<double> communication_interface::update_pv(std::vector<double> act_cmd_pos_)
{
}

// Update velocity and return velocity
std::vector<double> communication_interface::update_vv(std::vector<double> act_cmd_vel_)
{
}

// Update velocity and return pos
std::vector<double> communication_interface::update_vp(std::vector<double> act_cmd_vel_)
{
}
