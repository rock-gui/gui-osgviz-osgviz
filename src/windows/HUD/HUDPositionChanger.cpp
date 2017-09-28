/*
 * HUDPositionChanger.cpp
 *
 *  Created on: 08.09.2017
 *      Author: Anna Born
 */

#include "HUDPositionChanger.h"

#include "HUD.h"

#include <iostream>

namespace osgviz {

HUDPositionChanger::HUDPositionChanger(osgviz::Object* obj, const osg::Vec3d &screenPosition, HUD *hud)
    :obj(obj), screenPosition(screenPosition), hud(hud) {

}

bool HUDPositionChanger::windowResized(const int& windowHeight, const int& windowWidth){

    //
    //osg::Matrixd world2screen = (obj->getWorldMatrices().at(0) * hud->getViewMatrix() * hud->getProjectionMatrix() * hud->getViewport()->computeWindowMatrix());
    // osg::Vec3d window_coord = obj->getPosition() * world2screen;

    int pos_x = std::round(float(windowWidth) * (screenPosition.x() / 100.0));
    int pos_y = std::round(float(windowHeight) * (screenPosition.y() / 100.0));

    osg::Vec3d pos(pos_x, pos_y, 0);
    
    osg::Matrixd world2screen = (hud->getViewMatrix() * hud->getProjectionMatrix() * hud->getViewport()->computeWindowMatrix());
    osg::Matrixd screen2world =  osg::Matrixd::inverse(world2screen);

    osg::Vec3d positionInWorld = pos * screen2world;

    printf("move pos: %i,%i %.2f,%.2f to %.2f,%.2f\n",pos_x,pos_y,obj->getPosition().x(),obj->getPosition().y(),positionInWorld.x(), positionInWorld.y());

    obj->setPosition(positionInWorld.x(), positionInWorld.y(), 0);

    return false;
}



} /* namespace intercation */
