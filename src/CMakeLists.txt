rock_library(osgViz
    SOURCES OsgViz.cpp
    HEADERS OsgViz.hpp 
    DEPS_PKGCONFIG lib_manager openscenegraph)

rock_library(osgVizPlugin
    SOURCES plugins/Object.cpp
    HEADERS 
    plugins/Object.h
    plugins/OsgVizPlugin.h 
    plugins/OsgVizVisualizerPlugin.h 
    plugins/OsgVizDataPlugin.h 
    DEPS_PKGCONFIG lib_manager openscenegraph)


rock_library(ModelView
    SOURCES plugins/viz/ModelView/ModelViewFactory.cpp
    HEADERS plugins/viz/ModelView/ModelViewFactory.h
    DEPS osgVizPlugin)

rock_library(PrimitivesFactory
    SOURCES
    plugins/viz/Primitives/PrimitivesFactory.cpp
    plugins/viz/Primitives/Primitives/AxesNode.cpp
    plugins/viz/Primitives/Primitives/GridNode.cpp
    HEADERS plugins/viz/Primitives/PrimitivesFactory.h
    DEPS osgVizPlugin)


rock_library(ModelLoader
    SOURCES plugins/data/ModelLoader/ModelLoader.cpp
    HEADERS plugins/data/ModelLoader/ModelLoader.h
    DEPS osgVizPlugin)
    







rock_executable(osgViz_bin Main.cpp
    DEPS osgViz)

