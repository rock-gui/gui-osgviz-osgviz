#include <iostream>
#include "OsgViz.hpp"

#include "plugins/viz/ModelLoader/ModelLoader.h"

#include "plugins/viz/Primitives/PrimitivesFactory.h"

#include "windows/config/WindowConfig.h"

#include "windows/SuperView.h"

#include <unistd.h>//sleep
#include <stdio.h>


int main(int argc, char** argv)
{
	osgviz::OsgViz *osgViz = osgviz::OsgViz::getInstance();

	osgviz::WindowConfig windowConfig = osgviz::WindowConfig();
	windowConfig.fullScreen = false;

	unsigned int id = osgViz->createWindow(windowConfig);

	std::cout << "id: " << id << std::endl;

	windowConfig.fullScreen = false;
	windowConfig.dummyTwoViews = true;

	id = osgViz->createWindow(windowConfig);

	std::cout << "id: " << id << std::endl;

	osgviz::ModelLoader *modelloader = NULL;
	if (argc > 1){
		modelloader = osgViz->getVisualizerPlugin< osgviz::ModelLoader >("ModelLoader");
		printf("laoding model %s\n",argv[1]);
		osgviz::Object* model = modelloader->loadModel(argv[1]);
		osgViz->addChild(model);
	}
	osgviz::PrimitivesFactory *primitivesfactory = osgViz->getVisualizerPlugin< osgviz::PrimitivesFactory >("PrimitivesFactory");

	osg::ref_ptr<osgviz::Object> grid = primitivesfactory->createGrid();
	osgViz->addChild(grid);

	osgviz::WindowManager* winman = osgViz->getWindowManager();
	osg::ref_ptr<osgviz::Window> win_1 = winman->getWindowByID(0);

	
	//osgViz->addChild(axes);

	osg::ref_ptr<osgviz::Window> win_2 = winman->getWindowByID(1);

	osg::ref_ptr<osgviz::Object> axes = primitivesfactory->createAxes();
	win_2->addChild(axes);

	osg::ref_ptr<osgviz::Object> arrow = primitivesfactory->createArrow();
	arrow->rotate(M_PI/2.0,osg::Vec3d(0,1,0));
	((osgviz::SuperView*)win_2->getView(0))->addChild(arrow);



	//osgviz::GraphicsManagerInterface* manager = osgViz->getGraphicsManagerInterface();
	//manager->setCamera(2);
	//manager->showSnow(true);
	//manager->showRain(true);


	osgViz->startThread();



	while (true){
		sleep(1);
	}




	delete osgViz;

	return 0;
}
