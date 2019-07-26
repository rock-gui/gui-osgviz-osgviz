#pragma once
#include <osg/Node>
#include "../../../../Object.h"

#include <osg/Geode>

namespace osgviz
{
    class WireframeBox: public osgviz::Object
    {
    public:

        WireframeBox(const double xPos, const double yPos, const double zPos,
            const double xSize, const double ySize, const double zSize);

        WireframeBox(const double xSize, const double ySize, const double zSize);  

        virtual ~WireframeBox();      	

        void setDimensions(double xSize, double ySize, double zSize);


    private:
        osg::ref_ptr<osg::Geode> geode;

        osg::ref_ptr<osg::Box> boundingBox;
    };
}