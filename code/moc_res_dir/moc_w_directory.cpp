/****************************************************************************
** Meta object code from reading C++ file 'w_directory.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../common/common_classes/w_directory.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'w_directory.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata__w_directory_t {
    const uint offsetsAndSize[20];
    char stringdata0[121];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata__w_directory_t, stringdata0) + ofs), len 
static const qt_meta_stringdata__w_directory_t qt_meta_stringdata__w_directory = {
    {
QT_MOC_LITERAL(0, 12), // "_w_directory"
QT_MOC_LITERAL(13, 9), // "home_slot"
QT_MOC_LITERAL(23, 0), // ""
QT_MOC_LITERAL(24, 7), // "up_slot"
QT_MOC_LITERAL(32, 11), // "select_slot"
QT_MOC_LITERAL(44, 11), // "cancel_slot"
QT_MOC_LITERAL(56, 17), // "item_clicked_slot"
QT_MOC_LITERAL(74, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(91, 4), // "Item"
QT_MOC_LITERAL(96, 24) // "item_double_clicked_slot"

    },
    "_w_directory\0home_slot\0\0up_slot\0"
    "select_slot\0cancel_slot\0item_clicked_slot\0"
    "QListWidgetItem*\0Item\0item_double_clicked_slot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data__w_directory[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   50,    2, 0x0a,    1 /* Public */,
       3,    0,   51,    2, 0x0a,    2 /* Public */,
       4,    0,   52,    2, 0x0a,    3 /* Public */,
       5,    0,   53,    2, 0x0a,    4 /* Public */,
       6,    1,   54,    2, 0x0a,    5 /* Public */,
       9,    1,   57,    2, 0x0a,    7 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 7,    8,

       0        // eod
};

void _w_directory::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<_w_directory *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->home_slot(); break;
        case 1: _t->up_slot(); break;
        case 2: _t->select_slot(); break;
        case 3: _t->cancel_slot(); break;
        case 4: _t->item_clicked_slot((*reinterpret_cast< std::add_pointer_t<QListWidgetItem*>>(_a[1]))); break;
        case 5: _t->item_double_clicked_slot((*reinterpret_cast< std::add_pointer_t<QListWidgetItem*>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject _w_directory::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata__w_directory.offsetsAndSize,
    qt_meta_data__w_directory,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata__w_directory_t
, QtPrivate::TypeAndForceComplete<_w_directory, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QListWidgetItem *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QListWidgetItem *, std::false_type>


>,
    nullptr
} };


const QMetaObject *_w_directory::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *_w_directory::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata__w_directory.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int _w_directory::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
