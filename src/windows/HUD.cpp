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


HUD::HoverScaler::HoverScaler(osgviz::Object* obj, const osg::Vec3d &size, const osg::Vec3d &scale, HUD* hud):obj(obj),scale(scale),size(size),hud(hud){
    scaled = false;
    initial_scale = obj->getScale();
}

bool HUD::HoverScaler::mouseMoved(const int& x, const int& y, const float& xNorm, const float& yNorm, const int& modifierMask){

    osg::Vec3 pos = obj->getPosition();

    //Norm is from -1 to 1, but we want 0 to 1
    int mousex = (xNorm+1.0)/2.0 * hud->getViewPortSizeX();
    int mousey = (yNorm+1.0)/2.0 * hud->getViewPortSizeY();

    printf("Mouse pos %i, %i (%.2f,%.2f)\n",mousex,mousey,xNorm,yNorm);
    printf("Objec pos %.2f, %.2f, %.2f, %.2f\n",pos.x(),pos.y(),pos.x()+size.x(),pos.y()+size.y());

    //if inside scale up
    if (        pos.x()-(size.x()/2) < mousex
            &&  pos.y()-(size.y()/2) < mousey
            &&  pos.x()+(size.x()/2) > mousex
            &&  pos.y()+(size.y()/2) > mousey
            && !scaled
        ){
        printf("inside\n");
        obj->setScale(scale);
        scaled = true;
    }

    //if out (again) scale back
    if ((       pos.x()-(size.x()*scale.x()/2) > mousex //left
            ||  pos.y()-(size.y()*scale.x()/2) > mousey
            ||  pos.x()+(size.x()*scale.x()/2) < mousex
            ||  pos.y()+(size.y()*scale.x()/2) < mousey
    ) && scaled){
        printf("outside\n");
        obj->setScale(initial_scale);
        scaled = false;
    }

    return false;
}



    HUD::HUD(osg::ref_ptr<osgviz::Window> window, int width, int height):window(window) {
      //hudCamera = new osg::Camera();
      gw=window->getGraphicsWindow();


      hudTerminalList = new osg::Group;
      hudscale = new osg::MatrixTransform;
      hudscale->setMatrix(osg::Matrix::scale(1.0, 1.0, 1.0));
      hudscale->addChild(hudTerminalList.get());
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

            //hudCamera->setRenderer(new osgViewer::Renderer(hudCamera));
            osg::Camera::addChild(hudscale.get());




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


    void HUD::createScalableObject(osgviz::Object* obj, const osg::Vec3d size, const osg::Vec3d &scale){
        window->addMouseMoveCallback(new HoverScaler(obj,size,scale,this));
    }

} // end of namespace graphics


