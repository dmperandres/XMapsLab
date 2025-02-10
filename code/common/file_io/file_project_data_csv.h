//LIC

#ifndef FILE_PROJECT_DATA_CSV
#define FILE_PROJECT_DATA_CSV

#include <string>
#include <vector>
#include <cctype>

#include <QString>

#include "file_io.h"

#include "project_data.h"


namespace _file_project_data_csv_ns {
  const std::vector<std::string> Vec_allowed_words={"PROJECT_NAME","AUTHOR","DATE","DEVICE","TUBE","WIDTH_CM","HEIGHT_CM","WIDTH_PIXEL","HEIGHT_PIXEL","CS_ORIGIN","SPOT_SIZE","X","Y","XRF","XRD","RAMAN","COMMENT"};

const std::vector<std::string> Vec_names_methods={"XRF","XRD","RAMAN"};


    enum class _allowed_tokens:unsigned char{TOKEN_PROJECT_NAME, TOKEN_AUTHOR, TOKEN_DATE, TOKEN_DEVICE, TOKEN_TUBE, TOKEN_WIDTH_CM, TOKEN_HEIGHT_CM, TOKEN_WIDTH_PIXEL, TOKEN_HEIGHT_PIXEL, TOKEN_CS_ORIGIN, TOKEN_SPOT_SIZE, TOKEN_X, TOKEN_Y, TOKEN_XRF, TOKEN_XRD, TOKEN_RAMAN, TOKEN_COMMENT};

  enum class _mode:unsigned char{MODE_READ,MODE_WRITE};
}

class _file_project_data_csv:public _file_io
{
  public:
  bool read(_project_data_ns::_project_data &Project_data, std::string &Error);
  void write(_project_data_ns::_project_data &Project_data);

  protected:
  std::string trim(const std::string& String);
  // std::string replace_soft_hyphen(const std::string& String);
};

#endif
