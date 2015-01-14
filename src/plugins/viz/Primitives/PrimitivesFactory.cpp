/*
 * Primitives.cpp
 *
 *  Created on: 09.01.2015
 *      Author: planthaber
 */

#include "PrimitivesFactory.h"

#include "Primitives/AxesNode.hpp"
#include "Primitives/GridNode.hpp"

namespace osgviz {


OSGVIZ_PLUGIN(PrimitivesFactory);

PrimitivesFactory::PrimitivesFactory(mars::lib_manager::LibManager *theManager):OsgVizVisualizerPlugin(theManager) {}

PrimitivesFactory::~PrimitivesFactory() {}


Object* PrimitivesFactory::createAxes(){
	Object *obj = createObject();
	osg::ref_ptr<osg::Node> content = AxesNode::create();
	obj->setObject(content);
	return obj;
}

Object* PrimitivesFactory::createGrid(int rows,int cols,float dx, float dy, bool show_coordinates, const ::osg::Vec4 &color){
	Object *obj = createObject();
	osg::ref_ptr<osg::Node> content = GridNode::create(rows,cols,dx, dy, show_coordinates, color);
	obj->setObject(content);
	return obj;
}

} /* namespace osgviz */
