/*
 * Clickable.h
 *
 *  Created on: 09.03.2015
 *      Author: planthaber
 */

#ifndef OSGVIZ_OSGVIZ_SRC_INTERFACES_CLICKABLE_H_
#define OSGVIZ_OSGVIZ_SRC_INTERFACES_CLICKABLE_H_

#include <osg/Vec3d>


namespace osgviz {

class Clickable {
public:

	Clickable(){};
	virtual ~Clickable(){};

	/**
	 * @param object self, can be used to forward events to external handlers that operate on the object
	 */
	virtual bool clicked(const int &buttonMask, const osg::Vec3d &world, const osg::Vec3d &local, Clickable* object) = 0;

	virtual bool dragged(const int &buttonMask, const osg::Vec3d &world, const osg::Vec3d &local, Clickable* object){return false;}

};

} /* namespace osgviz */

#endif /* OSGVIZ_OSGVIZ_SRC_INTERFACES_CLICKABLE_H_ */
