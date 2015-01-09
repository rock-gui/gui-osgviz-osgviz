/*
 * ModelView.h
 *
 *  Created on: 08.01.2015
 *      Author: planthaber
 */


#include <osg/Node>
#include <osg/PositionAttitudeTransform>

#ifndef SRC_PLUGINS_MODELVIEW_H_
#define SRC_PLUGINS_MODELVIEW_H_

namespace osgviz {

class ModelView{
public:
	ModelView();

	virtual ~ModelView();


	virtual void setModel(osg::ref_ptr<osg::Node> object);

	virtual void setPosition(osg::Vec3 pos);

	virtual void setAttitude(osg::Quat attitude);

protected:
    friend class ModelViewFactory;

    inline void setRootNode(osg::Group* node){
      	root = node;
    }

private:
    osg::ref_ptr<osg::Group> root;
    osg::ref_ptr<osg::Node> object;
    osg::ref_ptr<osg::PositionAttitudeTransform> patransform;

};

} /* namespace osgviz */

#endif /* SRC_PLUGINS_MODELVIEW_H_ */
