/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef _W_OPTIONS_IMAGE_SECTION_H
#define _W_OPTIONS_IMAGE_SECTION_H

#include <QCheckBox>

#include <QDialog>
#include <iostream>

class _window_xmapslab;

/*************************************************************************/

class _w_options_image_section: public QDialog
{
Q_OBJECT

public:
  _w_options_image_section(_window_xmapslab *Window1, bool *Add_original_image1, bool *Add_colorbar1);

public slots:
  void accept_slot();

protected:
  // display
  QCheckBox *Checkbox_add_original_image=nullptr;
  QCheckBox *Checkbox_add_colorbar=nullptr;

  bool *Add_original_image=nullptr;
  bool *Add_colorbar=nullptr;

  _window_xmapslab *Window=nullptr;
};

#endif
