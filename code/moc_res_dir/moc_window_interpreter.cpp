/****************************************************************************
** Meta object code from reading C++ file 'window_interpreter.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../interpreter_src/window_interpreter.h"
#include <QtGui/qtextcursor.h>
#include <QScreen>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'window_interpreter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata__window_interpreter_t {
    const uint offsetsAndSize[204];
    char stringdata0[2427];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata__window_interpreter_t, stringdata0) + ofs), len 
static const qt_meta_stringdata__window_interpreter_t qt_meta_stringdata__window_interpreter = {
    {
QT_MOC_LITERAL(0, 19), // "_window_interpreter"
QT_MOC_LITERAL(20, 22), // "load_project_data_slot"
QT_MOC_LITERAL(43, 0), // ""
QT_MOC_LITERAL(44, 22), // "save_project_data_slot"
QT_MOC_LITERAL(67, 25), // "load_user_selections_slot"
QT_MOC_LITERAL(93, 19), // "save_one_graph_slot"
QT_MOC_LITERAL(113, 20), // "save_all_graphs_slot"
QT_MOC_LITERAL(134, 30), // "xrf_save_process_info_csv_slot"
QT_MOC_LITERAL(165, 33), // "xrf_elements_obs_row_changed_..."
QT_MOC_LITERAL(199, 3), // "Row"
QT_MOC_LITERAL(203, 12), // "xrf_selected"
QT_MOC_LITERAL(216, 7), // "Element"
QT_MOC_LITERAL(224, 31), // "chart_bar_xrf_double_click_slot"
QT_MOC_LITERAL(256, 12), // "QMouseEvent*"
QT_MOC_LITERAL(269, 5), // "Event"
QT_MOC_LITERAL(275, 32), // "chart_bar_xrf_before_replot_slot"
QT_MOC_LITERAL(308, 30), // "chart_bar_xrf_mouse_press_slot"
QT_MOC_LITERAL(339, 29), // "chart_bar_xrf_mouse_move_slot"
QT_MOC_LITERAL(369, 32), // "chart_bar_xrf_mouse_release_slot"
QT_MOC_LITERAL(402, 23), // "xrf_x_axis_changed_slot"
QT_MOC_LITERAL(426, 8), // "QCPRange"
QT_MOC_LITERAL(435, 5), // "Range"
QT_MOC_LITERAL(441, 23), // "xrf_y_axis_changed_slot"
QT_MOC_LITERAL(465, 18), // "xrf_threshold_slot"
QT_MOC_LITERAL(484, 5), // "Value"
QT_MOC_LITERAL(490, 25), // "xrf_add_element_tool_slot"
QT_MOC_LITERAL(516, 7), // "Checked"
QT_MOC_LITERAL(524, 28), // "xrf_delete_element_tool_slot"
QT_MOC_LITERAL(553, 20), // "xrf_chart_scale_slot"
QT_MOC_LITERAL(574, 29), // "xrf_threshold_percentage_slot"
QT_MOC_LITERAL(604, 23), // "xrf_show_obs_graph_slot"
QT_MOC_LITERAL(628, 5), // "State"
QT_MOC_LITERAL(634, 29), // "xrf_show_processed_graph_slot"
QT_MOC_LITERAL(664, 37), // "xrf_show_processed_shifted_gr..."
QT_MOC_LITERAL(702, 29), // "xrf_show_gaussians_graph_slot"
QT_MOC_LITERAL(732, 21), // "xrf_update_parameters"
QT_MOC_LITERAL(754, 18), // "xrf_process_change"
QT_MOC_LITERAL(773, 25), // "num_steps_smooth_xrf_slot"
QT_MOC_LITERAL(799, 32), // "num_steps_subtract_mean_xrf_slot"
QT_MOC_LITERAL(832, 32), // "num_steps_search_window_xrf_slot"
QT_MOC_LITERAL(865, 22), // "xrf_color_obs_raw_slot"
QT_MOC_LITERAL(888, 5), // "Color"
QT_MOC_LITERAL(894, 28), // "xrf_color_obs_processed_slot"
QT_MOC_LITERAL(923, 36), // "xrf_color_obs_processed_shift..."
QT_MOC_LITERAL(960, 24), // "xrf_color_gaussians_slot"
QT_MOC_LITERAL(985, 34), // "xrd_save_correlation_data_csv..."
QT_MOC_LITERAL(1020, 30), // "xrd_save_process_info_csv_slot"
QT_MOC_LITERAL(1051, 25), // "xrd_num_steps_smooth_slot"
QT_MOC_LITERAL(1077, 38), // "xrd_num_steps_subtract_backgr..."
QT_MOC_LITERAL(1116, 24), // "xrd_num_steps_shift_slot"
QT_MOC_LITERAL(1141, 33), // "xrd_pigments_obs_row_changed_..."
QT_MOC_LITERAL(1175, 23), // "xrd_good_threshold_slot"
QT_MOC_LITERAL(1199, 25), // "xrd_medium_threshold_slot"
QT_MOC_LITERAL(1225, 22), // "xrd_bad_threshold_slot"
QT_MOC_LITERAL(1248, 23), // "xrd_level_subtract_slot"
QT_MOC_LITERAL(1272, 31), // "chart_bar_xrd_double_click_slot"
QT_MOC_LITERAL(1304, 30), // "chart_bar_xrd_mouse_wheel_slot"
QT_MOC_LITERAL(1335, 12), // "QWheelEvent*"
QT_MOC_LITERAL(1348, 30), // "chart_bar_xrd_mouse_press_slot"
QT_MOC_LITERAL(1379, 29), // "chart_bar_xrd_mouse_move_slot"
QT_MOC_LITERAL(1409, 32), // "chart_bar_xrd_mouse_release_slot"
QT_MOC_LITERAL(1442, 23), // "xrd_x_axis_changed_slot"
QT_MOC_LITERAL(1466, 23), // "xrd_y_axis_changed_slot"
QT_MOC_LITERAL(1490, 22), // "xrd_color_obs_raw_slot"
QT_MOC_LITERAL(1513, 28), // "xrd_color_obs_processed_slot"
QT_MOC_LITERAL(1542, 36), // "xrd_color_obs_processed_shift..."
QT_MOC_LITERAL(1579, 18), // "xrd_color_pdb_slot"
QT_MOC_LITERAL(1598, 19), // "xrd_color_sqrt_slot"
QT_MOC_LITERAL(1618, 30), // "xrd_color_file_not_exists_slot"
QT_MOC_LITERAL(1649, 25), // "xrd_color_file_not_exists"
QT_MOC_LITERAL(1675, 33), // "xrd_color_element_not_exists_..."
QT_MOC_LITERAL(1709, 28), // "xrd_color_element_not_exists"
QT_MOC_LITERAL(1738, 25), // "xrd_color_valid_good_slot"
QT_MOC_LITERAL(1764, 20), // "xrd_color_valid_good"
QT_MOC_LITERAL(1785, 27), // "xrd_color_valid_medium_slot"
QT_MOC_LITERAL(1813, 22), // "xrd_color_valid_medium"
QT_MOC_LITERAL(1836, 24), // "xrd_color_valid_bad_slot"
QT_MOC_LITERAL(1861, 19), // "xrd_color_valid_bad"
QT_MOC_LITERAL(1881, 19), // "xrd_chart_type_slot"
QT_MOC_LITERAL(1901, 32), // "xrd_normalization_type_mean_slot"
QT_MOC_LITERAL(1934, 38), // "xrd_normalization_type_percen..."
QT_MOC_LITERAL(1973, 30), // "xrd_computation_type_sqrt_slot"
QT_MOC_LITERAL(2004, 34), // "xrd_computation_type_not_zero..."
QT_MOC_LITERAL(2039, 27), // "xrd_show_graph_raw_obs_slot"
QT_MOC_LITERAL(2067, 33), // "xrd_show_graph_obs_processed_..."
QT_MOC_LITERAL(2101, 41), // "xrd_show_graph_obs_processed_..."
QT_MOC_LITERAL(2143, 23), // "xrd_show_graph_pdb_slot"
QT_MOC_LITERAL(2167, 24), // "xrd_show_graph_sqrt_slot"
QT_MOC_LITERAL(2192, 20), // "xrd_pdb_options_slot"
QT_MOC_LITERAL(2213, 20), // "xrd_chart_scale_slot"
QT_MOC_LITERAL(2234, 17), // "split_screen_slot"
QT_MOC_LITERAL(2252, 30), // "xrd_create_spectral_from_peaks"
QT_MOC_LITERAL(2283, 18), // "std::vector<float>"
QT_MOC_LITERAL(2302, 19), // "std::vector<float>&"
QT_MOC_LITERAL(2322, 10), // "Vec_2theta"
QT_MOC_LITERAL(2333, 13), // "Vec_intensity"
QT_MOC_LITERAL(2347, 12), // "options_slot"
QT_MOC_LITERAL(2360, 13), // "pdb_mode_slot"
QT_MOC_LITERAL(2374, 13), // "save_pdb_slot"
QT_MOC_LITERAL(2388, 16), // "tab_changed_slot"
QT_MOC_LITERAL(2405, 5), // "Index"
QT_MOC_LITERAL(2411, 15) // "adjust_splitter"

    },
    "_window_interpreter\0load_project_data_slot\0"
    "\0save_project_data_slot\0"
    "load_user_selections_slot\0save_one_graph_slot\0"
    "save_all_graphs_slot\0"
    "xrf_save_process_info_csv_slot\0"
    "xrf_elements_obs_row_changed_slot\0Row\0"
    "xrf_selected\0Element\0"
    "chart_bar_xrf_double_click_slot\0"
    "QMouseEvent*\0Event\0chart_bar_xrf_before_replot_slot\0"
    "chart_bar_xrf_mouse_press_slot\0"
    "chart_bar_xrf_mouse_move_slot\0"
    "chart_bar_xrf_mouse_release_slot\0"
    "xrf_x_axis_changed_slot\0QCPRange\0Range\0"
    "xrf_y_axis_changed_slot\0xrf_threshold_slot\0"
    "Value\0xrf_add_element_tool_slot\0Checked\0"
    "xrf_delete_element_tool_slot\0"
    "xrf_chart_scale_slot\0xrf_threshold_percentage_slot\0"
    "xrf_show_obs_graph_slot\0State\0"
    "xrf_show_processed_graph_slot\0"
    "xrf_show_processed_shifted_graph_slot\0"
    "xrf_show_gaussians_graph_slot\0"
    "xrf_update_parameters\0xrf_process_change\0"
    "num_steps_smooth_xrf_slot\0"
    "num_steps_subtract_mean_xrf_slot\0"
    "num_steps_search_window_xrf_slot\0"
    "xrf_color_obs_raw_slot\0Color\0"
    "xrf_color_obs_processed_slot\0"
    "xrf_color_obs_processed_shifted_slot\0"
    "xrf_color_gaussians_slot\0"
    "xrd_save_correlation_data_csv_slot\0"
    "xrd_save_process_info_csv_slot\0"
    "xrd_num_steps_smooth_slot\0"
    "xrd_num_steps_subtract_background_slot\0"
    "xrd_num_steps_shift_slot\0"
    "xrd_pigments_obs_row_changed_slot\0"
    "xrd_good_threshold_slot\0"
    "xrd_medium_threshold_slot\0"
    "xrd_bad_threshold_slot\0xrd_level_subtract_slot\0"
    "chart_bar_xrd_double_click_slot\0"
    "chart_bar_xrd_mouse_wheel_slot\0"
    "QWheelEvent*\0chart_bar_xrd_mouse_press_slot\0"
    "chart_bar_xrd_mouse_move_slot\0"
    "chart_bar_xrd_mouse_release_slot\0"
    "xrd_x_axis_changed_slot\0xrd_y_axis_changed_slot\0"
    "xrd_color_obs_raw_slot\0"
    "xrd_color_obs_processed_slot\0"
    "xrd_color_obs_processed_shifted_slot\0"
    "xrd_color_pdb_slot\0xrd_color_sqrt_slot\0"
    "xrd_color_file_not_exists_slot\0"
    "xrd_color_file_not_exists\0"
    "xrd_color_element_not_exists_slot\0"
    "xrd_color_element_not_exists\0"
    "xrd_color_valid_good_slot\0"
    "xrd_color_valid_good\0xrd_color_valid_medium_slot\0"
    "xrd_color_valid_medium\0xrd_color_valid_bad_slot\0"
    "xrd_color_valid_bad\0xrd_chart_type_slot\0"
    "xrd_normalization_type_mean_slot\0"
    "xrd_normalization_type_percentage_slot\0"
    "xrd_computation_type_sqrt_slot\0"
    "xrd_computation_type_not_zero_slot\0"
    "xrd_show_graph_raw_obs_slot\0"
    "xrd_show_graph_obs_processed_slot\0"
    "xrd_show_graph_obs_processed_shifted_slot\0"
    "xrd_show_graph_pdb_slot\0"
    "xrd_show_graph_sqrt_slot\0xrd_pdb_options_slot\0"
    "xrd_chart_scale_slot\0split_screen_slot\0"
    "xrd_create_spectral_from_peaks\0"
    "std::vector<float>\0std::vector<float>&\0"
    "Vec_2theta\0Vec_intensity\0options_slot\0"
    "pdb_mode_slot\0save_pdb_slot\0"
    "tab_changed_slot\0Index\0adjust_splitter"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data__window_interpreter[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      84,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  518,    2, 0x0a,    1 /* Public */,
       3,    0,  519,    2, 0x0a,    2 /* Public */,
       4,    0,  520,    2, 0x0a,    3 /* Public */,
       5,    0,  521,    2, 0x0a,    4 /* Public */,
       6,    0,  522,    2, 0x0a,    5 /* Public */,
       7,    0,  523,    2, 0x0a,    6 /* Public */,
       8,    1,  524,    2, 0x0a,    7 /* Public */,
      10,    1,  527,    2, 0x0a,    9 /* Public */,
      12,    1,  530,    2, 0x0a,   11 /* Public */,
      15,    0,  533,    2, 0x0a,   13 /* Public */,
      16,    1,  534,    2, 0x0a,   14 /* Public */,
      17,    1,  537,    2, 0x0a,   16 /* Public */,
      18,    1,  540,    2, 0x0a,   18 /* Public */,
      19,    1,  543,    2, 0x0a,   20 /* Public */,
      22,    1,  546,    2, 0x0a,   22 /* Public */,
      23,    1,  549,    2, 0x0a,   24 /* Public */,
      25,    1,  552,    2, 0x0a,   26 /* Public */,
      27,    1,  555,    2, 0x0a,   28 /* Public */,
      28,    1,  558,    2, 0x0a,   30 /* Public */,
      29,    1,  561,    2, 0x0a,   32 /* Public */,
      30,    1,  564,    2, 0x0a,   34 /* Public */,
      32,    1,  567,    2, 0x0a,   36 /* Public */,
      33,    1,  570,    2, 0x0a,   38 /* Public */,
      34,    1,  573,    2, 0x0a,   40 /* Public */,
      35,    0,  576,    2, 0x0a,   42 /* Public */,
      36,    0,  577,    2, 0x0a,   43 /* Public */,
      37,    1,  578,    2, 0x0a,   44 /* Public */,
      38,    1,  581,    2, 0x0a,   46 /* Public */,
      39,    1,  584,    2, 0x0a,   48 /* Public */,
      40,    1,  587,    2, 0x0a,   50 /* Public */,
      42,    1,  590,    2, 0x0a,   52 /* Public */,
      43,    1,  593,    2, 0x0a,   54 /* Public */,
      44,    1,  596,    2, 0x0a,   56 /* Public */,
      45,    0,  599,    2, 0x0a,   58 /* Public */,
      46,    0,  600,    2, 0x0a,   59 /* Public */,
      47,    1,  601,    2, 0x0a,   60 /* Public */,
      48,    1,  604,    2, 0x0a,   62 /* Public */,
      49,    1,  607,    2, 0x0a,   64 /* Public */,
      50,    1,  610,    2, 0x0a,   66 /* Public */,
      51,    1,  613,    2, 0x0a,   68 /* Public */,
      52,    1,  616,    2, 0x0a,   70 /* Public */,
      53,    1,  619,    2, 0x0a,   72 /* Public */,
      54,    1,  622,    2, 0x0a,   74 /* Public */,
      55,    1,  625,    2, 0x0a,   76 /* Public */,
      56,    1,  628,    2, 0x0a,   78 /* Public */,
      58,    1,  631,    2, 0x0a,   80 /* Public */,
      59,    1,  634,    2, 0x0a,   82 /* Public */,
      60,    1,  637,    2, 0x0a,   84 /* Public */,
      61,    1,  640,    2, 0x0a,   86 /* Public */,
      62,    1,  643,    2, 0x0a,   88 /* Public */,
      63,    1,  646,    2, 0x0a,   90 /* Public */,
      64,    1,  649,    2, 0x0a,   92 /* Public */,
      65,    1,  652,    2, 0x0a,   94 /* Public */,
      66,    1,  655,    2, 0x0a,   96 /* Public */,
      67,    1,  658,    2, 0x0a,   98 /* Public */,
      68,    1,  661,    2, 0x0a,  100 /* Public */,
      69,    0,  664,    2, 0x0a,  102 /* Public */,
      70,    1,  665,    2, 0x0a,  103 /* Public */,
      71,    0,  668,    2, 0x0a,  105 /* Public */,
      72,    1,  669,    2, 0x0a,  106 /* Public */,
      73,    0,  672,    2, 0x0a,  108 /* Public */,
      74,    1,  673,    2, 0x0a,  109 /* Public */,
      75,    0,  676,    2, 0x0a,  111 /* Public */,
      76,    1,  677,    2, 0x0a,  112 /* Public */,
      77,    0,  680,    2, 0x0a,  114 /* Public */,
      78,    1,  681,    2, 0x0a,  115 /* Public */,
      79,    1,  684,    2, 0x0a,  117 /* Public */,
      80,    1,  687,    2, 0x0a,  119 /* Public */,
      81,    1,  690,    2, 0x0a,  121 /* Public */,
      82,    1,  693,    2, 0x0a,  123 /* Public */,
      83,    1,  696,    2, 0x0a,  125 /* Public */,
      84,    1,  699,    2, 0x0a,  127 /* Public */,
      85,    1,  702,    2, 0x0a,  129 /* Public */,
      86,    1,  705,    2, 0x0a,  131 /* Public */,
      87,    1,  708,    2, 0x0a,  133 /* Public */,
      88,    0,  711,    2, 0x0a,  135 /* Public */,
      89,    1,  712,    2, 0x0a,  136 /* Public */,
      90,    0,  715,    2, 0x0a,  138 /* Public */,
      91,    2,  716,    2, 0x0a,  139 /* Public */,
      96,    0,  721,    2, 0x0a,  142 /* Public */,
      97,    0,  722,    2, 0x0a,  143 /* Public */,
      98,    0,  723,    2, 0x0a,  144 /* Public */,
      99,    1,  724,    2, 0x0a,  145 /* Public */,
     101,    0,  727,    2, 0x0a,  147 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Bool, QMetaType::Int,   11,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void, 0x80000000 | 20,   21,
    QMetaType::Void, 0x80000000 | 20,   21,
    QMetaType::Void, QMetaType::Int,   24,
    QMetaType::Void, QMetaType::Bool,   26,
    QMetaType::Void, QMetaType::Bool,   26,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Int,   24,
    QMetaType::Void, QMetaType::Int,   31,
    QMetaType::Void, QMetaType::Int,   31,
    QMetaType::Void, QMetaType::Int,   31,
    QMetaType::Void, QMetaType::Int,   31,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   24,
    QMetaType::Void, QMetaType::Int,   24,
    QMetaType::Void, QMetaType::Int,   24,
    QMetaType::Void, QMetaType::QColor,   41,
    QMetaType::Void, QMetaType::QColor,   41,
    QMetaType::Void, QMetaType::QColor,   41,
    QMetaType::Void, QMetaType::QColor,   41,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   24,
    QMetaType::Void, QMetaType::Int,   24,
    QMetaType::Void, QMetaType::Int,   24,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,   24,
    QMetaType::Void, QMetaType::Int,   24,
    QMetaType::Void, QMetaType::Int,   24,
    QMetaType::Void, QMetaType::Double,   24,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void, 0x80000000 | 57,   14,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void, 0x80000000 | 20,   21,
    QMetaType::Void, 0x80000000 | 20,   21,
    QMetaType::Void, QMetaType::QColor,   41,
    QMetaType::Void, QMetaType::QColor,   41,
    QMetaType::Void, QMetaType::QColor,   41,
    QMetaType::Void, QMetaType::QColor,   41,
    QMetaType::Void, QMetaType::QColor,   41,
    QMetaType::Void, QMetaType::QColor,   41,
    QMetaType::QColor,
    QMetaType::Void, QMetaType::QColor,   41,
    QMetaType::QColor,
    QMetaType::Void, QMetaType::QColor,   41,
    QMetaType::QColor,
    QMetaType::Void, QMetaType::QColor,   41,
    QMetaType::QColor,
    QMetaType::Void, QMetaType::QColor,   41,
    QMetaType::QColor,
    QMetaType::Void, QMetaType::Bool,   31,
    QMetaType::Void, QMetaType::Bool,   31,
    QMetaType::Void, QMetaType::Bool,   31,
    QMetaType::Void, QMetaType::Bool,   31,
    QMetaType::Void, QMetaType::Bool,   31,
    QMetaType::Void, QMetaType::Int,   31,
    QMetaType::Void, QMetaType::Int,   31,
    QMetaType::Void, QMetaType::Int,   31,
    QMetaType::Void, QMetaType::Int,   31,
    QMetaType::Void, QMetaType::Int,   31,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    0x80000000 | 92, 0x80000000 | 93, 0x80000000 | 93,   94,   95,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,  100,
    QMetaType::Void,

       0        // eod
};

