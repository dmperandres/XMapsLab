#include "splitter.h"
#include "splitter_handle.h"

//HEA

_splitter::_splitter(Qt::Orientation orientation, QWidget *parent):QSplitter(orientation,parent)
{
}

//HEA

QSplitterHandle *_splitter::createHandle()
{
  return new _splitter_handle(orientation(), this);
}
