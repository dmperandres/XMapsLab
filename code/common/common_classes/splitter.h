#ifndef SPLITTER
#define SPLITTER

#include <QSplitter>
#include <QSplitterHandle>
#include <QPainter>
#include <QPaintEvent>

#include <iostream>

class _splitter: public QSplitter
{
public:
     _splitter(Qt::Orientation orientation, QWidget *parent =nullptr);

 protected:
     QSplitterHandle *createHandle() override;
};

#endif


