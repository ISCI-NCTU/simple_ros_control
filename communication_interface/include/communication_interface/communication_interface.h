#ifndef COMMUNICATION_INTERFACE_H
#define COMMUNICATION_INTERFACE_H

#include <vector>

namespace communication_interface 
{
  void init();
  void terminate();
  std::vector<int> get_curr_pos();
  std::vector<int> update(std::vector<int>);
}

#endif
