/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#include "filter_combination_addition_remove.h"
#include "glwidget_xmapslab_ge.h"
#include "window_xmapslab.h"

using namespace _f_element_ns;

/*************************************************************************/

_filter_combination_addition_remove::_filter_combination_addition_remove()
{
}

/*************************************************************************/

void _filter_combination_addition_remove::reset_data()
{
}

/*************************************************************************/

//void _filter_combination_addition_remove::compute_operation(int Row,int Col,shared_ptr<cv::Mat> Output_aux,shared_ptr<cv::Mat> Output_aux_A,shared_ptr<cv::Mat> Output_aux_B,float &Max_value_0,float &Max_value_1,float &Max_value_2)
//{
//  float Value0=0;
//  float Value1=0;
//  float Interval_min_value0=0;
//  float Interval_max_value0=0;
//  float Result_0=0;
//  float Result_1=0;
//  float Result_2=0;
//  float Computed_error=0;
//  float Proportion0=0;
//  float Value_aux0=0;
//  float Value_aux1=0;
//  float Remove0=0;
//  float Remove1=0;

//  float Max_value0=Vec_max_value_input_data[1];
//  float Max_value1=Vec_max_value_input_data[2];

//  Value0=float(Vec_input_data[1]->at<unsigned char>(Row,Col))*Max_value0/255.0f;
//  Value1=float(Vec_input_data[2]->at<unsigned char>(Row,Col))*Max_value1/255.0f;

//  if (Value0==0 || Value1==0){
//    Result_0=0;
//    Result_1=Value0;
//    Result_2=Value1;
//  }
//  else{ // Both values are different of 0

//    // Assume that A is ok. Compute the B
//    Value_aux1=Value0*Percentages[1]/Percentages[0];
//    if (Value_aux1<=Value1){
//      // There is enougb B to mix with all A
//       Remove1=Value1-Value_aux1;
//       Value1=Value_aux1;
//    }
//    else{
//      // Assume that B is ok. Compute the A
//      Value_aux0=Value1*Percentages[0]/Percentages[1];
//      if (Value_aux0<=Value0){
//        Remove0=Value0-Value_aux0;
//        Value0=Value_aux0;
//      }
//      else{
//        cout << "impossible" << endl;
//      }

//    }

//    Result_0=Value0+Value1;

//    Computed_error=Result_0*float(Error_element_A)/100.0f;

//    Proportion0=Result_0*Percentages[0];
//    Interval_min_value0=Proportion0-Computed_error;
//    Interval_max_value0=Proportion0+Computed_error;

//    if (Value0>=Interval_min_value0 && Value0<=Interval_max_value0){
//      // exact proportions for element A and so for element B
//      Result_1=Remove0;
//      Result_2=Remove1;
//    }
//    else{
//      // not the exact proportions for element A
//      if (Value0>Interval_max_value0){
//        // there is more proportion of element A than B
//        // assume that B is ok and compute A
//        float Aux_value0=Value1*Percentages[0]/Percentages[1];

//        if (Value0>=Aux_value0){
//          Result_0=Aux_value0+Value1;
//          Result_1=Value0-Aux_value0;
//          Result_2=0;
//        }
//        else{
//          Result_0=0;
//          Result_1=Value0;
//          Result_2=Value1;
//        }
//      }
//      else{
//        // there is less proportion of element A than B
//        // assume that A is ok and compute A
//        float Aux_value1=Value0*Percentages[1]/Percentages[0];
//        if (Value1>=Aux_value1){
//          Result_0=Aux_value1+Value0;
//          Result_1=0;
//          Result_2=Value1-Aux_value1;
//        }
//        else{
//          Result_0=0;
//          Result_1=Value0;
//          Result_2=Value1;
//        }
//      }
//    }
//  }

//  Output_aux->at<float>(Row,Col)=Result_0;
//  if (Result_0>Max_value_0) Max_value_0=Result_0;

//  Output_aux_A->at<float>(Row,Col)=Result_1;
//  if (Result_1>Max_value_1) Max_value_1=Result_1;

//  Output_aux_B->at<float>(Row,Col)=Result_2;
//  if (Result_2>Max_value_2) Max_value_2=Result_2;
//}

