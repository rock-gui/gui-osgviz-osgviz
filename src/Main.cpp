#include <iostream>
#include "OsgViz.hpp"

#include "plugins/viz/ModelLoader/ModelLoader.h"

#include "plugins/viz/Primitives/PrimitivesFactory.h"

#include <unistd.h>//sleep
#include <stdio.h>


int main(int argc, char** argv)
{
	osgviz::OsgViz *osgViz = new osgviz::OsgViz(argc,argv);

	osgviz::ModelLoader *modelloader = NULL;
	if (argc > 1){
		modelloader = osgViz->getVisualizerPlugin< osgviz::ModelLoader >("ModelLoader");
		printf("laoding model %s\n",argv[1]);
		modelloader->loadModel(argv[1]);
	}
	osgviz::PrimitivesFactory *primitivesfactory = osgViz->getVisualizerPlugin< osgviz::PrimitivesFactory >("PrimitivesFactory");

	osgviz::Object* axes = primitivesfactory->createAxes();
	osgviz::Object* grid = primitivesfactory->createGrid();





	osgviz::GraphicsManagerInterface* manager = osgViz->getGraphicsManagerInterface();
	//manager->setCamera(2);
	manager->showSnow(true);
	//manager->showRain(true);

	osgViz->startThread();

	while (true){
		sleep(1);
	}




	delete osgViz;

	return 0;
}
