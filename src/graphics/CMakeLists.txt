project(osgviz_graphics)
set(PROJECT_VERSION 1.0)
set(PROJECT_DESCRIPTION "This library provides a 3d visualization through simple interfaces.")
cmake_minimum_required(VERSION 2.6)

include(FindPkgConfig)
include(CheckIncludeFileCXX)

CHECK_INCLUDE_FILE_CXX("tr1/functional" USE_TR1)
if(${USE_TR1})
    ADD_DEFINITIONS(-DUSE_TR1)
else(${USE_TR1})
    ADD_DEFINITIONS(-DNO_TR1)
endif()

find_package(lib_manager)
lib_defaults()
define_module_info()

include_directories(
      ./ 
      interfaces
      hud_elements
      draw_objects
      glsl
      shadow
      3d_objects
)

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


find_package(OpenSceneGraph REQUIRED osgManipulator osgViewer osgFX osgShadow osgParticle osgTerrain osgDB osgGA osgWidget osgText osgUtil)
include_directories(${OPENSCENEGRAPH_INCLUDE_DIRS})
link_directories(${OPENSCENEGRAPH_LIBRARY_DIRS})

set (CMAKE_REQUIRED_INCLUDES ${CMAKE_REQUIRED_INCLUDES} ${OPENSCENEGRAPH_INCLUDE_DIRS})
CHECK_INCLUDE_FILE_CXX("osg/Version" HAVE_OSG_VERSION_H)
if(${HAVE_OSG_VERSION_H})
    ADD_DEFINITIONS(-DHAVE_OSG_VERSION_H)
endif()


pkg_check_modules(PKGCONFIG REQUIRED
			    opencv
			    lib_manager
			    mars_interfaces
			    cfg_manager
)

include_directories(${PKGCONFIG_INCLUDE_DIRS})
link_directories(${PKGCONFIG_LIBRARY_DIRS})
add_definitions(${PKGCONFIG_CFLAGS_OTHER})  #cflags without -I

set(HEADERS
           GraphicsCamera.h
           GraphicsManager.h
           GraphicsViewer.h
           GraphicsWidget.h
           gui_helper_functions.h
           HUD.h
           PostDrawCallback.h
           3d_objects/AxisPrimitive.h
           3d_objects/CapsuleDrawObject.h
           3d_objects/Clouds.h
           3d_objects/CoordsPrimitive.h
           3d_objects/CubeDrawObject.h
           3d_objects/CylinderDrawObject.h
           3d_objects/DrawObject.h
           3d_objects/GridPrimitive.h
           3d_objects/LoadDrawObject.h
           3d_objects/OceanDrawObject.h
           3d_objects/PlaneDrawObject.h
           3d_objects/SphereDrawObject.h
           3d_objects/TerrainDrawObject.h
           3d_objects/VertexBufferTerrain.h
           3d_objects/MarsVBOGeom.h

           3d_objects/MultiResHeightMapRenderer.h

           shader/bumpmapping.h
           shader/pixellight.h
           shader/shader-generator.h
           shader/shader-function.h
           shader/shader-types.h
           shader/texgen.h

           shadow/ShadowMap.h
)

set(HEADERS_2D
           2d_objects/HUDElement.h
           2d_objects/HUDNode.h
           2d_objects/HUDLabel.h
           2d_objects/HUDLines.h
           2d_objects/HUDTerminal.h
           2d_objects/HUDTexture.h
           2d_objects/HUDOSGNode.h
           
)

set(HEADERS_WRAPPER
           wrapper/OSGDrawItem.h
           wrapper/OSGHudElementStruct.h
           wrapper/OSGLightStruct.h
           wrapper/OSGMaterialStruct.h
           wrapper/OSGNodeStruct.h
)

