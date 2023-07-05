/*************************************************************************
Copyright (c) 2022, 2023 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: XXX

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

#include "window.h"

/*************************************************************************/

QWizardPage *createIntroPage_init()
{
  QWizardPage *page = new QWizardPage;

  QFont Font=page->font();
  Font.setPointSize(20);

  page->setFont(Font);
  page->setPixmap(QWizard::WatermarkPixmap, QPixmap(":/common/icons/logo_xmapslab_xmapslab.png","png"));
  return page;
}

/*************************************************************************/

int main( int argc, char ** argv )
{
  QApplication Application( argc, argv );

  QSurfaceFormat Format;
  Format.setProfile(QSurfaceFormat::CoreProfile);
  Format.setAlphaBufferSize(8);
  Format.setDepthBufferSize(24);
  Format.setStencilBufferSize(8);
  Format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
  QSurfaceFormat::setDefaultFormat(Format);

  QFont Font("Microsoft Sans Serif");
  Font.setPointSize(_common_ns::UI_FONT_SIZE_DEFAULT);
  Application.setFont(Font);

  QWizard Wizard;
  Wizard.setButtonText(QWizard::FinishButton, "Continue");
  Wizard.setWizardStyle(QWizard::ClassicStyle);
  Wizard.setWindowFlags(Qt::WindowStaysOnTopHint);
  Wizard.setOptions(QWizard::NoCancelButton | QWizard::NoBackButtonOnLastPage);
  Wizard.addPage(createIntroPage_init());
  Wizard.setWindowTitle("XMapsLab");
  Wizard.exec();

  _window Window;
  Window.show();

  return Application.exec();
}

