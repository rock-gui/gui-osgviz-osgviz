rock_library(osgviz
    SOURCES OsgViz.cpp
    HEADERS OsgViz.hpp plugins/OsgVizPlugin.h plugins/OsgVizVisualizerPlugin.h plugins/OsgVizDataPlugin.h
    DEPS_PKGCONFIG lib_manager openscenegraph)

rock_library(ModelLoader
    SOURCES plugins/data/ModelLoader.cpp
    HEADERS plugins/data/ModelLoader.h
    DEPS_PKGCONFIG lib_manager openscenegraph)

rock_library(ModelView
    SOURCES plugins/viz/ModelView.cpp
    HEADERS plugins/viz/ModelView.h
    DEPS_PKGCONFIG lib_manager openscenegraph)



rock_executable(osgviz_bin Main.cpp
    DEPS osgviz)

