//LIC

#ifndef _W_IMAGE_SECTION_H
#define _W_IMAGE_SECTION_H

#include <QDialog>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QPixmap>
#include <QDialogButtonBox>
#include <iostream>

class _window_xmapslab;

//HEA

class _w_image_section: public QDialog
{
Q_OBJECT

public:
  _w_image_section(_window_xmapslab *Window1);

//public slots:
//  void accept_slot();
//  void cancel_slot();

protected:
  _window_xmapslab *Window=nullptr;
};

#endif
