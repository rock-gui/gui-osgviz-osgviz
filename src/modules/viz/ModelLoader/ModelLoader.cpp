/*
 * ModelLoader.cpp
 *
 *  Created on: 09.01.2015
 *      Author: planthaber
 */

#include "ModelLoader.h"
#include <osgDB/ReadFile>
#include <osg/Node>

#include "../../../OsgViz.hpp"



namespace osgviz {


ModelLoader::ModelLoader():Module() {



}

ModelLoader::~ModelLoader() {
	// TODO Auto-generated destructor stub
}


void ModelLoader::init(int argc, char** argv){

	//modelfactory = getParent()->getVisualizerPlugin<ModelViewFactory>("ModelViewFactory");

}


osg::ref_ptr<Object> ModelLoader::loadModel(std::string path){
	printf("load %s\n",path.c_str());
    osg::ref_ptr<osg::Node> object = osgDB::readNodeFile(path);
    osg::ref_ptr<Object> model = new Object();
    model->setName(path);
	model->addChild(object);
	return model;
}


} /* namespace osgviz */
