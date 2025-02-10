//LIC

#include "layer_compound_from_elements.h"
#include "window_xmapslab.h"

using namespace _layer_compound_from_elements_ns;

//HEA

_layer_compound_from_elements::_layer_compound_from_elements()
{
  Layer_type=_layer_xmapslab_ns::_layer_type::LAYER_TYPE_COMPOUND_COMBINATION;
}

//HEA

_layer_compound_from_elements::~_layer_compound_from_elements()
{
#ifdef DEBUG_XML
  cout << "terminando layer element" << endl;
#endif
}


//HEA
// idea Element A 75% 500 + Element B 25% 250
// 75% ---- 500
// 25% ---- X=166
//
// if B>=X -> Valid


float _layer_compound_from_elements::compute_operation(std::vector<float>& Vec_intensities)
{
  std::vector<float> Vec_adjusted_intensities(Num_elements);
  float Adjusted_value;
  bool Valid=true;
  float Sum;
  float Maximum=0;
  int Pos_next;

  int Pos;
  for (unsigned int i=0;i<Vec_permutations.size();i++){
    // for the permutation, the first value gets all the intensitie
    Vec_adjusted_intensities[0]=Vec_intensities[Vec_permutations[i][0]]*Vec_max_intensities[Vec_permutations[i][0]]*Vec_global_percentages[Vec_permutations[i][0]];
    Sum=Vec_adjusted_intensities[0];
    // compute the other values
    Pos=1;
    Valid=true;
    while (Pos<Num_elements){
      Pos_next=Vec_permutations[i][Pos];
      Adjusted_value=Vec_adjusted_intensities[Pos-1]*Vec_percentages[Pos_next]/Vec_percentages[Vec_permutations[i][Pos-1]];
      if (Adjusted_value<=Vec_intensities[Pos_next]*Vec_max_intensities[Pos_next]*Vec_global_percentages[Pos_next]){
        Vec_adjusted_intensities[Pos]=Adjusted_value;
        Sum=Sum+Adjusted_value;
        Pos=Pos+1;
      }
      else{
        Valid=false;
        break;
      }
    }

    if (Valid==true){
      if (Sum>Maximum) Maximum=Sum;
    }
  }

  return Maximum;
}


//HEA

void _layer_compound_from_elements::add_input_data(std::vector<std::shared_ptr<cv::Mat> > &Vec_maps_intensities1, std::vector<float> &Vec_max_intensities1, std::vector<float> &Vec_percentages1,std::vector<float> &Vec_global_percentages1)
{
  Vec_maps_intensities=Vec_maps_intensities1;
  Vec_max_intensities=Vec_max_intensities1;
  Vec_percentages=Vec_percentages1;  
  Vec_global_percentages=Vec_global_percentages1;

  Num_elements=Vec_maps_intensities.size();

  std::vector<int> Vec_aux;

  for (int i=0;i<Num_elements;i++) Vec_aux.push_back(i);

  // Sort the given array
  sort(Vec_aux.begin(), Vec_aux.end());

  // Find all possible permutations
  bool Valid;
  Vec_permutations.clear();

  do {
    Vec_permutations.push_back(Vec_aux);
    Valid=next_permutation(Vec_aux.begin(), Vec_aux.end());
  } while (Valid);
}

//HEA

