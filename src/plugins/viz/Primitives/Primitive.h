/*
 * Primitive.h
 *
 *  Created on: 09.01.2015
 *      Author: planthaber
 */

#ifndef GUI_OSGVIZ_SRC_PLUGINS_VIZ_PRIMITIVES_PRIMITIVE_H_
#define GUI_OSGVIZ_SRC_PLUGINS_VIZ_PRIMITIVES_PRIMITIVE_H_

#include <osg/Node>
#include <osg/PositionAttitudeTransform>

namespace osgviz {

class Primitive{

public:

	Primitive();

	~Primitive();

    void setPrimitive(osg::ref_ptr<osg::Node> node){
    	primitive = node;
    	patransform = new osg::PositionAttitudeTransform;
    	patransform->addChild(primitive);
    	root->addChild(patransform);
    }

protected:
    friend class PrimitivesFactory;

    void setRootNode(osg::Group* node){
      	root = node;
    }

    void setPosition(osg::Vec3 pos);

    void setAttitude(osg::Quat attitude);

private:
    osg::ref_ptr<osg::Group> root;
    osg::ref_ptr<osg::Node> primitive;
    osg::ref_ptr<osg::PositionAttitudeTransform> patransform;

};

}//namespace


#endif /* GUI_OSGVIZ_SRC_PLUGINS_VIZ_PRIMITIVES_PRIMITIVE_H_ */
