rock_library(osgviz
    SOURCES OsgViz.cpp
    HEADERS OsgViz.hpp plugins/Visualizer.h
    DEPS_PKGCONFIG lib_manager openscenegraph)

rock_library(ModelView
    SOURCES plugins/ModelView.cpp
    HEADERS plugins/ModelView.h
    DEPS_PKGCONFIG lib_manager openscenegraph)

rock_executable(osgviz_bin Main.cpp
    DEPS osgviz)

