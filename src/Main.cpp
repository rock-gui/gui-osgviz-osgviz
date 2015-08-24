#include <iostream>
#include "OsgViz.hpp"
#include "plugins/viz/Primitives/PrimitivesFactory.h"

#include <unistd.h>//sleep
#include <stdio.h>



int main(int argc, char** argv)
{
	osgviz::OsgViz *osgViz = osgviz::OsgViz::getInstance();

	//load lib with some helpful primitives
	osgviz::PrimitivesFactory *primitivesfactory = osgViz->getVisualizerPlugin< osgviz::PrimitivesFactory >("PrimitivesFactory");

	osg::ref_ptr<osgviz::Object> grid = primitivesfactory->createGrid();
	osgViz->addChild(grid);

	osg::ref_ptr<osgviz::Object> arrow = primitivesfactory->createArrow();
	arrow->rotate(M_PI/2.0,osg::Vec3d(0,1,0));
	arrow->setName("Arrow");
	osgViz->addChild(arrow);

	osg::ref_ptr<osgviz::Object> axes = primitivesfactory->createAxes();
	osgViz->addChild(axes);

	osgViz->createWindow();

	//you can create multiple ones:
	//osgViz->createWindow();

	//this starts a update thread for the visualisation, requires locking in the other threads:
	//osgViz->lockThread();
	//do updates
	//osgViz->unlockThread();
	osgViz->startThread();

	//or don't start the thread and update manually using osgViz->update();


	while (true){
		osgViz->lockThread();
		//do updates
		osgViz->unlockThread();

		sleep(1);


	}




	delete osgViz;

	return 0;
}