void _filter_combination_addition_remove::compute_operation(int Row,int Col,std::shared_ptr<cv::Mat> Output_aux,std::shared_ptr<cv::Mat> Output_aux_A,std::shared_ptr<cv::Mat> Output_aux_B,float &Max_value_0,float &Max_value_1,float &Max_value_2)
{
  float Value0=0;
  float Value1=0;
//  float Interval_min_value0=0;
//  float Interval_max_value0=0;
  float Result_0=0;
  float Result_1=0;
  float Result_2=0;
//  float Computed_error=0;
//  float Proportion0=0;
  float Value_aux0=0;
  float Value_aux1=0;
  float Remove0=0;
  float Remove1=0;

  float Max_value0=Vec_max_value_input_data[1];
  float Max_value1=Vec_max_value_input_data[2];

  Value0=Vec_input_data[1]->at<float>(Row,Col)*Max_value0;
  Value1=Vec_input_data[2]->at<float>(Row,Col)*Max_value1;

  if (Value0==0 || Value1==0){
    Result_0=0;
    Result_1=Value0;
    Result_2=Value1;
  }
  else{ // Both values are different of 0
    // Assume that A is ok. Compute the B
    Value_aux1=Value0*Vec_percentages[1]/Vec_percentages[0];
    if (Value_aux1<=Value1){
      // There is enougb B to mix with all A
       Remove1=Value1-Value_aux1;
       Value1=Value_aux1;
    }
    else{
      // Assume that B is ok. Compute the A
      Value_aux0=Value1*Vec_percentages[0]/Vec_percentages[1];
      if (Value_aux0<=Value0){
        Remove0=Value0-Value_aux0;
        Value0=Value_aux0;
      }
    }

    Result_0=Value0+Value1;
    Result_1=Remove0;
    Result_2=Remove1;
  }

  Output_aux->at<float>(Row,Col)=Result_0;
  if (Result_0>Max_value_0) Max_value_0=Result_0;

  Output_aux_A->at<float>(Row,Col)=Result_1;
  if (Result_1>Max_value_1) Max_value_1=Result_1;

  Output_aux_B->at<float>(Row,Col)=Result_2;
  if (Result_2>Max_value_2) Max_value_2=Result_2;
}

/*************************************************************************/

void _filter_combination_addition_remove::update()
{
  float Max_value0=-1;
  float Max_value1=-1;
  float Max_value2=-1;

  update_max_values();

  shared_ptr<cv::Mat> Logic=Vec_input_data[0];

  shared_ptr<cv::Mat> Output_aux=make_shared<cv::Mat>();
  Output_aux->create(Vec_input_data[1]->rows,Vec_input_data[1]->cols,CV_32F);

  shared_ptr<cv::Mat> Output_aux_A=make_shared<cv::Mat>();
  Output_aux_A->create(Vec_input_data[1]->rows,Vec_input_data[1]->cols,CV_32F);

  shared_ptr<cv::Mat> Output_aux_B=make_shared<cv::Mat>();
  Output_aux_B->create(Vec_input_data[1]->rows,Vec_input_data[1]->cols,CV_32F);

  if (Logic!=nullptr){
    for (int Row=0;Row<Vec_input_data[1]->rows;Row++){
      for (int Col=0;Col<Vec_input_data[1]->cols;Col++){
        if (Original_image->at<cv::Vec3b>(Row,Col)[3]!=0){
          if (Logic->at<float>(Row,Col)==1.0f){
            compute_operation(Row,Col,Output_aux,Output_aux_A,Output_aux_B,Max_value0,Max_value1,Max_value2);
          }
          else{
            Output_aux->at<float>(Row,Col)=0;
            if (0>Max_value0) Max_value0=0;

            Output_aux_A->at<float>(Row,Col)=0;
            if (0>Max_value1) Max_value1=0;

            Output_aux_B->at<float>(Row,Col)=0;
            if (0>Max_value2) Max_value2=0;
          }
        }
      }
    }
  }
  else{
    for (int Row=0;Row<Vec_input_data[1]->rows;Row++){
      for (int Col=0;Col<Vec_input_data[1]->cols;Col++){
        if (Original_image->at<cv::Vec3b>(Row,Col)[3]!=0){
          compute_operation(Row,Col,Output_aux,Output_aux_A,Output_aux_B,Max_value0,Max_value1,Max_value2);
        }
      }
    }
  }

  // Do the normalization and compute the final values
  float Normalization_value0=0;
  float Normalization_value1=0;
  float Normalization_value2=0;
  if (Relative_normalization==true){
    Normalization_value0=Max_value0;
    Normalization_value1=Max_value1;
    Normalization_value2=Max_value2;
  }
  else{    
    Normalization_value0=Vec_max_value_input_data[1]+Vec_max_value_input_data[2];
    Normalization_value1=Vec_max_value_input_data[1];
    Normalization_value2=Vec_max_value_input_data[2];
  }

  for (int Row=0;Row<Vec_input_data[1]->rows;Row++){
    for (int Col=0;Col<Vec_input_data[1]->cols;Col++){
      Vec_output_data[0]->at<float>(Row,Col)=Output_aux->at<float>(Row,Col)/Normalization_value0;
      Vec_output_data[1]->at<float>(Row,Col)=Output_aux_A->at<float>(Row,Col)/Normalization_value1;
      Vec_output_data[2]->at<float>(Row,Col)=Output_aux_B->at<float>(Row,Col)/Normalization_value2;
    }
  }

  Vec_output_data[0]=Output_aux;
  Vec_output_data[1]=Output_aux_A;
  Vec_output_data[2]=Output_aux_B;

  Vec_max_value_output_data[0]=Normalization_value0;
  Vec_max_value_output_data[1]=Normalization_value1;
  Vec_max_value_output_data[2]=Normalization_value2;

  apply_colormap(Vec_output_data[0],Vec_output_images[0]);
}

