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
 * \file HUD.cpp
 * \author Malte Roemmermann
 * \brief The "HUD" class contains all necessary methods for rendering
 * data into a texture.
 */

#include "HUD.h"

#include "Window.h"

#include <cstdio>

#include <osgViz/windows/SuperView.h>

namespace osgviz{

    HUD::HUD(osgviz::Window* win, int width, int height) {
      //hudCamera = new osg::Camera();



      hudTerminalList = new osg::Group;
      hudscale = new osg::MatrixTransform;
      hudscale->setMatrix(osg::Matrix::scale(1.0, 1.0, 1.0));
      hudscale->addChild(hudTerminalList.get());
      cull_mask = 0;
      x1 = x2 = y1 = y2 = 0.0;
      window = win;

      osgViewer::GraphicsWindow* gw =  win->getGraphicsWindow();

      setViewSize(width,height);

      int x,y,wwidth, wheight;

      gw->getWindowRectangle (x,y,wwidth,wheight);
      resize(wwidth,wheight);

      setViewSize(width,height);

      resizecallback = new HUDCallback(this);
      gw->setResizedCallback(resizecallback);




            this->setGraphicsContext(gw);
            //hudCamera->setInheritanceMask(0x0); // <-- this seems to be bad
            //hudCamera->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            this->setClearMask(GL_DEPTH_BUFFER_BIT);
            //hudCamera->setClearMask(0);
            this->setClearColor(osg::Vec4(1.0f, 0.0f, 0.0f, 0.0f));
            //hudCamera->setComputeNearFarMode(osg::Camera::DO_NOT_COMPUTE_NEAR_FAR);
            //this->setViewport(0, 0, hud_width, hud_height);
            //hudCamera->setRenderOrder(osg::Camera::PRE_RENDER);
            this->setRenderOrder(osg::Camera::POST_RENDER);
            //hudCamera->setRenderOrder(osg::Camera::NESTED_RENDER, 10);
      #ifdef WIN32
            //hudCamera->setRenderTargetImplementation(osg::Camera::PIXEL_BUFFER);
      #else
            //hudCamera->setRenderTargetImplementation(osg::Camera::FRAME_BUFFER_OBJECT);
      #endif
            this->setProjectionMatrix(osg::Matrix::ortho2D(0,hud_width,0,hud_height));
            this->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
            this->setViewMatrix(osg::Matrix::identity());

            this->getOrCreateStateSet()->setMode(GL_LIGHTING,
                                                      osg::StateAttribute::OFF |
                                                      osg::StateAttribute::OVERRIDE |
                                                      osg::StateAttribute::PROTECTED);
            this->getOrCreateStateSet()->setMode(GL_DEPTH_TEST,
                                                      osg::StateAttribute::OFF |
                                                      osg::StateAttribute::OVERRIDE |
                                                      osg::StateAttribute::PROTECTED);
            this->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN |
                                                               osg::StateAttribute::OVERRIDE |
                                                               osg::StateAttribute::PROTECTED);
            this->getOrCreateStateSet()->setMode(GL_BLEND,osg::StateAttribute::ON |
                                                      osg::StateAttribute::OVERRIDE |
                                                      osg::StateAttribute::PROTECTED);
            this->setAllowEventFocus(true);

            //hudCamera->setRenderer(new osgViewer::Renderer(hudCamera));
            osg::Camera::addChild(hudscale.get());




    }

    HUD::~HUD(void) {
        delete resizecallback;
    }
  




    void HUD::setViewSize(double width, double height) {
      hud_width = width;
      hud_height = height;
      resize(window_width,window_height);
    }

    void HUD::resize(double width, double height) {

        printf("resize\n");


      window_width = width;
      window_height = height;
      double scale_x = window_width / hud_width;
      double scale_y = window_height / hud_height;
      hudscale->setMatrix(osg::Matrix::scale(scale_x, scale_y, 1.0));

      mousescale_x = hud_width / window_width;
      mousescale_y = hud_height / window_height;

      this->setProjectionMatrix(osg::Matrix::ortho2D(x1, x2+window_width,
                                                          y1, y2+window_height));
      this->setViewport(0, 0, hud_width, hud_height);
    }



    void HUD::resizedImplementation(osg::GraphicsContext* gc, int x, int y, int width, int height) {

        printf("resizedImplementation\n");

        this->resize(width,height);

    	//call the standard implementation
        gc->resizedImplementation(x, y, width, height);

    }

//	bool HUD::mousePosition(const int &windowposx, const int &windowposy, int &hudposx, int &hudposy){
//		hudposx = windowposx*mousescale_x;
//		hudposy = windowposy*mousescale_y;
//		return true;
//	}
//
//	bool HUD::localPosition(const osgviz::Object* obj, const osg::Vec3d &global, osg::Vec3d &local){
//		osg::Vec3d pos = obj->getPosition();
//		osg::Vec3d scale = obj->getScale();
//		local.x() = global.x() - pos.x();
//		local.y() = global.y() - pos.y();
//		local.x() /= scale.x();
//		local.y() /= scale.y();
//		return true;
//	}

} // end of namespace graphics


