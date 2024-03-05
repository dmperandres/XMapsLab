/****************************************************************************
** Meta object code from reading C++ file 'nodes_editor_maps_tab.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../xmapslab_src/nodes_editor_maps_tab.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'nodes_editor_maps_tab.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata__nodes_editor_maps_tab_t {
    const uint offsetsAndSize[34];
    char stringdata0[357];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata__nodes_editor_maps_tab_t, stringdata0) + ofs), len 
static const qt_meta_stringdata__nodes_editor_maps_tab_t qt_meta_stringdata__nodes_editor_maps_tab = {
    {
QT_MOC_LITERAL(0, 22), // "_nodes_editor_maps_tab"
QT_MOC_LITERAL(23, 12), // "item_clicked"
QT_MOC_LITERAL(36, 0), // ""
QT_MOC_LITERAL(37, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(54, 22), // "add_map_to_layers_slot"
QT_MOC_LITERAL(77, 29), // "lab_changed_palette_type_slot"
QT_MOC_LITERAL(107, 5), // "Index"
QT_MOC_LITERAL(113, 35), // "lab_changed_palette_color_typ..."
QT_MOC_LITERAL(149, 30), // "lab_changed_num_intervals_slot"
QT_MOC_LITERAL(180, 5), // "Value"
QT_MOC_LITERAL(186, 40), // "lab_changed_palette_color_ass..."
QT_MOC_LITERAL(227, 30), // "lab_palette_mutable_color_slot"
QT_MOC_LITERAL(258, 5), // "Color"
QT_MOC_LITERAL(264, 39), // "lab_changed_palette_fixed_pal..."
QT_MOC_LITERAL(304, 4), // "Name"
QT_MOC_LITERAL(309, 41), // "lab_button_pushed_palette_par..."
QT_MOC_LITERAL(351, 5) // "State"

    },
    "_nodes_editor_maps_tab\0item_clicked\0"
    "\0QListWidgetItem*\0add_map_to_layers_slot\0"
    "lab_changed_palette_type_slot\0Index\0"
    "lab_changed_palette_color_type_slot\0"
    "lab_changed_num_intervals_slot\0Value\0"
    "lab_changed_palette_color_assigning_slot\0"
    "lab_palette_mutable_color_slot\0Color\0"
    "lab_changed_palette_fixed_palettes_slot\0"
    "Name\0lab_button_pushed_palette_parameters_slot\0"
    "State"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data__nodes_editor_maps_tab[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   68,    2, 0x09,    1 /* Protected */,
       4,    0,   71,    2, 0x09,    3 /* Protected */,
       5,    1,   72,    2, 0x09,    4 /* Protected */,
       7,    1,   75,    2, 0x09,    6 /* Protected */,
       8,    1,   78,    2, 0x09,    8 /* Protected */,
      10,    1,   81,    2, 0x09,   10 /* Protected */,
      11,    1,   84,    2, 0x09,   12 /* Protected */,
      13,    1,   87,    2, 0x09,   14 /* Protected */,
      15,    1,   90,    2, 0x09,   16 /* Protected */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::QColor,   12,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void, QMetaType::Bool,   16,

       0        // eod
};

void _nodes_editor_maps_tab::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<_nodes_editor_maps_tab *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->item_clicked((*reinterpret_cast< std::add_pointer_t<QListWidgetItem*>>(_a[1]))); break;
        case 1: _t->add_map_to_layers_slot(); break;
        case 2: _t->lab_changed_palette_type_slot((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 3: _t->lab_changed_palette_color_type_slot((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 4: _t->lab_changed_num_intervals_slot((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 5: _t->lab_changed_palette_color_assigning_slot((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 6: _t->lab_palette_mutable_color_slot((*reinterpret_cast< std::add_pointer_t<QColor>>(_a[1]))); break;
        case 7: _t->lab_changed_palette_fixed_palettes_slot((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 8: _t->lab_button_pushed_palette_parameters_slot((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject _nodes_editor_maps_tab::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata__nodes_editor_maps_tab.offsetsAndSize,
    qt_meta_data__nodes_editor_maps_tab,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata__nodes_editor_maps_tab_t
, QtPrivate::TypeAndForceComplete<_nodes_editor_maps_tab, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QListWidgetItem *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QColor, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>


>,
    nullptr
} };


const QMetaObject *_nodes_editor_maps_tab::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *_nodes_editor_maps_tab::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata__nodes_editor_maps_tab.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int _nodes_editor_maps_tab::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
