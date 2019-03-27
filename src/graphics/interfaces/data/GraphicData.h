/*
*  Copyright 2011, 2012, 2014, DFKI GmbH Robotics Innovation Center
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

#ifndef OSGVIZ_INTERFACES_GRAPHIC_DATA_H
#define OSGVIZ_INTERFACES_GRAPHIC_DATA_H


#include "../OsgVizDefs.h"

namespace osgviz {
    namespace interfaces {

        // forward declaration
        class LoadCenter;

        class GraphicData {
        public:
            GraphicData();

            Color clearColor;
            bool fogEnabled;
            sReal fogDensity;
            sReal fogStart;
            sReal fogEnd;
            Color fogColor;
        };

    } // end of namespace interfaces
} // end of namespace mars

#endif /* MARS_INTERFACES_GRAPHIC_DATA_H */
