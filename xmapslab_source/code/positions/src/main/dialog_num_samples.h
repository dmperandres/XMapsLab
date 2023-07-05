#ifndef DIALOG_NUM_SAMPLES
#define DIALOG_NUM_SAMPLES

#include <QDialog>
#include <QGroupBox>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QIntValidator>
#include <QLineEdit>
#include <iostream>

class _w_tab;

class _dialog_num_samples: public QDialog
{
Q_OBJECT

public:
  _dialog_num_samples(int *Num_samples1,QString *Project_name1);

public slots:
  void accept_slot();

protected:
  QSpinBox *Spinbox_num_samples=nullptr;
  QLineEdit *Lineedit_project_name=nullptr;

  int *Num_samples=nullptr;
  QString *Project_name=nullptr;

//  QLineEdit *Lineedit_palette_name1;

//  QGroupBox *Groupbox_num_samples;
//  QGroupBox *Groupbox_type_value;

//  QLineEdit *Lineedit_interpolation1;
//  QLineEdit *Lineedit_interpolation2;
//  QLineEdit *Lineedit_palette_name1;
//  QLineEdit *Lineedit_void_value;

//  std::vector<QRadioButton *> Vec_radiobuttons;

//  _w_tab *W_tab=nullptr;
//  _palette_data *Palette_data=nullptr;
};
#endif
