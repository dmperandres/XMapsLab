DEFINES+=LINUX
#DEFINES+=WINDOWS


CONFIG+=XMAPSLAB

# DEFINES+=GC
#DEFINES+=DEBUG_XML

# PATHS
LINUX_PATH=/home/dmartin/codigo/funciontecas
WINDOWS_PATH=C:\CODIGO\

#
XMAPSLAB_PATH=xmapslab_src
RBF_PATH=$${XMAPSLAB_PATH}/rbf

FILE_IO_PATH=$${XMAPSLAB_PATH}/common/file_io
COMMON_CLASSES_PATH=$${XMAPSLAB_PATH}/common/common_classes
SHADERS_PATH=$${XMAPSLAB_PATH}/common/shaders


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
  $${FILE_IO_PATH}/file_elements_csv.h \
  $${FILE_IO_PATH}/file_interpreted_csv.h \
  $${FILE_IO_PATH}/file_xrf_artax.h \
  $${FILE_IO_PATH}/file_xrf_xy.h \
  $${FILE_IO_PATH}/file_compound_combination_csv.h \
  $${FILE_IO_PATH}/file_interpreter_user_selections_csv.h \
  $${FILE_IO_PATH}/file_positions_csv.h \
  $${FILE_IO_PATH}/file_color_map_csv.h \

SOURCES += \
  $${FILE_IO_PATH}/file_io.cc \
  $${FILE_IO_PATH}/file_project_data_csv.cc \
  $${FILE_IO_PATH}/file_interpreted_csv.cc \
  $${FILE_IO_PATH}/file_xrf_artax.cc \
  $${FILE_IO_PATH}/file_xrf_xy.cc \
  $${FILE_IO_PATH}/file_elements_csv.cc \
  $${FILE_IO_PATH}/file_xrf_process_info_csv.cc \
  $${FILE_IO_PATH}/file_compound_combination_csv.cc \
  $${FILE_IO_PATH}/file_interpreter_user_selections_csv.cc \
  $${FILE_IO_PATH}/file_positions_csv.cc \
  $${FILE_IO_PATH}/file_color_map_csv.cc \