void _window_interpreter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<_window_interpreter *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->load_project_data_slot(); break;
        case 1: _t->save_project_data_slot(); break;
        case 2: _t->load_user_selections_slot(); break;
        case 3: _t->save_one_graph_slot(); break;
        case 4: _t->save_all_graphs_slot(); break;
        case 5: _t->xrf_save_process_info_csv_slot(); break;
        case 6: _t->xrf_elements_obs_row_changed_slot((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 7: { bool _r = _t->xrf_selected((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 8: _t->chart_bar_xrf_double_click_slot((*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[1]))); break;
        case 9: _t->chart_bar_xrf_before_replot_slot(); break;
        case 10: _t->chart_bar_xrf_mouse_press_slot((*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[1]))); break;
        case 11: _t->chart_bar_xrf_mouse_move_slot((*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[1]))); break;
        case 12: _t->chart_bar_xrf_mouse_release_slot((*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[1]))); break;
        case 13: _t->xrf_x_axis_changed_slot((*reinterpret_cast< std::add_pointer_t<QCPRange>>(_a[1]))); break;
        case 14: _t->xrf_y_axis_changed_slot((*reinterpret_cast< std::add_pointer_t<QCPRange>>(_a[1]))); break;
        case 15: _t->xrf_threshold_slot((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 16: _t->xrf_add_element_tool_slot((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 17: _t->xrf_delete_element_tool_slot((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 18: _t->xrf_chart_scale_slot((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 19: _t->xrf_threshold_percentage_slot((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 20: _t->xrf_show_obs_graph_slot((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 21: _t->xrf_show_processed_graph_slot((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 22: _t->xrf_show_processed_shifted_graph_slot((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 23: _t->xrf_show_gaussians_graph_slot((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 24: _t->xrf_update_parameters(); break;
        case 25: _t->xrf_process_change(); break;
        case 26: _t->num_steps_smooth_xrf_slot((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 27: _t->num_steps_subtract_mean_xrf_slot((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 28: _t->num_steps_search_window_xrf_slot((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 29: _t->xrf_color_obs_raw_slot((*reinterpret_cast< std::add_pointer_t<QColor>>(_a[1]))); break;
        case 30: _t->xrf_color_obs_processed_slot((*reinterpret_cast< std::add_pointer_t<QColor>>(_a[1]))); break;
        case 31: _t->xrf_color_obs_processed_shifted_slot((*reinterpret_cast< std::add_pointer_t<QColor>>(_a[1]))); break;
        case 32: _t->xrf_color_gaussians_slot((*reinterpret_cast< std::add_pointer_t<QColor>>(_a[1]))); break;
        case 33: _t->xrd_save_correlation_data_csv_slot(); break;
        case 34: _t->xrd_save_process_info_csv_slot(); break;
        case 35: _t->xrd_num_steps_smooth_slot((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 36: _t->xrd_num_steps_subtract_background_slot((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 37: _t->xrd_num_steps_shift_slot((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 38: _t->xrd_pigments_obs_row_changed_slot((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 39: _t->xrd_good_threshold_slot((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 40: _t->xrd_medium_threshold_slot((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 41: _t->xrd_bad_threshold_slot((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 42: _t->xrd_level_subtract_slot((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 43: _t->chart_bar_xrd_double_click_slot((*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[1]))); break;
        case 44: _t->chart_bar_xrd_mouse_wheel_slot((*reinterpret_cast< std::add_pointer_t<QWheelEvent*>>(_a[1]))); break;
        case 45: _t->chart_bar_xrd_mouse_press_slot((*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[1]))); break;
        case 46: _t->chart_bar_xrd_mouse_move_slot((*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[1]))); break;
        case 47: _t->chart_bar_xrd_mouse_release_slot((*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[1]))); break;
        case 48: _t->xrd_x_axis_changed_slot((*reinterpret_cast< std::add_pointer_t<QCPRange>>(_a[1]))); break;
        case 49: _t->xrd_y_axis_changed_slot((*reinterpret_cast< std::add_pointer_t<QCPRange>>(_a[1]))); break;
        case 50: _t->xrd_color_obs_raw_slot((*reinterpret_cast< std::add_pointer_t<QColor>>(_a[1]))); break;
        case 51: _t->xrd_color_obs_processed_slot((*reinterpret_cast< std::add_pointer_t<QColor>>(_a[1]))); break;
        case 52: _t->xrd_color_obs_processed_shifted_slot((*reinterpret_cast< std::add_pointer_t<QColor>>(_a[1]))); break;
        case 53: _t->xrd_color_pdb_slot((*reinterpret_cast< std::add_pointer_t<QColor>>(_a[1]))); break;
        case 54: _t->xrd_color_sqrt_slot((*reinterpret_cast< std::add_pointer_t<QColor>>(_a[1]))); break;
        case 55: _t->xrd_color_file_not_exists_slot((*reinterpret_cast< std::add_pointer_t<QColor>>(_a[1]))); break;
        case 56: { QColor _r = _t->xrd_color_file_not_exists();
            if (_a[0]) *reinterpret_cast< QColor*>(_a[0]) = std::move(_r); }  break;
        case 57: _t->xrd_color_element_not_exists_slot((*reinterpret_cast< std::add_pointer_t<QColor>>(_a[1]))); break;
        case 58: { QColor _r = _t->xrd_color_element_not_exists();
            if (_a[0]) *reinterpret_cast< QColor*>(_a[0]) = std::move(_r); }  break;
        case 59: _t->xrd_color_valid_good_slot((*reinterpret_cast< std::add_pointer_t<QColor>>(_a[1]))); break;
        case 60: { QColor _r = _t->xrd_color_valid_good();
            if (_a[0]) *reinterpret_cast< QColor*>(_a[0]) = std::move(_r); }  break;
        case 61: _t->xrd_color_valid_medium_slot((*reinterpret_cast< std::add_pointer_t<QColor>>(_a[1]))); break;
        case 62: { QColor _r = _t->xrd_color_valid_medium();
            if (_a[0]) *reinterpret_cast< QColor*>(_a[0]) = std::move(_r); }  break;
        case 63: _t->xrd_color_valid_bad_slot((*reinterpret_cast< std::add_pointer_t<QColor>>(_a[1]))); break;
        case 64: { QColor _r = _t->xrd_color_valid_bad();
            if (_a[0]) *reinterpret_cast< QColor*>(_a[0]) = std::move(_r); }  break;
        case 65: _t->xrd_chart_type_slot((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 66: _t->xrd_normalization_type_mean_slot((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 67: _t->xrd_normalization_type_percentage_slot((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 68: _t->xrd_computation_type_sqrt_slot((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 69: _t->xrd_computation_type_not_zero_slot((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 70: _t->xrd_show_graph_raw_obs_slot((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 71: _t->xrd_show_graph_obs_processed_slot((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 72: _t->xrd_show_graph_obs_processed_shifted_slot((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 73: _t->xrd_show_graph_pdb_slot((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 74: _t->xrd_show_graph_sqrt_slot((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 75: _t->xrd_pdb_options_slot(); break;
        case 76: _t->xrd_chart_scale_slot((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 77: _t->split_screen_slot(); break;
        case 78: { std::vector<float> _r = _t->xrd_create_spectral_from_peaks((*reinterpret_cast< std::add_pointer_t<std::vector<float>&>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<std::vector<float>&>>(_a[2])));
            if (_a[0]) *reinterpret_cast< std::vector<float>*>(_a[0]) = std::move(_r); }  break;
        case 79: _t->options_slot(); break;
        case 80: _t->pdb_mode_slot(); break;
        case 81: _t->save_pdb_slot(); break;
        case 82: _t->tab_changed_slot((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 83: _t->adjust_splitter(); break;
        default: ;
        }
    }
}

const QMetaObject _window_interpreter::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata__window_interpreter.offsetsAndSize,
    qt_meta_data__window_interpreter,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata__window_interpreter_t
, QtPrivate::TypeAndForceComplete<_window_interpreter, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QCPRange, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QCPRange, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QColor, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QColor, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QColor, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QColor, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QWheelEvent *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QCPRange, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QCPRange, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QColor, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QColor, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QColor, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QColor, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QColor, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QColor, std::false_type>, QtPrivate::TypeAndForceComplete<QColor, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QColor, std::false_type>, QtPrivate::TypeAndForceComplete<QColor, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QColor, std::false_type>, QtPrivate::TypeAndForceComplete<QColor, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QColor, std::false_type>, QtPrivate::TypeAndForceComplete<QColor, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QColor, std::false_type>, QtPrivate::TypeAndForceComplete<QColor, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<std::vector<float>, std::false_type>, QtPrivate::TypeAndForceComplete<std::vector<float> &, std::false_type>, QtPrivate::TypeAndForceComplete<std::vector<float> &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *_window_interpreter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *_window_interpreter::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata__window_interpreter.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int _window_interpreter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 84)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 84;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 84)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 84;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
