#include <iostream>
#include <osgviz/OsgViz.hpp>

#include <osgviz/plugins/ModelView.h>

#include <unistd.h>//sleep
#include <stdio.h>


int main(int argc, char** argv)
{
	osgviz::OsgViz osgViz;

	//osgviz::ModelView *model = (osgviz::ModelView*) osgViz.getVizPlugin("ModelView");
	osgviz::ModelViewFactory *modelfactory = osgViz.getVizPlugin<osgviz::ModelViewFactory>("ModelView");
	osgviz::ModelView *model = modelfactory->createInstance();
	osgviz::ModelView *model2 = modelfactory->createInstance();

	printf("laoding model %s\n",argv[1]);
	model->loadModel(argv[1]);
	model2->loadModel(argv[1]);
	model2->setPosition(osg::Vec3(0,0,1));

	osgViz.createWindow();

	return 0;
}