#################
XMAPSLAB {

  CONFIG+=LAYERS_EDGES_ACTIVE
  # CONFIG+=COMPOUNDS_FROM_ELEMENTS_ACTIVE

  CONFIG+=STATISTIC_GRAPHS_ACTIVE
  CONFIG+=NODE_EDITOR_ACTIVE
  #CONFIG+=MODE_3D_ACTIVE

  DEFINES+=YES_LAYERS_EDGES_DOG

  # Node editor
  NODE_EDITOR_ACTIVE {
    DEFINES+=NODE_EDITOR_ACTIVE

    HEADERS += \
    $${XMAPSLAB_PATH}/ne_common.h \
    $${XMAPSLAB_PATH}/ne_block.h \
    $${XMAPSLAB_PATH}/ne_port.h \
    $${XMAPSLAB_PATH}/ne_connection.h \
    $${XMAPSLAB_PATH}/nodes_editor.h \
    $${XMAPSLAB_PATH}/graphics_view.h \
    $${XMAPSLAB_PATH}/graphics_scene.h \
    $${XMAPSLAB_PATH}/glwidget_xmapslab_ge.h \
    $${XMAPSLAB_PATH}/tree_widget.h \
    $${XMAPSLAB_PATH}/tree_widget_item.h \
    $${XMAPSLAB_PATH}/filter.h \
    $${XMAPSLAB_PATH}/filters_tab.h

    SOURCES += \
    $${XMAPSLAB_PATH}/ne_block.cc \
    $${XMAPSLAB_PATH}/ne_port.cc \
    $${XMAPSLAB_PATH}/ne_connection.cc \
    $${XMAPSLAB_PATH}/nodes_editor.cc \
    $${XMAPSLAB_PATH}/graphics_view.cc \
    $${XMAPSLAB_PATH}/graphics_scene.cc \
    $${XMAPSLAB_PATH}/glwidget_xmapslab_ge.cc \
    $${XMAPSLAB_PATH}/tree_widget.cc \
    $${XMAPSLAB_PATH}/tree_widget_item.cc \
    $${XMAPSLAB_PATH}/filter.cc \
    $${XMAPSLAB_PATH}/filters_tab.cc

    DEFINES+=DEFINE_FILTER_IMAGE
    CONFIG+=DEFINE_FILTER_IMAGE

    DEFINES+=DEFINE_FILTER_ELEMENT
    CONFIG+=DEFINE_FILTER_ELEMENT

    DEFINES+= DEFINE_FILTER_LOGIC_AND
    CONFIG+=DEFINE_FILTER_LOGIC_AND

    DEFINES+= DEFINE_FILTER_LOGIC_OR
    CONFIG+=DEFINE_FILTER_LOGIC_OR

    DEFINES+= DEFINE_FILTER_LOGIC_XOR
    CONFIG+=DEFINE_FILTER_LOGIC_XOR

    DEFINES+= DEFINE_FILTER_LOGIC_NOT
    CONFIG+=DEFINE_FILTER_LOGIC_NOT

    DEFINES+= DEFINE_FILTER_CONVERSION_BIN
    CONFIG+=DEFINE_FILTER_CONVERSION_BIN

    DEFINES+= DEFINE_FILTER_CONVERSION_COLOR_BIN
    CONFIG+=DEFINE_FILTER_CONVERSION_COLOR_BIN

    #DEFINES+= DEFINE_FILTER_ARITHMETIC_PRODUCT
    #CONFIG+=DEFINE_FILTER_ARITHMETIC_PRODUCT

    #DEFINES+= DEFINE_FILTER_ARITHMETIC_ADDITION
    #CONFIG+=DEFINE_FILTER_ARITHMETIC_ADDITION

    DEFINES+= DEFINE_FILTER_COMBINATION_ELEMENT
    CONFIG+=DEFINE_FILTER_COMBINATION_ELEMENT

    DEFINES+= DEFINE_FILTER_COMBINATION_PRODUCT
    CONFIG+=DEFINE_FILTER_COMBINATION_PRODUCT

    DEFINES+= DEFINE_FILTER_COMBINATION_ADDITION
    CONFIG+=DEFINE_FILTER_COMBINATION_ADDITION

    DEFINES+= DEFINE_FILTER_COMBINATION_DIFFERENCE
    CONFIG+=DEFINE_FILTER_COMBINATION_DIFFERENCE

    DEFINES+= DEFINE_FILTER_COMBINATION_ADDITION_PERCENTAGE
    CONFIG+=DEFINE_FILTER_COMBINATION_ADDITION_PERCENTAGE

    DEFINES+= DEFINE_FILTER_COMBINATION_ELEMENT_REMOVE
    CONFIG+= DEFINE_FILTER_COMBINATION_ELEMENT_REMOVE

    # DEFINES+= DEFINE_FILTER_COLORMAP
    # CONFIG+=DEFINE_FILTER_COLORMAP

    DEFINE_FILTER_IMAGE::HEADERS+=$${XMAPSLAB_PATH}/filter_image.h
    DEFINE_FILTER_IMAGE::SOURCES+=$${XMAPSLAB_PATH}/filter_image.cc

    DEFINE_FILTER_ELEMENT::HEADERS+=$${XMAPSLAB_PATH}/filter_element.h
    DEFINE_FILTER_ELEMENT::SOURCES+=$${XMAPSLAB_PATH}/filter_element.cc

    DEFINE_FILTER_LOGIC_AND:HEADERS+=$${XMAPSLAB_PATH}/filter_logic_and.h
    DEFINE_FILTER_LOGIC_AND:SOURCES+=$${XMAPSLAB_PATH}/filter_logic_and.cc

    DEFINE_FILTER_LOGIC_AND:HEADERS+=$${XMAPSLAB_PATH}/filter_logic_or.h
    DEFINE_FILTER_LOGIC_AND:SOURCES+=$${XMAPSLAB_PATH}/filter_logic_or.cc

    DEFINE_FILTER_LOGIC_XOR:HEADERS+=$${XMAPSLAB_PATH}/filter_logic_xor.h
    DEFINE_FILTER_LOGIC_XOR:SOURCES+=$${XMAPSLAB_PATH}/filter_logic_xor.cc

    DEFINE_FILTER_LOGIC_NOT:HEADERS+=$${XMAPSLAB_PATH}/filter_logic_not.h
    DEFINE_FILTER_LOGIC_NOT:SOURCES+=$${XMAPSLAB_PATH}/filter_logic_not.cc

    DEFINE_FILTER_CONVERSION_BIN:HEADERS+=$${XMAPSLAB_PATH}/filter_conversion_bin.h
    DEFINE_FILTER_CONVERSION_BIN:SOURCES+=$${XMAPSLAB_PATH}/filter_conversion_bin.cc

    DEFINE_FILTER_CONVERSION_COLOR_BIN:HEADERS+=$${XMAPSLAB_PATH}/filter_conversion_color_bin.h
    DEFINE_FILTER_CONVERSION_COLOR_BIN:SOURCES+=$${XMAPSLAB_PATH}/filter_conversion_color_bin.cc

    # DEFINE_FILTER_ARITHMETIC_PRODUCT:HEADERS+=$${XMAPSLAB_PATH}/filter_arithmetic_product.h
    # DEFINE_FILTER_ARITHMETIC_PRODUCT:SOURCES+=$${XMAPSLAB_PATH}/filter_arithmetic_product.cc

    # DEFINE_FILTER_ARITHMETIC_ADDITION:HEADERS+=$${XMAPSLAB_PATH}/filter_arithmetic_addition.h
    # DEFINE_FILTER_ARITHMETIC_ADDITION:SOURCES+=$${XMAPSLAB_PATH}/filter_arithmetic_addition.cc

    DEFINE_FILTER_COMBINATION_ELEMENT:HEADERS+=$${XMAPSLAB_PATH}/filter_combination_element.h
    DEFINE_FILTER_COMBINATION_ELEMENT:SOURCES+=$${XMAPSLAB_PATH}/filter_combination_element.cc

    DEFINE_FILTER_COMBINATION_PRODUCT:HEADERS+=$${XMAPSLAB_PATH}/filter_combination_product.h
    DEFINE_FILTER_COMBINATION_PRODUCT:SOURCES+=$${XMAPSLAB_PATH}/filter_combination_product.cc

    DEFINE_FILTER_COMBINATION_ADDITION:HEADERS+=$${XMAPSLAB_PATH}/filter_combination_addition.h
    DEFINE_FILTER_COMBINATION_ADDITION:SOURCES+=$${XMAPSLAB_PATH}/filter_combination_addition.cc

    DEFINE_FILTER_COMBINATION_DIFFERENCE:HEADERS+=$${XMAPSLAB_PATH}/filter_combination_difference.h
    DEFINE_FILTER_COMBINATION_DIFFERENCE:SOURCES+=$${XMAPSLAB_PATH}/filter_combination_difference.cc

    DEFINE_FILTER_COMBINATION_ADDITION_PERCENTAGE:HEADERS+=$${XMAPSLAB_PATH}/filter_combination_addition_percentage.h
    DEFINE_FILTER_COMBINATION_ADDITION_PERCENTAGE:SOURCES+=$${XMAPSLAB_PATH}/filter_combination_addition_percentage.cc


    # DEFINE_FILTER_COMBINATION_ADDITION_REMOVE:HEADERS+=$${XMAPSLAB_PATH}/filter_combination_addition_remove.h
    # DEFINE_FILTER_COMBINATION_ADDITION_REMOVE:SOURCES+=$${XMAPSLAB_PATH}/filter_combination_addition_remove.cc

    DEFINE_FILTER_COMBINATION_ELEMENT_REMOVE:HEADERS+=$${XMAPSLAB_PATH}/filter_combination_element_remove.h
    DEFINE_FILTER_COMBINATION_ELEMENT_REMOVE:SOURCES+=$${XMAPSLAB_PATH}/filter_combination_element_remove.cc

    # DEFINE_FILTER_COLORMAP:HEADERS+=$${XMAPSLAB_PATH}/filter_colormap.h
    # DEFINE_FILTER_COLORMAP:SOURCES+=$${XMAPSLAB_PATH}/filter_colormap.cc

  }else{

  }

  # 3D_MODE
  MODE_3D_ACTIVE {
    DEFINES+=MODE_3D_ACTIVE

    HEADERS += \
    $${XMAPSLAB_PATH}/object3D.h \
    $${XMAPSLAB_PATH}/board.h \
    $${XMAPSLAB_PATH}/object3D_wire.h \
    $${XMAPSLAB_PATH}/bounding_box.h \
    $${XMAPSLAB_PATH}/cube.h \
    $${XMAPSLAB_PATH}/board_cubes.h \
    $${XMAPSLAB_PATH}/glwidget_xmapslab_3D.h

    SOURCES += \
    $${XMAPSLAB_PATH}/object3D.cc \
    $${XMAPSLAB_PATH}/board.cc \
    $${XMAPSLAB_PATH}/object3D_wire.cc \
    $${XMAPSLAB_PATH}/bounding_box.cc \
    $${XMAPSLAB_PATH}/cube.cc \
    $${XMAPSLAB_PATH}/board_cubes.cc \
    $${XMAPSLAB_PATH}/glwidget_xmapslab_3D.cc

  }else{

  }

  # Special layers
  LAYERS_EDGES_ACTIVE {

    DEFINES+=LAYERS_EDGES_ACTIVE

    HEADERS += \
  #  $${XMAPSLAB_PATH}/layer_canny.h \
  #  $${XMAPSLAB_PATH}/layer_kang.h \
  #  $${XMAPSLAB_PATH}/layer_kmeans.h \
    $${XMAPSLAB_PATH}/layer_dog.h


    SOURCES += \
  #  $${XMAPSLAB_PATH}/layer_canny.cc \
  #  $${XMAPSLAB_PATH}/layer_kang.cc \
  #  $${XMAPSLAB_PATH}/layer_kmeans.cc \
    $${XMAPSLAB_PATH}/layer_dog.cc

  }else{

  }

  # Compounds from elements
  COMPOUNDS_FROM_ELEMENTS_ACTIVE {
    DEFINES+=COMPOUNDS_FROM_ELEMENTS_ACTIVE

    HEADERS += \
    $${XMAPSLAB_PATH}/layer_compound_from_elements.h

    SOURCES += \
    $${XMAPSLAB_PATH}/layer_compound_from_elements.cc

  }else{

  }

  # Statistic graphs
  STATISTIC_GRAPHS_ACTIVE {
    DEFINES+=STATISTIC_GRAPHS_ACTIVE

  }else{

  }

  # XRD
  XRD_ACTIVE {
    DEFINES+=XRD_ACTIVE
    DEFINES+=SPECTRAL_MODE_ACTIVE
    DEFINES+=ASTM_MODE_ACTIVE

  }else{

  }


HEADERS += \
  $${XMAPSLAB_PATH}/atomic_data.h \
  $${XMAPSLAB_PATH}/measurement_data.h \
  $${XMAPSLAB_PATH}/color_bar_abstract.h \
  $${XMAPSLAB_PATH}/color_bar_interpolation.h \
  $${XMAPSLAB_PATH}/color_bar_sections.h \
  $${XMAPSLAB_PATH}/table_layers.h \
  $${XMAPSLAB_PATH}/table_active_positions.h \
  $${XMAPSLAB_PATH}/glwidget_xmapslab.h \
  $${XMAPSLAB_PATH}/layer_data_xmapslab.h \
  #
  $${XMAPSLAB_PATH}/layer_xmapslab.h \
  $${XMAPSLAB_PATH}/layer_basic_xmapslab.h \
  $${XMAPSLAB_PATH}/layer_map.h \
  $${XMAPSLAB_PATH}/layer_map_distance.h \
  $${XMAPSLAB_PATH}/layer_map_triangulation.h \
  $${XMAPSLAB_PATH}/layer_map_rbf_interpolation.h \
  $${XMAPSLAB_PATH}/layer_map_rbf_interpolation_plus.h \
  $${XMAPSLAB_PATH}/layer_positions_xmapslab.h \
  $${XMAPSLAB_PATH}/layer_map_lab.h \
  $${XMAPSLAB_PATH}/layer_map_mhd_segmentation.h \
  $${XMAPSLAB_PATH}/layer_map_value_segmentation.h \
  #
  $${XMAPSLAB_PATH}/project_data_csv.h \
  #
  $${XMAPSLAB_PATH}/w_color_bar.h \
  $${XMAPSLAB_PATH}/w_tab_xmapslab.h \
  $${XMAPSLAB_PATH}/w_options_xmapslab.h \
  $${XMAPSLAB_PATH}/w_image_section.h \
  $${XMAPSLAB_PATH}/w_options_image_section.h \
  $${XMAPSLAB_PATH}/nodes_editor_maps_tab.h \
  $${XMAPSLAB_PATH}/delaunay.h \
  $${RBF_PATH}/new_rbf_interpolation_2d.h \
  $${RBF_PATH}/new_rbf_interpolation_2d_plus.h \
  $${XMAPSLAB_PATH}/vertex.h \
  $${XMAPSLAB_PATH}/window_xmapslab.h \

SOURCES += \
  $${XMAPSLAB_PATH}/measurement_data.cc \
  $${XMAPSLAB_PATH}/color_bar_abstract.cc \
  $${XMAPSLAB_PATH}/color_bar_interpolation.cc \
  $${XMAPSLAB_PATH}/color_bar_sections.cc \
  $${XMAPSLAB_PATH}/table_layers.cc \
  $${XMAPSLAB_PATH}/table_active_positions.cc \
  $${XMAPSLAB_PATH}/glwidget_xmapslab.cc \
  $${XMAPSLAB_PATH}/layer_data_xmapslab.cc \
  #
  $${XMAPSLAB_PATH}/layer_xmapslab.cc \
  $${XMAPSLAB_PATH}/layer_basic_xmapslab.cc \
  $${XMAPSLAB_PATH}/layer_map.cc \
  $${XMAPSLAB_PATH}/layer_map_distance.cc \
  $${XMAPSLAB_PATH}/layer_map_triangulation.cc \
  $${XMAPSLAB_PATH}/layer_map_rbf_interpolation.cc \
  $${XMAPSLAB_PATH}/layer_map_rbf_interpolation_plus.cc \
  $${XMAPSLAB_PATH}/layer_positions_xmapslab.cc \
  $${XMAPSLAB_PATH}/layer_map_lab.cc \
  $${XMAPSLAB_PATH}/layer_map_mhd_segmentation.cc \
  $${XMAPSLAB_PATH}/layer_map_value_segmentation.cc \
  #
  $${XMAPSLAB_PATH}/w_color_bar.cc \
  $${XMAPSLAB_PATH}/w_tab_xmapslab.cc \
  $${XMAPSLAB_PATH}/w_options_xmapslab.cc \
  $${XMAPSLAB_PATH}/w_image_section.cc \
  $${XMAPSLAB_PATH}/w_options_image_section.cc \
  $${XMAPSLAB_PATH}/nodes_editor_maps_tab.cc \
  $${XMAPSLAB_PATH}/delaunay.cc \
  $${RBF_PATH}/new_rbf_interpolation_2d.cc \
  $${RBF_PATH}/new_rbf_interpolation_2d_plus.cc \
  $${XMAPSLAB_PATH}/window_xmapslab.cc \
  $${XMAPSLAB_PATH}/main.cc

  RESOURCES += \
      $${XMAPSLAB_PATH}/resources_xmapslab.qrc
}


!linux {
  TARGET= XMapsLab

  INCLUDEPATH += "$${WINDOWS_PATH}\OPENCV460X64\OPENCV\BUILD\INCLUDE"
  INCLUDEPATH += "$${WINDOWS_PATH}\OPENCV460X64\OPENCV\BUILD\INCLUDE\OPENCV2"
  INCLUDEPATH += "$${WINDOWS_PATH}\OPENCV460X64\OPENCV\BUILD\INCLUDE\OPENCV"
  INCLUDEPATH += "$${WINDOWS_PATH}\GLEW\INCLUDE"

  INCLUDEPATH += $${XMAPSLAB_PATH}

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

  INCLUDEPATH += $${XMAPSLAB_PATH}

  INCLUDEPATH +=$${FILE_IO_PATH}
  INCLUDEPATH +=$${COMMON_CLASSES_PATH}
  INCLUDEPATH +=$${SHADERS_PATH}
  INCLUDEPATH +=$${RBF_PATH}

  INCLUDEPATH += $${LINUX_PATH}/Eigen

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


