#include "SphereNode.hpp"

namespace osgviz 
{
    SphereNode::SphereNode(double x, double y, double z, double radius)
    {
        geode = new osg::Geode();
        osg::Sphere *sphere = new osg::Sphere(osg::Vec3(x, y, z), radius);
        osg::ShapeDrawable *drawable =  new osg::ShapeDrawable(sphere);
        geode->addDrawable(drawable);
        addChild(geode);
    }
}
