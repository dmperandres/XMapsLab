DEFINES+=LINUX
#DEFINES+=WINDOWS

CONFIG+=POSITIONS

# PATHS
LINUX_PATH=/home/dmartin/codigo/funciontecas
WINDOWS_PATH=C:\CODIGO\

POSITIONS_PATH=positions_src

FILE_IO_PATH=$${POSITIONS_PATH}/common/file_io
COMMON_CLASSES_PATH=$${POSITIONS_PATH}/common/common_classes
SHADERS_PATH=$${POSITIONS_PATH}/common/shaders

# COMMON
HEADERS += \
  $${COMMON_CLASSES_PATH}/common.h \
  $${COMMON_CLASSES_PATH}/common_window.h \
  $${COMMON_CLASSES_PATH}/common_interpreter.h \
  $${COMMON_CLASSES_PATH}/data_io.h \
  $${COMMON_CLASSES_PATH}/data_xrf.h \
  $${COMMON_CLASSES_PATH}/data_xrd.h \
  $${COMMON_CLASSES_PATH}/project_data.h \
  $${COMMON_CLASSES_PATH}/vertex.h \
  $${COMMON_CLASSES_PATH}/atomic_data.h \
  $${COMMON_CLASSES_PATH}/w_directory.h \
  $${COMMON_CLASSES_PATH}/button_icon.h \
  $${COMMON_CLASSES_PATH}/button_color_simple.h \
  $${COMMON_CLASSES_PATH}/pure_color_bar.h \
  $${COMMON_CLASSES_PATH}/dialog_pure_color.h \
  $${COMMON_CLASSES_PATH}/table.h \
  $${COMMON_CLASSES_PATH}/palette_data.h \
  $${COMMON_CLASSES_PATH}/color_map.h \
  $${COMMON_CLASSES_PATH}/shaders.h \
  $${COMMON_CLASSES_PATH}/splitter_handle.h \
  $${COMMON_CLASSES_PATH}/splitter.h \
  $${COMMON_CLASSES_PATH}/image_IO.h \
  $${COMMON_CLASSES_PATH}/map_list.h \
  $${COMMON_CLASSES_PATH}/best_color.h \
  $${COMMON_CLASSES_PATH}/tokenizer.h \


SOURCES += \
  $${COMMON_CLASSES_PATH}/project_data.cc \
  $${COMMON_CLASSES_PATH}/data_io.cc \
  $${COMMON_CLASSES_PATH}/w_directory.cc \
  $${COMMON_CLASSES_PATH}/button_icon.cc \
  $${COMMON_CLASSES_PATH}/button_color_simple.cc \
  $${COMMON_CLASSES_PATH}/pure_color_bar.cc \
  $${COMMON_CLASSES_PATH}/dialog_pure_color.cc \
  $${COMMON_CLASSES_PATH}/table.cc \
  $${COMMON_CLASSES_PATH}/palette_data.cc \
  $${COMMON_CLASSES_PATH}/color_map.cc \
  $${COMMON_CLASSES_PATH}/shaders.cc \
  $${COMMON_CLASSES_PATH}/splitter_handle.cc \
  $${COMMON_CLASSES_PATH}/splitter.cc \
  $${COMMON_CLASSES_PATH}/image_IO.cc \
  $${COMMON_CLASSES_PATH}/best_color.cc \
  $${COMMON_CLASSES_PATH}/tokenizer.cc \

# FILE_IO
HEADERS += \
  $${FILE_IO_PATH}/file_io.h \
  $${FILE_IO_PATH}/file_project_data_csv.h \
  # $${FILE_IO_PATH}/file_elements_csv.h \
  # $${FILE_IO_PATH}/file_interpreted_csv.h \
  # $${FILE_IO_PATH}/file_xrf_artax.h \
  # $${FILE_IO_PATH}/file_xrf_xy.h \
  # $${FILE_IO_PATH}/file_compound_combination_csv.h \
  # $${FILE_IO_PATH}/file_interpreter_user_selections_csv.h \
  $${FILE_IO_PATH}/file_positions_csv.h \
  $${FILE_IO_PATH}/file_color_map_csv.h \

