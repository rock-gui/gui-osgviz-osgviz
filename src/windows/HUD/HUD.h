/*
*  Copyright 2011, 2012, DFKI GmbH Robotics Innovation Center
*
*  This file is part of the MARS simulation framework.
*
*  MARS is free software: you can redistribute it and/or modify
*  it under the terms of the GNU Lesser General Public License
*  as published by the Free Software Foundation, either version 3
*  of the License, or (at your option) any later version.
*
*  MARS is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU Lesser General Public License for more details.
*
*   You should have received a copy of the GNU Lesser General Public License
*   along with MARS.  If not, see <http://www.gnu.org/licenses/>.
*
*/

/**
* \file HUD.h
* \author Malte Roemmermann
* \brief The "HUD" class contains all necessary methods for rendering
* data into a texture.
*/

#ifndef OSGVIZ_WINDOWS_HUD_H
#define OSGVIZ_WINDOWS_HUD_H

#include <stdio.h>

#include <osg/Texture2D>
#include <osg/Camera>
#include <osg/Group>
#include <osg/MatrixTransform>
#include <osg/GraphicsContext>

#include <osgViewer/GraphicsWindow>
#include <osgViewer/ViewerEventHandlers>

#include "../../Object.h"

#include "../../graphics/interfaces/OsgVizDefs.h"

#include "../EventHandlers/MouseMoveEvent.h"
#include "../EventHandlers/ObjectSelector.h"
#include "../EventHandlers/WindowResizeEvent.h"

#include "HUDHoverScaler.h"

#include <iostream>

namespace osgviz{


    class HUD:  public osg::Camera {
    public:

        HUD(osg::ref_ptr<osg::GraphicsContext> graphicsContext, int width, int height, osg::Camera::ProjectionResizePolicy policy = osg::Camera::ProjectionResizePolicy::FIXED);
        ~HUD(void);


        void setViewPortSize(int width, int height);
        int getViewPortSizeX();
        int getViewPortSizeY();


        void resize(double width, double height);

        /**
        * @brief resize the hud to full viewport
        * @details [long description]
        */
        void resize();

        void changeObjectPositionByResize(osg::ref_ptr<osgviz::Object> obj, const osg::Vec3d init_position, const osg::Vec2d init_size);

        /**
        * Created an interactive object that scales on Hovering the mouse over it
        *
        * @param obj the Object to scale
        * @param size the size of the actual object obj->getPosition is the center, size is the area around it when the scale starts
        * @param scale how bit the object grows
        * @param type ZOOM,NE,SE,SW,NW, sets the fixed point when scaling
        * @param anchor_offset in case obj->getPosition is not the center, give the offset to the center (normally size/2)
        */
        void makeObjectScaleOnHover(osg::ref_ptr<osgviz::Object> obj, const osg::Vec3d size, const osg::Vec3d &scale, HUDHoverScaler::Type type = HUDHoverScaler::ZOOM, osg::Vec3d anchor_offset = osg::Vec3d(0,0,0));


        virtual bool addHudObject(osg::Node* node){
            return this->addChild(node);
        }

        void setMouseMoveEvent(MouseMoveEvent *mouseMoveEvent)
        {
            std::cout << "setMouse" <<std::endl;
            this->mouseMoveEvent = mouseMoveEvent;
            std::cout << "setMouse: " << this->mouseMoveEvent.get() <<std::endl;
        }

        void setWindowResizeEvent(WindowResizeEvent *windowResizeEvent)
        {
            this->windowResizeEvent = windowResizeEvent;
        }


        inline int getHudSizeX() {
            return hudSizeX;
        }

        inline int getHudSizeY() {
            return hudSizeY;
        }

        int getViewportSizeX();

        int getViewportSizeY();

        osg::Vec2d getConfigSize()
        {
            return osg::Vec2d(confSizeX, confSizeY);
        }

    private:

        //      unsigned long id;
        //      Color myColor;
        //      osg::Vec3f myoff;

        //double viewport_width, viewport_height;

        int hudSizeX,hudSizeY;

        int confSizeX, confSizeY;


        osg::ref_ptr<WindowResizeEvent> windowResizeEvent;
        osg::ref_ptr<MouseMoveEvent> mouseMoveEvent;

    };

} // end of namespace mars


#endif /* MARS_GRAPHICS_HUD_H */
