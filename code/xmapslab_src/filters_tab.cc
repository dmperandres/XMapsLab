/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#include "filters_tab.h"
#include "glwidget_xmapslab_ge.h"
#include "window_xmapslab.h"

/*************************************************************************/

_filters_tab::_filters_tab(_window_xmapslab *Window1, QWidget *Parent)
: QWidget(Parent)
{
  QString Str;

  Window=Window1;

  // images
  Group_box_filters=new QGroupBox(tr("Filters"));
  Group_box_filters->setAlignment(Qt::AlignCenter);

  Filters_list = new QListWidget;
  Filters_list->setToolTip(tr("Selects which filter is shown or saved"));

  // for adjusting the size of the widget depending on the height of the font
  QFontMetrics Font_metrics(Filters_list->fontMetrics());
  Filters_list->setMaximumHeight(Font_metrics.height()*10);

  QVBoxLayout *Vertical_filters = new QVBoxLayout;

  Vertical_filters->addWidget(Filters_list,0,Qt::AlignTop);
  Group_box_filters->setLayout(Vertical_filters);

  connect(Filters_list,SIGNAL(itemClicked(QListWidgetItem *)), this,SLOT(item_clicked(QListWidgetItem *)));

  // general
  Vertical_parameters=new QVBoxLayout(this);

  Vertical_parameters->addWidget(Group_box_filters);

//  for(int i=0;i<Filters.size();i++){
//    Vertical_parameters->addWidget((QGroupBox *)(Vec_gl_widget_ge->Filters.get_data(i)->get_link()),0,Qt::AlignTop); !!!
//  }

  setLayout(Vertical_parameters);
}

/*************************************************************************/

void _filters_tab::set_item(string Name)
{
  QListWidgetItem *Item=new QListWidgetItem;
  Item->setText(tr(Name.c_str()));
  Filters_list->insertItem(Filters_list->count(),Item);
  Filters_list->updateGeometry();
}

/*************************************************************************/

//void _filters_tab::insert_widgets()
//{
//  for (unsigned int i=0;i<Window->Map_filters.size();i++){
//    //Vertical_parameters->insertWidget(-1,(QGroupBox *)Vec_gl_widget_ge->Filters.get_data(i)->get_link()); !!!
//  }

//  Vertical_parameters->addStretch(-1);
//}

#ifdef NODE_EDITOR_ACTIVE
void _filters_tab::insert_filters()
{
  std::string Name;
  QListWidgetItem *Item;

  remove_filters();

  // add the names
  for (unsigned int i=0;i<Window->Vec_order_mapping->size();i++){
    Name=(*Window->Vec_order_mapping)[i];
    Item=new QListWidgetItem;
    Item->setText(tr(Name.c_str()));
    Filters_list->insertItem(Filters_list->count(),Item);
  }
  Filters_list->setCurrentRow(Window->mapping_selected_filter_index());

  // add the groupbox for the parameter of each filter
  QGroupBox *Groupbox_aux;
  for (unsigned int i=0;i<Window->Vec_order_mapping->size();i++){
    Name=(*Window->Vec_order_mapping)[i];
    Groupbox_aux=static_cast<QGroupBox *>(Window->Map_filters[Name]->get_link());
    if (Groupbox_aux!=nullptr){
      Vertical_parameters->insertWidget(-1,Groupbox_aux);
      Window->Map_filters[Name]->hide();
    }
  }
  Vertical_parameters->addStretch(-1);

  // show the selected item
  Name=(*Window->Vec_order_mapping)[Window->mapping_selected_filter_index()];
  Window->Map_filters[Name]->show();

  update();
}

void _filters_tab::remove_filters()
{
  std::string Name;
  // remove the names
  QListWidgetItem *Item;
  int Num_intems=Filters_list->count();

  for (int i=0;i<Num_intems;i++){
    Item=Filters_list->takeItem(0);
    delete Item;
  }

  QLayoutItem *Child;
  QWidget *Widget;
  while ((Child = Vertical_parameters->takeAt(1)) != 0){
    Widget=Child->widget();
    if (Widget!=nullptr){
      Child->widget()->setParent(0);
      Child->widget()->deleteLater();
    }
  }
}

/*************************************************************************/

void _filters_tab::remove_widgets()
{
  QLayoutItem *Child;
  while ((Child = Vertical_parameters->takeAt(0)) != 0) {
    //cout << "Borrando " << Vertical_parameters->count() << endl;
    delete Child->widget();
    delete Child;
  }

  Group_box_filters=new QGroupBox(tr("Filters"));
  Group_box_filters->setAlignment(Qt::AlignCenter);

  Filters_list = new QListWidget;
  Filters_list->setToolTip(tr("Selects which filter is shown or saved"));

  // for adjusting the size of the widget depending on the height of the font
  QFontMetrics Font_metrics(Filters_list->fontMetrics());
  Filters_list->setMaximumHeight(Font_metrics.height()*10);

  QVBoxLayout *Vertical_filters = new QVBoxLayout;
  Vertical_filters->addWidget(Filters_list,0,Qt::AlignTop);
  Group_box_filters->setLayout(Vertical_filters);

  Vertical_parameters->addWidget(Group_box_filters);

  connect(Filters_list,SIGNAL(itemClicked(QListWidgetItem *)), this,SLOT(item_clicked(QListWidgetItem *)));
}

/*************************************************************************/

void _filters_tab::set_selected_item(int Pos)
{
  Filters_list->setCurrentRow(Pos);
}

/*************************************************************************/

void _filters_tab::item_clicked(QListWidgetItem *Item)
{  
  Q_UNUSED(Item)
  Window->selected_filter((Item->text()).toStdString());
}
#endif
