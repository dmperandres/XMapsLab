#include <QApplication>
#include <QMainWindow>
#include <QSurfaceFormat>
#include <QWizardPage>
#include "window.h"

QWizardPage *createIntroPage_init()
{
  QWizardPage *page = new QWizardPage;

  QFont Font=page->font();
  Font.setPointSize(20);

  page->setFont(Font);
  page->setPixmap(QWizard::WatermarkPixmap, QPixmap(":/common/icons/logo_xmapslab_tools.png","png"));

  return page;
}

/*************************************************************************/

int main( int argc, char ** argv )
{
  QApplication Application( argc, argv );

  QSurfaceFormat Format;
  Format.setDepthBufferSize(24);
  Format.setStencilBufferSize(8);
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
  Wizard.setWindowTitle("Tools");
  Wizard.exec();

  _window Window;
  Window.show();

  return Application.exec();
}