/*************************************************************************/

void _filter_combination_addition_remove::color(QColor Color1)
{
  Color=Color1;
  // get the palette data of the object
  _palette_data &Vec_palette_data=Window->Map_filters_palette_data[Window->mapping_selected_filter_name()];
  Vec_palette_data.color(Color1);
  set_colormap(Vec_palette_data.vec_values(),Vec_palette_data.vec_colors(),Vec_palette_data.data_type());
}

/*************************************************************************/

void _filter_combination_addition_remove::num_atoms(int Pos,int Num_atoms1)
{
  Vec_num_atoms[Pos]=Num_atoms1;

  float Total_atoms=0;
  for (unsigned int i=0;i<Vec_num_atoms.size();i++){
    Total_atoms=Total_atoms+float(Vec_num_atoms[i]);
  }

  for (unsigned int i=0;i<Vec_num_atoms.size();i++){
    Vec_percentages[i]=float(Vec_num_atoms[i])/Total_atoms;
  }
}

/*************************************************************************/

_filter_combination_addition_remove_ui::_filter_combination_addition_remove_ui(_window_xmapslab *Window1, std::string Name1)
{
  Name=Name1;
  Window=Window1;
  Qtw_filter_combination_addition_remove=new _qtw_filter_combination_addition_remove(Window1,this,Name1);
}

/*************************************************************************/

_filter_combination_addition_remove_ui::_filter_combination_addition_remove_ui(_window_xmapslab *Window1, std::map<string, string> &Parameters, std::string Name1)
{
  read_parameters(Parameters);
  Name=Name1;
  Window=Window1;
  Qtw_filter_combination_addition_remove=new _qtw_filter_combination_addition_remove(Window1,this,Name1);
}

/*************************************************************************/

_filter_combination_addition_remove_ui::~_filter_combination_addition_remove_ui()
{
  delete Qtw_filter_combination_addition_remove;
}

/*************************************************************************/

void _filter_combination_addition_remove_ui::reset_data()
{
  _filter_combination_addition_remove::reset_data();
//  Qtw_filter_combination_addition_remove->parameter1(parameter1());
  hide();
}

/*************************************************************************/

void _filter_combination_addition_remove_ui::show()
{
  Qtw_filter_combination_addition_remove->show();
}

/*************************************************************************/

void _filter_combination_addition_remove_ui::hide()
{
  Qtw_filter_combination_addition_remove->hide();
}

/*************************************************************************/

void *_filter_combination_addition_remove_ui::get_link()
{
  return Qtw_filter_combination_addition_remove->get_link();
}

/*************************************************************************/

