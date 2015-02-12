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

Object::Object():cull_mask(0xffffffff),visible(true),object(NULL),scaleTransform(new osg::MatrixTransform),name(""){
	scaleTransform->setMatrix(osg::Matrix::scale(1.0, 1.0, 1.0));
	this->addChild(scaleTransform);
}

Object::~Object() {
	// TODO Auto-generated destructor stub
}

void Object::setContent(osg::ref_ptr<osg::Node> object) {
	this->object = object;
	scaleTransform->addChild(object);
	//root->addChild(this);
}

//void Object::setRootNode(osg::Group* node){
//	root = node;
//	root->addChild(this);
//}

void Object::setScale(float x, float y, float z){
	scaleTransform->setMatrix(osg::Matrix::scale(x, y, z));
}

void Object::displayName(float font_size){
	textgeode = new osg::Geode();

	osg::StateSet* stateset = textgeode->getOrCreateStateSet();
	stateset->setMode(GL_LIGHTING,osg::StateAttribute::OFF);
    stateset->setMode(GL_BLEND,osg::StateAttribute::OFF);
    //stateset->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
    stateset->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);

	text = new osgText::Text();
	text->setText(name);
	text->setCharacterSize(font_size);
	text->setAxisAlignment(osgText::Text::XY_PLANE);
	text->setAlignment(osgText::Text::LEFT_TOP);
	text->setPosition(osg::Vec3(0.0f, 0.0f, 0.0f));
	text->setAxisAlignment(osgText::Text::XY_PLANE);
	text->setAlignment(osgText::Text::LEFT_TOP);
	text->setColor(osg::Vec4(0,0,0,1));



	textgeode->addDrawable(text);
	this->addChild(textgeode);

}

void Object::xorCullMask(unsigned int mask) {
	cull_mask = cull_mask^mask;
	this->setNodeMask(cull_mask);
}

void Object::switchCullMask() {
  if(visible) {
    visible = false;
    this->setNodeMask(0);
  }
  else {
    visible = true;
    this->setNodeMask(cull_mask);
  }
}

} /* namespace osgviz */


