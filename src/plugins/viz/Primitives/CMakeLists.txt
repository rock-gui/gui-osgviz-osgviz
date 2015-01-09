rock_library(PrimitivesFactory
    SOURCES
    PrimitivesFactory.cpp
    Primitive.cpp
    Primitives/AxesNode.cpp
    Primitives/GridNode.cpp
    HEADERS PrimitivesFactory.h Primitive.h
    DEPS_PKGCONFIG lib_manager openscenegraph)

