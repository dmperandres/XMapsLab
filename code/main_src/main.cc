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
#include <QWizard>

#include <iostream>
#include <fstream>

#include "window_main.h"

/*************************************************************************/

//QWizardPage *createIntroPage_init()
//{
//  QWizardPage *page = new QWizardPage;

//  QFont Font=page->font();
//  Font.setPointSize(20);

//  page->setFont(Font);
//  page->setPixmap(QWizard::WatermarkPixmap, QPixmap(":/common/icons/logo_MapLab_Mapping.png","png"));
//  return page;
//}

/*************************************************************************/

int main( int argc, char ** argv )
{
  //
  QDate Limit_date(2024, 6, 30);
  QDate Current_date = QDate::currentDate();
  QApplication Application( argc, argv );

#ifdef DEBUG_XML
  std::ofstream archivo("salida.txt");
  // Verifica si el archivo se abrió correctamente
  if (!archivo.is_open()) {
      std::cerr << "Error al abrir el archivo." << std::endl;
      return 1;
  }

  // Redirige la salida estándar a 'archivo'
  std::streambuf *respaldo = std::cout.rdbuf();  // Guarda el flujo de salida actual
  std::cout.rdbuf(archivo.rdbuf());  // Redirige la salida estándar al archivo

  // Ahora todo lo que se imprima en std::cout se escribirá en "salida.txt"
  std::cout << "Este texto se escribirá en el archivo." << std::endl;
#endif

  if (Current_date < Limit_date){
#ifdef DEBUG_XML
    std::cout << "Comienza el formato" << std::endl;
#endif

    QSurfaceFormat Format;
    Format.setProfile(QSurfaceFormat::CoreProfile);
    Format.setAlphaBufferSize(8);
    Format.setDepthBufferSize(24);
    Format.setStencilBufferSize(8);
    Format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
    QSurfaceFormat::setDefaultFormat(Format);

#ifdef DEBUG_XML
    std::cout << "Termina el formato" << std::endl;
#endif

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

    _window_main Window;
    Window.show();  

    Application.exec();

#ifdef DEBUG_XML
    // Restaura el flujo de salida original
    std::cout.rdbuf(respaldo);

    // Cierra el archivo
    archivo.close();
#endif

    return 0;
  }
  else{
    QMessageBox messageBox;
    messageBox.setIcon(QMessageBox::Information);
    messageBox.setWindowTitle("Critical");
    messageBox.setText("The program is too old<br>Please, download a new version");
    messageBox.setStandardButtons(QMessageBox::Ok);
    messageBox.exec();

    return Application.exec();
  }
}

