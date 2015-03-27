/*
 * ArrowNode.h
 *
 *  Created on: 27.03.2015
 *      Author: planthaber
 */

#ifndef GUI_OSGVIZ_OSGVIZ_SRC_PLUGINS_VIZ_PRIMITIVES_PRIMITIVES_ARROWNODE_H_
#define GUI_OSGVIZ_OSGVIZ_SRC_PLUGINS_VIZ_PRIMITIVES_PRIMITIVES_ARROWNODE_H_

#include "../../../Object.h"
#include <osg/Shape>
#include <osg/ShapeDrawable>
//#include <osg/Cylinder>

namespace osgviz {

class ArrowNode : public osgviz::Object{
public:
	ArrowNode();
	virtual ~ArrowNode();


	osg::ref_ptr<osg::Cone> Cone(){
		return cone;
	}

	osg::ref_ptr<osg::Cylinder> Cylinder(){
		return cylinder;
	}


private:
	osg::ref_ptr<osg::Geode> geode;

	osg::ref_ptr<osg::Cone> cone;
	osg::ref_ptr<osg::ShapeDrawable> coneDrawable;

	osg::ref_ptr<osg::Cylinder> cylinder;
	osg::ref_ptr<osg::ShapeDrawable> cylinderDrawable;

};

} /* namespace robot_manager */

#endif /* GUI_OSGVIZ_OSGVIZ_SRC_PLUGINS_VIZ_PRIMITIVES_PRIMITIVES_ARROWNODE_H_ */
