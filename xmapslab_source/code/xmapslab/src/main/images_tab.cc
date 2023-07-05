/*************************************************************************
Copyright (c) 2022, 2023 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: XXX

*************************************************************************/

#include "images_tab.h"

#include "window.h"

/*************************************************************************/

_images_tab::_images_tab(_window *Window1, QWidget *Parent)
: QWidget(Parent)
{
//  QString Str;

  Window=Window1;

  // images
  QGroupBox *Group_box_images=new QGroupBox(tr("Images"));
  Group_box_images->setAlignment(Qt::AlignCenter);

  Images_list = new QListWidget;
  Images_list->setToolTip(tr("Selects which images is shown or saved"));

  // for adjusting the size of the widget depending on the height of the font
  QFontMetrics Font_metrics(Images_list->fontMetrics());
  Images_list->setMaximumHeight(Font_metrics.height()*25);

  QVBoxLayout *Vertical_images = new QVBoxLayout(this);

  Vertical_images->addWidget(Images_list,0,Qt::AlignTop);
  Group_box_images->setLayout(Vertical_images);

  connect(Images_list,SIGNAL(itemClicked(QListWidgetItem *)), this,SLOT(item_clicked(QListWidgetItem *)));

  // Palette
//  QFrame *Frame_element_palette=new QFrame;
//  Frame_element_palette->setFrameStyle(QFrame::Panel);

//  QGridLayout *Grid_element_palette=new QGridLayout;

//  QLabel *Label_element_palette1=new QLabel("Palette");

//  Combobox_palette = new QComboBox;
//  for (unsigned int i=0;i<Window->Vec_palette_data.size();i++){
//    Combobox_palette->addItem(Window->Vec_palette_data[i].name());
//  }

//  Grid_element_palette->addWidget(Label_element_palette1,0,0,Qt::AlignRight);
//  Grid_element_palette->addWidget(Combobox_palette,0,1,Qt::AlignLeft);

//  Frame_element_palette->setLayout(Grid_element_palette);

  // button
//  Button_create_element= new QPushButton("Create a single element", this);
//  Button_create_element->setEnabled(false);
//  connect(Button_create_element, SIGNAL(clicked()),this,SLOT(create_single_element_slot()));

  // general
  QVBoxLayout *Vertical_parameters=new QVBoxLayout;

  Vertical_parameters->addWidget(Group_box_images);
  Vertical_parameters->addStretch();
//  Vertical_parameters->addWidget(Frame_element_palette);
//  Vertical_parameters->addWidget(Button_create_element);

  setLayout(Vertical_parameters);
}

/*************************************************************************/

void _images_tab::set_item(std::string Name)
{
  QListWidgetItem *Item=new QListWidgetItem;
  Item->setText(tr(Name.c_str()));
  Images_list->insertItem(Images_list->count(),Item);
  Images_list->updateGeometry();
}

/*************************************************************************/

QString _images_tab::selected_item()
{
  QListWidgetItem *Item=Images_list->currentItem();
  return Item->text();
}

/*************************************************************************/

void _images_tab::set_selected_item(int Pos)
{
  Images_list->setCurrentRow(Pos);
}

/*************************************************************************/

void _images_tab::item_clicked(QListWidgetItem *Item)
{
  Q_UNUSED(Item)
  Window->selected_image((Item->text()).toStdString());
}

/*************************************************************************/

void _images_tab::insert_images()
{
  std::string Name;
  QListWidgetItem *Item;

  remove_images();

  // add the names
  for (unsigned int i=0;i<Window->Vec_order_mapping->size();i++){
    Name=(*Window->Vec_order_mapping)[i];
    Item=new QListWidgetItem;
    Item->setText(tr(Name.c_str()));
    Images_list->insertItem(Images_list->count(),Item);
  }
  Images_list->setCurrentRow(Window->mapping_selected_image_index());

  update();
}

void _images_tab::remove_images()
{
  std::string Name;
  QListWidgetItem *Item;
  int Num_intems=Images_list->count();

  for (int i=0;i<Num_intems;i++){
    Item=Images_list->takeItem(0);
    delete Item;
  }
}

/*************************************************************************/

void _images_tab::create_single_element_slot()
{
}
