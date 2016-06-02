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

#include <osg/Texture2D>
#include <osg/Camera>
#include <osg/Group>
#include <osg/MatrixTransform>
#include <osg/GraphicsContext>
#include <osgViewer/GraphicsWindow>

#include "../../graphics/interfaces/OsgVizDefs.h"

#include <osgViewer/ViewerEventHandlers>


#include <stdio.h>

#include "../SuperView.h"
#include "HUDHoverScaler.h"


namespace osgviz{

class Window;

class HUDCallback;

class HUD:  public osg::Camera {
    public:

      HUD(osg::ref_ptr<osgviz::Window> window, int width, int height);
      ~HUD(void);
  

      void setViewPortSize(int width, int height);
      int getViewPortSizeX();
      int getViewPortSizeY();


      void resize(double width, double height);

      /**
       * Created an interactive object that scales on Hovering the mouse over it
       *
       * @param obj the Object to scale
       * @param size the size of the actual object obj->getPosition is the center, size is the area around it when the scale starts
       * @param scale how bit the object grows
       * @param type ZOOM,NE,SE,SW,NW, sets the fixed point when scaling
       * @param anchor_offset in case obj->getPosition is not the center, give the offset to the center (normally size/2)
       */
      void makeObjectScaleOnHover(osgviz::Object* obj, const osg::Vec3d size, const osg::Vec3d &scale, HUDHoverScaler::Type type = HUDHoverScaler::ZOOM, osg::Vec3d anchor_offset = osg::Vec3d(0,0,0));


      virtual bool addHudObject(osg::Node* node){
          return this->addChild(node);
      }


    private:

      HUDCallback* resizecallback;

      osg::ref_ptr<osgViewer::GraphicsWindow> gw;
      osg::ref_ptr<osgviz::Window> window;

      unsigned long id;
      Color myColor;
      osg::Vec3f myoff;

      double viewport_width, viewport_height;

      unsigned int cull_mask;

    };

} // end of namespace mars


#endif /* MARS_GRAPHICS_HUD_H */
