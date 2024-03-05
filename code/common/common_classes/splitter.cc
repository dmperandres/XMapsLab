#include "splitter.h"
#include "splitter_handle.h"

/*************************************************************************/

_splitter::_splitter(Qt::Orientation orientation, QWidget *parent):QSplitter(orientation,parent)
{
}

/*************************************************************************/

QSplitterHandle *_splitter::createHandle()
{
  return new _splitter_handle(orientation(), this);
}
