 //LIC

#include "w_color_bar.h"
#include "window_xmapslab.h"

/*************************************************************************/

_w_color_bar::_w_color_bar(_window_xmapslab *Window1): Window(Window1)
{
  setMinimumSize(QSize(100,300));

  // margins
  setContentsMargins(0, 0, 0, 0);
  // borders
  setStyleSheet("border: none;");
  // Establece la bandera de ventana sin marco para eliminar los bordes del sistema operativo
  setWindowFlags(Qt::FramelessWindowHint);
  // padding
  setStyleSheet("QWidget { padding: 0px; }");

  // main layout
  Verticalbox_color_bar=new QVBoxLayout;
  Verticalbox_color_bar->setContentsMargins(0, 0, 0, 0);
  Verticalbox_color_bar->setSpacing(0);

  // label
  QFont Font;
  Label_name=new QLabel("");
  //  Label_name->setFrameStyle(QFrame::Panel | QFrame::Sunken);
  Label_name->setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
  Font = Label_name->font();
//  Font.setPointSize(24);
  Font.setBold(true);
  QFontMetrics Font_metrics(Font);

  Label_name->setMaximumHeight(Font_metrics.height()*1.2);
  Label_name->setFont(Font);
  Label_name->setAlignment(Qt::AlignCenter);
  Label_name->hide();

  // widget for layers
  Widget_color_bar_layers=new QWidget;
  // margins
  Widget_color_bar_layers->setContentsMargins(0, 0, 0, 0);
  // borders
  Widget_color_bar_layers->setStyleSheet("border: none;");
  // Establece la bandera de ventana sin marco para eliminar los bordes del sistema operativo
  Widget_color_bar_layers->setWindowFlags(Qt::FramelessWindowHint);
  // padding
  Widget_color_bar_layers->setStyleSheet("QWidget { padding: 0px; }");

  //
  Verticalbox_color_bar_layers=new QVBoxLayout;
  Verticalbox_color_bar_layers->setContentsMargins(0, 0, 0, 0);
  Verticalbox_color_bar_layers->setSpacing(0);

  Widget_color_bar_layers->setLayout(Verticalbox_color_bar_layers);

  Verticalbox_color_bar->addWidget(Label_name);
  Verticalbox_color_bar->addWidget(Widget_color_bar_layers);
  //  Verticalbox_color_bar->addWidget(Widget_color_bar_palettes);

  setLayout(Verticalbox_color_bar);

//  QFont Font=font();
//  QFontMetrics Font_metric(Font);
//  int Width_char=Font_metric.horizontalAdvance("0000000000")*Window->screen_height()/1080;

  // 10% of the size of the widow
  setMaximumWidth(Window->width()/10);
//  setMaximumWidth(Width_char);

  random_device Random_device;   // non-deterministic generator
  mt19937 Generator(Random_device());  // to seed mersenne twister.
  uniform_real_distribution<> Random(0,1);
//  Hue_offset=int(Random(Generator)*_palette_data_ns::INITIAL_HUE);

  Colors_mask.resize(256);
  for (unsigned int i=0;i<128;i++){
    Colors_mask[i]=QColor(255,255,255);
    Colors_mask[i+128]=QColor(0,0,0);
  }
}

/*************************************************************************/

_w_color_bar::~_w_color_bar()
{
#ifdef DEBUG_XML
  std::cout << "Terminando w_color_bar" << endl;
#endif
}

/*************************************************************************/

QSize _w_color_bar::sizeHint() const
{
  ensurePolished();
  return QSize(100,100);
}

/*************************************************************************/

QSize _w_color_bar::minimumSizeHint() const
{
    ensurePolished();
    return QSize(100,100);
}

/*************************************************************************/

