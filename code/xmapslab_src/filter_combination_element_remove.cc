/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#include "filter_combination_element_remove.h"
#include "glwidget_xmapslab_ge.h"
#include "window_xmapslab.h"

using namespace _f_element_ns;

/*************************************************************************/

_filter_combination_element_remove::_filter_combination_element_remove()
{
  Filter_type=_filter_ns::_filter_type::FILTER_TYPE_COMBINATION_ELEMENT_REMOVE_OP;
  Filter_class=_filter_ns::_filter_class::FILTER_CLASS_COMBINATION;
}

/*************************************************************************/

void _filter_combination_element_remove::reset_data()
{
}

/*************************************************************************/

float _filter_combination_element_remove::get_max_value()
{
  // float Value1=Vec_input_filters[1]->get_max_value();
  float Value1=Vec_max_value_output_data[0];

  return Value1;
}

/*************************************************************************/

void _filter_combination_element_remove::update()
{
  // float Value0=0;
  float Result=0;
  float Max_value0=-1;
  float Threshold1=float(Threshold)/100.0f;
  float Factor=1.0f-Threshold1;

  update_max_values();

  // float Max_input_value0=Vec_max_value_input_data[1];
  // float Threshold_value0=Max_input_value0*Threshold1;

  shared_ptr<cv::Mat> Logic=Vec_input_data[0];
  shared_ptr<cv::Mat> Input_A=Vec_input_data[1];
  shared_ptr<cv::Mat> Output=Vec_output_data[0];

  shared_ptr<cv::Mat> Output_aux=make_shared<cv::Mat>();
  Output_aux->create(Vec_input_data[1]->rows,Vec_input_data[1]->cols,CV_32F);

  if (Logic!=nullptr){
    for (int Row=0;Row<Input_A->rows;Row++){
      for (int Col=0;Col<Input_A->cols;Col++){
        if (Logic->at<float>(Row,Col)>0.5){ // True
          if (Input_A->at<float>(Row,Col)>Threshold1){
            Output_aux->at<float>(Row,Col)=Input_A->at<float>(Row,Col)*Factor;
            if (Output_aux->at<float>(Row,Col)>Max_value0) Max_value0=Output_aux->at<float>(Row,Col);
          }
          else Output_aux->at<float>(Row,Col)=0.0f;
        }
        else Output_aux->at<float>(Row,Col)=0.0f;
      }
    }
  }
  else{
    // there is not logic control all values are true
    for (int Row=0;Row<Input_A->rows;Row++){
      for (int Col=0;Col<Input_A->cols;Col++){
        if (Input_A->at<float>(Row,Col)>Threshold1){
          Output_aux->at<float>(Row,Col)=Input_A->at<float>(Row,Col)*Factor;
          if (Output_aux->at<float>(Row,Col)>Max_value0) Max_value0=Output_aux->at<float>(Row,Col);
        }
        else Output_aux->at<float>(Row,Col)=0.0f;
      }
    }
  }

  // Do the normalization and compute the final values
  // float Normalization_value=0;
  // if (Relative_normalization==true){
  //   Normalization_value=Max_value0;
  // }
  // else{
  //   Normalization_value=Max_input_value0;
  // }

  if (Max_value0>0){
    for (int Row=0;Row<Vec_input_data[1]->rows;Row++){
      for (int Col=0;Col<Vec_input_data[1]->cols;Col++){
        Output_aux->at<float>(Row,Col)=Output_aux->at<float>(Row,Col)/Max_value0;
      }
    }
  }

  // save the max value
  Vec_max_value_output_data[0]=Max_value0;

  *Vec_output_data[0]=Output_aux->clone();

  apply_colormap(Vec_output_data[0],Vec_output_images[0]);
}

/*************************************************************************/

