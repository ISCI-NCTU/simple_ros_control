#ifndef COMMUNICATION_INTERFACE_H
#define COMMUNICATION_INTERFACE_H

#include <vector>
#include <string>
#include <uart_faulhaber/uart_faulhaber.h>

namespace communication_interface 
{
  SerialHandle my_port;
  std::string control_type_;
  int n_dof_;

  void init(std::string, int);
  void terminate();
  std::vector<double> get_home_pos();
  std::vector<double> update_pp(std::vector<double>);
  std::vector<double> update_pv(std::vector<double>);
  std::vector<double> update_vv(std::vector<double>);
  std::vector<double> update_vp(std::vector<double>);
  void update_vp_fake(std::vector<double>);
  void write_cmd_pos(std::vector<double>);
}

#endif