set(SOURCES 
           GraphicsCamera.cpp
           GraphicsManager.cpp
           GraphicsViewer.cpp
           GraphicsWidget.cpp
           gui_helper_functions.cpp
           HUD.cpp
           PostDrawCallback.cpp
           
           wrapper/OSGDrawItem.cpp
           wrapper/OSGHudElementStruct.cpp
           wrapper/OSGLightStruct.cpp
           wrapper/OSGMaterialStruct.cpp
           wrapper/OSGNodeStruct.cpp
           
           3d_objects/AxisPrimitive.cpp
           3d_objects/CapsuleDrawObject.cpp
           3d_objects/CoordsPrimitive.cpp
           3d_objects/Clouds.cpp
           3d_objects/CubeDrawObject.cpp
           3d_objects/CylinderDrawObject.cpp
           3d_objects/DrawObject.cpp
           3d_objects/GridPrimitive.cpp
           3d_objects/LoadDrawObject.cpp
           3d_objects/OceanDrawObject.cpp
           3d_objects/PlaneDrawObject.cpp
           3d_objects/SphereDrawObject.cpp
           3d_objects/TerrainDrawObject.cpp
           3d_objects/VertexBufferTerrain.cpp
           3d_objects/MarsVBOGeom.cpp
           3d_objects/MultiResHeightMapRenderer.cpp
           2d_objects/HUDNode.cpp
           2d_objects/HUDLabel.cpp
           2d_objects/HUDTerminal.cpp
           2d_objects/HUDTexture.cpp
           2d_objects/HUDLines.cpp
           2d_objects/HUDOSGNode.cpp
           
           shader/bumpmapping.cpp
           shader/pixellight.cpp
           shader/shader-generator.cpp
           shader/shader-function.cpp
           shader/shader-types.cpp
           shader/texgen.cpp

           shadow/ShadowMap.cpp
)


#cmake variables
configure_file(${CMAKE_SOURCE_DIR}/src/graphics/configuration/config.h.in ${CMAKE_SOURCE_DIR}/src/graphics/config.h @ONLY)
include_directories("${CMAKE_BINARY_DIR}")

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${QT_MOC_HEADER_SRC} config.h)


if(APPLE)
 FIND_LIBRARY(OPENGL_LIBRARY OpenGL)
 SET(APPLE_LIBS ${OPENGL_LIBRARY} -L/opt/local/lib opencv_core opencv_highgui opencv_imgproc)
endif(APPLE)

if(WIN32)
  if(USE_VERTEX_BUFFER) 
    SET(WIN_LIBS glew32 opengl32)
  else(USE_VERTEX_BUFFER)
    SET(WIN_LIBS opengl32)
  endif(USE_VERTEX_BUFFER) 
endif(WIN32)

target_link_libraries(${PROJECT_NAME}         
            ${QT_LIBRARIES}
            ${OPENSCENEGRAPH_LIBRARIES}
            ${PKGCONFIG_LIBRARIES}
            ${APPLE_LIBS}
            ${WIN_LIBS}
            pthread
)

if(WIN32)
  set(LIB_INSTALL_DIR bin) # .dll are in PATH, like executables
else(WIN32)
  set(LIB_INSTALL_DIR lib)
endif(WIN32)

set(_INSTALL_DESTINATIONS
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION ${LIB_INSTALL_DIR}
	ARCHIVE DESTINATION lib
)

# Install the library
install(TARGETS ${PROJECT_NAME} ${_INSTALL_DESTINATIONS})

# Install headers into mars include directory
install(FILES ${HEADERS} DESTINATION include/mars/graphics)
install(FILES ${HEADERS_2D} DESTINATION include/mars/graphics/2d_objects)
install(FILES ${HEADERS_WRAPPER} DESTINATION include/mars/graphics/wrapper)

# Prepare and install necessary files to support finding of the library 
# using pkg-config
configure_file(configuration/${PROJECT_NAME}.pc.in ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pc @ONLY)
install(FILES ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pc DESTINATION lib/pkgconfig)

configure_file(configuration/mars_Graphics.in ${CMAKE_BINARY_DIR}/mars_Graphics.yaml @ONLY)
install(FILES ${CMAKE_BINARY_DIR}/mars_Graphics.yaml DESTINATION configuration/mars_default/)

INSTALL(DIRECTORY resources DESTINATION share/mars/graphics)
