/****************************************************************************
** Meta object code from reading C++ file 'color_bar_abstract.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../xmapslab_src/color_bar_abstract.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'color_bar_abstract.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata__color_bar_abstract_t {
    const uint offsetsAndSize[10];
    char stringdata0[75];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata__color_bar_abstract_t, stringdata0) + ofs), len 
static const qt_meta_stringdata__color_bar_abstract_t qt_meta_stringdata__color_bar_abstract = {
    {
QT_MOC_LITERAL(0, 19), // "_color_bar_abstract"
QT_MOC_LITERAL(20, 12), // "colorChanged"
QT_MOC_LITERAL(33, 0), // ""
QT_MOC_LITERAL(34, 19), // "std::vector<float>&"
QT_MOC_LITERAL(54, 20) // "std::vector<QColor>&"

    },
    "_color_bar_abstract\0colorChanged\0\0"
    "std::vector<float>&\0std::vector<QColor>&"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data__color_bar_abstract[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    3,   20,    2, 0x06,    1 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 4, QMetaType::Int,    2,    2,    2,

       0        // eod
};

void _color_bar_abstract::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<_color_bar_abstract *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->colorChanged((*reinterpret_cast< std::add_pointer_t<std::vector<float>&>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<std::vector<QColor>&>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (_color_bar_abstract::*)(std::vector<float> & , std::vector<QColor> & , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&_color_bar_abstract::colorChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject _color_bar_abstract::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata__color_bar_abstract.offsetsAndSize,
    qt_meta_data__color_bar_abstract,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata__color_bar_abstract_t
, QtPrivate::TypeAndForceComplete<_color_bar_abstract, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<std::vector<float> &, std::false_type>, QtPrivate::TypeAndForceComplete<std::vector<QColor> &, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>



>,
    nullptr
} };


const QMetaObject *_color_bar_abstract::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *_color_bar_abstract::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata__color_bar_abstract.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int _color_bar_abstract::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void _color_bar_abstract::colorChanged(std::vector<float> & _t1, std::vector<QColor> & _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
