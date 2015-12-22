/*
 * ShapeNode.cpp
 *
 *  Created on: 22.12.2015
 *      Author: planthaber
 */

#include "ShapeNode.h"

#include <osg/Geode>
#include <osg/Geometry>

#include <osgUtil/SmoothingVisitor>

namespace osgviz {

ShapeNode::ShapeNode(const Shape &shape):Object() {

    geode = new osg::Geode();
    geometry = new osg::Geometry();

    points = new osg::Vec3Array;
    colors = new osg::Vec4Array;
    normals = new osg::Vec3Array;

    switch (shape){
    case BOX: createBox(); break;
    }



}

ShapeNode::~ShapeNode() {
    // TODO Auto-generated destructor stub
}

void ShapeNode::setColor(const float &r,const float &g,const float &b,const float &a){
    colors->clear();
    colors->push_back(osg::Vec4(r,g,b,a));
    geometry->setColorArray(colors.get(),osg::Array::BIND_OVERALL);
}

void ShapeNode::createBox(){


    //top
    points->push_back(osg::Vec3f(0,0,1));
    points->push_back(osg::Vec3f(1,0,1));
    points->push_back(osg::Vec3f(0,1,1));

    points->push_back(osg::Vec3f(0,1,1));
    points->push_back(osg::Vec3f(1,0,1));
    points->push_back(osg::Vec3f(1,1,1));

    //left
    points->push_back(osg::Vec3f(0,0,1));
    points->push_back(osg::Vec3f(0,1,0));
    points->push_back(osg::Vec3f(0,0,0));

    points->push_back(osg::Vec3f(0,1,0));
    points->push_back(osg::Vec3f(0,1,1));
    points->push_back(osg::Vec3f(0,0,1));

    //bottom
    points->push_back(osg::Vec3f(0,0,0));
    points->push_back(osg::Vec3f(0,1,0));
    points->push_back(osg::Vec3f(1,0,0));

    points->push_back(osg::Vec3f(1,0,0));
    points->push_back(osg::Vec3f(0,1,0));
    points->push_back(osg::Vec3f(1,1,0));

    //front
    points->push_back(osg::Vec3f(0,0,0));
    points->push_back(osg::Vec3f(1,0,0));
    points->push_back(osg::Vec3f(0,0,1));

    points->push_back(osg::Vec3f(0,0,1));
    points->push_back(osg::Vec3f(1,0,1));
    points->push_back(osg::Vec3f(1,0,0));

    //right
    points->push_back(osg::Vec3f(1,0,0));
    points->push_back(osg::Vec3f(1,1,0));
    points->push_back(osg::Vec3f(1,1,1));

    points->push_back(osg::Vec3f(1,0,0));
    points->push_back(osg::Vec3f(1,0,1));
    points->push_back(osg::Vec3f(1,1,1));

    //back
    points->push_back(osg::Vec3f(0,1,0));
    points->push_back(osg::Vec3f(1,1,0));
    points->push_back(osg::Vec3f(0,1,1));

    points->push_back(osg::Vec3f(0,1,1));
    points->push_back(osg::Vec3f(1,1,1));
    points->push_back(osg::Vec3f(1,1,0));

    //set white as default
    colors->push_back(osg::Vec4(1.0,1.0,1.0,1.0));

    geometry->setVertexArray(points.get());
    geometry->setNormalArray(normals, osg::Array::BIND_OVERALL);
    geometry->setColorArray(colors.get(),osg::Array::BIND_OVERALL);


    geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLES,0,points->size()));


    geometry->getOrCreateStateSet()->setMode(GL_LIGHTING, ::osg::StateAttribute::ON );
    geometry->getOrCreateStateSet()->setMode(GL_RESCALE_NORMAL, osg::StateAttribute::ON );

    geode->addDrawable(geometry);

    //apply SmoothingVisitor to compute normals
    osgUtil::SmoothingVisitor sv;
    sv.apply(*(geode.get()));


    this->addChild(geode);

}


} /* namespace osgviz */
