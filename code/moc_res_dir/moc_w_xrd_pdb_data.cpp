/****************************************************************************
** Meta object code from reading C++ file 'w_xrd_pdb_data.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../interpreter_src/w_xrd_pdb_data.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'w_xrd_pdb_data.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata__w_xrd_pdb_data_t {
    const uint offsetsAndSize[6];
    char stringdata0[29];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata__w_xrd_pdb_data_t, stringdata0) + ofs), len 
static const qt_meta_stringdata__w_xrd_pdb_data_t qt_meta_stringdata__w_xrd_pdb_data = {
    {
QT_MOC_LITERAL(0, 15), // "_w_xrd_pdb_data"
QT_MOC_LITERAL(16, 11), // "accept_slot"
QT_MOC_LITERAL(28, 0) // ""

    },
    "_w_xrd_pdb_data\0accept_slot\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data__w_xrd_pdb_data[] = {

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
       1,    0,   20,    2, 0x0a,    1 /* Public */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void _w_xrd_pdb_data::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<_w_xrd_pdb_data *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->accept_slot(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject _w_xrd_pdb_data::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata__w_xrd_pdb_data.offsetsAndSize,
    qt_meta_data__w_xrd_pdb_data,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata__w_xrd_pdb_data_t
, QtPrivate::TypeAndForceComplete<_w_xrd_pdb_data, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *_w_xrd_pdb_data::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *_w_xrd_pdb_data::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata__w_xrd_pdb_data.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int _w_xrd_pdb_data::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
