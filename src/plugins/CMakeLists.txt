
rock_library(osgVizPlugin
    SOURCES Object.cpp
    HEADERS Object.h OsgVizPlugin.h OsgVizDataPlugin.h OsgVizVisualizerPlugin.h
    DEPS_PKGCONFIG lib_manager openscenegraph)
    

add_subdirectory(viz/ModelView)
add_subdirectory(viz/Primitives)

add_subdirectory(data/ModelLoader)


