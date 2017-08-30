/*
 * Object.cpp
 *
 *  Created on: 08.01.2015
 *      Author: planthaber
 */

#include "Object.h"

#include <stdio.h>
//#include <cxxabi.h>

//#include <unistd.h>

#include <osg/ValueObject>
#include <algorithm>

namespace osgviz {

Object::Object():cull_mask(0xffffffff),visible(true){
    text_size = 0.1;
    text_position = osg::Vec3(0,0,0);
    text_color = osg::Vec4(0,0,0,1);
    text = NULL;

    //scaleTransform->setMatrix(osg::Matrix::scale(1.0, 1.0, 1.0));
    //PositionAttitudeTransform::addChild(scaleTransform);
}

Object::~Object() {

}

//void Object::setContent(osg::ref_ptr<osg::Node> object) {
    //this->object = object;
    //scaleTransform->addChild(object);
    ////root->addChild(this);
//}

//void Object::setRootNode(osg::Group* node){
    //root = node;
    //root->addChild(this);
//}


void Object::displayName(float font_size){

    if (!texttransform.valid()){
        texttransform = new osg::AutoTransform();
        textgeode = new osg::Geode();

        osg::StateSet* stateset = textgeode->getOrCreateStateSet();
        stateset->setMode(GL_LIGHTING,osg::StateAttribute::OFF);
        stateset->setMode(GL_BLEND,osg::StateAttribute::OFF);
        //stateset->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
        stateset->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);

        text = new osgText::Text();

        text->setCharacterSize(text_size);
        text->setAxisAlignment(osgText::Text::XY_PLANE);
        text->setAlignment(osgText::Text::LEFT_TOP);
        text->setPosition(text_position);
        text->setColor(text_color);


        texttransform->setAutoRotateMode(osg::AutoTransform::ROTATE_TO_SCREEN);

        textgeode->addDrawable(text);
        texttransform->addChild(textgeode);
    }

    text->setText(this->getName());

    this->addChild(texttransform);

}

void Object::setTextSize(float font_size) {
    text_size = font_size;
    if (text != NULL)
        text->setCharacterSize(text_size);
}

void Object::setTextPosition(osg::Vec3 pos) {
    text_position = pos;
    if (text != NULL)
        text->setPosition(text_position);
}

void Object::setTextColor(osg::Vec4 color) {
    text_color = color;
    if (text != NULL)
        text->setColor(text_color);
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


bool Object::clicked(const int &buttonMask, const osg::Vec2d &cursor, const osg::Vec3d &world,
                     const osg::Vec3d &local, Clickable *object, const int modKeyMask,
                     WindowInterface* window){
    printf("%s click world: %.2f,%.2f,%.2f local: %.2f,%.2f,%.2f \n",this->getName().c_str(),world.x(),world.y(),world.z(),local.x(),local.y(),local.z());
    bool finish = false;
    if (!clickablecb.empty()){
        for(std::shared_ptr<Clickable>& clickable : clickablecb) {
            if (clickable->clicked(buttonMask,cursor,world,local, this, modKeyMask, window)){
                printf("%s forwarded click\n",this->getName().c_str());
                finish = true;
            }
        }

    }
    return finish;
}

bool Object::dragged(const int &buttonMask, const osg::Vec2d &cursor,
                     const osg::Vec3d &world, const osg::Vec3d &local,
                     Clickable *object, const int modKeyMask, WindowInterface* window){
    //printf("%s dragged %.2f,%.2f,%.2f\n",this->getName().c_str(),world.x(),world.y(),world.z());
    bool finish = false;
    if (!clickablecb.empty()){
        for(std::shared_ptr<Clickable>& clickable : clickablecb) {
            if (clickable->dragged(buttonMask,cursor,world,local, this, modKeyMask, window)){
                //printf("%s forwarded dragged\n",this->getName().c_str());
                finish = true;
            }
        }

    }
    return finish;
}

void Object::addClickableCallback(std::shared_ptr<Clickable> cb) {
    this->clickablecb.push_back(cb);
}

void Object::setDirty(){
    this->setUserValue("dirty",true);
}

void Object::setName(const std::string &name){
    osg::PositionAttitudeTransform::setName(name);
    if (text.valid()){
        text->setText(name);
    }
}

bool Object::hasClickableCallback(std::shared_ptr<Clickable> cb)
{
    return std::find(clickablecb.begin(), clickablecb.end(), cb) != clickablecb.end();
}



} /* namespace osgviz */


