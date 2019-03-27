/*
 * HUDPositionChanger.cpp
 *
 *  Created on: 08.09.2017
 *      Author: Anna Born
 */

#include "HUDPositionChanger.h"

#include "HUD.h"

#include <iostream>

#include <cmath>
#if(WIN32)
	inline double round(double value) { return value < 0 ? -std::floor(0.5 - value) : std::floor(0.5 + value); }
#else
  inline double round(double value) { return std::round(value); }
#endif

namespace osgviz {

HUDPositionChanger::HUDPositionChanger(osgviz::Object* obj, const osg::Vec3d &init_pos, const osg::Vec2d init_size, HUD *hud)
    :obj(obj), init_pos(init_pos), init_size(init_size), hud(hud) {


}

bool HUDPositionChanger::windowResized(const int& windowWidth, const int& windowHeight){


    //std::cout << "--------------------" << std::endl;
    hud->resize(windowWidth, windowHeight);

    //std::cout << "HUD: " << windowWidth << " " << windowHeight << std::endl;
 
    //osg::Matrixd world2screen = (obj->getWorldMatrices().at(0) * hud->getViewMatrix() * hud->getProjectionMatrix() * hud->getViewport()->computeWindowMatrix());
    // osg::Vec3d window_coord = obj->getPosition() * world2screen;

    float scaleFactor_x = (float) windowWidth / hud->getConfigSize().x();
    float scaleFactor_y = (float) windowHeight / hud->getConfigSize().y();    

    // change the obj position only if the current hud size (viewport size) is smaller than its user-defined size

    int pos_x = round(scaleFactor_x * init_pos.x());
    int pos_y = round(scaleFactor_y * init_pos.y());

    //std::cout << "init_size: " << init_size.x() << " " << init_size.y() << std::endl;
    //std::cout << "init_pos: " << init_pos.x() << " " << init_pos.y() << std::endl;
    //std::cout << "getConfigSize: " << hud->getConfigSize().x() << " " << hud->getConfigSize().y() << std::endl;

    //std::cout << "pos: " << pos_x << " " << pos_y << std::endl;

    osg::Vec3d pos(pos_x, pos_y, 0);
    
    osg::Matrixd world2screen = (hud->getViewMatrix() * hud->getProjectionMatrix() * hud->getViewport()->computeWindowMatrix());
    osg::Matrixd screen2world =  osg::Matrixd::inverse(world2screen);

    osg::Vec3d positionInWorld = pos * screen2world;

    obj->setPosition(positionInWorld.x(), positionInWorld.y(), 0);

    if (windowWidth < hud->getConfigSize().x() || windowHeight < hud->getConfigSize().y())
    {
        // rescale the object
        // the object size is given relative to the hud size
        // since the hud will be always resized to the window size
        // we should rescale the object to keep the right proportion


        if (scaleFactor_x < scaleFactor_y)
            obj->setScale(scaleFactor_x, scaleFactor_x, 1.0);  
        else
            obj->setScale(scaleFactor_y, scaleFactor_y, 1.0); 
        //std::cout << "scale: " << scaleFactor_x << " " << scaleFactor_y << std::endl;      
    } else {
        obj->setScale(1.0, 1.0, 1.0);
    }   

    return false;
}



} /* namespace intercation */
