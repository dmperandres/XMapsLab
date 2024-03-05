/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#include "layer_map_rbf_interpolation.h"
#include "window_xmapslab.h"

using namespace _layer_map_rbf_interpolation_ns;

/*************************************************************************/

_layer_map_rbf_interpolation::_layer_map_rbf_interpolation()
{
  Layer_type=_layer_xmapslab_ns::_layer_type::LAYER_TYPE_MAP_RBF_INTERPOLATION;
}

/*************************************************************************/

_layer_map_rbf_interpolation::~_layer_map_rbf_interpolation()
{
#ifdef DEBUG_XML
  cout << "terminando layer element" << endl;
#endif
}

/*************************************************************************/

void _layer_map_rbf_interpolation::add_input_data(std::vector<float> &Vec_coordinate_x1, std::vector<float> &Vec_coordinate_y1, std::vector<float> &Vec_value1, float Epsilon1)
{

  for (unsigned int i=0;i<Vec_active_positions.size();i++){
    if (Vec_active_positions[i]==true){
      Coordinates_x.push_back(Vec_coordinate_x1[i]/float(Width-1));
      Coordinates_y.push_back(1.0f-Vec_coordinate_y1[i]/float(Height-1));
      Intensities.push_back(Vec_value1[i]);
    }
  }

  Epsilon=Epsilon1;
}

/*************************************************************************/

void _layer_map_rbf_interpolation::update_map()
{

  // the computation of the distances is made only one time
  if (Computed==false){
    Computed=true;

    // compute the dimensions of the RBF result image that is then up scaled
    int Max_dimension;
    if (Width>Height) Max_dimension=Width;
    else Max_dimension=Height;

    float Width_aux;
    float Height_aux;
    if (Max_dimension<=_layer_map_ns::MAX_DIMENSION_DEFAULT){
      Width_aux=float(Width);
      Height_aux=float(Height);
    }
    else{
      float Quotient;

      if (Width>Height){
        Width_aux=float(_layer_map_ns::MAX_DIMENSION_DEFAULT);
        Height_aux=float(Height*_layer_map_ns::MAX_DIMENSION_DEFAULT)/float(Width);

        Quotient=Height_aux/4.0f;
        Height_aux=roundf(Quotient)*4.0f;
      }
      else{
        Height_aux=float(_layer_map_ns::MAX_DIMENSION_DEFAULT);
        Width_aux=float(Width*_layer_map_ns::MAX_DIMENSION_DEFAULT)/float(Height);

        Quotient=Width_aux/4.0f;
        Width_aux=roundf(Quotient)*4.0f;
      }
    }

    _new_rbf_interpolation_2d RBF;
    RBF.set_input_data(Coordinates_x,Coordinates_y,Intensities,Epsilon);
    RBF.set_output_positions(Width_aux,Height_aux);
    RBF.set_function_type(Function_type);

    std::string Error;
    if (RBF.compute_interpolation(Interpolated_intensities,Error)==false){
      QMessageBox::warning(Window,"Warning",QString::fromStdString(Error));
    }
    else{
      // convert the vector to a matrix
      cv::Mat Result;
      Result.create(Height_aux,Width_aux,CV_32FC1);

      int Pos=0;
      for (int Row=0;Row<int(Height_aux);Row++){
        for (int Col=0;Col<int(Width_aux);Col++){
          Result.at<float>(Row,Col)=Interpolated_intensities[Pos];
          Pos++;
        }
      }

      cv::flip(Result,Result,0);

      // read the result
      if (Result_floats_image==nullptr){
        Result_floats_image=make_shared<cv::Mat>();
        Result_floats_image->create(Height,Width,CV_32FC1);
      }

      cv::resize(Result,*Result_floats_image,cv::Size(Width,Height), cv::INTER_LINEAR);

      // to check if there are transparent pixels
      shared_ptr<cv::Mat> Image_normalized=Vec_input_images[0];
      cv::Vec4f Pixel;
      for (int Row=0;Row<Result_floats_image->rows;Row++){
        for (int Col=0;Col<Result_floats_image->cols;Col++){
          Pixel=Image_normalized->at<cv::Vec4f>(Row,Col);
          if (Pixel[3]==0){
            if (Col%20<10 && Row%20<10) Result_floats_image->at<float>(Row,Col)=1.0f;
            else Result_floats_image->at<float>(Row,Col)=0.0f;
          }
        }
      }

      apply_colormap();
      apply_color_mixing();
    }
  }
  else{
    // only update if necessary
    if (Colormap_changed){
      Colormap_changed=false;
      apply_colormap();
    }
    if (Color_mixing_changed){
      Color_mixing_changed=false;
      apply_color_mixing();
    }
  }
}

/*************************************************************************/

void _layer_map_rbf_interpolation::update()
{
  update_map();
}

/*************************************************************************/

_layer_map_rbf_interpolation_ui::_layer_map_rbf_interpolation_ui(_window_xmapslab *Window1, std::string Name1)
{
  Window=Window1;
  Name=Name1;
  Qtw_layer_map_rbf_interpolation_a=new _qtw_layer_map_rbf_interpolation(Window1,this,Name);
}

