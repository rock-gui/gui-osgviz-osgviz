/*
 * ModelView.cpp
 *
 *  Created on: 08.01.2015
 *      Author: planthaber
 */

#include "ModelView.h"

#include <stdio.h>


namespace osgviz {

OSGVIZ_PLUGIN(ModelViewFactory);


ModelViewFactory::ModelViewFactory(mars::lib_manager::LibManager *theManager):OsgVizVisualizerPlugin(theManager){
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

void ModelView::setModel(osg::ref_ptr<osg::Node> object) {
	this->object = object;
	patransform = new osg::PositionAttitudeTransform();
	root->addChild(patransform);
	patransform->addChild(object);
}

void ModelView::setPosition(osg::Vec3 pos) {
	patransform->setPosition(pos);
}

void ModelView::setAttitude(osg::Quat attitude){
	patransform->setAttitude(attitude);
}

} /* namespace osgviz */