void _filter_combination_addition_remove_ui::read_parameters(std::map<std::string,std::string> &Parameters)
{
  if (Parameters["_INI_"]=="EDITOR"){// default parameters
//    parameter1(_f_combination_addition_remove_ns::THRESHOLD_DEFAULT);
      parameter3(_f_combination_addition_remove_ns::NUM_ATOMS_DEFAULT);
      parameter4(_f_combination_addition_remove_ns::NUM_ATOMS_DEFAULT);
//      parameter5(_f_combination_addition_remove_ns::ERROR_ELEMENT_A_DEFAULT);
  }
  else{// Parameters from file or from initialised filter
    try{
//      if (Parameters["threshold"]=="default") parameter1(_f_combination_addition_remove_ns::THRESHOLD_DEFAULT);
//      else parameter1(atoi(Parameters["threshold"].c_str()));
      if (Parameters["num_atoms_a"]=="default") parameter3(_f_combination_addition_remove_ns::NUM_ATOMS_DEFAULT);
      else parameter3(atoi(Parameters["num_atoms_a"].c_str()));

      if (Parameters["num_atoms_b"]=="default") parameter4(_f_combination_addition_remove_ns::NUM_ATOMS_DEFAULT);
      else parameter4(atoi(Parameters["num_atoms_b"].c_str()));

//      if (Parameters["error"]=="default") parameter5(_f_combination_addition_remove_ns::ERROR_ELEMENT_A_DEFAULT);
//      else parameter5(atoi(Parameters["error"].c_str()));
    }
    catch (...) {
      QMessageBox MsgBox;
      MsgBox.setText("Error in the data of combination addtion remove filter");
      MsgBox.exec();
      exit(-1);
    }
  }
}

/*************************************************************************/

void _filter_combination_addition_remove_ui::write_parameters(std::map<std::string,std::string> &Parameters)
{
  char Aux[100];

//  sprintf(Aux,"%d",parameter1());
//  Parameters["threshold"]=std::string(Aux);
  sprintf(Aux,"%d",parameter3());
  Parameters["num_atoms_a"]=std::string(Aux);

  sprintf(Aux,"%d",parameter4());
  Parameters["num_atoms_b"]=std::string(Aux);

//  sprintf(Aux,"%d",parameter5());
//  Parameters["error"]=std::string(Aux);
}

/*************************************************************************/

void _filter_combination_addition_remove_ui::color(QColor Color1)
{
  Color=Color1;
  Qtw_filter_combination_addition_remove->parameter2(Color);
}

/*************************************************************************/

_qtw_filter_combination_addition_remove::_qtw_filter_combination_addition_remove(_window_xmapslab *Window1,_filter_combination_addition_remove_ui *Filter1,std::string Box_name)
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
//  Spinbox_parameter1=new QSpinBox;
//  Spinbox_parameter1->setRange(0,100);
//  Spinbox_parameter1->setAlignment(Qt::AlignRight);
//  Spinbox_parameter1->setSuffix(" %");

//  parameter1(Filter->parameter1());

//  connect(Spinbox_parameter1,SIGNAL(valueChanged(int)),this,SLOT(parameter1_slot(int)));

  // Parameter2
  float Factor=Window->screen_height()/1080.0f;
  Button_parameter2=new _button_color_simple(QColor(255,0,0),Factor);

  connect(Button_parameter2,SIGNAL(colorChanged(QColor)),this,SLOT(parameter2_slot(QColor)));

  // A value
  Spinbox_parameter3=new QSpinBox;
  Spinbox_parameter3->setRange(1,10);
  Spinbox_parameter3->setAlignment(Qt::AlignRight);
  Spinbox_parameter3->setValue(Filter->parameter3());
//  Spinbox_parameter3->setSuffix(" %");

  connect(Spinbox_parameter3,SIGNAL(valueChanged(int)),this,SLOT(parameter3_slot(int)));

  // B value
  Spinbox_parameter4=new QSpinBox;
  Spinbox_parameter4->setRange(1,10);
  Spinbox_parameter4->setAlignment(Qt::AlignRight);
  Spinbox_parameter4->setValue(Filter->parameter4());
