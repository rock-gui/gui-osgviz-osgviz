/*
 * HUDHoverScaler.cpp
 *
 *  Created on: 02.06.2016
 *      Author: planthaber
 */

#include "HUDHoverScaler.h"

#include "HUD.h"

namespace osgviz {

HUDHoverScaler::HUDHoverScaler(osgviz::Object* obj, const osg::Vec3d &size, const osg::Vec3d &scale, Type type, HUD* hud):obj(obj),scale(scale),size(size),type(type),hud(hud){
    scaled = false;
    initial_scale = obj->getScale();
    if (scale.x() == 0 || scale.y() == 0 || scale.z() == 0){
        printf("%s scale cannot be 0\n",__PRETTY_FUNCTION__);
    }
}

bool HUDHoverScaler::mouseMoved(const int& x, const int& y, const float& xNorm, const float& yNorm, const int& modifierMask){

    osg::Vec3 pos = obj->getPosition();

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
        switch(type){
        case NE: obj->setPosition(position_unscaled.x()+size.x()*scale.x()/4.0,position_unscaled.y()+size.y()*scale.y()/4.0,position_unscaled.z());break;
        case SE: obj->setPosition(position_unscaled.x()+size.x()*scale.x()/4.0,position_unscaled.y()-size.y()*scale.y()/4.0,position_unscaled.z());break;
        case SW: obj->setPosition(position_unscaled.x()-size.x()*scale.x()/4.0,position_unscaled.y()-size.y()*scale.y()/4.0,position_unscaled.z());break;
        case NW: obj->setPosition(position_unscaled.x()-size.x()*scale.x()/4.0,position_unscaled.y()+size.y()*scale.y()/4.0,position_unscaled.z());break;
        case ZOOM:break;
        }

        scaled = true;
    }

    //if out (again) scale back
    if (scaled
            && (pos.x()-(size.x()*scale.x()/2) > mousex //left
                    ||  pos.y()-(size.y()*scale.y()/2) > mousey
                    ||  pos.x()+(size.x()*scale.x()/2) < mousex
                    ||  pos.y()+(size.y()*scale.y()/2) < mousey
            )
    ){
        printf("unscale %i:%i\n",mousex,mousey);
        obj->setScale(initial_scale);
        obj->setPosition(position_unscaled);
        scaled = false;
    }

    return false;
}



} /* namespace intercation */
