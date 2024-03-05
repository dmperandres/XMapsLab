/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#include <QApplication>
#include <QMainWindow>
#include <QSurfaceFormat>
#include <QDateTime>
#include <QDate>
//#include <QDesktopWidget>
#include <QStyle>
#include <QTimer>

#include <algorithm>

#include <random>

#include "window_xmapslab.h"

/*************************************************************************/

QWizardPage *createIntroPage_init()
{
  QWizardPage *page = new QWizardPage;

  QFont Font=page->font();
  Font.setPointSize(20);

  page->setFont(Font);
  page->setPixmap(QWizard::WatermarkPixmap, QPixmap(":/common/icons/logo_MapLab_Mapping.png","png"));
  return page;
}

/*************************************************************************/

int main( int argc, char ** argv )
{
  QApplication Application( argc, argv );

#ifdef CONTROL_TIME
  random_device Random_device;   // non-deterministic generator
  mt19937 Generator(Random_device());  // to seed mersenne twister.
  uniform_int_distribution<> Random(0,10);
  QDateTime Current_date_time=QDateTime::currentDateTime();
//  QDateTime End_date_time(QDate(2022,10,30));
  QDateTime End_date_time(QDate(2023,6,30).startOfDay());

  if (Current_date_time>End_date_time){
    if (Random(Generator)<5) exit(-1);
  }
#endif

  #ifdef REDIRECT
  #ifdef LINUX
    std::ofstream Output_stream("log.txt",std::ofstream::out);
  #else
    std::ofstream Output_stream("C:/log.txt",std::ofstream::out);
  #endif

  cout.rdbuf(Output_stream.rdbuf());
  #endif

  #ifdef DEBUG_PROGRAM
  cout << "Debugging" << endl;
  cout << "Current dir " << QDir::currentPath().toStdString() << endl;
  #endif

  QSurfaceFormat Format;
  Format.setProfile(QSurfaceFormat::CoreProfile);
  Format.setAlphaBufferSize(8);
  Format.setDepthBufferSize(24);
  Format.setStencilBufferSize(8);
  Format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
  QSurfaceFormat::setDefaultFormat(Format);

#ifdef LINUX
  QFont Font("Arial");
#else
  QFont Font("Microsoft Sans Serif");
#endif
  Font.setPointSize(_common_ns::UI_FONT_SIZE_DEFAULT);
  Application.setFont(Font);

//  Window.setWindowState(Qt::WindowMaximized);

//  QWizard Wizard;
////  _wizard Wizard(&Application);
//  Wizard.setButtonText(QWizard::FinishButton, "Continue");
//  Wizard.setWizardStyle(QWizard::ClassicStyle);
//  Wizard.setWindowFlags(Qt::WindowStaysOnTopHint);
//  Wizard.setOptions(QWizard::NoCancelButton | QWizard::NoBackButtonOnLastPage);
//  Wizard.addPage(createIntroPage_init());
//  //Wizard.setWindowTitle("License");

//  // for centering the window of the wizard
////  QRect screenGeometry = Window.geometry();
////  int x = (screenGeometry.width()-Wizard.width()-300) / 2;
////  int y = (screenGeometry.height()-Wizard.height()) / 2;
////  Wizard.move(screenGeometry.x()+x,screenGeometry.y()+y);
//  Wizard.exec();

  _window_xmapslab Window;
   Window.show();
//   Window.check_project();

  return Application.exec();
}

