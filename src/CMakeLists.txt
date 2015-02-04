rock_find_cmake(Boost REQUIRED system)


rock_library(osgViz
    SOURCES OsgViz.cpp
    HEADERS OsgViz.hpp
    LIBS ${Boost_SYSTEM_LIBRARY}
    DEPS_PKGCONFIG lib_manager openscenegraph)

rock_library(osgVizPlugin
    SOURCES plugins/Object.cpp
    HEADERS 
    plugins/Object.h
    plugins/OsgVizPlugin.h 
    plugins/OsgVizVisualizerPlugin.h 
    plugins/OsgVizDataPlugin.h 
    DEPS_PKGCONFIG lib_manager openscenegraph)



rock_library(PrimitivesFactory
    SOURCES
    plugins/viz/Primitives/PrimitivesFactory.cpp
    plugins/viz/Primitives/Primitives/AxesNode.cpp
    plugins/viz/Primitives/Primitives/GridNode.cpp
    HEADERS plugins/viz/Primitives/PrimitivesFactory.h
    DEPS osgVizPlugin)


rock_library(ModelLoader
    SOURCES plugins/viz/ModelLoader/ModelLoader.cpp
    HEADERS plugins/viz/ModelLoader/ModelLoader.h
    DEPS osgVizPlugin)
    

rock_executable(osgViz_bin Main.cpp
    DEPS osgViz)



add_subdirectory(graphics)
