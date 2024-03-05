/****************************************************************************
** Meta object code from reading C++ file 'w_color_bar.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../xmapslab_src/w_color_bar.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'w_color_bar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata__w_color_bar_t {
    const uint offsetsAndSize[16];
    char stringdata0[107];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata__w_color_bar_t, stringdata0) + ofs), len 
static const qt_meta_stringdata__w_color_bar_t qt_meta_stringdata__w_color_bar = {
    {
QT_MOC_LITERAL(0, 12), // "_w_color_bar"
QT_MOC_LITERAL(13, 22), // "color_bar_changed_slot"
QT_MOC_LITERAL(36, 0), // ""
QT_MOC_LITERAL(37, 19), // "std::vector<float>&"
QT_MOC_LITERAL(57, 11), // "Vec_values1"
QT_MOC_LITERAL(69, 20), // "std::vector<QColor>&"
QT_MOC_LITERAL(90, 11), // "Vec_colors1"
QT_MOC_LITERAL(102, 4) // "Type"

    },
    "_w_color_bar\0color_bar_changed_slot\0"
    "\0std::vector<float>&\0Vec_values1\0"
    "std::vector<QColor>&\0Vec_colors1\0Type"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data__w_color_bar[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    3,   20,    2, 0x09,    1 /* Protected */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5, QMetaType::Int,    4,    6,    7,

       0        // eod
};

void _w_color_bar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<_w_color_bar *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->color_bar_changed_slot((*reinterpret_cast< std::add_pointer_t<std::vector<float>&>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<std::vector<QColor>&>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        default: ;
        }
    }
}

const QMetaObject _w_color_bar::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata__w_color_bar.offsetsAndSize,
    qt_meta_data__w_color_bar,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata__w_color_bar_t
, QtPrivate::TypeAndForceComplete<_w_color_bar, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<std::vector<float> &, std::false_type>, QtPrivate::TypeAndForceComplete<std::vector<QColor> &, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>


>,
    nullptr
} };


const QMetaObject *_w_color_bar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *_w_color_bar::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata__w_color_bar.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int _w_color_bar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 1;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
