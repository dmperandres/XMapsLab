/*
* Practicas de IG
* Domingo Martin Perandres© 2014-2018
* dmartin@ugr.es
*
* GPL 3
*/

#ifndef FILE_ELEMENTS_WEIGHT
#define FILE_ELEMENTS_WEIGHT

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include "vertex.h"

#include "file_io.h"

#include "element_data.h"

class _file_elements_weight: public _file_io
{
public:
  void read(std::vector<_element_data_ns::_data_element_weight> &Vec_elements_weight);
};

#endif
