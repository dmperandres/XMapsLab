//LIC

#include "filter_combination_product.h"
#include "glwidget_xmapslab_ge.h"
#include "window_xmapslab.h"

using namespace _f_element_ns;

//HEA

_filter_combination_product::_filter_combination_product()
{
  Filter_type=_filter_ns::_filter_type::FILTER_TYPE_COMBINATION_PRODUCT_OP;
  Filter_class=_filter_ns::_filter_class::FILTER_CLASS_COMBINATION;
}

//HEA

void _filter_combination_product::reset_data()
{
}

//HEA

float _filter_combination_product::get_max_value()
{
  float Value1=Vec_input_filters[1]->get_max_value();
  float Value2=Vec_input_filters[2]->get_max_value();

  return Value1*Value2;
}

//HEA

void _filter_combination_product::update()
{
  float Value0=0;
  float Value1=0;
  float Threshold1=float(Threshold)/100.0f;
  float Result;
  //  float Max_value0=-1;
  float Max_value=-1;
  // bool show=true;

  update_max_values();

  //  float Max_input_value0=Vec_max_value_input_data[1];
  float Threshold_value0=Threshold1;

  //  float Max_input_value1=Vec_max_value_input_data[2];
  float Threshold_value1=Threshold1;

  shared_ptr<cv::Mat> Logic=Vec_input_data[0];
  shared_ptr<cv::Mat> Input_A=Vec_input_data[1];
  shared_ptr<cv::Mat> Input_B=Vec_input_data[2];
  shared_ptr<cv::Mat> Output=Vec_output_data[0];

  // std::cout << "Product (2025,2670) " << Input_A->at<float>(2025,2670) << " " << Input_B->at<float>(2025,2670) << std::endl;
  // std::cout << "Product (2025,598) " << Input_A->at<float>(2025,598) << " " << Input_B->at<float>(2025,598) << std::endl;

  if (Logic!=nullptr){
    for (int Row=0;Row<Input_A->rows;Row++){
      for (int Col=0;Col<Input_A->cols;Col++){
        if (Logic->at<float>(Row,Col)==1.0f){
          Value0=Input_A->at<float>(Row,Col);
          Value1=Input_B->at<float>(Row,Col);

          if (Value0>Threshold_value0 && Value1>Threshold_value1){
            Result=Value0*Value1;
            Output->at<float>(Row,Col)=Result;
            if (Result>Max_value) Max_value=Result;
          }
          else{
            Output->at<float>(Row,Col)=0;
          }
        }
        else Output->at<float>(Row,Col)=0;
      }
    }
  }
  else{
    for (int Row=0;Row<Input_A->rows;Row++){
      for (int Col=0;Col<Input_A->cols;Col++){
        // if (Input_A->at<float>(Row,Col)>0 && Input_B->at<float>(Row,Col)>0 && show==true){
        //   std::cout << Row << " " << Col << " " << Input_A->at<float>(Row,Col) << " " << Input_B->at<float>(Row,Col) << std::endl;
        //   show=false;
        // }

        Value0=Input_A->at<float>(Row,Col);
        Value1=Input_B->at<float>(Row,Col);

        if (Value0>Threshold_value0 && Value1>Threshold_value1){
          Result=Value0*Value1;
          Output->at<float>(Row,Col)=Result;
          if (Result>Max_value) Max_value=Result;
        }
        else{
          Output->at<float>(Row,Col)=0;
        }
      }
    }
  }

  // Vec_output_data[0]=Output_aux;

  // the new max value is the product of the max values
  if (Max_value>0) Vec_max_value_output_data[0]=sqrt(Max_value*Vec_max_value_input_data[1]*Vec_max_value_input_data[2]);
  else Vec_max_value_output_data[0]=0;

  // std::cout << "Product out (2025,2670) " << Vec_output_data[0]->at<float>(2025,2670) << std::endl;

  apply_colormap(Vec_output_data[0],Vec_output_images[0]);
}

//HEA

void _filter_combination_product::color(QColor Color1)
{
  Color=Color1;
  // get the palette data of the object
  _palette_data_ns::_palette_data &Palette_data=Window->Map_filters_palette_data[Window->mapping_selected_filter_name()];
  Palette_data.color(Color1);
  set_colormap(Palette_data.vec_values(),Palette_data.vec_colors(),Palette_data.type());
}

//HEA

_filter_combination_product_ui::_filter_combination_product_ui(_window_xmapslab *Window1, std::string Name1)
{
  Name=Name1;
  Window=Window1;
  Qtw_filter_combination_product=new _qtw_filter_combination_product(Window1,this,Name1);
}

//HEA

