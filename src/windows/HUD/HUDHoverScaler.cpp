/*
 * HUDHoverScaler.cpp
 *
 *  Created on: 02.06.2016
 *      Author: planthaber
 */

#include "HUDHoverScaler.h"

#include "HUD.h"

namespace osgviz {

HUDHoverScaler::HUDHoverScaler(osgviz::Object* obj, const osg::Vec3d &size, const osg::Vec3d &scale, Type type, osg::Vec3d anchor_offset, HUD* hud):obj(obj),anchor_offset(anchor_offset),scale(scale),size(size),type(type),hud(hud){
    scaled = false;
    initial_scale = obj->getScale();
    if (scale.x() == 0 || scale.y() == 0 || scale.z() == 0){
        printf("%s scale cannot be 0\n",__PRETTY_FUNCTION__);
    }
}

bool HUDHoverScaler::mouseMoved(const int& x, const int& y, const float& xNorm, const float& yNorm, const int& modifierMask){

    osg::Vec3 pos = obj->getPosition() + anchor_offset;

    //Norm is from -1 to 1, but we want 0 to 1
    int mousex = (xNorm+1.0)/2.0 * hud->getViewPortSizeX();
    int mousey = (yNorm+1.0)/2.0 * hud->getViewPortSizeY();

    //if inside scale up
    if (!scaled
            && pos.x()-(size.x()/2) < mousex
            && pos.y()-(size.y()/2) < mousey
            &&  pos.x()+(size.x()/2) > mousex
            &&  pos.y()+(size.y()/2) > mousey
    ){

        printf("scale %i:%i\n",mousex,mousey);

        initial_scale = obj->getScale();
        totalscale = osg::Vec3d(scale.x()*initial_scale.x(),scale.y()*initial_scale.y(),scale.z()*initial_scale.z());

        obj->setScale(totalscale);

        position_unscaled = obj->getPosition();
        osg::Vec3d position_scaled;
        switch(type){
        case NE: position_scaled = osg::Vec3d(position_unscaled.x()+size.x()*scale.x()/4.0,position_unscaled.y()+size.y()*scale.y()/4.0,position_unscaled.z());break;
        case SE: position_scaled = osg::Vec3d(position_unscaled.x()+size.x()*scale.x()/4.0,position_unscaled.y()-size.y()*scale.y()/4.0,position_unscaled.z());break;
        case SW: position_scaled = osg::Vec3d(position_unscaled.x()-size.x()*scale.x()/4.0,position_unscaled.y()-size.y()*scale.y()/4.0,position_unscaled.z());break;
        case NW: position_scaled = osg::Vec3d(position_unscaled.x()-size.x()*scale.x()/4.0,position_unscaled.y()+size.y()*scale.y()/4.0,position_unscaled.z());break;
        case ZOOM: position_scaled = pos;
        }
        position_scaled -= anchor_offset;
        obj->setPosition(position_scaled);


        scaled = true;
    }

    //if out (again) scale back
    //pos is the actual position
    if (scaled){

        //pos is the actial (scaled) position, but the lower left corner
        //to calc outside from center, we add the offset
        osg::Vec3d position_scaled = pos + anchor_offset;

        if (    position_scaled.x()-(size.x()*scale.x()/2) > mousex //left
            ||  position_scaled.y()-(size.y()*scale.y()/2) > mousey
            ||  position_scaled.x()+(size.x()*scale.x()/2) < mousex
            ||  position_scaled.y()+(size.y()*scale.y()/2) < mousey
        ){
            printf("unscale %i:%i\n",mousex,mousey);
            obj->setScale(initial_scale);
            obj->setPosition(position_unscaled);
            scaled = false;
        }
    }

    return false;
}



} /* namespace intercation */
