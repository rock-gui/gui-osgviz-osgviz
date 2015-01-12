/*
 * Object.cpp
 *
 *  Created on: 08.01.2015
 *      Author: planthaber
 */

#include "ModelViewFactory.h"

#include <stdio.h>


namespace osgviz {

OSGVIZ_PLUGIN(ModelViewFactory);


ModelViewFactory::ModelViewFactory(mars::lib_manager::LibManager *theManager):OsgVizVisualizerPlugin(theManager){
}

ModelViewFactory::~ModelViewFactory() {
	for (std::vector<Object*>::iterator it = instances.begin();it != instances.end();it++){
		delete *it;
	}
}

} /* namespace osgviz */


