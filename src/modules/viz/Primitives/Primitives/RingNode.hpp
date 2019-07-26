#pragma once
#include <osg/Shape>
#include <osg/ShapeDrawable>

#include "../../../../Object.h"

namespace osgManipulator
{
    class CylinderPlaneProjector;
}

namespace osgviz {

    class RingNode : public osgviz::Object{
    public:
        RingNode(const float radius, const float height, const float thickness);

        void setColor(const osg::Vec4& color);


    private:
        osg::ref_ptr<osg::Geode> geode; 
        osg::ref_ptr<osgManipulator::CylinderPlaneProjector> projector;
    };

} 