_filter_combination_product_ui::_filter_combination_product_ui(_window_xmapslab *Window1, std::map<string, string> &Parameters, std::string Name1)
{
  read_parameters(Parameters);
  Name=Name1;
  Window=Window1;
  Qtw_filter_combination_product=new _qtw_filter_combination_product(Window1,this,Name1);
}

//HEA

_filter_combination_product_ui::~_filter_combination_product_ui()
{
  delete Qtw_filter_combination_product;
}

//HEA

void _filter_combination_product_ui::reset_data()
{
  _filter_combination_product::reset_data();
  Qtw_filter_combination_product->parameter1(parameter1());
  hide();
}

//HEA

void _filter_combination_product_ui::show()
{
  Qtw_filter_combination_product->show();
}

//HEA

void _filter_combination_product_ui::hide()
{
  Qtw_filter_combination_product->hide();
}

//HEA

void *_filter_combination_product_ui::get_link()
{
  return Qtw_filter_combination_product->get_link();
}

//HEA

void _filter_combination_product_ui::read_parameters(std::map<std::string,std::string> &Parameters)
{
  if (Parameters["_INI_"]=="EDITOR"){// default parameters
    parameter1(_f_combination_product_ns::THRESHOLD_DEFAULT);
  }
  else{// Parameters from file or from initialised filter
    try{
      if (Parameters["threshold"]=="default") parameter1(_f_combination_product_ns::THRESHOLD_DEFAULT);
      else parameter1(atoi(Parameters["threshold"].c_str()));
    }
    catch (...) {
      QMessageBox MsgBox;
      MsgBox.setText("Error in the data of combination product filter");
      MsgBox.exec();
      exit(-1);
    }
  }
}

//HEA

void _filter_combination_product_ui::write_parameters(std::map<std::string,std::string> &Parameters)
{
  char Aux[100];

  sprintf(Aux,"%d",parameter1());
  Parameters["threshold"]=std::string(Aux);
}

//HEA

void _filter_combination_product_ui::color(QColor Color1)
{
  Color=Color1;
  Qtw_filter_combination_product->parameter2(Color);
}

//HEA

_qtw_filter_combination_product::_qtw_filter_combination_product(_window_xmapslab *Window1,_filter_combination_product_ui *Filter1,std::string Box_name)
{
  Window=Window1;
  Filter=Filter1;

  Group_box_main=new QGroupBox(tr(Box_name.c_str()));
  Group_box_main->setAlignment(Qt::AlignCenter);

  QVBoxLayout *Vertical_box_main=new QVBoxLayout;

  // Parameter 1
  QFrame *Frame_parameter1=new QFrame;
  Frame_parameter1->setFrameStyle(QFrame::Panel);

  QGridLayout *Grid_parameter1=new QGridLayout;

  // Parameter1
  // 0 thresold
  Spinbox_parameter1=new QSpinBox;
  Spinbox_parameter1->setRange(0,100);
  Spinbox_parameter1->setAlignment(Qt::AlignRight);
  Spinbox_parameter1->setSuffix(" %");

  parameter1(Filter->parameter1());

  connect(Spinbox_parameter1,SIGNAL(valueChanged(int)),this,SLOT(parameter1_slot(int)));

  // Parameter2
  float Factor=Window->screen_height()/1080.0f;
  Button_parameter2=new _button_color_simple(QColor(255,0,0),Factor);

  connect(Button_parameter2,SIGNAL(colorChanged(QColor)),this,SLOT(parameter2_slot(QColor)));

  QLabel *Label_parameter1=new QLabel("0 threshold");
  QLabel *Label_parameter2=new QLabel("Color");

  Grid_parameter1->addWidget(Label_parameter1,0,0,Qt::AlignRight);
  Grid_parameter1->addWidget(Spinbox_parameter1,0,1,Qt::AlignLeft);
  Grid_parameter1->addWidget(Label_parameter2,1,0,Qt::AlignRight);
  Grid_parameter1->addWidget(Button_parameter2,1,1,Qt::AlignLeft);

  Frame_parameter1->setLayout(Grid_parameter1);
  //
  Vertical_box_main->addWidget(Frame_parameter1);

  Group_box_main->setLayout(Vertical_box_main);
}

//HEA

void _qtw_filter_combination_product::parameter1(int Value)
{
  Spinbox_parameter1->blockSignals(true);
  Spinbox_parameter1->setValue(Value);
  Spinbox_parameter1->blockSignals(false);
}

//HEA

void _qtw_filter_combination_product::parameter2(QColor Color1)
{
  Button_parameter2->color(Color1);
}

//HEA

void _qtw_filter_combination_product::parameter1_slot(int Value)
{
  Filter->parameter1(Value);
  Window->update_filter(Filter->name());
}

//HEA

void _qtw_filter_combination_product::parameter2_slot(QColor Color1)
{
  Filter->parameter2(Color1);
  Window->update_filter(Filter->name());
}
