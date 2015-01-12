#include <iostream>
#include "OsgViz.hpp"

#include "plugins/data/ModelLoader/ModelLoader.h"

#include "plugins/viz/Primitives/PrimitivesFactory.h"

#include <unistd.h>//sleep
#include <stdio.h>


int main(int argc, char** argv)
{
	osgviz::OsgViz osgViz(argc,argv);

	//osgviz::ModelView *model = (osgviz::ModelView*) osgViz.getVizPlugin("ModelView");
	//osgviz::ModelLoader *modelloader = osgViz.getDataPlugin< osgviz::ModelLoader >("ModelLoader");

	//printf("laoding model %s\n",argv[1]);
	//modelloader->loadModel(argv[1]);

	osgviz::PrimitivesFactory *primitivesfactory = osgViz.getVisualizerPlugin< osgviz::PrimitivesFactory >("PrimitivesFactory");

	osgviz::Object* axes = primitivesfactory->createAxes();
	osgviz::Object* grid = primitivesfactory->createGrid();

	osgViz.createWindow();

	return 0;
}
