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

rock_library(osgViz
    SOURCES OsgViz.cpp
           graphics/GraphicsCamera.cpp
           graphics/GraphicsManager.cpp
           graphics/GraphicsViewer.cpp
           graphics/GraphicsWindow.cpp
           graphics/gui_helper_functions.cpp
           graphics/HUD.cpp
           graphics/PostDrawCallback.cpp
           
#           objects/wrapper/OSGDrawItem.cpp
#           objects/wrapper/OSGHudElementStruct.cpp
#           objects/wrapper/OSGNodeStruct.cpp
#           
           graphics/wrapper/OSGLightStruct.cpp
           graphics/wrapper/OSGMaterialStruct.cpp
           
           
           graphics/DrawObject.cpp
#           objects/3d_objects/AxisPrimitive.cpp
#           objects/3d_objects/CapsuleDrawObject.cpp
#           objects/3d_objects/CoordsPrimitive.cpp
#           objects/3d_objects/Clouds.cpp
#           objects/3d_objects/CubeDrawObject.cpp
#           objects/3d_objects/CylinderDrawObject.cpp
#           objects/3d_objects/GridPrimitive.cpp
#           objects/3d_objects/LoadDrawObject.cpp
#           objects/3d_objects/OceanDrawObject.cpp
#           objects/3d_objects/PlaneDrawObject.cpp
#           objects/3d_objects/SphereDrawObject.cpp
#           objects/3d_objects/TerrainDrawObject.cpp
#           objects/3d_objects/VertexBufferTerrain.cpp
#           objects/3d_objects/MarsVBOGeom.cpp
#           objects/3d_objects/MultiResHeightMapRenderer.cpp
#           objects/2d_objects/HUDNode.cpp
#           objects/2d_objects/HUDLabel.cpp
#           objects/2d_objects/HUDTerminal.cpp
#           objects/2d_objects/HUDTexture.cpp
#           objects/2d_objects/HUDLines.cpp
#           objects/2d_objects/HUDOSGNode.cpp
           
           graphics/shader/bumpmapping.cpp
           graphics/shader/pixellight.cpp
           graphics/shader/shader-generator.cpp
           graphics/shader/shader-function.cpp
           graphics/shader/shader-types.cpp
           graphics/shader/texgen.cpp

           graphics/shadow/ShadowMap.cpp
           
           graphics/interfaces/data/GraphicData.cpp
			graphics/interfaces/data/LightData.cpp
			graphics/interfaces/data/MaterialData.cpp
           
    HEADERS OsgViz.hpp
           graphics/GraphicsCamera.h
           graphics/GraphicsManager.h
           graphics/GraphicsViewer.h
           graphics/GraphicsWindow.h
           graphics/gui_helper_functions.h
           graphics/HUD.h
           graphics/PostDrawCallback.h
           
           graphics/DrawObject.h
#           objects/3d_objects/AxisPrimitive.h
#           objects/3d_objects/CapsuleDrawObject.h
#           objects/3d_objects/Clouds.h
#           objects/3d_objects/CoordsPrimitive.h
#           objects/3d_objects/CubeDrawObject.h
#           objects/3d_objects/CylinderDrawObject.h
#           objects/3d_objects/GridPrimitive.h
#           objects/3d_objects/LoadDrawObject.h
#           objects/3d_objects/OceanDrawObject.h
#           objects/3d_objects/PlaneDrawObject.h
#           objects/3d_objects/SphereDrawObject.h
#           objects/3d_objects/TerrainDrawObject.h
#           objects/3d_objects/VertexBufferTerrain.h
#           objects/3d_objects/MarsVBOGeom.h
#           objects/3d_objects/MultiResHeightMapRenderer.h

           graphics/shader/bumpmapping.h
           graphics/shader/pixellight.h
           graphics/shader/shader-generator.h
           graphics/shader/shader-function.h
           graphics/shader/shader-types.h
           graphics/shader/texgen.h

           
           graphics/HUDElement.h
           graphics/shadow/ShadowMap.h
           
#           objects/2d_objects/HUDNode.h
#           objects/2d_objects/HUDLabel.h
#           objects/2d_objects/HUDLines.h
#           objects/2d_objects/HUDTerminal.h
#           objects/2d_objects/HUDTexture.h
#           objects/2d_objects/HUDOSGNode.h
#           
#           objects/wrapper/OSGDrawItem.h
#           objects/wrapper/OSGHudElementStruct.h
#           objects/wrapper/OSGNodeStruct.h
#           
           graphics/wrapper/OSGLightStruct.h
           graphics/wrapper/OSGMaterialStruct.h
           
           
           graphics/interfaces/cameraStruct.h
		   graphics/interfaces/GraphicsCameraInterface.h
			graphics/interfaces/GraphicsEventInterface.h
			graphics/interfaces/GraphicsWindowInterface.h
			graphics/interfaces/GraphicsManagerInterface.h
			graphics/interfaces/GuiEventInterface.h
			
			graphics/interfaces/data/GraphicData.h
			graphics/interfaces/data/LightData.h
			graphics/interfaces/data/MaterialData.h
			graphics/interfaces/OsgVizDefs.h
           
    LIBS ${Boost_SYSTEM_LIBRARY}
    DEPS_PKGCONFIG opencv lib_manager openscenegraph eigen3 )

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




