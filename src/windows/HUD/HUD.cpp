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

#include "../Window.h"

#include <cstdio>

#include "../SuperView.h"
#include "../../plugins/Object.h"

namespace osgviz{

    HUD::HUD(osg::ref_ptr<osgviz::Window> window, int width, int height):window(window) {
      //hudCamera = new osg::Camera();
      gw=window->getGraphicsWindow();

      cull_mask = 0;
      //x1 = x2 = y1 = y2 = 0.0;
      //window = win;


      //setViewSize(width,height);

      int x,y,wwidth, wheight;

      gw->getWindowRectangle (x,y,wwidth,wheight);
      setViewPortSize(width,height);
      resize(wwidth,wheight);
      gw->resizedImplementation(x, y, wwidth, wheight);


//      resizecallback = new HUDCallback(this);
//      gw->setResizedCallback(resizecallback);




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
            this->setProjectionMatrix(osg::Matrix::ortho2D(0,width,0,height));
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

    }

    HUD::~HUD(void) {
    }


    void HUD::setViewPortSize(int width, int height) {
        viewport_height = height;
        viewport_width = width;
        this->setViewport(0, 0, width, height);
    }

    int HUD::getViewPortSizeX() {
         return viewport_width;
    }

    int HUD::getViewPortSizeY() {
        return viewport_height;
    }

    void HUD::resize(double width, double height) {
      this->setProjectionMatrix(osg::Matrix::ortho2D(0, width, 0, height));

    }


    void HUD::makeObjectScaleOnHover(osgviz::Object* obj, const osg::Vec3d size, const osg::Vec3d &scale, HUDHoverScaler::Type type, osg::Vec3d anchor_offset){
        window->addMouseMoveCallback(new HUDHoverScaler(obj,size,scale,type,anchor_offset,this));
    }

} // end of namespace graphics


