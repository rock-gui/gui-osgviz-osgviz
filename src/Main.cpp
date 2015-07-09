#include <iostream>
#include "OsgViz.hpp"

#include "plugins/viz/ModelLoader/ModelLoader.h"

#include "plugins/viz/Primitives/PrimitivesFactory.h"

#include "windows/config/WindowConfig.h"

#include "windows/SuperView.h"

#include <unistd.h>//sleep
#include <stdio.h>

#include "tools/GraphPrinter.h"


int main(int argc, char** argv)
{
	osgviz::OsgViz *osgViz = osgviz::OsgViz::getInstance();

	// --------- create first window ---------
	osgviz::WindowConfig windowConfig = osgviz::WindowConfig();
	windowConfig.fullScreen = false;
	windowConfig.viewsConfig.push_back(osgviz::ViewConfig());

	unsigned int id = osgViz->createWindow(windowConfig);
	std::cout << "window id: " << id << std::endl;

	// --------- create second window ---------
	windowConfig.fullScreen = false;
	windowConfig.viewsConfig.at(0) = osgviz::ViewConfig(0, 0, 0.5, 1.0);
	windowConfig.viewsConfig.push_back(osgviz::ViewConfig(0.5, 0, 0.5, 1.0));

	id = osgViz->createWindow(windowConfig);
	std::cout << "window id: " << id << std::endl;

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

	win_2->showSnow(true);
	//win_2->showRain(true);

	osg::ref_ptr<osgviz::Object> arrow = primitivesfactory->createArrow();
	arrow->rotate(M_PI/2.0,osg::Vec3d(0,1,0));
	((osgviz::SuperView*)win_2->getView(0))->addChild(arrow);
	arrow->setName("Arrow");


	osg::ref_ptr<osgviz::Object> axes = primitivesfactory->createAxes();
	win_2->addChild(axes);

	//osgviz::GraphicsManagerInterface* manager = osgViz->getGraphicsManagerInterface();
	//manager->setCamera(2);
	//manager->showSnow(true);
	//manager->showRain(true);


	osgViz->createWindow();
	osg::ref_ptr<osgviz::Window> win_3 = winman->getWindowByID(2);

	osg::ref_ptr<osg::Node> copy;



	osgViz->startThread();



	while (true){
		sleep(1);


		osgViz->lockThread();
		osgviz::SerializedObject obj = osgViz->serialize(arrow);
		printf("size %i\n",obj.size());
		win_3->getRootNode()->removeChild(0,win_3->getRootNode()->getNumChildren());
		copy = osgViz->deserialize(obj);
		win_3->addChild(copy);
		osgViz->unlockThread();

		GraphPrinter::print(win_3->getRootNode(),true,"out.dot");


	}




	delete osgViz;

	return 0;
}
