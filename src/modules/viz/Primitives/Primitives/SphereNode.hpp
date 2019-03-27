#pragma once

#include <osg/Shape>
#include <osg/ShapeDrawable>
#include "../../../../Object.h"

namespace osgviz {

    class SphereNode : public osgviz::Object{
    public:
        SphereNode(double x, double y, double z, double radius);
        void setColor(const osg::Vec4& color);
    private:
        osg::ref_ptr<osg::Geode> geode;
    };

}

