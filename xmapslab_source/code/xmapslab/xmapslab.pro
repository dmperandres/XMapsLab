DEFINES+=LINUX
#DEFINES+=WINDOWS

CONFIG+=LAYERS_EDGES_ACTIVE
CONFIG+=COMPOUNDS_FROM_ELEMENTS_ACTIVE

# PATHS
LINUX_PATH=/home/dmartin/codigo/funciontecas
WINDOWS_PATH=C:\CODIGO\

MAIN_PATH=src/main
FILE_IO_PATH=../common/file_io
COMMON_CLASSES_PATH=../common/common_classes
RBF_PATH=src/rbf
SHADERS_PATH=../common



# Special layers
LAYERS_EDGES_ACTIVE {

    DEFINES+=LAYERS_EDGES_ACTIVE

    HEADERS+= \
    $${MAIN_PATH}/layer_dog.h

    SOURCES+= \
    $${MAIN_PATH}/layer_dog.cc

}else{

}

# Compounds from elements
COMPOUNDS_FROM_ELEMENTS_ACTIVE {
    DEFINES+=COMPOUNDS_FROM_ELEMENTS_ACTIVE

    HEADERS += \
    $${FILE_IO_PATH}/file_compound_combination_csv.h \
    $${MAIN_PATH}/layer_compound_combination.h


    SOURCES += \
    $${FILE_IO_PATH}/file_compound_combination_csv.cc \
    $${MAIN_PATH}/layer_compound_combination.cc

}else{

}


HEADERS += \
  $${COMMON_CLASSES_PATH}/common.h \
  $${COMMON_CLASSES_PATH}/common_window.h \
  $${COMMON_CLASSES_PATH}/common_interpreter.h \
  $${COMMON_CLASSES_PATH}/data_io.h \
  $${MAIN_PATH}/color_map.h \
  $${MAIN_PATH}/atomic_data.h \
  $${COMMON_CLASSES_PATH}/data_xrf.h \
  $${COMMON_CLASSES_PATH}/data_xrd.h \
  $${COMMON_CLASSES_PATH}/project_data.h \
  $${COMMON_CLASSES_PATH}/w_directory.h \
  $${MAIN_PATH}/pigment_data.h \
  $${MAIN_PATH}/color_bar_abstract.h \
  $${MAIN_PATH}/color_bar_interpolation.h \
  $${MAIN_PATH}/color_bar_sections.h \
  $${MAIN_PATH}/button_icon.h \
  $${MAIN_PATH}/button_color_simple.h \
  $${MAIN_PATH}/dialog_create_palette.h \
  $${MAIN_PATH}/pure_color_bar.h \
  $${MAIN_PATH}/dialog_pure_color.h \
  $${MAIN_PATH}/table.h \
  $${MAIN_PATH}/table_layers.h \
  $${MAIN_PATH}/table_active_positions.h \
  $${MAIN_PATH}/shaders.h \
  $${MAIN_PATH}/glwidget.h \
  $${MAIN_PATH}/image_IO.h \
  $${MAIN_PATH}/layer_data.h \
  $${MAIN_PATH}/line_edit.h \
  $${MAIN_PATH}/layer.h \
  $${MAIN_PATH}/layer_basic.h \
  #
  $${MAIN_PATH}/layer_map.h \
  $${MAIN_PATH}/layer_map_distance.h \
  $${MAIN_PATH}/layer_map_triangulation.h \
  $${MAIN_PATH}/layer_map_rbf_interpolation.h \
  $${MAIN_PATH}/layer_positions.h \
  $${MAIN_PATH}/palette_data.h \
  $${MAIN_PATH}/element_data.h \
  $${MAIN_PATH}/project_data_csv.h \
  #
  $${FILE_IO_PATH}/file_io.h \
  $${FILE_IO_PATH}/file_project_data_csv.h \
  $${FILE_IO_PATH}/file_elements_csv.h \
  $${FILE_IO_PATH}/file_positions_txt.h \
  $${FILE_IO_PATH}/file_info_txt.h \
  $${FILE_IO_PATH}/file_interpreted_csv.h \
  #
  $${MAIN_PATH}/w_color_bar.h \
  $${MAIN_PATH}/w_tab.h \
  $${MAIN_PATH}/w_options.h \
  $${MAIN_PATH}/splitter_handle.h \
  $${MAIN_PATH}/splitter.h \
  $${MAIN_PATH}/images_tab.h \
  $${MAIN_PATH}/delaunay.h \
  $${RBF_PATH}/new_rbf_interpolation_2d.h \
  $${MAIN_PATH}/vertex.h \
  $${MAIN_PATH}/window.h

