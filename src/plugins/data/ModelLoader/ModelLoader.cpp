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

OSGVIZ_PLUGIN(ModelLoader);

ModelLoader::ModelLoader(mars::lib_manager::LibManager *theManager):OsgVizDataPlugin(theManager) {



}

ModelLoader::~ModelLoader() {
	// TODO Auto-generated destructor stub
}


void ModelLoader::init(int argc, char** argv){

	modelfactory = getParent()->getVisualizerPlugin<ModelViewFactory>("ModelViewFactory");

}


void ModelLoader::loadModel(std::string path){
	printf("load %s\n",path.c_str());
    osg::ref_ptr<osg::Node> object = osgDB::readNodeFile(path);

	Object* model = modelfactory->createInstance();
	model->setObject(object);

}


} /* namespace osgviz */