void _filter_combination_element_remove::color(QColor Color1)
{
  Color=Color1;
  // get the palette data of the object
  _palette_data_ns::_palette_data &Palette_data=Window->Map_filters_palette_data[Window->mapping_selected_filter_name()];
  Palette_data.color(Color1);
  set_colormap(Palette_data.vec_values(),Palette_data.vec_colors(),Palette_data.type());
}

/*************************************************************************/

_filter_combination_element_remove_ui::_filter_combination_element_remove_ui(_window_xmapslab *Window1, std::string Name1)
{
  Name=Name1;
  Window=Window1;
  Qtw_filter_combination_element_remove=new _qtw_filter_combination_element_remove(Window1,this,Name1);
}

/*************************************************************************/

_filter_combination_element_remove_ui::_filter_combination_element_remove_ui(_window_xmapslab *Window1, std::map<string, string> &Parameters, std::string Name1)
{
  read_parameters(Parameters);
  Name=Name1;
  Window=Window1;
  Qtw_filter_combination_element_remove=new _qtw_filter_combination_element_remove(Window1,this,Name1);
}

/*************************************************************************/

_filter_combination_element_remove_ui::~_filter_combination_element_remove_ui()
{
  delete Qtw_filter_combination_element_remove;
}

/*************************************************************************/

void _filter_combination_element_remove_ui::reset_data()
{
  _filter_combination_element_remove::reset_data();
  Qtw_filter_combination_element_remove->parameter1(parameter1());
  hide();
}

/*************************************************************************/

void _filter_combination_element_remove_ui::show()
{
  Qtw_filter_combination_element_remove->show();
}

/*************************************************************************/

void _filter_combination_element_remove_ui::hide()
{
  Qtw_filter_combination_element_remove->hide();
}

/*************************************************************************/

void *_filter_combination_element_remove_ui::get_link()
{
  return Qtw_filter_combination_element_remove->get_link();
}

/*************************************************************************/

void _filter_combination_element_remove_ui::read_parameters(std::map<std::string,std::string> &Parameters)
{
  if (Parameters["_INI_"]=="EDITOR"){// default parameters
    parameter1(_f_combination_element_remove_ns::THRESHOLD_DEFAULT);
  }
  else{// Parameters from file or from initialised filter
    try{
      if (Parameters["threshold"]=="default") parameter1(_f_combination_element_remove_ns::THRESHOLD_DEFAULT);
      else parameter1(atoi(Parameters["threshold"].c_str()));
    }
    catch (...) {
      QMessageBox MsgBox;
      MsgBox.setText("Error in the data of combination remove filter");
      MsgBox.exec();
      exit(-1);
    }
  }
}

/*************************************************************************/

void _filter_combination_element_remove_ui::write_parameters(std::map<std::string,std::string> &Parameters)
{
  char Aux[100];

  sprintf(Aux,"%d",parameter1());
  Parameters["threshold"]=std::string(Aux);
}

/*************************************************************************/

void _filter_combination_element_remove_ui::color(QColor Color1)
{
  Color=Color1;
  Qtw_filter_combination_element_remove->parameter2(Color);
}

/*************************************************************************/

_qtw_filter_combination_element_remove::_qtw_filter_combination_element_remove(_window_xmapslab *Window1,_filter_combination_element_remove_ui *Filter1,std::string Box_name)
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

/*************************************************************************/

void _qtw_filter_combination_element_remove::parameter1(int Value)
{
  Spinbox_parameter1->blockSignals(true);
  Spinbox_parameter1->setValue(Value);
  Spinbox_parameter1->blockSignals(false);
}

/*************************************************************************/

void _qtw_filter_combination_element_remove::parameter2(QColor Color1)
{
  Button_parameter2->color(Color1);
}

/*************************************************************************/

void _qtw_filter_combination_element_remove::parameter1_slot(int Value)
{
  Filter->parameter1(Value);
  Window->update_filter(Filter->name());
}

/*************************************************************************/

void _qtw_filter_combination_element_remove::parameter2_slot(QColor Color1)
{
  Filter->parameter2(Color1);
  Window->update_filter(Filter->name());
}
