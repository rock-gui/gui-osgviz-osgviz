#pragma once
#include <osg/Node>
namespace osgviz
{
    class WireframeBox
    {
        public:
            /**  Creates a new sub scene graph for a wireframe box.  */
            static ::osg::Node* create(const double xSize, const double ySize,
                                       const double zSize);
            
            static ::osg::Node* create(const double xPos, const double yPos, const double zPos,
                                       const double xSize, const double ySize, const double zSize);
    };
}