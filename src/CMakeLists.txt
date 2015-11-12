rock_find_cmake(Boost REQUIRED system)


find_package(OpenSceneGraph REQUIRED osgManipulator osgViewer osgFX osgShadow osgParticle osgTerrain osgDB osgGA osgWidget osgText osgUtil)
include_directories(${OPENSCENEGRAPH_INCLUDE_DIRS})
link_directories(${OPENSCENEGRAPH_LIBRARY_DIRS})


include(CheckIncludeFileCXX)

set (CMAKE_REQUIRED_INCLUDES ${CMAKE_REQUIRED_INCLUDES} ${OPENSCENEGRAPH_INCLUDE_DIRS})
CHECK_INCLUDE_FILE_CXX("osg/Version" HAVE_OSG_VERSION_H)
if(${HAVE_OSG_VERSION_H})
    ADD_DEFINITIONS(-DHAVE_OSG_VERSION_H)
endif()

CHECK_INCLUDE_FILE_CXX("tr1/functional" USE_TR1)
if(${USE_TR1})
    ADD_DEFINITIONS(-DUSE_TR1)
else(${USE_TR1})
    ADD_DEFINITIONS(-DNO_TR1)
endif()

set(USE_MARS_VBO 0)
if(USE_MARS_VBO)
    ADD_DEFINITIONS(-DUSE_MARS_VBO)
endif()

if (UNIX)
	set(ADDITIONAL_LIBS X11)
endif (UNIX)

rock_library(osgVizInterfaces
	HEADERS interfaces/Clickable.h
			interfaces/WindowInterface.h
)


rock_library(osgVizGraphics
    SOURCES graphics/interfaces/data/GraphicData.cpp
            graphics/interfaces/data/LightData.cpp
            graphics/wrapper/OSGLightStruct.cpp
    HEADERS
            graphics/interfaces/OsgVizDefs.h
            graphics/interfaces/data/GraphicData.h
            graphics/interfaces/data/LightData.h
            graphics/wrapper/OSGLightStruct.h

    DEPS_PKGCONFIG openscenegraph eigen3)


rock_library(osgViz
    SOURCES OsgViz.cpp
           windows/Window.cpp
           windows/WindowManager.cpp
           windows/SuperView.cpp    
           windows/ObjectSelector.cpp   
           tools/UpdateThread.cpp    
           
    HEADERS OsgViz.hpp
           windows/Window.h
           windows/WindowManager.h
           windows/SuperView.h
           windows/ObjectSelector.h
           windows/config/WindowConfig.h
           tools/UpdateThread.h
           tools/Timing.h
           tools/TypeNameDemangling.h
           tools/GraphPrinter.h
           tools/SearchNodes.h
           tools/GlobalPos.h
               
    LIBS ${Boost_SYSTEM_LIBRARY} ${ADDITIONAL_LIBS}
    DEPS osgVizGraphics 
    DEPS_PKGCONFIG opencv lib_manager openscenegraph eigen3
)

rock_library(osgVizPlugin
    SOURCES
    plugins/Object.cpp
    HEADERS 
    plugins/Object.h
    plugins/OsgVizPlugin.h 
    plugins/OsgVizVisualizerPlugin.h 
    plugins/OsgVizDataPlugin.h 
    DEPS_PKGCONFIG lib_manager openscenegraph eigen3
    LIBS ${ADDITIONAL_LIBS})


rock_library(PrimitivesFactory
    SOURCES
    plugins/viz/Primitives/PrimitivesFactory.cpp
    plugins/viz/Primitives/Primitives/AxesNode.cpp
    plugins/viz/Primitives/Primitives/GridNode.cpp
    plugins/viz/Primitives/Primitives/ArrowNode.cpp
    HEADERS
    plugins/viz/Primitives/PrimitivesFactory.h
    plugins/viz/Primitives/Primitives/ArrowNode.h
    DEPS osgVizPlugin)


rock_library(ModelLoader
    SOURCES plugins/viz/ModelLoader/ModelLoader.cpp
    HEADERS plugins/viz/ModelLoader/ModelLoader.h
    DEPS osgVizPlugin)
    
rock_executable(osgViz_bin Main.cpp
    DEPS osgViz
    LIBS ${ADDITIONAL_LIBS})




