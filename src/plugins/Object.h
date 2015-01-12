/*
 * Object.h
 *
 *  Created on: 08.01.2015
 *      Author: planthaber
 */


#include <osg/Node>
#include <osg/PositionAttitudeTransform>

#ifndef SRC_PLUGINS_MODELVIEW_H_
#define SRC_PLUGINS_MODELVIEW_H_

namespace osgviz {

class Object{
public:
	Object();

	virtual ~Object();


	virtual void setObject(osg::ref_ptr<osg::Node> object);

	virtual void setPosition(osg::Vec3 pos);

	virtual void setAttitude(osg::Quat attitude);

    virtual void setRootNode(osg::Group* node);

protected:
    friend class ModelViewFactory;



private:
    osg::ref_ptr<osg::Group> root;
    osg::ref_ptr<osg::Node> object;
    osg::ref_ptr<osg::PositionAttitudeTransform> patransform;

};

} /* namespace osgviz */

#endif /* SRC_PLUGINS_MODELVIEW_H_ */
