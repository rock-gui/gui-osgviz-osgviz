/*
* HUDHoverScaler.cpp
*
*  Created on: 02.06.2016
*      Author: planthaber
*/

#include "HUDHoverScaler.h"

#include "HUD.h"

namespace osgviz {

    HUDHoverScaler::HUDHoverScaler(osg::ref_ptr<osgviz::Object> obj, const osg::Vec3d &size, const osg::Vec3d &scale, Type type, osg::Vec3d anchor_offset, HUD* hud)
        :obj(obj), scale(scale), size(size), anchor_offset(anchor_offset), type(type), hud(hud){
            scaled = false;
            initial_scale = obj->getScale();
            if (scale.x() == 0 || scale.y() == 0 || scale.z() == 0){
                //printf("%s scale cannot be 0\n",__PRETTY_FUNCTION__);
            }
    }

    bool HUDHoverScaler::mouseMoved(const int& x, const int& y, const float& xNorm, const float& yNorm, const int& modifierMask){

        osg::Vec3 pos = obj->getPosition() + anchor_offset;

        //Norm is from -1 to 1, but we want 0 to 1
        //    int mousex = (xNorm+1.0)/2.0 * hud->getHudSizeX();
        //    int mousey = (yNorm+1.0)/2.0 * hud->getHudSizeY();

        int mousex = (xNorm+1.0)/2.0 * hud->getViewportSizeX();
        int mousey = (yNorm+1.0)/2.0 * hud->getViewportSizeY();


        //convert mouse coords (screen pixels to orto2d martic in hud

        osg::Vec3d mpos(mousex, mousey, 0);

        osg::Matrixd world2screen = (hud->getViewMatrix() * hud->getProjectionMatrix() * hud->getViewport()->computeWindowMatrix());
        osg::Matrixd screen2world =  osg::Matrixd::inverse(world2screen);

        osg::Vec3d positionInWorld = mpos * screen2world;


        //if inside scale up
        if (!scaled
            && pos.x()-(size.x()/2) < positionInWorld.x()
            && pos.y()-(size.y()/2) < positionInWorld.y()
            &&  pos.x()+(size.x()/2) > positionInWorld.x()
            &&  pos.y()+(size.y()/2) > positionInWorld.y()
            ){

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
                case ZOOM: position_scaled = pos-anchor_offset;
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

            if (    position_scaled.x()-(size.x()*scale.x()/2) > positionInWorld.x() //left
                ||  position_scaled.y()-(size.y()*scale.y()/2) > positionInWorld.y()
                ||  position_scaled.x()+(size.x()*scale.x()/2) < positionInWorld.x()
                ||  position_scaled.y()+(size.y()*scale.y()/2) < positionInWorld.y()
                ){
                    obj->setScale(initial_scale);
                    obj->setPosition(position_unscaled);
                    scaled = false;
            }
        }

        return false;
    }



} /* namespace intercation */
