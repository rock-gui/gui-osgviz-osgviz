/*
 * ModelView.cpp
 *
 *  Created on: 08.01.2015
 *      Author: planthaber
 */

#include "ModelView.h"

#include <stdio.h>
#include <osgDB/ReadFile>



namespace osgviz {

VISUALIZER_PLUGIN(ModelView);


ModelView::ModelView(mars::lib_manager::LibManager *theManager):Visualizer(theManager){
	object = NULL;
}

ModelView::~ModelView() {
	// TODO Auto-generated destructor stub
}

void ModelView::loadModel(std::string path) {
	printf("load %s\n",path.c_str());
	patransform = new osg::PositionAttitudeTransform();
	getRootNode()->addChild(patransform);
	object = osgDB::readNodeFile(path);
	patransform->addChild(object);

}

void ModelView::setPosition(osg::Vec3 pos) {
	patransform->setPosition(pos);
}

void ModelView::setAttitude(osg::Quat attitude){
	patransform->setAttitude(attitude);
}

} /* namespace osgviz */