/*************************************************************************/

_layer_map_rbf_interpolation_ui::~_layer_map_rbf_interpolation_ui()
{
  delete Qtw_layer_map_rbf_interpolation_a;
}

/*************************************************************************/

void _layer_map_rbf_interpolation_ui::reset_data()
{
  _layer_map_rbf_interpolation::reset_data();
  Qtw_layer_map_rbf_interpolation_a->parameter1(parameter1());
  hide();
}

/*************************************************************************/

void _layer_map_rbf_interpolation_ui::show()
{
  Qtw_layer_map_rbf_interpolation_a->show();
}

/*************************************************************************/

void _layer_map_rbf_interpolation_ui::hide()
{
  Qtw_layer_map_rbf_interpolation_a->hide();
}

/*************************************************************************/

void *_layer_map_rbf_interpolation_ui::get_link()
{
  return Qtw_layer_map_rbf_interpolation_a->get_link();
}

/*************************************************************************/

void _layer_map_rbf_interpolation_ui::enable()
{
  Qtw_layer_map_rbf_interpolation_a->enable();
}

/*************************************************************************/

void _layer_map_rbf_interpolation_ui::disable()
{
  Qtw_layer_map_rbf_interpolation_a->disable();
}

/*************************************************************************/

void _layer_map_rbf_interpolation_ui::parameter1_ui(float Value)
{
  Qtw_layer_map_rbf_interpolation_a->parameter1(int(Value*255.0f));
}

/*************************************************************************/

void _layer_map_rbf_interpolation_ui::parameter2_ui(float Value)
{
  Qtw_layer_map_rbf_interpolation_a->parameter2(int(Value*255.0f));
}

/*************************************************************************/

void _layer_map_rbf_interpolation_ui::parameter3_ui(float Value)
{
  Qtw_layer_map_rbf_interpolation_a->parameter3(int(Value*255.0f));
}

/*************************************************************************/

void _layer_map_rbf_interpolation_ui::parameter4_ui(int Value)
{
  Qtw_layer_map_rbf_interpolation_a->parameter4(Value);
}

/*************************************************************************/

void _layer_map_rbf_interpolation_ui::data_type_print(_palette_data_ns::_data_type_print Data_type_print1)
{
  Data_type_print=Data_type_print1;
  Qtw_layer_map_rbf_interpolation_a->parameter4(int(Data_type_print1));
}

/*************************************************************************/

_qtw_layer_map_rbf_interpolation::_qtw_layer_map_rbf_interpolation(_window_xmapslab *Window1,_layer_map_rbf_interpolation_ui *Filter1,std::string Box_name)
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

  Slider_parameter1 = new QSlider(Qt::Horizontal);
  Slider_parameter1->setRange(Parameter1_min_value,Parameter1_max_value);
  Slider_parameter1->setSingleStep(Parameter1_single_step);
  Slider_parameter1->setPageStep(Parameter1_page_step);
  Slider_parameter1->setTickInterval(Parameter1_tick_interval);
  Slider_parameter1->setTickPosition(QSlider::TicksRight);
  Slider_parameter1->setTracking(Parameter1_set_tracking);
  Slider_parameter1->setToolTip(tr(String_parameter1_tooltip.c_str()));

  parameter1(Filter->parameter1());

