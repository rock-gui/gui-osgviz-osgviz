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

VISUALIZER_PLUGIN(ModelViewFactory);


ModelViewFactory::ModelViewFactory(mars::lib_manager::LibManager *theManager):Visualizer(theManager){
}

ModelViewFactory::~ModelViewFactory() {
	for (std::vector<ModelView*>::iterator it = instances.begin();it != instances.end();it++){
		delete *it;
	}
}

ModelView::ModelView(){
	object = NULL;
}

ModelView::~ModelView() {
	// TODO Auto-generated destructor stub
}

void ModelView::loadModel(std::string path) {
	printf("load %s\n",path.c_str());
	patransform = new osg::PositionAttitudeTransform();
	root->addChild(patransform);
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


