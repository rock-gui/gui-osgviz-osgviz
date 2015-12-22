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

osg::ref_ptr<PrimitivesFactory::Shape> PrimitivesFactory::createShape(Shapes shape, const float &sizex,const float &sizey,const float &sizez){
    osg::ref_ptr<Shape> obj = new Shape();
    obj->geode = new osg::Geode();

    switch(shape){
    case BOX: obj->shape = new osg::Box(osg::Vec3(0,0,0),sizex,sizey,sizez); break;
    case CAPSULE: break;
    case CONE: break;
    case CYLINDER: break;
    case SPHERE: break;
    }
    obj->drawable = new osg::ShapeDrawable(obj->shape);
    obj->geode->addDrawable(obj->drawable);
    obj->addChild(obj->geode);
    return obj;
}


osg::ref_ptr<PrimitivesFactory::BoundingBox> PrimitivesFactory::createBoundingBox(osg::Group* object){

	osg::ref_ptr<BoundingBox> box = new BoundingBox();



	//create bounding box
	osg::ComputeBoundsVisitor  cbv;

	//the object location might be at 0,0,0, so we traverse its children
	for (int i=0; i< object->getNumChildren();++i){
		object->getChild(i)->accept(cbv);
	}
	osg::BoundingBox &bb(cbv.getBoundingBox());

	box->selectionBoxGeode = new osg::Geode();
	box->selectionBoxGeode->setName("Robot selection box");
	box->selectionBox = new osg::Geometry();

	box->points = new osg::Vec3Array;
	box->colors = new osg::Vec4Array;
	box->normals = new osg::Vec3Array;

	for (int i = 0;i<8;i++){
		for (int j = 0;j<8;j++){
		    box->points->push_back(bb.corner(i));
		    box->points->push_back(bb.corner(j));
		}

	}


	box->colors->push_back(osg::Vec4(1.0,1.0,1.0,1));

	box->normals->push_back(osg::Vec3(0.0f,-1.0f,0.0f));

	box->selectionBox->setVertexArray(box->points.get());
	box->selectionBox->setColorArray(box->colors.get(),osg::Array::BIND_OVERALL);
	box->selectionBox->setNormalArray(box->normals, osg::Array::BIND_OVERALL);
	box->selectionBox->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES,0,box->points->size()));


	box->selectionBox->getOrCreateStateSet()->setAttribute( new osg::LineWidth(2.0f),osg::StateAttribute::ON );
	box->selectionBoxGeode->getOrCreateStateSet()->setMode( GL_LIGHTING, ::osg::StateAttribute::OFF );

	box->selectionBoxGeode->addDrawable(box->selectionBox);

	box->addChild(box->selectionBoxGeode);

	return box;
}
} /* namespace osgviz */
