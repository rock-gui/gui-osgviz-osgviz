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
#include "Primitives/WireframeBox.hpp"
#include "Primitives/LinesNode.h"
#include "Primitives/RingNode.hpp"
#include "Primitives/SphereNode.hpp"


#include <osg/Geometry>
#include <osg/LineWidth>
#include <osg/Geode>
#include <osg/ComputeBoundsVisitor>
#include <osg/Version>

#include <osgDB/ReadFile>

namespace osgviz {


//OSGVIZ_PLUGIN(PrimitivesFactory);

PrimitivesFactory::PrimitivesFactory():Module() {}

PrimitivesFactory::~PrimitivesFactory() {}


osg::ref_ptr<Object> PrimitivesFactory::createAxes(float scale,bool blabels){
    osg::ref_ptr<Object> obj = new Object();
    osg::ref_ptr<osg::Node> content = AxesNode::create(scale,blabels);
    obj->addChild(content);
    obj->setName("Axes");
    return obj;
}

osg::ref_ptr<Object> PrimitivesFactory::createRingNode(const float radius, const float height, const float thickness)
{
    return new RingNode(radius, height, thickness);
}

osg::ref_ptr<Object> PrimitivesFactory::createSphereNode(double x, double y, double z, double radius)
{
    return new SphereNode(x, y, z, radius);
}

osg::ref_ptr< Object > PrimitivesFactory::createWireframeBox(const double xSize, const double ySize, const double zSize) const
{
    osg::ref_ptr<Object> obj = new Object();
    osg::ref_ptr<osg::Node> content = WireframeBox::create(xSize, ySize, zSize);
    obj->addChild(content);
    obj->setName("WireframeBox");
    return obj;  
}



osg::ref_ptr<Object> PrimitivesFactory::createGrid(int rows,int cols,float dx, float dy, bool show_coordinates, const ::osg::Vec4 &color){
    osg::ref_ptr<Object> obj = new Object();
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

osg::ref_ptr<Object> PrimitivesFactory::createLinesNode(osg::Vec4 color)
{
    osg::ref_ptr<Object> node = new LinesNode(color);
    node->setName("Lines");
    return node;
}

osg::ref_ptr<PrimitivesFactory::Shape> PrimitivesFactory::createShape(Shapes shape, const float &sizex,const float &sizey,const float &sizez){
    osg::ref_ptr<Shape> obj = new Shape();
    obj->geode = new osg::Geode();

    switch(shape){
    case BOX: obj->shape = new osg::Box(osg::Vec3(0,0,0),sizex,sizey,sizez); break;
    case CAPSULE: obj->shape = new osg::Capsule(osg::Vec3(0,0,0),sizex,sizez); break;break;
    case CONE: obj->shape = new osg::Cone(osg::Vec3(0,0,0),sizex,sizez); break;break;
    case CYLINDER: obj->shape = new osg::Cylinder(osg::Vec3(0,0,0),sizex,sizez); break;break;
    case SPHERE: obj->shape = new osg::Sphere(osg::Vec3(0,0,0),sizex); break;break;
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
    for (size_t i=0; i< object->getNumChildren();++i){
        object->getChild(i)->accept(cbv);
    }
    osg::BoundingBox &bb(cbv.getBoundingBox());

    box->selectionBoxGeode = new osg::Geode();
    box->selectionBoxGeode->setName("Robot selection box");
    box->selectionBox = new osg::Geometry();

    box->points = new osg::Vec3Array;
    box->colors = new osg::Vec4Array;
    box->normals = new osg::Vec3Array;





//	for (int i = 0;i<8;i++){
//		for (int j = 0;j<8;j++){
//		    box->points->push_back(bb.corner(i));
//		    box->points->push_back(bb.corner(j));
//		}
//
//	}

    //Bottom
    box->points->push_back(osg::Vec3(bb.xMin(),bb.yMin(),bb.zMin()));
    box->points->push_back(osg::Vec3(bb.xMax(),bb.yMin(),bb.zMin()));

    box->points->push_back(osg::Vec3(bb.xMin(),bb.yMin(),bb.zMin()));
    box->points->push_back(osg::Vec3(bb.xMin(),bb.yMax(),bb.zMin()));

    box->points->push_back(osg::Vec3(bb.xMax(),bb.yMax(),bb.zMin()));
    box->points->push_back(osg::Vec3(bb.xMin(),bb.yMax(),bb.zMin()));

    box->points->push_back(osg::Vec3(bb.xMax(),bb.yMax(),bb.zMin()));
    box->points->push_back(osg::Vec3(bb.xMax(),bb.yMin(),bb.zMin()));

    //Top
    box->points->push_back(osg::Vec3(bb.xMin(),bb.yMin(),bb.zMax()));
    box->points->push_back(osg::Vec3(bb.xMax(),bb.yMin(),bb.zMax()));

    box->points->push_back(osg::Vec3(bb.xMin(),bb.yMin(),bb.zMax()));
    box->points->push_back(osg::Vec3(bb.xMin(),bb.yMax(),bb.zMax()));

    box->points->push_back(osg::Vec3(bb.xMax(),bb.yMax(),bb.zMax()));
    box->points->push_back(osg::Vec3(bb.xMin(),bb.yMax(),bb.zMax()));

    box->points->push_back(osg::Vec3(bb.xMax(),bb.yMax(),bb.zMax()));
    box->points->push_back(osg::Vec3(bb.xMax(),bb.yMin(),bb.zMax()));


    //corners
    box->points->push_back(osg::Vec3(bb.xMin(),bb.yMin(),bb.zMin()));
    box->points->push_back(osg::Vec3(bb.xMin(),bb.yMin(),bb.zMax()));

    box->points->push_back(osg::Vec3(bb.xMax(),bb.yMin(),bb.zMin()));
    box->points->push_back(osg::Vec3(bb.xMax(),bb.yMin(),bb.zMax()));

    box->points->push_back(osg::Vec3(bb.xMin(),bb.yMax(),bb.zMin()));
    box->points->push_back(osg::Vec3(bb.xMin(),bb.yMax(),bb.zMax()));

    box->points->push_back(osg::Vec3(bb.xMax(),bb.yMax(),bb.zMin()));
    box->points->push_back(osg::Vec3(bb.xMax(),bb.yMax(),bb.zMax()));


    box->colors->push_back(osg::Vec4(1.0,1.0,1.0,1));

    box->normals->push_back(osg::Vec3(0.0f,-1.0f,0.0f));

    box->selectionBox->setVertexArray(box->points.get());
#if OSG_VERSION_LESS_OR_EQUAL(3,0,2)
    // needed for osg 3.0.2, present on ubuntu 12.04
    box->selectionBox->setColorArray(box->colors.get());
    box->selectionBox->setNormalArray(box->normals);
#else
    box->selectionBox->setColorArray(box->colors.get(),osg::Array::BIND_OVERALL);
    box->selectionBox->setNormalArray(box->normals, osg::Array::BIND_OVERALL);
#endif
    box->selectionBox->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES,0,box->points->size()));


    box->selectionBox->getOrCreateStateSet()->setAttribute( new osg::LineWidth(2.0f),osg::StateAttribute::ON );
    box->selectionBoxGeode->getOrCreateStateSet()->setMode( GL_LIGHTING, ::osg::StateAttribute::OFF );

    box->selectionBoxGeode->addDrawable(box->selectionBox);

    box->addChild(box->selectionBoxGeode);

    return box;
}


osg::ref_ptr<Object> PrimitivesFactory::loadImage(std::string path){
    osg::ref_ptr<Object> imageobject = new Object();
    osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
    osg::ref_ptr<osg::Geode> textureHolder = new osg::Geode();
    texture->setDataVariance(osg::Object::DYNAMIC);
    osg::Image* image = osgDB::readImageFile(path);
    texture->setImage(image);


    osg::ref_ptr<osg::Geometry> imageQuad = osg::createTexturedQuadGeometry(osg::Vec3(0.0f,0.0f,0.0f),
                                                                                  osg::Vec3(image->s(),0.0f,0.0f),
                                                                                  osg::Vec3(0.0f,image->t(),0.0f),
                                                                                  0.0f,
                                                                                  0.0f,
                                                                                  1.0f,
                                                                                  1.0f);
    imageQuad->getOrCreateStateSet()->setTextureAttributeAndModes(0, texture.get());
    imageQuad->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);
    textureHolder->addDrawable(imageQuad);
    imageobject->addChild(textureHolder);

    return imageobject;
}




} /* namespace osgviz */
