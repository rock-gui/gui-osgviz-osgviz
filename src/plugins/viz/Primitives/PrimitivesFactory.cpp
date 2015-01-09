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

Primitive* PrimitivesFactory::createAxes(){
	Primitive *prim = new Primitive();
	prim->setRootNode(getRootNode());
	osg::ref_ptr<osg::Node> obj = AxesNode::create();
	prim->setPrimitive(obj);
	return prim;
}

Primitive* PrimitivesFactory::createGrid(int rows,int cols,float dx, float dy, bool show_coordinates, const ::osg::Vec4 &color){
	Primitive *prim = new Primitive();
	prim->setRootNode(getRootNode());
	osg::ref_ptr<osg::Node> obj = GridNode::create(rows,cols,dx, dy, show_coordinates, color);
	prim->setPrimitive(obj);
	return prim;
}

} /* namespace osgviz */
