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

#ifndef OSGVIZ_GRAPHICS_HUD_H
#define OSGVIZ_GRAPHICS_HUD_H

#include <osg/Texture2D>
#include <osg/Camera>
#include <osg/Group>
#include <osg/MatrixTransform>
#include <osgViewer/GraphicsWindow>

#include "interfaces/OsgVizDefs.h"



#include "HUDElement.h"


namespace osgviz {
  namespace graphics {

    class HUD {

    public:
      HUD(unsigned long id);
      ~HUD(void);
  
      void init(osgViewer::GraphicsWindow *gw);
      void init(sReal width, sReal height);

      osg::ref_ptr<osg::Texture2D> getTexture(void);
      osg::ref_ptr<osg::Camera> getCamera(void);
      void getSize(sReal &width, sReal &height);
      void setViewSize(double width, double height);
      void getOffset(Vector &offset);
      void resize(double width, double height);
      void setCullMask(unsigned int cull_mask);
      void addHUDElement(HUDElement *elem);
      void removeHUDElement(HUDElement *elem);
      void switchCullElement(int key);
      void switchElementVis(int num_element);
      void setViewOffsets(double x1, double y1, double x2, double y2);

    private:
      osg::ref_ptr<osg::Camera> hudCamera;
      osg::ref_ptr<osg::Group> hudTerminalList;
      osg::ref_ptr<osg::MatrixTransform> scaleTransform;
      std::vector<HUDElement*> elements;
      sReal swidth;
      sReal sheight;
      unsigned long id;
      Color myColor;
      Vector myoff;
      unsigned int width, height;
      double view_width, view_height;
      double x1, x2, y1, y2;
      unsigned int row_index;
      unsigned int cull_mask;
      void initialize(osgViewer::GraphicsWindow* gw);

    }; // end of class HUD 

  } // end of namespace graphics
} // end of namespace mars

#endif /* MARS_GRAPHICS_HUD_H */
