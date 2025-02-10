#ifndef _MAP_LIST_H
#define _MAP_LIST_H

#include <string>
#include <stdexcept>
#include <iostream>
#include <QMessageBox>

using namespace std;

template <class Type>
class _map_list
{
public:

  int size(){return Data_by_string.size();};
  void clear();

  void set(string Name,Type Data1);
  Type get_data(string Name);
  Type get_data(int Position);
  int get_position(string Name);
  string get_string(int Position);
  void erase_data(string Name);
  void erase_data(int Position);
  
  map<string,Type> Data_by_string;
  map<int,Type> Data_by_position;
  map<string,int> Key_by_string;
  map<int, string> Key_by_position;
};



/**
* 150320
*
* function for setting the input and output images
*@param
*@returns nothing
*/

template <class Type>
void _map_list<Type>::clear()
{
  Data_by_string.clear();
  Data_by_position.clear();
  Key_by_string.clear();
  Key_by_position.clear();
}


/**
* 150320
*
* function for setting the input and output images
*@param
*@returns nothing
*/

template <class Type>
void _map_list<Type>::set(string Name,Type Data1)
{
  try{
    Data_by_string.at(Name);
  }
  catch (const std::out_of_range& oor) {

    int Position=Data_by_string.size();

    Data_by_string[Name]=Data1;
    Data_by_position[Position]=Data1;
    Key_by_string[Name]=Position;
    Key_by_position[Position]=Name;
    return;
  }
  QString Error("Error: the name is duplicated:  ");
  Error+=Name.c_str();
  QMessageBox MsgBox;
  MsgBox.setText(Error);
  MsgBox.exec();

}


/**
* 150320
*
* function for setting the input and output images
*@param
*@returns nothing
*/

template <class Type>
Type _map_list<Type>::get_data(string Name)
{
  try{
    Data_by_string.at(Name);
  }
  catch (const std::out_of_range& oor) {
    QString Error("Error in the definition of filter with this text:  ");
    Error+=Name.c_str();
    QMessageBox MsgBox;
    MsgBox.setText(Error);
    MsgBox.exec();
    return ((Type) NULL);
  }
  return Data_by_string.at(Name);
}

/**
* 150320
*
* function for setting the input and output images
*@param
*@returns nothing
*/

template <class Type>
Type _map_list<Type>::get_data(int Position)
{
  try{
    Data_by_position.at(Position);
  }
  catch (const std::out_of_range& oor) {
    QString Error("Error: the position does not exist:  ");
    QMessageBox MsgBox;
    MsgBox.setText(Error);
    MsgBox.exec();
    return ((Type) NULL);
  }
  return Data_by_position.at(Position);
}


/**
* 150320
*
* function for setting the input and output images
*@param
*@returns nothing
*/

template <class Type>
int _map_list< Type>::get_position(string Name)
{

  try{
    Key_by_string.at(Name);
  }
  catch (const std::out_of_range& oor) {
    QString Error("Error: the name does not exist:  ");
    Error+=Name.c_str();
    QMessageBox MsgBox;
    MsgBox.setText(Error);
    MsgBox.exec();
    return (-1);
  }
  return Key_by_string.at(Name);
}

/**
* 150320
*
* function for setting the input and output images
*@param
*@returns nothing
*/

template <class Type>
string _map_list< Type>::get_string(int Position)
{
  try{
    Key_by_position.at(Position);
  }
  catch (const std::out_of_range& oor) {
    QString Error("Error: the position does not exist");
    QMessageBox MsgBox;
    MsgBox.setText(Error);
    MsgBox.exec();
    return ("");
  }
  return Key_by_position.at(Position);
}


//HEA

//map<int,Type> Data_by_position;
//map<string,int> Key_by_string;
//map<int, string> Key_by_position;

template <class Type>
void _map_list<Type>::erase_data(string Name)
{
  typename std::map<string,Type>::iterator It;
  It=Data_by_string.find(Name);
  if (It!=Data_by_string.end()){
    Data_by_string.erase(It);

    int Position=Key_by_string.at(Name);
    std::map<string,int>::iterator It1;
    It1=Key_by_string.find(Name);
    Key_by_string.erase(It1);

    std::map<int,string>::iterator It2;
    It2=Key_by_position.find(Position);
    Key_by_position.erase(It2);

    typename std::map<int,Type>::iterator It3;
    It3=Data_by_position.find(Position);
    Data_by_position.erase(It3);
  }
}

//HEA

template <class Type>
void _map_list<Type>::erase_data(int Position)
{
  typename std::map<int,Type>::iterator It;
  It=Data_by_position.find(Position);
  if (It!=Data_by_string.end()){
    Data_by_position.erase(It);

    string Name=Key_by_position.at(Position);
    std::map<int,string>::iterator It1;
    It1=Key_by_position.find(Position);
    Key_by_position.erase(It1);

    typename std::map<string,Type>::iterator It2;
    It2=Data_by_string.find(Name);
    Data_by_string.erase(It2);

    std::map<string,int>::iterator It3;
    It3=Key_by_string.find(Name);
    Key_by_string.erase(It3);
  }
}


#endif // _MAP_LIST_H
