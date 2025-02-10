//LIC

#include "filter_logic_and.h"
//#include "glwidget_xmapslab_ge.h"
#include "window_xmapslab.h"

using namespace _f_element_ns;

//HEA

_filter_logic_and::_filter_logic_and()
{
  Filter_type=_filter_ns::_filter_type::FILTER_TYPE_LOGIC_AND_OP;
  Filter_class=_filter_ns::_filter_class::FILTER_CLASS_BINARY;

  Max_value=1.0f;
}

//HEA

void _filter_logic_and::reset_data()
{
}

//HEA

float _filter_logic_and::get_max_value()
{
  float Value1=Vec_input_filters[0]->get_max_value();

  return Value1;
}

//HEA

//void _filter_logic_and::update()
//{
//  float Value0=0;
//  float Value1=0;
//  float Threshold1=float(Threshold)/100.0f;

//  shared_ptr<cv::Mat> Input_A=Vec_input_data[0];
//  shared_ptr<cv::Mat> Input_B=Vec_input_data[1];
//  shared_ptr<cv::Mat> Output=Vec_output_data[0];

//  for (int Row=0;Row<Input_A->rows;Row++){
//    for (int Col=0;Col<Input_A->cols;Col++){
//      Value0=float(Input_A->at<unsigned char>(Row,Col))/255.0f;
//      Value1=float(Input_B->at<unsigned char>(Row,Col))/255.0f;

//      if (Value0>Threshold1 && Value1>Threshold1){
//        Output->at<unsigned char>(Row,Col)=255;
//      }
//      else{
//        Output->at<unsigned char>(Row,Col)=0;
//      }
//    }
//  }

//  apply_colormap(Vec_output_data[0],Vec_output_images[0]);
//}

//void _filter_logic_and::update()
//{
//  float Value0=0;
//  float Value1=0;
//  float Threshold1=float(Threshold)/100.0f;

//  shared_ptr<cv::Mat> Input_A=Vec_input_data[0];
//  shared_ptr<cv::Mat> Input_B=Vec_input_data[1];
//  shared_ptr<cv::Mat> Output=Vec_output_data[0];

//  for (int Row=0;Row<Input_A->rows;Row++){
//    for (int Col=0;Col<Input_A->cols;Col++){
//      Value0=Input_A->at<float>(Row,Col);
//      Value1=Input_B->at<float>(Row,Col);

//      if (Value0>Threshold1 && Value1>Threshold1){
//        Output->at<unsigned char>(Row,Col)=255;
//      }
//      else{
//        Output->at<unsigned char>(Row,Col)=0;
//      }
//    }
//  }

//  apply_colormap(Vec_output_data[0],Vec_output_images[0]);
//}


// assumes that the input is binary!

void _filter_logic_and::update()
{
  float Value0=0;
  float Value1=0;
//  float Threshold1=float(Threshold)/100.0f;

  shared_ptr<cv::Mat> Input_A=Vec_input_data[0];
  shared_ptr<cv::Mat> Input_B=Vec_input_data[1];
  shared_ptr<cv::Mat> Output=Vec_output_data[0];

  for (int Row=0;Row<Input_A->rows;Row++){
    for (int Col=0;Col<Input_A->cols;Col++){
      Value0=Input_A->at<float>(Row,Col);
      Value1=Input_B->at<float>(Row,Col);

      if (Value0==1.0f && Value1==1.0f){
        Output->at<float>(Row,Col)=1.0f;
      }
      else{
        Output->at<float>(Row,Col)=0.0f;
      }
    }
  }

  apply_colormap(Vec_output_data[0],Vec_output_images[0]);
}


//HEA

_filter_logic_and_ui::_filter_logic_and_ui(_window_xmapslab *Window1, std::string Name1)
{
  Name=Name1;
  Qtw_filter_logic_and=new _qtw_filter_logic_and(Window1,this,Name1);
}

//HEA

_filter_logic_and_ui::_filter_logic_and_ui(_window_xmapslab *Window1, std::map<string, string> &Parameters, std::string Name1)
{
  read_parameters(Parameters);
  Name=Name1;
  Qtw_filter_logic_and=new _qtw_filter_logic_and(Window1,this,Name1);
}

//HEA

_filter_logic_and_ui::~_filter_logic_and_ui()
{
  delete Qtw_filter_logic_and;
}

//HEA

void _filter_logic_and_ui::reset_data()
{
  _filter_logic_and::reset_data();
  Qtw_filter_logic_and->parameter1(parameter1());
  hide();
}

//HEA

void _filter_logic_and_ui::show()
{
  Qtw_filter_logic_and->show();
}

//HEA

void _filter_logic_and_ui::hide()
{
  Qtw_filter_logic_and->hide();
}

//HEA

void *_filter_logic_and_ui::get_link()
{
  return Qtw_filter_logic_and->get_link();
}

//HEA

void _filter_logic_and_ui::read_parameters(std::map<std::string,std::string> &Parameters)
{
  if (Parameters["_INI_"]=="EDITOR"){// default parameters
    parameter1(_f_logic_and_ns::THRESHOLD_DEFAULT);
  }
  else{// Parameters from file or from initialised filter
    try{
      if (Parameters["threshold"]=="default") parameter1(_f_logic_and_ns::THRESHOLD_DEFAULT);
      else parameter1(atoi(Parameters["threshold"].c_str()));
    }
    catch (...) {
      QMessageBox MsgBox;
      MsgBox.setText("Error in the data of AND filter");
      MsgBox.exec();
      exit(-1);
    }
  }
}

//HEA

void _filter_logic_and_ui::write_parameters(std::map<std::string,std::string> &Parameters)
{
  char Aux[100];

  sprintf(Aux,"%d",parameter1());
  Parameters["threshold"]=std::string(Aux);
}

//HEA

//void _filter_logic_and_ui::color(QColor Color1)
//{
//  Color=Color1;
//  Qtw_filter_logic_and->parameter2(Color);
//}

//HEA

_qtw_filter_logic_and::_qtw_filter_logic_and(_window_xmapslab *Window1,_filter_logic_and_ui *Filter1,std::string Box_name)
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

  QLabel *Label_parameter1=new QLabel("0 threshold");

  Grid_parameter1->addWidget(Label_parameter1,0,0,Qt::AlignRight);
  Grid_parameter1->addWidget(Spinbox_parameter1,0,1,Qt::AlignLeft);

  Frame_parameter1->setLayout(Grid_parameter1);

  connect(Spinbox_parameter1,SIGNAL(valueChanged(int)),this,SLOT(parameter1_slot(int)));

  //
  Vertical_box_main->addWidget(Frame_parameter1);

  Group_box_main->setLayout(Vertical_box_main);
}

//HEA

void _qtw_filter_logic_and::parameter1(int Value)
{
  Spinbox_parameter1->blockSignals(true);
  Spinbox_parameter1->setValue(Value);
  Spinbox_parameter1->blockSignals(false);
}

//HEA

//void _qtw_filter_logic_and::parameter2(QColor Color1)
//{
//  Button_parameter2->color(Color1);
//}

//HEA

void _qtw_filter_logic_and::parameter1_slot(int Value)
{
  Filter->parameter1(Value);
  Window->update_filter(Filter->name());
}

//HEA

//void _qtw_filter_logic_and::parameter2_slot(QColor Color1)
//{
//  Filter->parameter2(Color1);
//  Window->update_filter(Filter->name());
//}