//  Grid_parameter1->addWidget(Line_edit_parameter1,0,1,Qt::AlignCenter);
  Grid_parameter1->addWidget(Label_parameter1_min,0,0,Qt::AlignRight);
  Grid_parameter1->addWidget(Slider_parameter1,0,1);
  Grid_parameter1->addWidget(Label_parameter1_max,0,2,Qt::AlignLeft);

  Group_box_parameter1->setLayout(Grid_parameter1);

  connect(Slider_parameter1, SIGNAL(valueChanged(int)),this,SLOT(parameter1_slot(int)));

  // Parameter2
  QGroupBox *Group_box_parameter2=new QGroupBox(tr(String_group_box_parameter2.c_str()));
  Group_box_parameter2->setAlignment(Qt::AlignCenter);

  QGridLayout *Grid_parameter2 = new QGridLayout;

  QLabel *Label_parameter2_title= new QLabel(tr(String_label_parameter2_title.c_str()));
  QLabel *Label_parameter2_min= new QLabel(tr(String_label_parameter2_min.c_str()));
  QLabel *Label_parameter2_max= new QLabel(tr(String_label_parameter2_max.c_str()));

  QLabel *Label_parameter3_title= new QLabel(tr(String_label_parameter3_title.c_str()));
  QLabel *Label_parameter3_min= new QLabel(tr(String_label_parameter3_min.c_str()));
  QLabel *Label_parameter3_max= new QLabel(tr(String_label_parameter3_max.c_str()));

  Slider_parameter2 = new QSlider(Qt::Horizontal);
  Slider_parameter2->setRange(Parameter2_min_value,Parameter2_max_value);
  Slider_parameter2->setSingleStep(Parameter2_single_step);
  Slider_parameter2->setPageStep(Parameter2_page_step);
  Slider_parameter2->setTickInterval(Parameter2_tick_interval);
  Slider_parameter2->setTickPosition(QSlider::TicksRight);
  Slider_parameter2->setTracking(Parameter2_set_tracking);
  Slider_parameter2->setToolTip(tr(String_parameter2_tooltip.c_str()));

  parameter2(Filter->parameter2());

  // parameter 3
  Slider_parameter3 = new QSlider(Qt::Horizontal);
  Slider_parameter3->setRange(Parameter3_min_value,Parameter3_max_value);
  Slider_parameter3->setSingleStep(Parameter3_single_step);
  Slider_parameter3->setPageStep(Parameter3_page_step);
  Slider_parameter3->setTickInterval(Parameter3_tick_interval);
  Slider_parameter3->setTickPosition(QSlider::TicksRight);
  Slider_parameter3->setTracking(Parameter3_set_tracking);
  Slider_parameter3->setToolTip(tr(String_parameter3_tooltip.c_str()));

  parameter3(Filter->parameter3());

  Grid_parameter2->addWidget(Label_parameter2_title,0,1,Qt::AlignCenter);
  Grid_parameter2->addWidget(Label_parameter2_min,1,0,Qt::AlignRight);
  Grid_parameter2->addWidget(Slider_parameter2,1,1);
  Grid_parameter2->addWidget(Label_parameter2_max,1,2,Qt::AlignLeft);

  Grid_parameter2->addWidget(Label_parameter3_title,2,1,Qt::AlignCenter);
  Grid_parameter2->addWidget(Label_parameter3_min,3,0,Qt::AlignRight);
  Grid_parameter2->addWidget(Slider_parameter3,3,1);
  Grid_parameter2->addWidget(Label_parameter3_max,3,2,Qt::AlignLeft);

  Group_box_parameter2->setLayout(Grid_parameter2);

  connect(Slider_parameter2, SIGNAL(valueChanged(int)),this,SLOT(parameter2_slot(int)));
  connect(Slider_parameter3, SIGNAL(valueChanged(int)),this,SLOT(parameter3_slot(int)));

  // Parameter 4
  QFrame *Frame_parameter4=new QFrame;
  Frame_parameter4->setFrameStyle(QFrame::Panel);

  QGridLayout *Grid_parameter4=new QGridLayout;

  QLabel *Label_operations1=new QLabel(tr(String_group_box_parameter4.c_str()));

  Combobox_parameter4 = new QComboBox;
  for (unsigned int i=0;i<_palette_data_ns::Vec_names_data_type_print.size();i++){
    Combobox_parameter4->addItem(_palette_data_ns::Vec_names_data_type_print[i]);
  }
  Combobox_parameter4->setCurrentIndex(Filter->parameter4());

  Grid_parameter4->addWidget(Label_operations1,0,0,Qt::AlignRight);
  Grid_parameter4->addWidget(Combobox_parameter4,0,1,Qt::AlignLeft);;

  Frame_parameter4->setLayout(Grid_parameter4);

  connect(Combobox_parameter4, SIGNAL(activated(int)), this,SLOT(parameter4_slot(int)));

  //
  Vertical_box_main->addWidget(Group_box_parameter1);
  Vertical_box_main->addWidget(Group_box_parameter2);
  Vertical_box_main->addWidget(Frame_parameter4);

  Group_box_main->setLayout(Vertical_box_main);
}

/*************************************************************************/

void _qtw_layer_map_rbf_interpolation::parameter1(int Value)
{
  Slider_parameter1->blockSignals(true);
  Slider_parameter1->setValue(Value);
  Slider_parameter1->blockSignals(false);
}

/*************************************************************************/

void _qtw_layer_map_rbf_interpolation::parameter2(int Value)
{
  Slider_parameter2->blockSignals(true);
  Slider_parameter2->setValue(Value);
  Slider_parameter2->blockSignals(false);
}

/*************************************************************************/

void _qtw_layer_map_rbf_interpolation::parameter3(int Value)
{
  Slider_parameter3->blockSignals(true);
  Slider_parameter3->setValue(Value);
  Slider_parameter3->blockSignals(false);
}

/*************************************************************************/

void _qtw_layer_map_rbf_interpolation::parameter4(int Value)
{
  Combobox_parameter4->blockSignals(true);
  Combobox_parameter4->setCurrentIndex(Value);
  Combobox_parameter4->blockSignals(false);
}

/*************************************************************************/

void _qtw_layer_map_rbf_interpolation::parameter1_slot(int Value)
{
  Filter->parameter1(Value);
  Window->update_layer(Filter->name());
}

/*************************************************************************/

void _qtw_layer_map_rbf_interpolation::parameter2_slot(int Value)
{
  Filter->parameter2(Value);
  Window->update_layer(Filter->name());
}

/*************************************************************************/

void _qtw_layer_map_rbf_interpolation::parameter3_slot(int Value)
{
  Filter->parameter3(Value);
  Window->update_layer(Filter->name());
}

/*************************************************************************/

void _qtw_layer_map_rbf_interpolation::parameter4_slot(int Value)
{
  Filter->parameter2(Value);
  Window->update_color_bar_data_type_print(Value);
}