SOURCES += \
  $${FILE_IO_PATH}/file_io.cc \
  $${FILE_IO_PATH}/file_project_data_csv.cc \
  # $${FILE_IO_PATH}/file_interpreted_csv.cc \
  # $${FILE_IO_PATH}/file_xrf_artax.cc \
  # $${FILE_IO_PATH}/file_xrf_xy.cc \
  # $${FILE_IO_PATH}/file_elements_csv.cc \
  # $${FILE_IO_PATH}/file_xrf_process_info_csv.cc \
  # $${FILE_IO_PATH}/file_compound_combination_csv.cc \
  # $${FILE_IO_PATH}/file_interpreter_user_selections_csv.cc \
  $${FILE_IO_PATH}/file_positions_csv.cc \
  $${FILE_IO_PATH}/file_color_map_csv.cc \


############
POSITIONS {

HEADERS += \
  $${POSITIONS_PATH}/glwidget_positions.h \
  $${POSITIONS_PATH}/layer_data_positions.h \
  $${POSITIONS_PATH}/layer_positions.h \
  $${POSITIONS_PATH}/layer_basic_positions.h \
  $${POSITIONS_PATH}/layer_positions_positions.h \
  $${POSITIONS_PATH}/dialog_num_samples.h \
  $${POSITIONS_PATH}/w_options_positions.h \
  $${POSITIONS_PATH}/w_number.h \
  #
  $${POSITIONS_PATH}/table_positions.h \
  $${POSITIONS_PATH}/window_positions.h \

SOURCES += \
  $${POSITIONS_PATH}/glwidget_positions.cc \
  $${POSITIONS_PATH}/layer_data_positions.cc \
  $${POSITIONS_PATH}/layer_positions.cc \
  $${POSITIONS_PATH}/layer_basic_positions.cc \
  $${POSITIONS_PATH}/layer_positions_positions.cc \
  $${POSITIONS_PATH}/w_options_positions.cc \
  $${POSITIONS_PATH}/w_number.cc \
  $${POSITIONS_PATH}/dialog_num_samples.cc \
  #
  $${POSITIONS_PATH}/table_positions.cc \
  $${POSITIONS_PATH}/window_positions.cc \
  $${POSITIONS_PATH}/main.cc \


 RESOURCES += \
   $${POSITIONS_PATH}/resources_positions.qrc
}


!linux {
  TARGET= Positions

  INCLUDEPATH += "$${WINDOWS_PATH}\OPENCV460X64\OPENCV\BUILD\INCLUDE"
  INCLUDEPATH += "$${WINDOWS_PATH}\OPENCV460X64\OPENCV\BUILD\INCLUDE\OPENCV2"
  INCLUDEPATH += "$${WINDOWS_PATH}\OPENCV460X64\OPENCV\BUILD\INCLUDE\OPENCV"
  INCLUDEPATH += "$${WINDOWS_PATH}\GLEW\INCLUDE"

  INCLUDEPATH += $${POSITIONS_PATH}

  INCLUDEPATH +=$${FILE_IO_PATH}
  INCLUDEPATH +=$${COMMON_CLASSES_PATH}
  INCLUDEPATH +=$${SHADERS_PATH}

  # INCLUDEPATH += "$${WINDOWS_PATH}\EIGEN"

  LIBS += -lopengl32 -L"$${WINDOWS_PATH}\OPENCV460X64\OPENCV\BUILD\X64\VC14\LIB" -lopencv_world460 -L"$${WINDOWS_PATH}\GLEW\LIB\RELEASE\X64" -lglew32
}

linux {
  TARGET= positions

  INCLUDEPATH += $${LINUX_PATH}/opencv-4.6.0/include/opencv4
  INCLUDEPATH += $${LINUX_PATH}/opencv-4.6.0/include/opencv4/opencv2

  INCLUDEPATH += $${LINUX_PATH}/glew-2.1.0/include

  INCLUDEPATH += $${POSITIONS_PATH}

  INCLUDEPATH +=$${FILE_IO_PATH}
  INCLUDEPATH +=$${COMMON_CLASSES_PATH}
  INCLUDEPATH +=$${SHADERS_PATH}

  # INCLUDEPATH += $${LINUX_PATH}/Eigen

  LIBS += \
      -L$${LINUX_PATH}/glew-2.1.0/lib -lGLEW \
      -L$${LINUX_PATH}/opencv-4.6.0/lib -lopencv_core -lopencv_highgui \
      -lopencv_imgproc -lopencv_imgcodecs \
      -lGL
}

DESTDIR=.
OBJECTS_DIR=temp
MOC_DIR=moc_res_dir
RCC_DIR=moc_res_dir

CONFIG += c++14
QT += widgets opengl openglwidgets printsupport charts


