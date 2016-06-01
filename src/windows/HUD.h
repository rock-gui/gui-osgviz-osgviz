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

#include "../graphics/interfaces/OsgVizDefs.h"
//#include <osgViz/graphics/interfaces/GraphicsEventInterface.h>

#include <osgViewer/ViewerEventHandlers>


#include <stdio.h>

#include "SuperView.h"
#include "../interfaces/MouseMoveCallback.h"
#include "../plugins/Object.h"

namespace osgviz{

class Window;

class HUDCallback;

class HUD:  public osg::Camera {
    public:

    struct HoverScaler: public osgviz::MouseMoveCallback, public osg::Referenced{
        HoverScaler(osgviz::Object* obj, const osg::Vec3d& size, const osg::Vec3d &scale, HUD* hud);
        virtual bool mouseMoved(const int& x, const int& y, const float& xNorm, const float& yNorm, const int& modifierMask);

    private:
        osgviz::Object* obj;
        osg::Vec3d initial_scale,scale,size;
        bool scaled;
        HUD* hud;
    };

      HUD(osg::ref_ptr<osgviz::Window> window, int width, int height);
      ~HUD(void);
  

      void setViewPortSize(int width, int height);
      int getViewPortSizeX();
      int getViewPortSizeY();


      void resize(double width, double height);

      void createScalableObject(osgviz::Object* obj, const osg::Vec3d size, const osg::Vec3d &scale);


      virtual bool addHudObject(osg::Node* node){
          return hudTerminalList->addChild(node);
      }


    private:
      //osg::ref_ptr<osg::Camera> hudCamera;
      osg::ref_ptr<osg::Group> hudTerminalList;
      osg::ref_ptr<osg::MatrixTransform> hudscale;

      HUDCallback* resizecallback;

//    	osg::ref_ptr<osg::Image> hudImage;
//    	osg::ref_ptr<osg::Texture2D> hudTexture;

      osg::ref_ptr<osgViewer::GraphicsWindow> gw;
      osg::ref_ptr<osgviz::Window> window;

      unsigned long id;
      Color myColor;
      osg::Vec3f myoff;

      double viewport_width, viewport_height;

      unsigned int cull_mask;
      /**
       * should not be used!
       */
      virtual bool addChild(osg::Node* node){fprintf(stderr,"please use addHudElement() instead od addChild\n");return false;}



    };


//class HUDCallback: public osg::GraphicsContext::ResizedCallback{
//
//public:
//
//    HUDCallback(HUD* hud):myhud(hud){};
//
//    /**
//     * from osg::ResizedCallback
//     */
//    void resizedImplementation (osg::GraphicsContext *gc, int x, int y, int width, int height){
//        myhud->resizedImplementation(gc,x,y,width,height);
//    }
//
//
//private:
//    HUD* myhud;
//
//};



} // end of namespace mars


#endif /* MARS_GRAPHICS_HUD_H */
