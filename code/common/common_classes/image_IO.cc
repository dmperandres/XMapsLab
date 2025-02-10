//LIC

#include "image_IO.h"

//HEA

void _image_IO::read_image(std::string Name,cv::Mat &Image_in)
{
  #ifdef WINDOWS
  std::string Aux_string;
  for (int i=0;i<Name.size();i++){
    if (Name[i]=='/'){
      Aux_string.push_back('\\');
    }
    else Aux_string.push_back(Name[i]);
  }
  Name=Aux_string;
  #endif

  Image_in=cv::imread(Name,cv::IMREAD_UNCHANGED);
  if( !Image_in.data ){ // check if the image has been loaded properly
    std::cout << "Error reading the image: " << Name << std::endl;
    exit(-1);
  }
}

//HEA

void _image_IO::write_image(std::string Name,cv::Mat &Image_out)
{
	imwrite(Name, Image_out);
}
