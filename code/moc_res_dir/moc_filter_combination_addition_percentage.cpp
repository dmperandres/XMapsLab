/****************************************************************************
** Meta object code from reading C++ file 'filter_combination_addition_percentage.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../xmapslab_src/filter_combination_addition_percentage.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'filter_combination_addition_percentage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata__qtw_filter_combination_addition_percentage_t {
    const uint offsetsAndSize[14];
    char stringdata0[106];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata__qtw_filter_combination_addition_percentage_t, stringdata0) + ofs), len 
static const qt_meta_stringdata__qtw_filter_combination_addition_percentage_t qt_meta_stringdata__qtw_filter_combination_addition_percentage = {
    {
QT_MOC_LITERAL(0, 43), // "_qtw_filter_combination_addit..."
QT_MOC_LITERAL(44, 15), // "parameter2_slot"
QT_MOC_LITERAL(60, 0), // ""
QT_MOC_LITERAL(61, 6), // "Color1"
QT_MOC_LITERAL(68, 15), // "parameter3_slot"
QT_MOC_LITERAL(84, 5), // "Value"
QT_MOC_LITERAL(90, 15) // "parameter4_slot"

    },
    "_qtw_filter_combination_addition_percentage\0"
    "parameter2_slot\0\0Color1\0parameter3_slot\0"
    "Value\0parameter4_slot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data__qtw_filter_combination_addition_percentage[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   32,    2, 0x09,    1 /* Protected */,
       4,    1,   35,    2, 0x09,    3 /* Protected */,
       6,    1,   38,    2, 0x09,    5 /* Protected */,

 // slots: parameters
    QMetaType::Void, QMetaType::QColor,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,

       0        // eod
};

void _qtw_filter_combination_addition_percentage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<_qtw_filter_combination_addition_percentage *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->parameter2_slot((*reinterpret_cast< std::add_pointer_t<QColor>>(_a[1]))); break;
        case 1: _t->parameter3_slot((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->parameter4_slot((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject _qtw_filter_combination_addition_percentage::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata__qtw_filter_combination_addition_percentage.offsetsAndSize,
    qt_meta_data__qtw_filter_combination_addition_percentage,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata__qtw_filter_combination_addition_percentage_t
, QtPrivate::TypeAndForceComplete<_qtw_filter_combination_addition_percentage, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QColor, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>


>,
    nullptr
} };


const QMetaObject *_qtw_filter_combination_addition_percentage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *_qtw_filter_combination_addition_percentage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata__qtw_filter_combination_addition_percentage.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int _qtw_filter_combination_addition_percentage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
