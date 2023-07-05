/*************************************************************************
Copyright (c) 2022, 2023 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: XXX

*************************************************************************/

#ifndef LINE_EDIT_H
#define LINE_EDIT_H

#include <QLineEdit>
#include <QKeyEvent>

class _line_edit : public QLineEdit
{
Q_OBJECT

public:
  _line_edit();

signals:
//void tabPressed();

protected:
//void focusOutEvent(QFocusEvent *Event);
//bool event(QEvent *Event);
//void keyPressEvent(QKeyEvent *Event);

};

#endif // LINE_EDIT_H