int _w_color_bar::total_width(float Value, QFont Font)
{
    // compute the space of a '0'
    QFontMetrics Font_metric(Font);
    QRect Rect_char=Font_metric.boundingRect('0');
    int Font_pixels_width=Rect_char.width();
    int Font_pixels_height=Rect_char.height();

    // compute the parameters
    // border
    int Border_space_width=int(roundf(float(Font_pixels_width)*_color_bar_abstract_ns::BORDER_SPACE_FACTOR));
    if (Border_space_width<1) Border_space_width=1;

    int Border_space_height=int(roundf(float(Font_pixels_height)*_color_bar_abstract_ns::BORDER_SPACE_FACTOR));
    if (Border_space_height<1) Border_space_height=1;

    // white space
    int White_space_width=int(roundf(float(Font_pixels_width)*_color_bar_abstract_ns::WHITE_SPACE_FACTOR));
    if (White_space_width<1) White_space_width=1;

    // color box. It must be odd
    int Color_box_width=int(roundf(float(Font_pixels_width)*_color_bar_abstract_ns::COLOR_BOX_FACTOR));
    if (Color_box_width<_color_bar_abstract_ns::COLOR_BOX_MIN) Color_box_width=_color_bar_abstract_ns::COLOR_BOX_MIN;
    if (Color_box_width%2!=0) Color_box_width++;

    // text
    // conform the measure string suing the 0 (it is the wider number symbol)
    int Log10=int(log10f(Value));
    if (Log10<0) Log10=1;
    else Log10=Log10+2;

    int Num_decimals=_common_ns::NUM_MAX_DECIMALS-Log10;
    if (Num_decimals<0) Num_decimals=0;

//    QString Text = QString(Character).repeated(Repetitions);
    QString Text=QString::number(Value, 'f',Num_decimals);
    int Text_width=Font_metric.horizontalAdvance(Text);

    return (2*(Border_space_width+White_space_width+Color_box_width)+Color_box_width+Text_width);
}

/*************************************************************************/

void _w_color_bar::adjust_width(float Value)
{
  // width= Border+Color_box+space+bar+space+text+border
    int Total_width=total_width(Value,QApplication::font());

  setMinimumWidth(Total_width);
  setMaximumWidth(Total_width);
}

/*************************************************************************/
// This is call when the data is loaded
void _w_color_bar::initialize()
{
  create_palettes();
}

/*************************************************************************/

void _w_color_bar::create_palettes()
{

  int Pos=0;
  for (unsigned int i=0;i<Window->Vec_palette_data.size();i++){
    if (Window->Vec_palette_data[i].type()==_palette_data_ns::_palette_type::PALETTE_TYPE_DISCRETE){
      Palettes.push_back(new _color_bar_sections(Window->Vec_palette_data[i].color_type(),Window->Vec_palette_data[i].num_stops(),Window->Vec_palette_data[i].vec_values(),Window->Vec_palette_data[i].vec_colors(),Window->color_for_zero_value(),Window));
    }
    else{
      Palettes.push_back(new _color_bar_interpolation(Window->Vec_palette_data[i].color_type(),Window->Vec_palette_data[i].num_stops(),Window->Vec_palette_data[i].vec_values(),Window->Vec_palette_data[i].vec_colors(),Window));
    }
    Palettes[Pos++]->show_data(false);
  }
}

/*************************************************************************/

