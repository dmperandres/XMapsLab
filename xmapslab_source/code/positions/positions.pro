DEFINES+=LINUX
#DEFINES+=WINDOWS

# PATHS
LINUX_PATH=/home/dmartin/codigo/funciontecas
WINDOWS_PATH=C:\CODIGO\

MAIN_PATH=src/main
FILE_IO_PATH=../common/file_io
COMMON_CLASSES_PATH=../common/common_classes
RBF_PATH=src/rbf
SHADERS_PATH=../common

# XRD

HEADERS += \
  $${MAIN_PATH}/palette_data.h \
  $${MAIN_PATH}/button_color_simple.h \
  $${COMMON_CLASSES_PATH}/common.h \
  $${COMMON_CLASSES_PATH}/common_window.h \
  $${COMMON_CLASSES_PATH}/data_io.h \
  $${COMMON_CLASSES_PATH}/project_data.h \
  $${COMMON_CLASSES_PATH}/data_xrf.h \
  $${COMMON_CLASSES_PATH}/w_directory.h \
  $${MAIN_PATH}/pure_color_bar.h \
  $${MAIN_PATH}/dialog_pure_color.h \
  $${MAIN_PATH}/map_list.h \
  $${MAIN_PATH}/shaders.h \
  $${MAIN_PATH}/glwidget.h \
  $${MAIN_PATH}/image_IO.h \
  $${MAIN_PATH}/layer_data.h \
  $${MAIN_PATH}/line_edit.h \
  $${MAIN_PATH}/layer.h \
  $${MAIN_PATH}/layer_basic.h \
  $${MAIN_PATH}/layer_positions.h \
  $${MAIN_PATH}/dialog_num_samples.h \
  $${MAIN_PATH}/w_options.h \
  $${MAIN_PATH}/w_number.h \
  $${MAIN_PATH}/splitter_handle.h \
  $${MAIN_PATH}/splitter.h \
  $${COMMON_CLASSES_PATH}/project_data.h \
  $${FILE_IO_PATH}/file_io.h \
  $${FILE_IO_PATH}/file_positions_txt.h \
  $${FILE_IO_PATH}/file_info_txt.h \
  $${FILE_IO_PATH}/file_project_data_csv.h \
  $${FILE_IO_PATH}/file_elements_csv.h \
  $${FILE_IO_PATH}/file_interpreted_csv.h \
  #
  $${MAIN_PATH}/table_positions.h \
  $${MAIN_PATH}/vertex.h \
  $${MAIN_PATH}/window.h

SOURCES += \
  $${COMMON_CLASSES_PATH}/project_data.cc \
  $${COMMON_CLASSES_PATH}/data_io.cc \
  $${COMMON_CLASSES_PATH}/w_directory.cc \
  $${MAIN_PATH}/button_color_simple.cc \
  $${MAIN_PATH}/pure_color_bar.cc \
  $${MAIN_PATH}/dialog_pure_color.cc \
  $${MAIN_PATH}/shaders.cc \
  $${MAIN_PATH}/main.cc \
  $${MAIN_PATH}/glwidget.cc \
  $${MAIN_PATH}/layer_data.cc \
  $${MAIN_PATH}/image_IO.cc \
  $${MAIN_PATH}/line_edit.cc \
  $${MAIN_PATH}/layer.cc \
  $${MAIN_PATH}/layer_basic.cc \
  $${MAIN_PATH}/layer_positions.cc \
  $${MAIN_PATH}/w_options.cc \
  $${MAIN_PATH}/w_number.cc \
  $${MAIN_PATH}/dialog_num_samples.cc \
  $${MAIN_PATH}/splitter_handle.cc \
  $${MAIN_PATH}/splitter.cc \
  $${FILE_IO_PATH}/file_io.cc \
  $${FILE_IO_PATH}/file_positions_txt.cc \
  $${FILE_IO_PATH}/file_info_txt.cc \
  $${FILE_IO_PATH}/file_project_data_csv.cc \
  $${FILE_IO_PATH}/file_elements_csv.cc \
  $${FILE_IO_PATH}/file_interpreted_csv.cc \
  #
  $${MAIN_PATH}/table_positions.cc \
  $${MAIN_PATH}/window.cc

!linux {
TARGET=Positions

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
TARGET=positions

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
QT += widgets opengl openglwidgets

RESOURCES += \
    $${MAIN_PATH}/resources.qrc
