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


HEADERS += \
  $${COMMON_CLASSES_PATH}/project_data.h \
  $${COMMON_CLASSES_PATH}/common.h \
  $${COMMON_CLASSES_PATH}/common_window.h \
  $${COMMON_CLASSES_PATH}/data_xrf.h \
  $${COMMON_CLASSES_PATH}/data_xrd.h \
  $${COMMON_CLASSES_PATH}/data_io.h \
  $${COMMON_CLASSES_PATH}/w_directory.h \
  #
  $${FILE_IO_PATH}/file_io.h \
  $${FILE_IO_PATH}/file_project_data_csv.h \
  $${FILE_IO_PATH}/file_elements_csv.h \
  $${FILE_IO_PATH}/file_positions_txt.h \
  $${FILE_IO_PATH}/file_info_txt.h \
  $${FILE_IO_PATH}/file_xrf_txt.h \
  $${FILE_IO_PATH}/file_ka_uxd.h \
  $${FILE_IO_PATH}/file_interpreted_csv.h \
  #
  $${MAIN_PATH}/element_data.h \
  $${MAIN_PATH}/w_int_file_parameters.h \
  $${MAIN_PATH}/w_project.h \
  $${MAIN_PATH}/w_image.h \
  $${MAIN_PATH}/w_files.h \
  $${MAIN_PATH}/w_table.h \
  $${MAIN_PATH}/window.h

SOURCES += \
  $${COMMON_CLASSES_PATH}/data_io.cc \
  $${COMMON_CLASSES_PATH}/w_directory.cc \
  #
  $${FILE_IO_PATH}/file_io.cc \
  $${FILE_IO_PATH}/file_project_data_csv.cc \
  $${FILE_IO_PATH}/file_elements_csv.cc \
  $${FILE_IO_PATH}/file_positions_txt.cc \
  $${FILE_IO_PATH}/file_info_txt.cc \
  $${FILE_IO_PATH}/file_xrf_txt.cc \
  $${FILE_IO_PATH}/file_ka_uxd.cc \
  $${FILE_IO_PATH}/file_interpreted_csv.cc \
  #
  $${MAIN_PATH}/w_int_file_parameters.cc \
  $${MAIN_PATH}/w_project.cc \
  $${MAIN_PATH}/w_image.cc \
  $${MAIN_PATH}/w_files.cc \
  $${MAIN_PATH}/w_table.cc \
  $${MAIN_PATH}/window.cc \
  $${MAIN_PATH}/main.cc

!linux {
TARGET=Tools

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
TARGET=tools

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
QT += widgets

RESOURCES += \
    $${MAIN_PATH}/resources.qrc