SOURCES += \
  $${MAIN_PATH}/color_map.cc \
  $${COMMON_CLASSES_PATH}/project_data.cc \
  $${COMMON_CLASSES_PATH}/data_io.cc \
  $${COMMON_CLASSES_PATH}/w_directory.cc \
  $${MAIN_PATH}/pigment_data.cc \
  $${MAIN_PATH}/color_bar_abstract.cc \
  $${MAIN_PATH}/color_bar_interpolation.cc \
  $${MAIN_PATH}/color_bar_sections.cc \
  $${MAIN_PATH}/button_icon.cc \
  $${MAIN_PATH}/button_color_simple.cc \
  $${MAIN_PATH}/dialog_create_palette.cc \
  $${MAIN_PATH}/pure_color_bar.cc \
  $${MAIN_PATH}/dialog_pure_color.cc \
  $${MAIN_PATH}/table.cc \
  $${MAIN_PATH}/table_layers.cc \
  $${MAIN_PATH}/table_active_positions.cc \
  $${MAIN_PATH}/shaders.cc \
  $${MAIN_PATH}/glwidget.cc \
  $${MAIN_PATH}/layer_data.cc \
  $${MAIN_PATH}/image_IO.cc \
  $${MAIN_PATH}/line_edit.cc \
  $${MAIN_PATH}/layer.cc \
  $${MAIN_PATH}/layer_basic.cc \
  $${MAIN_PATH}/layer_map.cc \
  $${MAIN_PATH}/layer_map_distance.cc \
  $${MAIN_PATH}/layer_map_triangulation.cc \
  $${MAIN_PATH}/layer_map_rbf_interpolation.cc \
  $${MAIN_PATH}/layer_positions.cc \
  $${MAIN_PATH}/palette_data.cc \
  #
  $${FILE_IO_PATH}/file_io.cc \
  $${FILE_IO_PATH}/file_project_data_csv.cc \
  $${FILE_IO_PATH}/file_elements_csv.cc \
  $${FILE_IO_PATH}/file_positions_txt.cc \
  $${FILE_IO_PATH}/file_info_txt.cc \
  $${FILE_IO_PATH}/file_interpreted_csv.cc \
  #
  $${MAIN_PATH}/w_color_bar.cc \
  $${MAIN_PATH}/w_tab.cc \
  $${MAIN_PATH}/w_options.cc \
  $${MAIN_PATH}/splitter_handle.cc \
  $${MAIN_PATH}/splitter.cc \
  $${MAIN_PATH}/images_tab.cc \
  $${MAIN_PATH}/delaunay.cc \
  $${MAIN_PATH}/window.cc \
  $${RBF_PATH}/new_rbf_interpolation_2d.cc \
  $${MAIN_PATH}/main.cc



!linux {
TARGET= XMapsLab

INCLUDEPATH += "$${WINDOWS_PATH}\OPENCV460X64\OPENCV\BUILD\INCLUDE"
INCLUDEPATH += "$${WINDOWS_PATH}\OPENCV460X64\OPENCV\BUILD\INCLUDE\OPENCV2"
INCLUDEPATH += "$${WINDOWS_PATH}\OPENCV460X64\OPENCV\BUILD\INCLUDE\OPENCV"
INCLUDEPATH += "$${WINDOWS_PATH}\GLEW\INCLUDE"

INCLUDEPATH += $${MAIN_PATH}
INCLUDEPATH +=$${FILE_IO_PATH}
INCLUDEPATH +=$${COMMON_CLASSES_PATH}
INCLUDEPATH +=$${RBF_PATH}
INCLUDEPATH +=$${SHADERS_PATH}

INCLUDEPATH += "$${WINDOWS_PATH}\EIGEN"

LIBS += -lopengl32 -L"$${WINDOWS_PATH}\OPENCV460X64\OPENCV\BUILD\X64\VC14\LIB" -lopencv_world460 -L"$${WINDOWS_PATH}\GLEW\LIB\RELEASE\X64" -lglew32
}

linux {

TARGET= xmapslab

INCLUDEPATH += $${LINUX_PATH}/opencv-4.6.0/include/opencv4
INCLUDEPATH += $${LINUX_PATH}/opencv-4.6.0/include/opencv4/opencv2

INCLUDEPATH += $${LINUX_PATH}/glew-2.1.0/include

INCLUDEPATH += $${MAIN_PATH}
INCLUDEPATH +=$${FILE_IO_PATH}
INCLUDEPATH +=$${COMMON_CLASSES_PATH}
INCLUDEPATH +=$${RBF_PATH}
INCLUDEPATH +=$${SHADERS_PATH}

INCLUDEPATH += $${LINUX_PATH}/Eigen

LIBS += \
    -L$${LINUX_PATH}/glew-2.1.0/lib -lGLEW \
    -L$${LINUX_PATH}/opencv-4.6.0/lib -lopencv_core -lopencv_highgui \
    -lopencv_imgproc -lopencv_imgcodecs \
    -lGL
}

DESTDIR=.
OBJECTS_DIR=src/temp
MOC_DIR=src/moc_dir
RCC_DIR=src/resources_dir

CONFIG += c++14
QT += widgets opengl openglwidgets charts

RESOURCES += \
    $${MAIN_PATH}/resources.qrc
