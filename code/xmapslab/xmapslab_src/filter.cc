//LIC

#include "filter.h"

//HEA

void _filter::set_data(std::vector<std::shared_ptr<cv::Mat>> Vec_input_data1, std::vector<std::shared_ptr<cv::Mat>> Vec_output_data1, std::vector<std::shared_ptr<cv::Mat> > Vec_output_images1, std::vector<float> Vec_max_value_input_data1)
{
  Vec_input_data=Vec_input_data1;
  Vec_output_data=Vec_output_data1;
  Vec_output_images=Vec_output_images1;
  Vec_max_value_input_data=Vec_max_value_input_data1;

  Vec_max_value_output_data.resize(Vec_output_data1.size());

  Ready=true;
}

//HEA

void _filter::set_input_filters(std::vector<std::shared_ptr<_filter>> Vec_input_filters1,std::vector<int> Vec_input_port_index1)
{
  Vec_input_filters=Vec_input_filters1;
  Vec_input_port_index=Vec_input_port_index1;
}

//HEA

void _filter::set_colormap(std::vector<float> &Vec_proportions, std::vector<QColor> &Vec_colors1,_palette_data_ns::_palette_type Palette_type)
{
  if (Color_table==nullptr){
    Color_table=std::make_shared<cv::Mat>();
    Color_table->create(1,256,CV_8UC3);
  }

  std::vector<int> Vec_int_proportions;

  Vec_int_proportions.resize(Vec_proportions.size());
  for (unsigned int i=0;i<Vec_proportions.size();i++){
    Vec_int_proportions[i]=int(Vec_proportions[i]*255.0f);
  }

  int Start_value;
  int End_value;
  int Steps;
  float t;
  int Pos=0;

  if (Palette_type==_palette_data_ns::_palette_type::PALETTE_TYPE_CONTINUOUS){
    // interpolations
    for (unsigned int i=0;i<Vec_int_proportions.size()-1;i++){
      Start_value=Vec_int_proportions[i];
      End_value=Vec_int_proportions[i+1];
      Steps=End_value-Start_value;

      cv::Vec3f Start_color(Vec_colors1[i].red(),Vec_colors1[i].green(),Vec_colors1[i].blue());
      cv::Vec3f End_color(Vec_colors1[i+1].red(),Vec_colors1[i+1].green(),Vec_colors1[i+1].blue());
      cv::Vec3f Color;

      for (int j=0;j<Steps;j++){
        t=float(j)/float(Steps);
        Color=(End_color-Start_color)*t+Start_color;
        Color_table->at<cv::Vec3b>(Pos)[0]=static_cast<unsigned char>(Color[0]);
        Color_table->at<cv::Vec3b>(Pos)[1]=static_cast<unsigned char>(Color[1]);
        Color_table->at<cv::Vec3b>(Pos)[2]=static_cast<unsigned char>(Color[2]);
        Pos++;
      }
    }
    // last element
    Color_table->at<cv::Vec3b>(Pos)[0]=static_cast<unsigned char>(Vec_colors1[Vec_colors1.size()-1].red());
    Color_table->at<cv::Vec3b>(Pos)[1]=static_cast<unsigned char>(Vec_colors1[Vec_colors1.size()-1].green());
    Color_table->at<cv::Vec3b>(Pos)[2]=static_cast<unsigned char>(Vec_colors1[Vec_colors1.size()-1].blue());
  }
  else{
    // sections
    for (unsigned int i=0;i<Vec_int_proportions.size()-1;i++){
      Start_value=Vec_int_proportions[i];
      End_value=Vec_int_proportions[i+1];
      Steps=End_value-Start_value;

      cv::Vec3f Start_color(Vec_colors1[i].red(),Vec_colors1[i].green(),Vec_colors1[i].blue());
      for (int j=0;j<Steps;j++){
        Color_table->at<cv::Vec3b>(Pos)[0]=static_cast<unsigned char>(Start_color[0]);
        Color_table->at<cv::Vec3b>(Pos)[1]=static_cast<unsigned char>(Start_color[1]);
        Color_table->at<cv::Vec3b>(Pos)[2]=static_cast<unsigned char>(Start_color[2]);
        Pos++;
      }
    }
    cv::Vec3f Start_color(Vec_colors1[Vec_colors1.size()-2].red(),Vec_colors1[Vec_colors1.size()-2].green(),Vec_colors1[Vec_colors1.size()-2].blue());
    Color_table->at<cv::Vec3b>(Pos)[0]=static_cast<unsigned char>(Start_color[0]);
    Color_table->at<cv::Vec3b>(Pos)[1]=static_cast<unsigned char>(Start_color[1]);
    Color_table->at<cv::Vec3b>(Pos)[2]=static_cast<unsigned char>(Start_color[2]);
  }

//  End_color=Vec_colors1[Vec_colors1.size()-1];
}

//HEA

void _filter::apply_colormap(std::shared_ptr<cv::Mat> Float_values_image,std::shared_ptr<cv::Mat> Result_image)
{
  cv::Mat Image_out_uc;
  cv::Mat Gray;

  // to check if there are transparent pixels and put the pattern
  //  cv::Vec4b Pixel;
  //  for (int Row=0;Row<Original_image->rows;Row++){
  //    for (int Col=0;Col<Original_image->cols;Col++){
  //      Pixel=Original_image->at<cv::Vec4b>(Row,Col);
  //      if (Pixel[3]==0){
  //        if (Col%20<10 && Row%20<10) Float_values_image->at<float>(Row,Col)=1.0f;
  //        else Float_values_image->at<float>(Row,Col)=0.0f;
  //      }
  //    }
  //  }

  // adjustment to 255 and unsigned char
  cv::Mat Image_aux;
  Image_aux=Float_values_image->clone();
  Image_aux=Image_aux*255.0F;

  cv::Mat Result_gray_image;
  Image_aux.convertTo(Result_gray_image,CV_8U);

  cvtColor(Result_gray_image,Gray,cv::COLOR_GRAY2RGB,3);

  LUT(Gray,*Color_table,Image_out_uc);

  cvtColor(Image_out_uc,*Result_image,cv::COLOR_RGB2BGR,3);
}

//HEA

void _filter::max_value_input_data(int Pos,float Max_value1)
{
  if (Pos>=0 && Pos<int(Vec_max_value_input_data.size())) Vec_max_value_input_data[Pos]=Max_value1;
  else exit(-1);
}

//HEA

float _filter::max_value_input_data(int Pos)
{
  if (Pos>=0 && Pos<int(Vec_max_value_input_data.size())) return(Vec_max_value_input_data[Pos]);
  else exit(-1);
}

//HEA

void _filter::max_value_output_data(int Pos,float Max_value1)
{
  if (Pos>=0 && Pos<int(Vec_max_value_output_data.size())) Vec_max_value_output_data[Pos]=Max_value1;
  else exit(-1);
}

//HEA

float _filter::max_value_output_data(int Pos)
{
  if (Pos>=0 && Pos<int(Vec_max_value_output_data.size())) return(Vec_max_value_output_data[Pos]);
  else exit(-1);
}

//HEA

void _filter::update_max_values()
{
  for (unsigned int i=0;i<Vec_input_filters.size();i++){
    if (Vec_input_filters[i]!=nullptr){
      Vec_max_value_input_data[i]=Vec_input_filters[i]->max_value_output_data(Vec_input_port_index[i]);
    }
  }
}
