/*
 * ShapeNode.h
 *
 *  Created on: 22.12.2015
 *      Author: planthaber
 */

#ifndef GUI_OSGVIZ_OSGVIZ_SRC_PLUGINS_VIZ_PRIMITIVES_PRIMITIVES_SHAPENODE_H_
#define GUI_OSGVIZ_OSGVIZ_SRC_PLUGINS_VIZ_PRIMITIVES_PRIMITIVES_SHAPENODE_H_

#include "../../../Object.h"



namespace osgviz {

class ShapeNode: public Object {
public:

    enum Shape {BOX};

    ShapeNode(const Shape &shape);

    virtual ~ShapeNode();


    void createBox();

    virtual void setColor(const float &r,const float &g,const float &b,const float &a = 1);


private:
    osg::ref_ptr<osg::Geometry> geometry;
    osg::ref_ptr<osg::Geode> geode;
    osg::ref_ptr<osg::Vec3Array> points;
    osg::ref_ptr<osg::Vec4Array> colors;
    osg::ref_ptr<osg::Vec3Array> normals;

};

} /* namespace osgviz */

#endif /* GUI_OSGVIZ_OSGVIZ_SRC_PLUGINS_VIZ_PRIMITIVES_PRIMITIVES_SHAPENODE_H_ */
