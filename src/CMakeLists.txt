rock_library(osgviz
    SOURCES Dummy.cpp
    HEADERS Dummy.hpp)

rock_executable(osgviz_bin Main.cpp
    DEPS osgviz)

