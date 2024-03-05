/****************************************************************************
** Meta object code from reading C++ file 'window_positions.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../positions_src/window_positions.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'window_positions.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata__window_positions_t {
    const uint offsetsAndSize[26];
    char stringdata0[240];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata__window_positions_t, stringdata0) + ofs), len 
static const qt_meta_stringdata__window_positions_t qt_meta_stringdata__window_positions = {
    {
QT_MOC_LITERAL(0, 17), // "_window_positions"
QT_MOC_LITERAL(18, 17), // "load_project_slot"
QT_MOC_LITERAL(36, 0), // ""
QT_MOC_LITERAL(37, 25), // "load_auxiliary_image_slot"
QT_MOC_LITERAL(63, 19), // "save_positions_slot"
QT_MOC_LITERAL(83, 15), // "save_image_slot"
QT_MOC_LITERAL(99, 12), // "options_slot"
QT_MOC_LITERAL(112, 16), // "left_handle_slot"
QT_MOC_LITERAL(129, 17), // "right_handle_slot"
QT_MOC_LITERAL(147, 19), // "action_default_slot"
QT_MOC_LITERAL(167, 22), // "action_add_points_slot"
QT_MOC_LITERAL(190, 25), // "action_remove_points_slot"
QT_MOC_LITERAL(216, 23) // "action_move_points_slot"

    },
    "_window_positions\0load_project_slot\0"
    "\0load_auxiliary_image_slot\0"
    "save_positions_slot\0save_image_slot\0"
    "options_slot\0left_handle_slot\0"
    "right_handle_slot\0action_default_slot\0"
    "action_add_points_slot\0action_remove_points_slot\0"
    "action_move_points_slot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data__window_positions[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   80,    2, 0x0a,    1 /* Public */,
       3,    0,   81,    2, 0x0a,    2 /* Public */,
       4,    0,   82,    2, 0x0a,    3 /* Public */,
       5,    0,   83,    2, 0x0a,    4 /* Public */,
       6,    0,   84,    2, 0x0a,    5 /* Public */,
       7,    0,   85,    2, 0x0a,    6 /* Public */,
       8,    0,   86,    2, 0x0a,    7 /* Public */,
       9,    0,   87,    2, 0x0a,    8 /* Public */,
      10,    0,   88,    2, 0x0a,    9 /* Public */,
      11,    0,   89,    2, 0x0a,   10 /* Public */,
      12,    0,   90,    2, 0x0a,   11 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void _window_positions::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<_window_positions *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->load_project_slot(); break;
        case 1: _t->load_auxiliary_image_slot(); break;
        case 2: _t->save_positions_slot(); break;
        case 3: _t->save_image_slot(); break;
        case 4: _t->options_slot(); break;
        case 5: _t->left_handle_slot(); break;
        case 6: _t->right_handle_slot(); break;
        case 7: _t->action_default_slot(); break;
        case 8: _t->action_add_points_slot(); break;
        case 9: _t->action_remove_points_slot(); break;
        case 10: _t->action_move_points_slot(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject _window_positions::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata__window_positions.offsetsAndSize,
    qt_meta_data__window_positions,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata__window_positions_t
, QtPrivate::TypeAndForceComplete<_window_positions, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *_window_positions::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *_window_positions::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata__window_positions.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int _window_positions::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