void _w_color_bar::update_color_bar(_w_tab_xmapslab_ns::_tabs Selected_tab)
{
  switch(Selected_tab){
    case _w_tab_xmapslab_ns::_tabs::LAYERS_TAB:
      {
        if (Window->loaded_image()==true){
          // layers
//          Widget_color_bar_palettes->hide();

          for (unsigned int i=0;i<Window->Vec_order_of_layers_by_name.size();i++){
            Window->Map_name_to_layer[Window->Vec_order_of_layers_by_name[i]].Color_bar->hide();
          }

          for (unsigned int i=0;i<Palettes.size();i++){
            Palettes[i]->hide();
          }

          Window->Map_name_to_layer[Window->Vec_order_of_layers_by_name[Window->selected_layer()]].Color_bar->show();

          // adjust the font size depending on the lenght of the name
          QString Text=QString::fromStdString(Window->Map_name_to_layer[Window->Vec_order_of_layers_by_name[Window->selected_layer()]].Color_bar_name);

          QFont Font(QApplication::font());
          int Font_size=Font.pointSize();

          // set a font at double size
          Font.setPointSize(Font_size*2);
          Font.setBold(true);
          QFontMetrics Font_metric(Font);
          QRect Rect_char=Font_metric.boundingRect('M');
          int Font_pixels_height=Rect_char.height();
          Label_name->setFont(Font);
          // set the height of the label
          Label_name->setMinimumHeight(Font_pixels_height*2);
          Label_name->setMaximumHeight(Font_pixels_height*2);

          // check the font size that allows to show the text
          int Text_width;
          Font_size=2*Font_size+1;
          do{
            Font_size--;
            QFont Font2(QApplication::font());
            Font2.setPointSize(Font_size);
            QFontMetrics Font_metric2(Font2);
            Text_width=Font_metric2.horizontalAdvance(Text);
          } while (Font_size>10 && Text_width>(Label_name->width()-2));

          // remove text if it is bigger than the space
          QFont Font2(QApplication::font());
          Font2.setPointSize(Font_size);
          Font2.setBold(true);
          Label_name->setFont(Font2);

          QFontMetrics Font_metric1(Font2);
          int Width = Label_name->width() - 2;
          QString Clipped_text = Font_metric1.elidedText(Text, Qt::ElideMiddle, Width);
          Label_name->setText(Clipped_text);

          Label_name->show();

          Widget_color_bar_layers->show();
        }
      }
    break;
  case _w_tab_xmapslab_ns::_tabs::TAB_PALETTES:
//    {
//      // palettes
//      Widget_color_bar_layers->hide();

//      for (unsigned int i=0;i<Window->Vec_order_of_layers_by_name.size();i++){
//        Window->Map_name_to_layer[Window->Vec_order_of_layers_by_name[i]].Color_bar->hide();
//      }

//      for (unsigned int i=0;i<Palettes.size();i++){
//        Palettes[i]->hide();
//      }

//      Palettes[Window->selected_palette()]->show();

//      Label_name->hide();

//      Widget_color_bar_palettes->show();
//    }
    break;
  case _w_tab_xmapslab_ns::_tabs::POSITIONS_TAB:
  case _w_tab_xmapslab_ns::_tabs::COMPOUNDS_XRD_TAB:
  case _w_tab_xmapslab_ns::_tabs::COMPOUNDS_FROM_XRF_TAB:
  case _w_tab_xmapslab_ns::_tabs::ELEMENTS_TAB:
      // palettes
      Widget_color_bar_layers->hide();

      for (unsigned int i=0;i<Window->Vec_order_of_layers_by_name.size();i++){
        Window->Map_name_to_layer[Window->Vec_order_of_layers_by_name[i]].Color_bar->hide();
      }

      for (unsigned int i=0;i<Palettes.size();i++){
        Palettes[i]->hide();
      }

      Label_name->hide();
    break;
  default:break;
  }

  update();
}

/*************************************************************************/
// add a new widget in the list. Only one is visible
// Name is the name for the label of the color bar

void _w_color_bar::add_palette_layer(std::string Name)
{
  Verticalbox_color_bar_layers->addWidget(Window->Map_name_to_layer[Name].Color_bar);

  // do the connection for doing the changes on it
  connect(Window->Map_name_to_layer[Name].Color_bar,SIGNAL(colorChanged(std::vector<float>&, std::vector<QColor>&, int)),this,SLOT(color_bar_changed_slot(std::vector<float>&, std::vector<QColor>&, int)));
}

/*************************************************************************/
// Each layer with a map creates a color bar

_color_bar_abstract *_w_color_bar::create_color_bar(_palette_data_ns::_palette_data Palette1, _common_ns::_xray_data_type Data_type1, std::string Name_element1, float Max_value, std::vector<QColor> &Colors, _palette_data_ns::_data_type_print Data_type_print1, _color_map_ns::_color_for_zero_value Color_for_zero_value1)
{
  _color_bar_abstract *Color_bar;

  // it is necessary to compute the new colors depending on the element
  if (Palette1.type() ==_palette_data_ns::_palette_type::PALETTE_TYPE_DISCRETE){    
    _color_bar_sections *Color_bar_sections=new _color_bar_sections(Palette1.color_type(),Palette1.num_stops(),Palette1.vec_values(),Colors,Color_for_zero_value1,Window);

    Color_bar=Color_bar_sections;
  }
  else{

    _color_bar_interpolation *Color_bar_interpolation=new _color_bar_interpolation(Palette1.color_type(),Palette1.num_stops(),Palette1.vec_values(),Colors,Window);
    Color_bar=Color_bar_interpolation;
  }

  Color_bar->changeable(true);
  Color_bar->set_data_values(0,Max_value);
  Color_bar->data_type_print(Data_type_print1);
  Color_bar->show_data(true);

  return(Color_bar);
}

