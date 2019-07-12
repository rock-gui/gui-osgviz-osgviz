# Osgviz

Osgviz aims to provide an easily accessible visualization using OpenSceneGraph (http://www.openscenegraph.org/).

## Compiling

### Installation

The easiest way to build and install this package is to use Rock's build system.
See [this page](http://rock-robotics.org/stable/documentation/installation.html)
on how to install Rock.

However, if you feel that it's too heavy for your needs, Rock aims at having
most of its "library" packages (such as this one) to follow best practices. See
[this page](http://rock-robotics.org/stable/documentation/packages/outside_of_rock.html)
for installation instructions outside of Rock.

### Rock CMake Macros

This package uses a set of CMake helper shipped as the Rock CMake macros.
Documentations is available on [this page](http://rock-robotics.org/stable/documentation/packages/cmake_macros.html).


## Structure

Osgviz separates window handling and contents to display.

The main library allows to create windows and different views.

The contents can be put together manually or using so called Modules.
These Modules are meant to be re-usable code to provide additional functionality.


## Usage

It can be used in a threaded way or the update() function has to be called by your application

In order to visualize, you need to create a scene graph which is compatible to OpenSceneGraph,
nevertheless Osgviz provides a helper class (Object) which can make is easier to handle your scene or click events.

Modules can be used directly or you can used the singleton loader provided by Osgviz, which makes it possible for modules to 
share a single Instance of another module

For usage examples have a look into the Main.cpp and start the demo program (osgViz_bin) 


### Extension Modules

Modules are extensions to osgviz that are hold by the main class as singleton.
These modules do not need to have any dependency to osgviz.

To create a custom module, you just have to write a c++ class, that has a constructor similar to a main function:

`MyModule(int argc = 0, char** argv = nullptr);` 

To instanciate it as a singleton module, you can use the static function `osgviz::OsgViz::getModuleInstance(std::string moduleName, int argc = 0, char **argv = NULL)`.
The name is the identifier of the singleton. This way, Modules may interact with each other without any dependency to the OsgViz library

