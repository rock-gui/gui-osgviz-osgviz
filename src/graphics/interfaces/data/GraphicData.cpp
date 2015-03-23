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

#include "GraphicData.h"

#define GET_VALUE(str, val, type)                    \
  if((it = config->find(str)) != config->end())      \
    val = it->second[0].get##type()

#define SET_VALUE(str, val)                              \
    (*config)[str][0] = ConfigItem(val)

namespace osgviz {
  namespace interfaces {

    GraphicData::GraphicData() {
      windowWidth = 720;
      windowHeight = 405;
      windowPosX = 0;
      windowPosY = 0;

      clearColor.r() = 0.55;
      clearColor.g() = 0.67;
      clearColor.b() = 0.88;
      clearColor.a() = 1.0;

      fogEnabled = true;
      fogDensity = 0.35;
      fogStart = 20.0;
      fogEnd = 500.0;

      fogColor.r() = 0.2;
      fogColor.g() = 0.2;
      fogColor.b() = 0.2;
      fogColor.a() = 1.0;
    }


  } // end of namespace interfaces
} // end of namespace mars
