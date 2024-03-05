/****************************************************************************
** Meta object code from reading C++ file 'table_layers.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../xmapslab_src/table_layers.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'table_layers.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata__table_layers_t {
    const uint offsetsAndSize[14];
    char stringdata0[81];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata__table_layers_t, stringdata0) + ofs), len 
static const qt_meta_stringdata__table_layers_t qt_meta_stringdata__table_layers = {
    {
QT_MOC_LITERAL(0, 13), // "_table_layers"
QT_MOC_LITERAL(14, 19), // "button_clicked_slot"
QT_MOC_LITERAL(34, 0), // ""
QT_MOC_LITERAL(35, 3), // "Row"
QT_MOC_LITERAL(39, 3), // "Col"
QT_MOC_LITERAL(43, 17), // "cell_clicked_slot"
QT_MOC_LITERAL(61, 19) // "header_clicked_slot"

    },
    "_table_layers\0button_clicked_slot\0\0"
    "Row\0Col\0cell_clicked_slot\0header_clicked_slot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data__table_layers[] = {

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
       1,    2,   32,    2, 0x0a,    1 /* Public */,
       5,    2,   37,    2, 0x0a,    4 /* Public */,
       6,    1,   42,    2, 0x0a,    7 /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::Int,    4,

       0        // eod
};

void _table_layers::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<_table_layers *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->button_clicked_slot((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 1: _t->cell_clicked_slot((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 2: _t->header_clicked_slot((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject _table_layers::staticMetaObject = { {
    QMetaObject::SuperData::link<_table::staticMetaObject>(),
    qt_meta_stringdata__table_layers.offsetsAndSize,
    qt_meta_data__table_layers,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata__table_layers_t
, QtPrivate::TypeAndForceComplete<_table_layers, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>


>,
    nullptr
} };


const QMetaObject *_table_layers::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *_table_layers::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata__table_layers.stringdata0))
        return static_cast<void*>(this);
    return _table::qt_metacast(_clname);
}

int _table_layers::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = _table::qt_metacall(_c, _id, _a);
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
