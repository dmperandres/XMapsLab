/****************************************************************************
** Meta object code from reading C++ file 'window_tools.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../tools_src/window_tools.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'window_tools.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata__window_tools_t {
    const uint offsetsAndSize[30];
    char stringdata0[293];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata__window_tools_t, stringdata0) + ofs), len 
static const qt_meta_stringdata__window_tools_t qt_meta_stringdata__window_tools = {
    {
QT_MOC_LITERAL(0, 13), // "_window_tools"
QT_MOC_LITERAL(14, 19), // "create_project_slot"
QT_MOC_LITERAL(34, 0), // ""
QT_MOC_LITERAL(35, 17), // "open_project_slot"
QT_MOC_LITERAL(53, 14), // "add_image_slot"
QT_MOC_LITERAL(68, 27), // "add_positions_data_csv_slot"
QT_MOC_LITERAL(96, 25), // "add_random_positions_slot"
QT_MOC_LITERAL(122, 20), // "add_artax_files_slot"
QT_MOC_LITERAL(143, 17), // "add_xy_files_slot"
QT_MOC_LITERAL(161, 18), // "add_uxd_files_slot"
QT_MOC_LITERAL(180, 18), // "add_plv_files_slot"
QT_MOC_LITERAL(199, 12), // "options_slot"
QT_MOC_LITERAL(212, 12), // "program_slot"
QT_MOC_LITERAL(225, 33), // "xrf_data_csv_to_project_data_..."
QT_MOC_LITERAL(259, 33) // "xrd_data_csv_to_project_data_..."

    },
    "_window_tools\0create_project_slot\0\0"
    "open_project_slot\0add_image_slot\0"
    "add_positions_data_csv_slot\0"
    "add_random_positions_slot\0"
    "add_artax_files_slot\0add_xy_files_slot\0"
    "add_uxd_files_slot\0add_plv_files_slot\0"
    "options_slot\0program_slot\0"
    "xrf_data_csv_to_project_data_slot\0"
    "xrd_data_csv_to_project_data_slot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data__window_tools[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   92,    2, 0x09,    1 /* Protected */,
       3,    0,   93,    2, 0x09,    2 /* Protected */,
       4,    0,   94,    2, 0x09,    3 /* Protected */,
       5,    0,   95,    2, 0x09,    4 /* Protected */,
       6,    0,   96,    2, 0x09,    5 /* Protected */,
       7,    0,   97,    2, 0x09,    6 /* Protected */,
       8,    0,   98,    2, 0x09,    7 /* Protected */,
       9,    0,   99,    2, 0x09,    8 /* Protected */,
      10,    0,  100,    2, 0x09,    9 /* Protected */,
      11,    0,  101,    2, 0x09,   10 /* Protected */,
      12,    0,  102,    2, 0x09,   11 /* Protected */,
      13,    0,  103,    2, 0x09,   12 /* Protected */,
      14,    0,  104,    2, 0x09,   13 /* Protected */,

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
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void _window_tools::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<_window_tools *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->create_project_slot(); break;
        case 1: _t->open_project_slot(); break;
        case 2: _t->add_image_slot(); break;
        case 3: _t->add_positions_data_csv_slot(); break;
        case 4: _t->add_random_positions_slot(); break;
        case 5: _t->add_artax_files_slot(); break;
        case 6: _t->add_xy_files_slot(); break;
        case 7: _t->add_uxd_files_slot(); break;
        case 8: _t->add_plv_files_slot(); break;
        case 9: _t->options_slot(); break;
        case 10: _t->program_slot(); break;
        case 11: _t->xrf_data_csv_to_project_data_slot(); break;
        case 12: _t->xrd_data_csv_to_project_data_slot(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject _window_tools::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata__window_tools.offsetsAndSize,
    qt_meta_data__window_tools,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata__window_tools_t
, QtPrivate::TypeAndForceComplete<_window_tools, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *_window_tools::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *_window_tools::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata__window_tools.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int _window_tools::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
