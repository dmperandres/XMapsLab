//LIC

#include "w_directory.h"
//#include "window_xmapslab.h"

_w_directory::_w_directory(QWidget *Window1, QString Title1, QString Path1, QString *Directory1, _mode Mode1, QStringList Filters1):
  QDialog((QWidget*)Window1),Window(Window1),Directory(Directory1)
{
  setMinimumWidth(500);

  QDir Dir(Path1);
  Home=Path1;
  Path=Dir.absolutePath();
  Mode=Mode1;
  Filters=Filters1;

  // up button
  // control buttons

  QPushButton *Button_home = new QPushButton;
  Button_home->setIcon(QIcon(":/common/icons/go-home.svg"));
  Button_home->setToolTip("Go to home directory");
  connect(Button_home,SIGNAL(clicked(bool)),this,SLOT(home_slot()));

  QPushButton *Button_up = new QPushButton;
  Button_up->setIcon(QIcon(":/common/icons/go-up.svg"));
  Button_up->setToolTip("Go to upper directory");
  connect(Button_up,SIGNAL(clicked(bool)),this,SLOT(up_slot()));

  QWidget *Widget_up=new QWidget;
  QHBoxLayout *Horizontal_layout_up=new QHBoxLayout;
  Horizontal_layout_up->setContentsMargins(0,0,0,0);

  Horizontal_layout_up->addStretch();
  Horizontal_layout_up->addWidget(Button_home);
  Horizontal_layout_up->addWidget(Button_up);

  Widget_up->setLayout(Horizontal_layout_up);

  //
  QWidget *Widget_list=new QWidget;
  QVBoxLayout *Vertical_layout_list=new QVBoxLayout;
  Vertical_layout_list->setContentsMargins(0,0,0,0);

  List_folders = new QListWidget(this);
   connect(List_folders,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(item_clicked_slot(QListWidgetItem*)));
  connect(List_folders,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(item_double_clicked_slot(QListWidgetItem*)));

  update_list();

  Vertical_layout_list->addWidget(List_folders);

  Widget_list->setLayout(Vertical_layout_list);


  // control buttons
  QPushButton *Button_select = new QPushButton(tr("Select"));
  connect(Button_select,SIGNAL(clicked(bool)),this,SLOT(select_slot()));

  QPushButton *Button_cancel = new QPushButton(tr("Cancel"));
  connect(Button_cancel,SIGNAL(clicked(bool)),this,SLOT(cancel_slot()));

  QWidget *Widget_control=new QWidget;
  QHBoxLayout *Horizontal_layout_control=new QHBoxLayout;
  Horizontal_layout_control->setContentsMargins(0,0,0,0);

  Horizontal_layout_control->addStretch();
  Horizontal_layout_control->addWidget(Button_select);
  Horizontal_layout_control->addWidget(Button_cancel);

  Widget_control->setLayout(Horizontal_layout_control);


  // main
  QVBoxLayout *Vertical_layout=new QVBoxLayout;
//  Vertical_layout->setContentsMargins(0,0,0,0);

  Vertical_layout->addWidget(Widget_up);
  Vertical_layout->addWidget(Widget_list);
  Vertical_layout->addWidget(Widget_control);

  setLayout(Vertical_layout);

  setWindowTitle(Title1);

  setMinimumWidth(500);
}

//HEA
// fill the list

bool compare_strings_ignore_case(const QString& str1, const QString& str2) {
  return str1.toLower() < str2.toLower();
}

void _w_directory::update_list()
{
  QDir Dir(Path);
  QStringList List_directories=Dir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot);

  int Pos;
  QString Name;
  QString Dir1;
  QListWidgetItem *Item;

  while(List_folders->count()>0){
    delete List_folders->takeItem(0);
  }

  for (int i=0;i<List_directories.size();i++){
    Dir1=List_directories[i];
    Pos=Dir1.lastIndexOf('/');
    Name=Dir1.right(Dir1.size()-Pos-1);
    Item = new QListWidgetItem;
    Item->setText(Name);
    Item->setIcon(QIcon(":/common/icons/folder.svg"));
    List_folders->insertItem(i, Item);
  }

  // now the files
  List_directories=Dir.entryList(Filters,QDir::Files,QDir::Name);

  std::sort(List_directories.begin(), List_directories.end(), compare_strings_ignore_case);

  int Num_items=List_folders->count();
  for (int i=0;i<List_directories.size();i++){
    Dir1=List_directories[i];
    Pos=Dir1.lastIndexOf('/');
    Name=Dir1.right(Dir1.size()-Pos-1);
    Item = new QListWidgetItem;
    if (Mode==MODE_DIR) Item->setFlags(Qt::NoItemFlags);
    Item->setText(Name);
    Item->setIcon(QIcon(":/common/icons/file.svg"));
    List_folders->insertItem(i+Num_items, Item);
  }
}



//HEA

void _w_directory::home_slot()
{
  *Directory="";
  Path=Home;
  update_list();
}

//HEA

void _w_directory::up_slot()
{
//  int Pos;
//  Pos=Path.lastIndexOf('/');
//  Path=Path.left(Pos);
  QDir Dir(Path);
  Dir.cdUp();
  Path=Dir.absolutePath();
  *Directory="";
  update_list();
}


//HEA

void _w_directory::select_slot()
{
  if  (*Directory!=""){
    *Directory=Path+'/'+(*Directory);
    QFileInfo Check_file(*Directory);
    if (Mode==MODE_FILE){
      if (Check_file.isDir()){
        QMessageBox::information(this,"Information","Please select a <b>file</b> or click on 'Cancel' button");
      }
      else accept();
    }
    else{ // Dir
      if (Check_file.isFile()){ // selected a file
        QMessageBox::information(this,"Information","Please select a <b>folder</b> or click on 'Cancel' button");
      }
      else{ // it is a dir
        accept();
      }
    }
  }
  else{
    if (Mode==MODE_DIR){
      QFileInfo Check_file(*Directory);
      if (Check_file.exists() && Check_file.isFile()){
        QMessageBox::information(this,"Information","Please select a <b>folder</b> or click on 'Cancel' button");
      }
      else{
        *Directory=Path;
        accept();
      }
    }
    else QMessageBox::information(this,"Information","Please select a <b>file</b> or click on 'Cancel' button");
  }
}

//HEA

void _w_directory::cancel_slot()
{
  *Directory="";
  close();
}

//HEA

void _w_directory::item_clicked_slot(QListWidgetItem *Item)
{
  *Directory=Item->text();
//  Path=Path+'/'+(*Directory);
}


//HEA

void _w_directory::item_double_clicked_slot(QListWidgetItem *Item)
{
  *Directory=Item->text();
  Path=Path+'/'+(*Directory);
  *Directory="";
  update_list();
}


