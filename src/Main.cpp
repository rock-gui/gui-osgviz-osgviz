#include <iostream>
#include "OsgViz.hpp"

#include "plugins/viz/ModelLoader/ModelLoader.h"

#include "plugins/viz/Primitives/PrimitivesFactory.h"

#include <unistd.h>//sleep
#include <stdio.h>


int main(int argc, char** argv)
{
	osgviz::OsgViz *osgViz = osgviz::OsgViz::getInstance();

	osgviz::ModelLoader *modelloader = NULL;
	if (argc > 1){
		modelloader = osgViz->getVisualizerPlugin< osgviz::ModelLoader >("ModelLoader");
		printf("laoding model %s\n",argv[1]);
		osgviz::Object* model = modelloader->loadModel(argv[1]);
		osgViz->addChild(model);
	}
	osgviz::PrimitivesFactory *primitivesfactory = osgViz->getVisualizerPlugin< osgviz::PrimitivesFactory >("PrimitivesFactory");

	osg::ref_ptr<osgviz::Object> axes = primitivesfactory->createAxes();
	osgViz->addChild(axes);

	osg::ref_ptr<osgviz::Object> grid = primitivesfactory->createGrid();
	osgViz->addChild(grid);




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
