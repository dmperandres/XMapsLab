#ifndef ATOMIC_DATA
#define ATOMIC_DATA

#include <string>
#include <vector>
#include <iostream>
#include <QColor>

//#include <opencv.hpp>

struct _atomic_data{
public:
  std::string Short_name;
  std::string Name;
  float Atomic_number=0;
  float Atomic_weight=0;
  QColor Color;
};

#endif


