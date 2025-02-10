//LIC

#ifndef DIALOG_PURE_COLOR_H
#define DIALOG_PURE_COLOR_H

#include <QDialog>
#include <QGroupBox>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QIntValidator>
#include <iostream>

#include "pure_color_bar.h"

//HEAD
// This class is for a dialog that changes the color by using a pure color bar or the normal widget

class _gl_widget;

class _dialog_pure_color: public QDialog
{
Q_OBJECT

public:
  _dialog_pure_color(QWidget *Parent,QColor *Color1,bool Solid_black1=true);

protected:
  _pure_color_bar *Pure_color_bar=nullptr;
  QColor *Color=nullptr;

  _gl_widget *Vec_gl_widget=nullptr;
};
#endif