//  Spinbox_parameter4->setSuffix(" %");
//  Spinbox_parameter4->setEnabled(false);

  connect(Spinbox_parameter4,SIGNAL(valueChanged(int)),this,SLOT(parameter4_slot(int)));

  // A error
//  Spinbox_parameter5=new QSpinBox;
//  Spinbox_parameter5->setRange(0,100);
//  Spinbox_parameter5->setAlignment(Qt::AlignRight);
//  Spinbox_parameter5->setSuffix(" %");

  // I have to put this instruction here because it affect to parameter 4 that must be created
//  parameter3(Filter1->parameter3());

//  parameter5(Filter1->parameter5());

//  connect(Spinbox_parameter5,SIGNAL(valueChanged(int)),this,SLOT(parameter5_slot(int)));

  //
//  QLabel *Label_parameter1=new QLabel("0 threshold");
  QLabel *Label_parameter2=new QLabel("Color");
  QLabel *Label_parameter3=new QLabel("Num atoms A");
  QLabel *Label_parameter4=new QLabel("Num atoms B");
//  QLabel *Label_parameter5=new QLabel("Error");

//  Grid_parameter1->addWidget(Label_parameter1,0,0,Qt::AlignRight);
//  Grid_parameter1->addWidget(Spinbox_parameter1,0,1,Qt::AlignLeft);
  Grid_parameter1->addWidget(Label_parameter2,1,0,Qt::AlignRight);
  Grid_parameter1->addWidget(Button_parameter2,1,1,Qt::AlignLeft);
  Grid_parameter1->addWidget(Label_parameter3,2,0,Qt::AlignRight);
  Grid_parameter1->addWidget(Spinbox_parameter3,2,1,Qt::AlignLeft);
  Grid_parameter1->addWidget(Label_parameter4,3,0,Qt::AlignRight);
  Grid_parameter1->addWidget(Spinbox_parameter4,3,1,Qt::AlignLeft);
//  Grid_parameter1->addWidget(Label_parameter5,4,0,Qt::AlignRight);
//  Grid_parameter1->addWidget(Spinbox_parameter5,4,1,Qt::AlignLeft);

  Frame_parameter1->setLayout(Grid_parameter1);
  //
  Vertical_box_main->addWidget(Frame_parameter1);

  Group_box_main->setLayout(Vertical_box_main);
}

/*************************************************************************/

//void _qtw_filter_combination_addition_remove::parameter1(int Value)
//{
//  Spinbox_parameter1->blockSignals(true);
//  Spinbox_parameter1->setValue(Value);
//  Spinbox_parameter1->blockSignals(false);
//}

/*************************************************************************/

void _qtw_filter_combination_addition_remove::parameter2(QColor Color1)
{
  Button_parameter2->color(Color1);
}

/*************************************************************************/

void _qtw_filter_combination_addition_remove::parameter3(int Value)
{
  Spinbox_parameter3->blockSignals(true);
  Spinbox_parameter3->setValue(Value);
  Spinbox_parameter3->blockSignals(false);

  Spinbox_parameter4->setValue(100-Value);
}

/*************************************************************************/

//void _qtw_filter_combination_addition_remove::parameter5(int Value)
//{
//  Spinbox_parameter5->blockSignals(true);
//  Spinbox_parameter5->setValue(Value);
//  Spinbox_parameter5->blockSignals(false);
//}

/*************************************************************************/

//void _qtw_filter_combination_addition_remove::parameter1_slot(int Value)
//{
//  Filter->parameter1(Value);
//  Window->update_filter(Filter->name());
//}

/*************************************************************************/

void _qtw_filter_combination_addition_remove::parameter2_slot(QColor Color1)
{
  Filter->parameter2(Color1);
  Window->update_filter(Filter->name());
}

/*************************************************************************/

void _qtw_filter_combination_addition_remove::parameter3_slot(int Value)
{
  Filter->parameter3(Value);
  Window->update_filter(Filter->name());
}

/*************************************************************************/

void _qtw_filter_combination_addition_remove::parameter4_slot(int Value)
{
  Filter->parameter4(Value);
  Window->update_filter(Filter->name());
}

/*************************************************************************/

//void _qtw_filter_combination_addition_remove::parameter5_slot(int Value)
//{
//  Filter->parameter5(Value);
//  Window->update_filter(Filter->name());
//}
