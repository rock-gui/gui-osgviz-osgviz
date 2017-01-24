#include "RingNode.hpp"
#include <osgManipulator/Projector>


namespace osgviz {

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
    
    
    
RingNode::RingNode(const float radius, const float height, const float thickness) 
{
    projector = new osgManipulator::CylinderPlaneProjector();
    geode = new osg::Geode();

    osg::TessellationHints* hints = new osg::TessellationHints;
    hints->setCreateTop(false);
    hints->setCreateBottom(false);
    hints->setCreateBackFace(false);

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
    addChild(geode);
}

} 

