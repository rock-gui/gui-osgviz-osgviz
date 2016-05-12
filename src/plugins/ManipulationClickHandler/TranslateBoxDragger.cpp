#include "TranslateBoxDragger.h"

#include <osgViz/plugins/viz/Primitives/Primitives/AxesNode.hpp>

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
  
/** @warning this method is copied from osgManipulator/RotateCylinderDragger.cpp
 *           because osg does not export the method. */
osg::Geometry* createDiskGeometry(float radius, float offset, float z, unsigned int numSegments)
{
   const float angleDelta = 2.0f*osg::PI/float(numSegments);
   const unsigned int numPoints = (numSegments+1) * 2;
   float angle = 0.0f;
   osg::Vec3Array* vertexArray = new osg::Vec3Array(numPoints);
   osg::Vec3Array* normalArray = new osg::Vec3Array(numPoints);
   unsigned int p = 0;
   for(unsigned int i = 0; i < numSegments; ++i,angle+=angleDelta)
   {
      float c = cosf(angle);
      float s = sinf(angle);
      // Outer point
      (*vertexArray)[p].set(radius*c, radius*s, z);
      (*normalArray)[p].set(0.0, 0.0, -1.0);
      ++p;
      // Inner point
      (*vertexArray)[p].set((radius-offset)*c, (radius-offset)*s, z);
      (*normalArray)[p].set(0.0, 0.0, -1.0);
      ++p;
   }
   // do last points by hand to ensure no round off errors.
   (*vertexArray)[p] = (*vertexArray)[0];
   (*normalArray)[p] = (*normalArray)[0];
   ++p;
   (*vertexArray)[p] = (*vertexArray)[1];
   (*normalArray)[p] = (*normalArray)[1];

   osg::Geometry* geometry = new osg::Geometry;
   geometry->setVertexArray(vertexArray);
   geometry->setNormalArray(normalArray, osg::Array::BIND_PER_VERTEX);
   geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLE_STRIP, 0, vertexArray->size()));
   return geometry;
}
  

TranslateBoxDragger::TranslateBoxDragger()
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

TranslateBoxDragger::~TranslateBoxDragger()
{
}

void TranslateBoxDragger::setupDefaultGeometry()
{
    for (unsigned int i = 0; i < planeDraggers.size(); ++i)
        planeDraggers[i]->setupDefaultGeometry();
    for(unsigned int i = 0; i < rotatateDraggers.size(); ++i)
        setupCylinderDefaultGeometry(rotatateDraggers[i].get());
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

void TranslateBoxDragger::setupCylinderDefaultGeometry(RotateCylinderDragger* dragger) const
{
    osg::Geode* geode = new osg::Geode;
    {
        osg::TessellationHints* hints = new osg::TessellationHints;
        hints->setCreateTop(false);
        hints->setCreateBottom(false);
        hints->setCreateBackFace(false);

        const float radius    = 1.0f;
        const float height    = 0.05f;
        const float thickness = 0.01f;

        // outer cylinder
        osg::Cylinder* cylinder = new osg::Cylinder;
        cylinder->setHeight(height);
        cylinder->setRadius(radius);
        osg::ShapeDrawable* cylinderDrawable = new osg::ShapeDrawable(cylinder, hints);
        geode->addDrawable(cylinderDrawable);

        // inner cylinder
        osg::Cylinder* cylinder1 = const_cast<osg::Cylinder*>(projector->getCylinder());
        cylinder1->setHeight(height);
        cylinder1->setRadius(radius-thickness);
        osg::ShapeDrawable* cylinderDrawable1 = new osg::ShapeDrawable(cylinder1, hints);
        geode->addDrawable(cylinderDrawable1);

        // top
        geode->addDrawable(createDiskGeometry(radius, thickness,  height/2, 100));
        // bottom
        geode->addDrawable(createDiskGeometry(radius, thickness, -height/2, 100));
    }
    dragger->addChild(geode);
}

}