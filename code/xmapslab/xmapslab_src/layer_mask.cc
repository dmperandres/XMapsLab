//LIC

#include "layer_mask.h"
#include "window.h"

using namespace _layer_mask_ns;


//HEA

_layer_mask::_layer_mask()
{
  Transparence=0;

  Layer_type=_layer_ns::_layer_type::LAYER_TYPE_MASK;

  // color map
  Color_table=make_shared<cv::Mat>();
  Color_table->create(1,256,CV_8UC3);

  Num_channels=1;
}

//HEA

void _layer_mask::reset_data()
{
  Transparence=0;
}


void _layer_mask::set_colormap(vector<float> &Vec_proportions, vector<QColor> &Vec_colors1, int Type)
{
  vector<int> Vec_int_proportions;

  Vec_int_proportions.resize(Vec_proportions.size());
  for (unsigned int i=0;i<Vec_proportions.size();i++){
    Vec_int_proportions[i]=int(Vec_proportions[i]*255.0f);
  }

  int Start_value;
  int End_value;
  int Steps;
  float t;
  int Pos=0;

  if (Type==1){
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

  End_color=Vec_colors1[Vec_colors1.size()-1];
}


//HEA

void _layer_mask::apply_colormap()
{
  cv::Mat Image_out_uc;

  cv::Mat Gray;
  cvtColor(*Result_gray_image,Gray,cv::COLOR_GRAY2RGB,3);

  LUT(Gray,*Color_table,Image_out_uc);

  cvtColor(Image_out_uc,*Image,cv::COLOR_RGB2BGRA,4);
}


//HEA

void _layer_mask::compute_logic_operation()
{
  // first make the logical operation and add the result
  float Value0=0;
  float Value1=0;
  bool Selected=false;

  for (int Row=0;Row<Result_gray_image->rows;Row++){
    for (int Col=0;Col<Result_gray_image->cols;Col++){
      Selected=false;
      Value0=float(Vec_images[0]->at<unsigned char>(Row,Col))/255.0f;


      // AND(A,B)
      switch (Logic_operation){
      case _layer_ns::_logic_operation::LOGIC_OPERATION_A_AND_B:
        Value1=float(Vec_images[1]->at<unsigned char>(Row,Col))/255.0f;
        if (Value0>Threshold && Value1>Threshold) Selected=true;
        break;
      case _layer_ns::_logic_operation::LOGIC_OPERATION_A_OR_B:
        Value1=float(Vec_images[1]->at<unsigned char>(Row,Col))/255.0f;
        if (Value0>Threshold || Value1>Threshold) Selected=true;
        break;
      case _layer_ns::_logic_operation::LOGIC_OPERATION_A_AND_NOT_B:
        Value1=float(Vec_images[1]->at<unsigned char>(Row,Col))/255.0f;
        if (Value0>Threshold && !(Value1>Threshold)) Selected=true;
        break;
      case _layer_ns::_logic_operation::LOGIC_OPERATION_A_OR_NOT_B:
        Value1=float(Vec_images[1]->at<unsigned char>(Row,Col))/255.0f;
        if (Value0>Threshold || !(Value1>Threshold)) Selected=true;
        break;
      case _layer_ns::_logic_operation::LOGIC_OPERATION_NOT_A:
        if (Value0>Threshold ) Selected=false;
        else Selected=true;
        break;
      }

      if (Selected){
        Result_gray_image->at<unsigned char>(Row,Col)=255;
      }
      else{
        Result_gray_image->at<unsigned char>(Row,Col)=0;
      }
    }
  }  
}

//HEA

void _layer_mask::compute_values()
{
  Computed=true;

  if (Image==nullptr){
    Image=make_shared<cv::Mat>();
    Result_gray_image=make_shared<cv::Mat>();
    Result_gray_image->create(Vec_images[0]->rows,Vec_images[0]->cols,CV_8U);
  }

  compute_logic_operation();
}


//HEA

void _layer_mask::update()
{
  apply_colormap();
}

//HEA

_layer_mask_ui::_layer_mask_ui(_window *Window1, string Name1)
{
  Name=Name1;
  Qtw_layer_mask=new _qtw_layer_mask(Window1,this,Name);
}

//HEA

_layer_mask_ui::~_layer_mask_ui()
{
  delete Qtw_layer_mask;
}

//HEA

void _layer_mask_ui::reset_data()
{
  _layer_mask::reset_data();
  Qtw_layer_mask->parameter1(parameter1());
  hide();
}

//HEA

void _layer_mask_ui::show()
{
  Qtw_layer_mask->show();
}

//HEA

void _layer_mask_ui::hide()
{
  Qtw_layer_mask->hide();
}

//HEA

void *_layer_mask_ui::get_link()
{
  return Qtw_layer_mask->get_link();
}

//HEA

//void _layer_mask_ui::read_parameters(std::map<std::string,std::string> &Parameters)
//{
//  if (Parameters["_INI_"]=="EDITOR"){// default parameters
//    parameter1(CANNY_SIZE_DEFAULT);
//    parameter2(CANNY_THRESHOLD1_DEFAULT);
//    parameter3(CANNY_THRESHOLD2_DEFAULT);
//  }
//  else{// Parameters from file or from initialised filter
//    try{
//      if (Parameters["kernel_size"]=="default") parameter1(CANNY_SIZE_DEFAULT);
//      else parameter1(atoi(Parameters["kernel_size"].c_str()));
//      if (Parameters["threshold1"]=="default") parameter2(CANNY_THRESHOLD1_DEFAULT);
//      else parameter2(atoi(Parameters["threshold1"].c_str()));
//      if (Parameters["threshold2"]=="default") parameter3(CANNY_THRESHOLD2_DEFAULT);
//      else parameter3(atoi(Parameters["threshold2"].c_str()));
//    }
//    catch (const std::out_of_range) {
//      QMessageBox MsgBox;
//      MsgBox.setText("Error in the data of CANNY filter");
//      MsgBox.exec();
//      exit(-1);
//    }
//  }
//}

//HEA

//void _layer_mask_ui::write_parameters(std::map<std::string,std::string> &Parameters)
//{
//  char Aux[100];

//  sprintf(Aux,"%d",parameter1());
//  Parameters["kernel_size"]=string(Aux);
//  sprintf(Aux,"%d",parameter2());
//  Parameters["threshold1"]=string(Aux);
//  sprintf(Aux,"%d",parameter3());
//  Parameters["threshold2"]=string(Aux);
//}


//void _layer_mask_ui::colormap(int Value)
//{
//  _layer_mask::colormap(Value);
//  Qtw_layer_mask->parameter2(Value);
//}

//HEA

_qtw_layer_mask::_qtw_layer_mask(_window *Window1,_layer_mask_ui *Filter1,string Box_name)
{
  Window=Window1;
  Filter=Filter1;

  Group_box_main=new QGroupBox(tr(Box_name.c_str()));
  Group_box_main->setAlignment(Qt::AlignCenter);

  QVBoxLayout *Vertical_box_main=new QVBoxLayout;

  // Parameter1
  QGroupBox *Group_box_parameter1=new QGroupBox(tr(String_group_box_parameter1.c_str()));
  Group_box_parameter1->setAlignment(Qt::AlignCenter);

  QGridLayout *Grid_parameter1 = new QGridLayout;

  QLabel *Label_parameter1_min= new QLabel(tr(String_label_parameter1_min.c_str()));
  QLabel *Label_parameter1_max= new QLabel(tr(String_label_parameter1_max.c_str()));

  Line_edit_parameter1=new QLineEdit();
  Line_edit_parameter1->setAlignment(Qt::AlignRight);
  Line_edit_parameter1->setReadOnly(true);
  Line_edit_parameter1->setEnabled(false);
  Line_edit_parameter1->setToolTip(tr(String_label_parameter1_tooltip.c_str()));

  Slider_parameter1 = new QSlider(Qt::Horizontal);
  Slider_parameter1->setRange(Parameter1_min_value,Parameter1_max_value);
  Slider_parameter1->setSingleStep(Parameter1_single_step);
  Slider_parameter1->setPageStep(Parameter1_page_step);
  Slider_parameter1->setTickInterval(Parameter1_tick_interval);
  Slider_parameter1->setTickPosition(QSlider::TicksRight);
  Slider_parameter1->setTracking(Parameter1_set_tracking);
  Slider_parameter1->setToolTip(tr(String_parameter1_tooltip.c_str()));

  parameter1(Filter->parameter1());

  Grid_parameter1->addWidget(Line_edit_parameter1,0,1,Qt::AlignCenter);
  Grid_parameter1->addWidget(Label_parameter1_min,1,0,Qt::AlignRight);
  Grid_parameter1->addWidget(Slider_parameter1,1,1);
  Grid_parameter1->addWidget(Label_parameter1_max,1,2,Qt::AlignLeft);

  Group_box_parameter1->setLayout(Grid_parameter1);

  connect(Slider_parameter1, SIGNAL(valueChanged(int)),this,SLOT(parameter1_slot(int)));

  // Parameter2
  QGroupBox *Group_box_parameter2=new QGroupBox(tr(String_group_box_parameter2.c_str()));
  Group_box_parameter2->setAlignment(Qt::AlignCenter);

  QHBoxLayout *Horizontal_box_parameter2=new QHBoxLayout;
  Horizontal_box_parameter2->setAlignment(Qt::AlignCenter);

  Combobox_parameter2 = new QComboBox;
  for (unsigned int i=0;i<_color_bar_abstract_ns::Vec_data_type.size();i++){
    Combobox_parameter2->addItem(_color_bar_abstract_ns::Vec_data_type[i]);
  }

  Horizontal_box_parameter2->addWidget(Combobox_parameter2);

  Group_box_parameter2->setLayout(Horizontal_box_parameter2);

  connect(Combobox_parameter2, SIGNAL(activated(int)), this,SLOT(parameter2_slot(int)));


  //
  Vertical_box_main->addWidget(Group_box_parameter1);
  Vertical_box_main->addWidget(Group_box_parameter2);

  Group_box_main->setLayout(Vertical_box_main);
}

//HEA

void _qtw_layer_mask::parameter1(int Value)
{
  QString Str;

  Str=Str.number(Value);
  Line_edit_parameter1->setText(Str);
  Slider_parameter1->blockSignals(true);
  Slider_parameter1->setValue((Value/2)-1);
  Slider_parameter1->blockSignals(false);
}

//HEA

void _qtw_layer_mask::parameter2(int Value)
{
  Combobox_parameter2->blockSignals(true);
  Combobox_parameter2->setCurrentIndex(Value);
  Combobox_parameter2->blockSignals(false);
}

//HEA

void _qtw_layer_mask::parameter1_slot(int Value)
{
  QString Str;
  char Aux[100];

  sprintf(Aux,"%2d",Value);
  Str=Aux;
  Line_edit_parameter1->setText(Str);
  Filter->parameter1(Value);
  Window->update_layer(Filter->name());
}

//HEA

void _qtw_layer_mask::parameter2_slot(int Value)
{
  Filter->parameter2(Value);
  Window->update_color_bar_data_type_print(Value);
}


