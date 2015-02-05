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

#include "LightData.h"
#include <mars/utils/mathUtils.h>
#include "../OsgVizDefs.h"

#define GET_VALUE(str, val, type)                    \
  if((it = config->find(str)) != config->end())      \
  val = it->second[0].get##type()

#define GET_OBJECT(str, val, type)              \
  if((it = config->find(str)) != config->end())      \
    type##FromConfigItem(&it->second[0], &val);

#define SET_VALUE(str, val)                              \
    (*config)[str][0] = ConfigItem(val)

#define SET_OBJECT(str, val, type)                                      \
    (*config)[str][0] = ConfigItem(std::string());                      \
    type##ToConfigItem(&(*config)[str][0], &val);

namespace osgviz {
  namespace interfaces {

    using namespace mars::utils;


  } // end of namespace interfaces
} // end of namespace mars
