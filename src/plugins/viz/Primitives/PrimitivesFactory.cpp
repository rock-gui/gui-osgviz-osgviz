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

#include <osg/Geometry>
#include <osg/LineWidth>
#include <osg/Geode>
#include <osg/ComputeBoundsVisitor>

namespace osgviz {


OSGVIZ_PLUGIN(PrimitivesFactory);

PrimitivesFactory::PrimitivesFactory(lib_manager::LibManager *theManager):OsgVizVisualizerPlugin(theManager) {}

PrimitivesFactory::~PrimitivesFactory() {}


osg::ref_ptr<Object> PrimitivesFactory::createAxes(float scale,bool blabels){
	osg::ref_ptr<Object> obj = createObject();
	osg::ref_ptr<osg::Node> content = AxesNode::create(scale,blabels);
	obj->addChild(content);
	obj->setName("Axes");
	return obj;
}

osg::ref_ptr<Object> PrimitivesFactory::createGrid(int rows,int cols,float dx, float dy, bool show_coordinates, const ::osg::Vec4 &color){
	osg::ref_ptr<Object> obj = createObject();
	osg::ref_ptr<osg::Node> content = GridNode::create(rows,cols,dx, dy, show_coordinates, color);
	obj->addChild(content);
	obj->setName("Grid");
	return obj;
}

osg::ref_ptr<Object> PrimitivesFactory::createArrow(){
	osg::ref_ptr<Object> node = new ArrowNode();
	node->setName("Arrow");
	return node;
}

osg::ref_ptr<Object> PrimitivesFactory::createBoundingBox(osg::Group* object){

	osg::ref_ptr<Object> box = new Object();
	osg::ref_ptr<osg::Geometry> selectionBox;
	osg::ref_ptr<osg::Geode> selectionBoxGeode;
	osg::ref_ptr<osg::Vec3Array> points;
	osg::ref_ptr<osg::Vec4Array> colors;
	osg::ref_ptr<osg::Vec3Array> normals;


	//create bounding box
	osg::ComputeBoundsVisitor  cbv;

	//the object location might be at 0,0,0, so we traverse its children
	for (int i=0; i< object->getNumChildren();++i){
		object->getChild(i)->accept(cbv);
	}
	osg::BoundingBox &bb(cbv.getBoundingBox());

	selectionBoxGeode = new osg::Geode();
	selectionBoxGeode->setName("Robot selection box");
	selectionBox = new osg::Geometry();

	points = new osg::Vec3Array;
	colors = new osg::Vec4Array;
	normals = new osg::Vec3Array;

	for (int i = 0;i<8;i++){
		for (int j = 0;j<8;j++){
			points->push_back(bb.corner(i));
			points->push_back(bb.corner(j));
		}

	}


	colors->push_back(osg::Vec4(1.0,1.0,1.0,1));

	normals->push_back(osg::Vec3(0.0f,-1.0f,0.0f));

	selectionBox->setVertexArray(points.get());
	selectionBox->setColorArray(colors.get(),osg::Array::BIND_OVERALL);
	selectionBox->setNormalArray(normals, osg::Array::BIND_OVERALL);
	selectionBox->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES,0,points->size()));


	selectionBox->getOrCreateStateSet()->setAttribute( new osg::LineWidth(2.0f),osg::StateAttribute::ON );
	selectionBoxGeode->getOrCreateStateSet()->setMode( GL_LIGHTING, ::osg::StateAttribute::OFF );

	selectionBoxGeode->addDrawable(selectionBox);

	box->addChild(selectionBoxGeode);

	return box;
}
} /* namespace osgviz */
