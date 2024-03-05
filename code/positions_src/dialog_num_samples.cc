#include "dialog_num_samples.h"
#include "glwidget_positions.h"

_dialog_num_samples::_dialog_num_samples(int *Num_samples1, QString *Project_name1):Num_samples(Num_samples1),Project_name(Project_name1)
{

  // name
  QFrame *Frame_project_name=new QFrame;
  Frame_project_name->setFrameStyle(QFrame::Box | QFrame::Plain);

  QGridLayout *Grid_project_name=new QGridLayout;

  QLabel *Label_project_name=new QLabel("Project name:");

  Lineedit_project_name=new QLineEdit;

  Grid_project_name->addWidget(Label_project_name,0,0,Qt::AlignLeft);
  Grid_project_name->addWidget(Lineedit_project_name,0,1,Qt::AlignRight);

  Frame_project_name->setLayout(Grid_project_name);

  // Num samples
//  QGroupBox *Groupbox_num_samples=new QGroupBox;
//  Groupbox_num_samples->setTitle("Number of samples");

  QGridLayout *Grid_num_samples=new QGridLayout;

  QLabel *Label_num_samples1=new QLabel("Num of samples");

  Spinbox_num_samples=new QSpinBox;
  Spinbox_num_samples->setRange(1,500);

  Grid_num_samples->addWidget(Label_num_samples1,0,0,Qt::AlignLeft);
  Grid_num_samples->addWidget(Spinbox_num_samples,0,1,Qt::AlignRight);

//  Groupbox_num_samples->setLayout(Grid_num_samples);

  //
//  QHBoxLayout *Horizontal1=new QHBoxLayout;

//  Horizontal1->addWidget(Groupbox_num_samples);

  QFrame *Frame_num_samples=new QFrame;
  Frame_num_samples->setFrameStyle(QFrame::Box | QFrame::Plain);

//  Frame_num_samples->setLayout(Horizontal1);
  Frame_num_samples->setLayout(Grid_num_samples);

  // control buttons
  QPushButton *Button_ok = new QPushButton(tr("Ok"));
  QPushButton *Button_cancel = new QPushButton(tr("Cancel"));

  connect(Button_ok,SIGNAL(clicked(bool)),this,SLOT(accept_slot()));
  connect(Button_cancel,SIGNAL(clicked(bool)),this,SLOT(reject()));

  QWidget *Widget_b=new QWidget;
  QHBoxLayout *Horizontal_layout=new QHBoxLayout;

//  Horizontal_layout->addStretch();
  Horizontal_layout->addWidget(Button_ok);
  Horizontal_layout->addWidget(Button_cancel);

  Widget_b->setLayout(Horizontal_layout);

//  // main
  QVBoxLayout *Vertical_layout=new QVBoxLayout;

  Vertical_layout->addWidget(Frame_project_name);
  Vertical_layout->addWidget(Frame_num_samples);
  Vertical_layout->addWidget(Widget_b);

  setLayout(Vertical_layout);

  setWindowTitle("Number of samples");
}

/*************************************************************************/

void _dialog_num_samples::accept_slot()
{
  // check the results
  *Num_samples=Spinbox_num_samples->value();
  *Project_name=Lineedit_project_name->text();

  if (*Num_samples<1) *Num_samples=1;
  if (*Num_samples>500) *Num_samples=500;

  emit accept();
}
