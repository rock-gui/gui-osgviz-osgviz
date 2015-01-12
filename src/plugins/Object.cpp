/*
 * Object.cpp
 *
 *  Created on: 08.01.2015
 *      Author: planthaber
 */

#include "Object.h"

#include <stdio.h>


namespace osgviz {

Object::Object(){
	object = NULL;
}

Object::~Object() {
	// TODO Auto-generated destructor stub
}

void Object::setObject(osg::ref_ptr<osg::Node> object) {
	this->object = object;
	patransform = new osg::PositionAttitudeTransform();
	root->addChild(patransform);
	patransform->addChild(object);
}

void Object::setPosition(osg::Vec3 pos) {
	patransform->setPosition(pos);
}

void Object::setAttitude(osg::Quat attitude){
	patransform->setAttitude(attitude);
}

void Object::setRootNode(osg::Group* node){
	root = node;
	root->addChild(patransform);
}


} /* namespace osgviz */