void _layer_compound_from_elements::update_map()
{

  // the computation of the distances is made only one time
  if (Computed==false){
    Computed=true;

    // read the result
    if (Result_floats_image==nullptr){
      Result_floats_image=make_shared<cv::Mat>();
      Result_floats_image->create(Height,Width,CV_32FC1);
    }

    // the intensities of the elements at each pixel
    std::vector<float> Vec_intensities_aux(Num_elements);
    float Result;

    for (int Row=0;Row<Result_floats_image->rows;Row++){
      for (int Col=0;Col<Result_floats_image->cols;Col++){
        for (int Pos=0;Pos<Num_elements;Pos++){
          Vec_intensities_aux[Pos]=Vec_maps_intensities[Pos]->at<float>(Row,Col);
        }
        Result=compute_operation(Vec_intensities_aux);
        if (Result>Max_intensity) Max_intensity=Result;
        Result_floats_image->at<float>(Row,Col)=Result;
      }
    }

    // to check if there are transparent pixels and normalize
    shared_ptr<cv::Mat> Image_normalized=Vec_input_images[0];
    cv::Vec4f Pixel;
    for (int Row=0;Row<Result_floats_image->rows;Row++){
      for (int Col=0;Col<Result_floats_image->cols;Col++){
        Pixel=Image_normalized->at<cv::Vec4f>(Row,Col);
        if (Pixel[3]==0){
          if (Col%20<10 && Row%20<10) Result_floats_image->at<float>(Row,Col)=1.0f;
          else Result_floats_image->at<float>(Row,Col)=0.0f;
        }
        else{
          // normalization
          Result_floats_image->at<float>(Row,Col)=Result_floats_image->at<float>(Row,Col)/Max_intensity;
        }
      }
    }

    apply_colormap();
    apply_color_mixing();

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

//HEA

void _layer_compound_from_elements::update()
{
  update_map();
}

//HEA

_layer_compound_from_elements_ui::_layer_compound_from_elements_ui(_window_xmapslab *Window1, std::string Name1)
{
  Window=Window1;
  Name=Name1;
  Qtw_layer_compound_from_elements_a=new _qtw_layer_compound_from_elements(Window1,this,Name);
}

//HEA

_layer_compound_from_elements_ui::~_layer_compound_from_elements_ui()
{
  delete Qtw_layer_compound_from_elements_a;
}

//HEA

void _layer_compound_from_elements_ui::reset_data()
{
  _layer_compound_from_elements::reset_data();
  Qtw_layer_compound_from_elements_a->parameter1(parameter1());
  hide();
}

//HEA

void _layer_compound_from_elements_ui::show()
{
  Qtw_layer_compound_from_elements_a->show();
}

//HEA

void _layer_compound_from_elements_ui::hide()
{
  Qtw_layer_compound_from_elements_a->hide();
}

//HEA

void *_layer_compound_from_elements_ui::get_link()
{
  return Qtw_layer_compound_from_elements_a->get_link();
}

//HEA

void _layer_compound_from_elements_ui::enable()
{
  Qtw_layer_compound_from_elements_a->enable();
}

//HEA

void _layer_compound_from_elements_ui::disable()
{
  Qtw_layer_compound_from_elements_a->disable();
}

//HEA

void _layer_compound_from_elements_ui::parameter1_ui(float Value)
{
  Qtw_layer_compound_from_elements_a->parameter1(int(Value*255.0f));
}

//HEA

void _layer_compound_from_elements_ui::parameter2_ui(float Value)
{
  Qtw_layer_compound_from_elements_a->parameter2(int(Value*255.0f));
}

//HEA

void _layer_compound_from_elements_ui::parameter3_ui(float Value)
{
  Qtw_layer_compound_from_elements_a->parameter3(int(Value*255.0f));
}

//HEA

void _layer_compound_from_elements_ui::parameter4_ui(int Value)
{
  Qtw_layer_compound_from_elements_a->parameter4(Value);
}

//HEA

void _layer_compound_from_elements_ui::data_type_print(_palette_data_ns::_data_type_print Data_type_print1)
{
  Data_type_print=Data_type_print1;
  Qtw_layer_compound_from_elements_a->parameter4(int(Data_type_print1));
}

//HEA

_qtw_layer_compound_from_elements::_qtw_layer_compound_from_elements(_window_xmapslab *Window1, _layer_compound_from_elements_ui *Filter1, std::string Box_name)
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

//HEA

void _qtw_layer_compound_from_elements::parameter1(int Value)
{
  Slider_parameter1->blockSignals(true);
  Slider_parameter1->setValue(Value);
  Slider_parameter1->blockSignals(false);
}

//HEA

void _qtw_layer_compound_from_elements::parameter2(int Value)
{
  Slider_parameter2->blockSignals(true);
  Slider_parameter2->setValue(Value);
  Slider_parameter2->blockSignals(false);
}

//HEA

void _qtw_layer_compound_from_elements::parameter3(int Value)
{
  Slider_parameter3->blockSignals(true);
  Slider_parameter3->setValue(Value);
  Slider_parameter3->blockSignals(false);
}

//HEA

void _qtw_layer_compound_from_elements::parameter4(int Value)
{
  Combobox_parameter4->blockSignals(true);
  Combobox_parameter4->setCurrentIndex(Value);
  Combobox_parameter4->blockSignals(false);
}

//HEA

void _qtw_layer_compound_from_elements::parameter1_slot(int Value)
{
  Filter->parameter1(Value);
  Window->update_layer(Filter->name());
}

//HEA

void _qtw_layer_compound_from_elements::parameter2_slot(int Value)
{
  Filter->parameter2(Value);
  Window->update_layer(Filter->name());
}

//HEA

void _qtw_layer_compound_from_elements::parameter3_slot(int Value)
{
  Filter->parameter3(Value);
  Window->update_layer(Filter->name());
}

//HEA

void _qtw_layer_compound_from_elements::parameter4_slot(int Value)
{
  Filter->parameter2(Value);
  Window->update_color_bar_data_type_print(Value);
}
