rock_library(osgViz
    SOURCES OsgViz.cpp
    HEADERS OsgViz.hpp plugins/OsgVizPlugin.h plugins/OsgVizVisualizerPlugin.h plugins/OsgVizDataPlugin.h
    DEPS_PKGCONFIG lib_manager openscenegraph)

add_subdirectory(plugins)

rock_executable(osgViz_bin Main.cpp
    DEPS osgViz)

