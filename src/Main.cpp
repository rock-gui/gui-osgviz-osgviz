#include <iostream>
#include <osgviz/OsgViz.hpp>

#include <osgviz/plugins/ModelView.h>

#include <unistd.h>//sleep
#include <stdio.h>


int main(int argc, char** argv)
{
	osgviz::OsgViz osgViz;

	//osgviz::ModelView *model = (osgviz::ModelView*) osgViz.getVizPlugin("ModelView");
	osgviz::ModelView *model = osgViz.getVizPlugin<osgviz::ModelView>("ModelView");

	printf("laoding model %s\n",argv[1]);
	model->loadModel(argv[1]);

	osgViz.createWindow();

	printf("spleep\n");



	return 0;
}
