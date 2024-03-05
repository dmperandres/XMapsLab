#include <QApplication>
#include <QMainWindow>
#include <QSurfaceFormat>
#include <QWizardPage>
#include "window_tools.h"

//QWizardPage *createIntroPage_init()
//{
//  QWizardPage *page = new QWizardPage;

//  QFont Font=page->font();
//  Font.setPointSize(20);

//  page->setFont(Font);
//  page->setPixmap(QWizard::WatermarkPixmap, QPixmap(":/icons/logo_MapLab_Project.png","png"));

//  return page;
//}

/*************************************************************************/

int main( int argc, char ** argv )
{
  QApplication Application( argc, argv );

  QSurfaceFormat Format;
  Format.setDepthBufferSize(24);
  Format.setStencilBufferSize(8);
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

  _window_tools Window;
  Window.show();
//  Window.check_project();

  return Application.exec();
}
