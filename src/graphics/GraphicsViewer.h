/*
 *  Copyright 2011, 2012 DFKI GmbH Robotics Innovation Center
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
 * \file GraphicsViewer.h
 * \author Malte Roemmermann
 * \brief The "GraphicsViewer" 
 */

#ifndef OSGVIZ_GRAPHICS_VIEWER_H
#define OSGVIZ_GRAPHICS_VIEWER_H

#include <osgViewer/CompositeViewer>
#include "interfaces/GuiEventInterface.h"

namespace osgviz {
  namespace graphics {

    class GraphicsViewer : public osgViewer::CompositeViewer {

    public:
      GraphicsViewer(GuiEventInterface *_guiEventHandler);
      ~GraphicsViewer(void);

      void eventTraversal();

    private:
      GuiEventInterface *guiEventHandler;
    }; // end of class GraphicsViewer

  } // end of namespace graphics
} // end of namespace mars

#endif /* MARS_GRAPHICS_VIEWER_H */
