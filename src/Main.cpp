#include <iostream>
#include "OsgViz.hpp"
#include "plugins/viz/Primitives/PrimitivesFactory.h"

#include <unistd.h>//sleep
#include <stdio.h>



int main(int argc, char** argv)
{
	printf("getting instance\n");
	fflush(stdout);
	osgviz::OsgViz *osgViz = osgviz::OsgViz::getInstance();

	//load lib with some helpful primitives
	printf("load plugin\n");	fflush(stdout);
	osgviz::PrimitivesFactory *primitivesfactory = osgViz->getVisualizerPlugin< osgviz::PrimitivesFactory >("PrimitivesFactory");

	if (!primitivesfactory){
		printf("plugin not found\n");	fflush(stdout);
	}
	
	osg::ref_ptr<osgviz::Object> grid = primitivesfactory->createGrid();
	osgViz->addChild(grid);

	osg::ref_ptr<osgviz::Object> arrow = primitivesfactory->createArrow();
	arrow->rotate(M_PI/2.0,osg::Vec3d(0,1,0));
	arrow->setName("Arrow");
	osgViz->addChild(arrow);

	osg::ref_ptr<osgviz::Object> axes = primitivesfactory->createAxes();
	osgViz->addChild(axes);
	
	printf("creating window\n");fflush(stdout);

	osgViz->createWindow();

	sleep(1);
	//you can create multiple ones:
	//osgViz->createWindow();

	//this starts a update thread for the visualisation, requires locking in the other threads:
	//osgViz->lockThread();
	//do updates
	//osgViz->unlockThread();
	printf("startThread\n");fflush(stdout);
	osgViz->startThread();

	//or don't start the thread and update manually using osgViz->update();


	while (true){
		//osgViz->lockThread();
		//do updates
		//osgViz->unlockThread();
		//osgViz->update();
		printf("sleep\n");fflush(stdout);

		sleep(5);
//		osgViz->getWindowManager()->getWindowByID(0)->setFullscreen(true);
//		sleep(5);
//		osgViz->getWindowManager()->getWindowByID(0)->setFullscreen(false);
//		sleep(5);
//		osgViz->getWindowManager()->getWindowByID(0)->setWindowGeometry(150,150,1240,768);
//		sleep(5);

	}

	return 0;
}
