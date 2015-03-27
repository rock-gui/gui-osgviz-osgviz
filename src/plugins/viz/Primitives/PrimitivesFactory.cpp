/*
 * Primitives.cpp
 *
 *  Created on: 09.01.2015
 *      Author: planthaber
 */

#include "PrimitivesFactory.h"

#include "Primitives/ArrowNode.h"
#include "Primitives/AxesNode.hpp"
#include "Primitives/GridNode.hpp"

namespace osgviz {


OSGVIZ_PLUGIN(PrimitivesFactory);

PrimitivesFactory::PrimitivesFactory(lib_manager::LibManager *theManager):OsgVizVisualizerPlugin(theManager) {}

PrimitivesFactory::~PrimitivesFactory() {}


osg::ref_ptr<Object> PrimitivesFactory::createAxes(float scale,bool blabels){
	osg::ref_ptr<Object> obj = createObject();
	osg::ref_ptr<osg::Node> content = AxesNode::create(scale,blabels);
	obj->addChild(content);
	return obj;
}

osg::ref_ptr<Object> PrimitivesFactory::createGrid(int rows,int cols,float dx, float dy, bool show_coordinates, const ::osg::Vec4 &color){
	osg::ref_ptr<Object> obj = createObject();
	osg::ref_ptr<osg::Node> content = GridNode::create(rows,cols,dx, dy, show_coordinates, color);
	obj->addChild(content);
	return obj;
}

osg::ref_ptr<Object> PrimitivesFactory::createArrow(){
	return new ArrowNode();
}

} /* namespace osgviz */
