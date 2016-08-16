#ifndef COMMUNICATION_INTERFACE_H
#define COMMUNICATION_INTERFACE_H

#include <vector>

namespace communication_interface 
{
  void init();
  void terminate();
  std::vector<double> get_home_pos();
  std::vector<double> update_pp(std::vector<double>);
  std::vector<double> update_pv(std::vector<double>);
  std::vector<double> update_vv(std::vector<double>);
  std::vector<double> update_vp(std::vector<double>);
  void write_cmd_pos(std::vector<double>);
}

#endif
