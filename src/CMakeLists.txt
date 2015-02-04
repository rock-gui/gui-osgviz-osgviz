rock_find_cmake(Boost REQUIRED system)


find_package(OpenSceneGraph REQUIRED osgManipulator osgViewer osgFX osgShadow osgParticle osgTerrain osgDB osgGA osgWidget osgText osgUtil)
include_directories(${OPENSCENEGRAPH_INCLUDE_DIRS})
link_directories(${OPENSCENEGRAPH_LIBRARY_DIRS})



include_directories(
      graphics 
      graphics/interfaces
      graphics/hud_elements
      graphics/draw_objects
      graphics/glsl
      graphics/shadow
      graphics/3d_objects
)
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

OPTION(DEPTH_IMAGES "Compile with Depth image support, might not work on all machines" true)
if(DEPTH_IMAGES)
    ADD_DEFINITIONS(-DDEPTH_IMAGES)
endif()

set(USE_VERTEX_BUFFER 0)
if(USE_VERTEX_BUFFER)
    ADD_DEFINITIONS(-DUSE_VERTEX_BUFFER)
endif()

set(USE_MARS_VBO 0)
if(USE_MARS_VBO)
    ADD_DEFINITIONS(-DUSE_MARS_VBO)
endif()


#cmake variables
configure_file(${CMAKE_SOURCE_DIR}/src/graphics/configuration/config.h.in ${CMAKE_SOURCE_DIR}/src/graphics/config.h @ONLY)


rock_library(osgViz
    SOURCES OsgViz.cpp
           graphics/GraphicsCamera.cpp
           graphics/GraphicsManager.cpp
           graphics/GraphicsViewer.cpp
           graphics/GraphicsWindow.cpp
           graphics/gui_helper_functions.cpp
           graphics/HUD.cpp
           graphics/PostDrawCallback.cpp
           
           graphics/wrapper/OSGDrawItem.cpp
           graphics/wrapper/OSGHudElementStruct.cpp
           graphics/wrapper/OSGLightStruct.cpp
           graphics/wrapper/OSGMaterialStruct.cpp
           graphics/wrapper/OSGNodeStruct.cpp
           
           graphics/3d_objects/AxisPrimitive.cpp
           graphics/3d_objects/CapsuleDrawObject.cpp
           graphics/3d_objects/CoordsPrimitive.cpp
           graphics/3d_objects/Clouds.cpp
           graphics/3d_objects/CubeDrawObject.cpp
           graphics/3d_objects/CylinderDrawObject.cpp
           graphics/3d_objects/DrawObject.cpp
           graphics/3d_objects/GridPrimitive.cpp
           graphics/3d_objects/LoadDrawObject.cpp
           graphics/3d_objects/OceanDrawObject.cpp
           graphics/3d_objects/PlaneDrawObject.cpp
           graphics/3d_objects/SphereDrawObject.cpp
           graphics/3d_objects/TerrainDrawObject.cpp
           graphics/3d_objects/VertexBufferTerrain.cpp
           graphics/3d_objects/MarsVBOGeom.cpp
           graphics/3d_objects/MultiResHeightMapRenderer.cpp
           graphics/2d_objects/HUDNode.cpp
           graphics/2d_objects/HUDLabel.cpp
           graphics/2d_objects/HUDTerminal.cpp
           graphics/2d_objects/HUDTexture.cpp
           graphics/2d_objects/HUDLines.cpp
           graphics/2d_objects/HUDOSGNode.cpp
           
           graphics/shader/bumpmapping.cpp
           graphics/shader/pixellight.cpp
           graphics/shader/shader-generator.cpp
           graphics/shader/shader-function.cpp
           graphics/shader/shader-types.cpp
           graphics/shader/texgen.cpp

           graphics/shadow/ShadowMap.cpp
    HEADERS OsgViz.hpp
           graphics/GraphicsCamera.h
           graphics/GraphicsManager.h
           graphics/GraphicsViewer.h
           graphics/GraphicsWindow.h
           graphics/gui_helper_functions.h
           graphics/HUD.h
           graphics/PostDrawCallback.h
           graphics/3d_objects/AxisPrimitive.h
           graphics/3d_objects/CapsuleDrawObject.h
           graphics/3d_objects/Clouds.h
           graphics/3d_objects/CoordsPrimitive.h
           graphics/3d_objects/CubeDrawObject.h
           graphics/3d_objects/CylinderDrawObject.h
           graphics/3d_objects/DrawObject.h
           graphics/3d_objects/GridPrimitive.h
           graphics/3d_objects/LoadDrawObject.h
           graphics/3d_objects/OceanDrawObject.h
           graphics/3d_objects/PlaneDrawObject.h
           graphics/3d_objects/SphereDrawObject.h
           graphics/3d_objects/TerrainDrawObject.h
           graphics/3d_objects/VertexBufferTerrain.h
           graphics/3d_objects/MarsVBOGeom.h

           graphics/3d_objects/MultiResHeightMapRenderer.h

           graphics/shader/bumpmapping.h
           graphics/shader/pixellight.h
           graphics/shader/shader-generator.h
           graphics/shader/shader-function.h
           graphics/shader/shader-types.h
           graphics/shader/texgen.h

           graphics/shadow/ShadowMap.h
           graphics/2d_objects/HUDElement.h
           graphics/2d_objects/HUDNode.h
           graphics/2d_objects/HUDLabel.h
           graphics/2d_objects/HUDLines.h
           graphics/2d_objects/HUDTerminal.h
           graphics/2d_objects/HUDTexture.h
           graphics/2d_objects/HUDOSGNode.h
           
           graphics/wrapper/OSGDrawItem.h
           graphics/wrapper/OSGHudElementStruct.h
           graphics/wrapper/OSGLightStruct.h
           graphics/wrapper/OSGMaterialStruct.h
           graphics/wrapper/OSGNodeStruct.h
           
    LIBS ${Boost_SYSTEM_LIBRARY}
    DEPS_PKGCONFIG opencv lib_manager mars_interfaces openscenegraph eigen3 )

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




