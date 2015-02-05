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

#include "MaterialData.h"
//#include "utils.h"

#include <mars/utils/misc.h>

namespace osgviz {
  namespace interfaces {

    using namespace mars::utils;
    
    bool MaterialData::operator==(const MaterialData& other) const {
      return (exists == other.exists) &&
        (ambientFront == other.ambientFront) &&
        (diffuseFront == other.diffuseFront) &&
        (specularFront == other.specularFront) &&
        (emissionFront == other.emissionFront) &&
        (ambientBack == other.ambientBack) &&
        (diffuseBack == other.diffuseBack) &&
        (specularBack == other.specularBack) &&
        (emissionBack == other.emissionBack) &&
        (transparency == other.transparency) &&
        (shininess == other.shininess) &&
        (texturename == other.texturename);
    }


  } // end of namespace interfaces
} // end of namespace mars
