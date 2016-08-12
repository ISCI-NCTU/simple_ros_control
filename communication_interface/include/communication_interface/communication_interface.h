#ifndef COMMUNICATION_INTERFACE_H
#define COMMUNICATION_INTERFACE_H

#include <vector>

namespace communication_interface 
{
  void init();
  void terminate();
  std::vector<double> get_curr_pos();
  std::vector<double> update(std::vector<double>);
  void write_cmd_pos(std::vector<double>);
}

#endif
