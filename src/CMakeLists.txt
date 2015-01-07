rock_library(osgviz
    SOURCES OsgViz.cpp
    HEADERS OsgViz.hpp
    DEPS_PKGCONFIG lib_manager openscenegraph)

rock_executable(osgviz_bin Main.cpp
    DEPS osgviz)

