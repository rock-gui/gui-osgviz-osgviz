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


#include "HUDPositionChanger.h"


#include <cstdio>



namespace osgviz{

    HUD::HUD(osg::ref_ptr<osg::GraphicsContext> graphicsContext, int width, int height, osg::Camera::ProjectionResizePolicy policy) {

      // hud make resize to hud according to the viewport

    hudSizeX = width;
    hudSizeY = height;

    confSizeX = width;
    confSizeY = height;

    // Keep the projection matrix fixed, despite window resizes.
    // this will stretch or constrict the object drawn in hud
    this->setProjectionResizePolicy(policy);

    this->setGraphicsContext(graphicsContext);
    //hudCamera->setInheritanceMask(0x0); // <-- this seems to be bad
    //hudCamera->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    this->setClearMask(GL_DEPTH_BUFFER_BIT);
    //hudCamera->setClearMask(0);
    this->setClearColor(osg::Vec4(1.0f, 0.0f, 0.0f, 0.2f));
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
    this->setProjectionMatrix(osg::Matrix::ortho2D(0,hudSizeX,0,hudSizeY));
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


    int HUD::getViewportSizeX() {
        return this->getViewport()->width();
    }

    int HUD::getViewportSizeY() {
        return this->getViewport()->height();
    }

    void HUD::resize(double width, double height) {
        hudSizeX = width;
        hudSizeY = height;
        this->setProjectionMatrix(osg::Matrix::ortho2D(0, hudSizeX, 0, hudSizeY));
    }

    void HUD::resize() {
      resize(getViewportSizeX(), getViewportSizeY());
    }

    void HUD::changeObjectPositionByResize(osgviz::Object *obj, const osg::Vec3d init_position)
    {
      HUDPositionChanger *positionChanger = new HUDPositionChanger(obj, init_position, this);

      if (windowResizeEvent.get() != NULL)
        windowResizeEvent->addCallback(positionChanger);
      else
        throw std::runtime_error("HUD: the WindowResizeEvent is undefined.");

      // set right position according to the size of window
      positionChanger->windowResized(getViewportSizeX(), getViewportSizeY());

      // rescale the object
      // the object size is given relative to the hud size
      // since the hud will be always resized to the window size
      // we should rescale the object to keep the right proportion
      float scaleFactor_x = getViewportSizeX() / (float)confSizeX;
      float scaleFactor_y = getViewportSizeY() / (float)confSizeY;

      obj->setScale(scaleFactor_x, scaleFactor_y, 1.0);      
    }


    void HUD::makeObjectScaleOnHover(osgviz::Object* obj, const osg::Vec3d size, const osg::Vec3d &scale, HUDHoverScaler::Type type, osg::Vec3d anchor_offset){
      if (mouseMoveEvent.get() != NULL)
        mouseMoveEvent->addCallback(new HUDHoverScaler(obj,size,scale,type,anchor_offset,this));
      else
        throw std::runtime_error("HUD: the MouseMoveEvent is undefined.");
    }

} // end of namespace graphics