/*************************************************************************/

void _w_color_bar::add_palette(_color_bar_abstract *Palette_aux)
{

  Palettes.push_back(Palette_aux);

  Palettes[Palettes.size()-1]->show_data(false);

//  Verticalbox_color_bar_palettes->addWidget(Palettes[Palettes.size()-1]);
  Palettes[Palettes.size()-1]->hide();
}

/*************************************************************************/

void _w_color_bar::remove_color_bar(std::string Name)
{
  Verticalbox_color_bar_layers->removeWidget(Window->Map_name_to_layer[Name].Color_bar);
  Window->Map_name_to_layer[Name].Color_bar->setParent(0);
  Window->Map_name_to_layer[Name].Color_bar->deleteLater();
}

/*************************************************************************/

void _w_color_bar::color_bar_changed_slot(std::vector<float> &Vec_values1, std::vector<QColor> &Vec_colors1, int Type)
{
//  cout << "change color" << endl;

  std::string Name=Window->Vec_order_of_layers_by_name[Window->selected_layer()];

  switch (Window->Map_name_to_layer[Name].Layer->layer_type()){
  case _layer_xmapslab_ns::_layer_type::LAYER_TYPE_MAP_DISTANCE:
    dynamic_pointer_cast<_layer_map_distance_ui>(Window->Map_name_to_layer[Name].Layer)->set_colormap(Vec_values1,Vec_colors1, _palette_data_ns::_palette_type(Type));
    break;
  case _layer_xmapslab_ns::_layer_type::LAYER_TYPE_MAP_TRIANGULATION:
    dynamic_pointer_cast<_layer_map_triangulation_ui>(Window->Map_name_to_layer[Name].Layer)->set_colormap(Vec_values1,Vec_colors1, _palette_data_ns::_palette_type(Type));
    break;
#ifdef COMPOUNDS_FROM_ELEMENTS_ACTIVE
  case _layer_xmapslab_ns::_layer_type::LAYER_TYPE_COMPOUND_COMBINATION:
    dynamic_pointer_cast<_layer_compound_from_elements_ui>(Window->Map_name_to_layer[Name].Layer)->set_colormap(Vec_values1,Vec_colors1, _palette_data_ns::_palette_type(Type));
    break;
#endif
  case _layer_xmapslab_ns::_layer_type::LAYER_TYPE_MAP_RBF_INTERPOLATION:
    dynamic_pointer_cast<_layer_map_rbf_interpolation_ui>(Window->Map_name_to_layer[Name].Layer)->set_colormap(Vec_values1,Vec_colors1, _palette_data_ns::_palette_type(Type));
    break;
  case _layer_xmapslab_ns::_layer_type::LAYER_TYPE_MAP_LAB:
    std::dynamic_pointer_cast<_layer_map_lab_ui>(Window->Map_name_to_layer[Name].Layer)->set_colormap(Vec_values1,Vec_colors1, _palette_data_ns::_palette_type(Type));
    break;
  default:break;
  }

  Window->Map_name_to_layer[Name].Layer->update();

  Window->GL_widget->update_texture(Name);

  Window->GL_widget->update();

  if (Window->state()==_window_xmapslab_ns::_state::STATE_STATISTICS){
#ifdef STATISTIC_GRAPHS_ACTIVE
    Window->update_chart(Window->Statistics_x,Window->Statistics_y);
#endif
  }
}

/*************************************************************************/

void _w_color_bar::compute_regular_values_noise(int Num_values,vector<float> &Vec_values,float Noise)
{
  float t;

  Vec_values.resize(Num_values);
  Vec_values[0]=0;

  for (int i=0;i<Num_values-1;i++) {
    t=float(i)/float(Num_values-2);
    Vec_values[i+1]=(1.0-Noise)*t+Noise;
  }
}

