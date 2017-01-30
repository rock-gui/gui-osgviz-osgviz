#include "TranslateRotateDragger.h"

#include "../../modules/viz/Primitives/Primitives/AxesNode.hpp"
#include "../../modules/viz/Primitives/Primitives/RingNode.hpp"

#include <osg/ShapeDrawable>
#include <osg/Geometry>
#include <osg/LineWidth>
#include <osg/Quat>
#include <osgManipulator/TranslatePlaneDragger>
#include <osgManipulator/RotateCylinderDragger>
#include <osgManipulator/Projector>

using namespace osgManipulator;

namespace osgviz
{
  

TranslateRotateDragger::TranslateRotateDragger()
{
    projector = new CylinderPlaneProjector();
    
    for (int i=0; i<6; ++i)
    {
        planeDraggers.push_back(new TranslatePlaneDragger());
        addChild(planeDraggers[i].get());
        addDragger(planeDraggers[i].get());
        
        rotatateDraggers.push_back(new RotateCylinderDragger());
        addChild(rotatateDraggers[i].get());
        addDragger(rotatateDraggers[i].get());
    }
    
    addChild(osgviz::AxesNode::create());   
    resetPosition();
    setParentDragger(getParentDragger());
}

TranslateRotateDragger::~TranslateRotateDragger()
{
}

void TranslateRotateDragger::setupDefaultGeometry()
{
    for (unsigned int i = 0; i < planeDraggers.size(); ++i)
        planeDraggers[i]->setupDefaultGeometry();
    for(unsigned int i = 0; i < rotatateDraggers.size(); ++i)
        setupCylinderDefaultGeometry(rotatateDraggers[i].get());
}

void TranslateRotateDragger::resetPosition()
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
    
    // Rotate X-axis dragger appropriately.
    {
        osg::Quat rotation; rotation.makeRotate(osg::Vec3(0.0f, 0.0f, 1.0f), osg::Vec3(1.0f, 0.0f, 0.0f));
        rotatateDraggers[0]->setMatrix(osg::Matrix(rotation));
    }

    // Rotate Y-axis dragger appropriately.
    {
        osg::Quat rotation; rotation.makeRotate(osg::Vec3(0.0f, 0.0f, 1.0f), osg::Vec3(0.0f, 1.0f, 0.0f));
        rotatateDraggers[1]->setMatrix(osg::Matrix(rotation));
    }
    //Z-axis dragger is already rotated correctly b y default

    // Send different colors for each dragger.
    rotatateDraggers[0]->setColor(osg::Vec4(1.0f,0.0f,0.0f,1.0f));
    rotatateDraggers[1]->setColor(osg::Vec4(0.0f,1.0f,0.0f,1.0f));
    rotatateDraggers[2]->setColor(osg::Vec4(0.0f,0.0f,1.0f,1.0f));
}

void TranslateRotateDragger::setupCylinderDefaultGeometry(RotateCylinderDragger* dragger) const
{
    RingNode* ring = new RingNode(1.0f, 0.05f, 0.01f);
    dragger->addChild(ring);
}

}//end namespace
