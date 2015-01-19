/*
 * Object.cpp
 *
 *  Created on: 08.01.2015
 *      Author: planthaber
 */

#include "Object.h"

#include <stdio.h>
#include <cxxabi.h>

namespace osgviz {

Object::Object(){
	object = NULL;
	name = "";
}

Object::~Object() {
	// TODO Auto-generated destructor stub
}

void Object::setContent(osg::ref_ptr<osg::Node> object) {
	this->object = object;
	this->addChild(object);
	root->addChild(this);
}


void Object::setRootNode(osg::Group* node){
	root = node;
	root->addChild(this);
}


} /* namespace osgviz */


