rock_library(osgViz
    SOURCES OsgViz.cpp
    HEADERS OsgViz.hpp plugins/OsgVizPlugin.h plugins/OsgVizVisualizerPlugin.h plugins/OsgVizDataPlugin.h
    DEPS_PKGCONFIG lib_manager openscenegraph)

rock_library(osgVizModelLoader
    SOURCES plugins/data/ModelLoader/ModelLoader.cpp
    HEADERS plugins/data/ModelLoader/ModelLoader.h
    DEPS_PKGCONFIG lib_manager openscenegraph)

rock_library(osgVizModelView
    SOURCES plugins/viz/ModelView/ModelView.cpp
    HEADERS plugins/viz/ModelView/ModelView.h
    DEPS_PKGCONFIG lib_manager openscenegraph)

#rock_library(osgVizPrimitives
#    SOURCES plugins/viz/Primitives/PrimitivesFactory.cpp
#    HEADERS plugins/viz/Primitives/PrimitivesFactory.h
#    DEPS_PKGCONFIG lib_manager openscenegraph)

rock_executable(osgviz_bin Main.cpp
    DEPS osgViz)

