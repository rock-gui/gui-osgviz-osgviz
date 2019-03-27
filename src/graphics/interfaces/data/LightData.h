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

#ifndef OSGVIZ_INTERFACES_LIGHT_DATA_H
#define OSGVIZ_INTERFACES_LIGHT_DATA_H

#include "../OsgVizDefs.h"

#include <string>

namespace osgviz {
    namespace interfaces {

        /**
        * LightData is a struct to exchange light information between the
        * Dialog_Add_Light, the MainWindow and the osg widget
        */
        class LightData {
        public:

            LightData();

            unsigned int index;
            std::string name; //light name
            osg::Vec3f pos; //light position
            osg::Vec3f lookAt; //light direction
            Color ambient; //color of the ambient part of the light
            Color diffuse; //color of the diffuse part of the light
            Color specular; //specular color of the light
            double constantAttenuation;
            double linearAttenuation;
            double quadraticAttenuation;
            int type;
            double angle; //angle of the spot cutoff
            double exponent; //spot exponent
            bool directional; //directional light
        }; // end of struct LightData

    } // end of namespace interfaces
} // end of namespace mars

#endif // MARS_INTERFACES_LIGHT_DATA_H
