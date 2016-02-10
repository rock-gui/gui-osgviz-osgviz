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

namespace osgviz{

class Window;

class HUDCallback;

class HUD:  public osg::Camera
            {

    public:
      HUD(osg::ref_ptr<osgViewer::GraphicsWindow> gw, int width, int height);
      ~HUD(void);
  

      //void addHudObject(osg::Node *elem);


      void getSize(sReal &width, sReal &height);
      void setViewSize(double width, double height);
      void getOffset(Vector &offset);
      void resize(double width, double height);

//      void addHudObject(osgviz::Object *elem);

      virtual bool addHudObject(osg::Node* node){
          return hudTerminalList->addChild(node);
      }


//      void addHUDElement(HUDElement *elem);
//      void removeHUDElement(HUDElement *elem);

      /**
       * from osg::ResizedCallback
       */
      virtual void resizedImplementation (osg::GraphicsContext *gc, int x, int y, int width, int height);


//	virtual void emitPickEvent(int x, int y) {printf("emitPickEvent x:%i, y: %i\n",x,y);}
//	//virtual void mouseMove(int x, int y) {printf("mouseMove x:%i, y: %i\n",x,y);}
//	virtual void mousePress(int x, int y, int button) {printf("mousePress x:%i, y: %i\n",x,y);}
//	virtual void mouseRelease(int x, int y, int button) {printf("mouseRelease x:%i, y: %i\n",x,y);}



//	virtual bool clicked(const int &buttonMask, const osg::Vec2d &cursor, const osg::Vec3d &world, const osg::Vec3d &local, osgviz::Clickable* object, WindowInterface* window = NULL);
//	virtual bool dragged(const int &buttonMask, const osg::Vec2d &cursor, const osg::Vec3d &world, const osg::Vec3d &local, osgviz::Clickable* object, WindowInterface* window = NULL);
//	virtual bool pointerEvent(int buttonMask, const osg::Vec3d &world, const osg::Vec3d &local);
//	virtual bool keyEvent(int key, bool keyDown);

    protected:

//	  	bool mousePosition(const int &windowposx, const int &windowposy, int &hudposx, int &hudposy);
//
//	  	bool localPosition(const osgviz::Object* obj, const osg::Vec3d &global, osg::Vec3d &local);

//	  	bool inside(const osgviz::Object* obj, osg::Vec3d &local);

    private:
      //osg::ref_ptr<osg::Camera> hudCamera;
      osg::ref_ptr<osg::Group> hudTerminalList;
      osg::ref_ptr<osg::MatrixTransform> hudscale;

      HUDCallback* resizecallback;

//    	osg::ref_ptr<osg::Image> hudImage;
//    	osg::ref_ptr<osg::Texture2D> hudTexture;

      osg::ref_ptr<osgViewer::GraphicsWindow> gw;

      unsigned long id;
      Color myColor;
      Vector myoff;

      double hud_width, hud_height, window_width, window_height;
      double mousescale_x,mousescale_y;

      double x1, x2, y1, y2;
      unsigned int row_index;
      unsigned int cull_mask;
      //void initialize(osgViewer::GraphicsWindow* gw);


      //osg::ref_ptr<osg::Camera> hudcam;
      //osgviz::Window* window;

      /**
       * should not be used!
       */
      virtual bool addChild(osg::Node* node){fprintf(stderr,"please use addHudElement() instead od addChild\n");return false;}



    };


class HUDCallback: public osg::GraphicsContext::ResizedCallback{

public:

    HUDCallback(HUD* hud):myhud(hud){};

    /**
     * from osg::ResizedCallback
     */
    void resizedImplementation (osg::GraphicsContext *gc, int x, int y, int width, int height){
        myhud->resizedImplementation(gc,x,y,width,height);
    }


private:
    HUD* myhud;

};



} // end of namespace mars


#endif /* MARS_GRAPHICS_HUD_H */
