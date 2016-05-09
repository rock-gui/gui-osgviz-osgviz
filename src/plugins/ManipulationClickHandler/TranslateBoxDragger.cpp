#include "TranslateBoxDragger.h"

#include <osgViz/plugins/viz/Primitives/Primitives/AxesNode.hpp>

#include <osg/ShapeDrawable>
#include <osg/Geometry>
#include <osg/LineWidth>
#include <osg/Quat>

using namespace osgManipulator;

namespace osgviz
{

TranslateBoxDragger::TranslateBoxDragger()
{
    for (int i=0; i<6; ++i)
    {
        planeDraggers.push_back(new TranslatePlaneDragger());
        addChild(planeDraggers[i].get());
        addDragger(planeDraggers[i].get());
    }
    
    addChild(osgviz::AxesNode::create());   
    
    resetPosition();
    setParentDragger(getParentDragger());
}

TranslateBoxDragger::~TranslateBoxDragger()
{
}

void TranslateBoxDragger::setupDefaultGeometry()
{
    for (unsigned int i=0; i<planeDraggers.size(); ++i)
        planeDraggers[i]->setupDefaultGeometry();
}

void TranslateBoxDragger::resetPosition()
{

    planeDraggers[0]->setMatrix(osg::Matrix::translate(osg::Vec3(0.0,0.5,0.0)));
    {
        osg::Quat rotation; rotation.makeRotate(osg::Vec3(0.0f, -1.0f, 0.0f), osg::Vec3(0.0f, 1.0f, 0.0f));
        planeDraggers[1]->setMatrix(osg::Matrix(rotation)*osg::Matrix::translate(osg::Vec3(0.0,-0.5,0.0)));
    }
    {
        osg::Quat rotation; rotation.makeRotate(osg::Vec3(0.0f, 0.0f, 1.0f), osg::Vec3(0.0f, 1.0f, 0.0f));
        planeDraggers[2]->setMatrix(osg::Matrix(rotation)*osg::Matrix::translate(osg::Vec3(0.0,0.0,-0.5)));
    }

    {
        osg::Quat rotation; rotation.makeRotate(osg::Vec3(0.0f, 1.0f, 0.0f), osg::Vec3(0.0f, 0.0f, 1.0f));
        planeDraggers[3]->setMatrix(osg::Matrix(rotation)*osg::Matrix::translate(osg::Vec3(0.0,0.0,0.5)));
    }

    {
        osg::Quat rotation; rotation.makeRotate(osg::Vec3(1.0f, 0.0f, 0.0f), osg::Vec3(0.0f, 1.0f, 0.0f));
        planeDraggers[4]->setMatrix(osg::Matrix(rotation)*osg::Matrix::translate(osg::Vec3(-0.5,0.0,0.0)));
    }

    {
        osg::Quat rotation; rotation.makeRotate(osg::Vec3(0.0f, 1.0f, 0.0f), osg::Vec3(1.0f, 0.0f, 0.0f));
        planeDraggers[5]->setMatrix(osg::Matrix(rotation)*osg::Matrix::translate(osg::Vec3(0.5,0.0,0.0)));
    }
}
}