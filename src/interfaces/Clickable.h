/*
 * Clickable.h
 *
 *  Created on: 09.03.2015
 *      Author: planthaber
 */

#ifndef OSGVIZ_OSGVIZ_SRC_INTERFACES_CLICKABLE_H_
#define OSGVIZ_OSGVIZ_SRC_INTERFACES_CLICKABLE_H_

#include <osg/Vec3d>
#include "WindowInterface.h"


namespace osgviz {

class Clickable {
public:

	Clickable(){};
	virtual ~Clickable(){};

    /**
     * Called when this object was clicked
     * @param buttonMask the osgGA::GUIEventAdapter::MouseButtonMask
     * @param cursor the cursor position in the 2d plane of the window
     * @param world global coordinates of the click position
     * @param local the local coordinated of the click position
     * @param object the object hit (normally "this"), needed when a "non Object" Clickable is added to this Object as event handler using addClickableCallback
     * @param modifierMask the modifier key mask
     * @param window Interface to the window where this event originates from
     * @return true if the event was handled, false if not -> event is propargated into the graph below this node to find another Object
     */
	virtual bool clicked(const int &buttonMask, const osg::Vec2d &cursor,
                       const osg::Vec3d &world, const osg::Vec3d &local,
                       Clickable* object, const int modifierMask,
                       WindowInterface* window = NULL) = 0;

    /**
     * Called when this object was dragged
     * @param buttonMask the osgGA::GUIEventAdapter::MouseButtonMask
     * @param cursor the cursor position in the 2d plane of the window
     * @param world global coordinates of the click position
     * @param local the local coordinated of the click position
     * @param object the object hit (normally "this"), needed when a "non Object" Clickable is added to this Object as event handler using addClickableCallback
     * @param modifierMask the modifier key mask
     * @param window Interface to the window where this event originates from
     * @return true if the event was handled, false if not -> event is propargated into the graph below this node to find another Object
     */
	virtual bool dragged(const int &buttonMask, const osg::Vec2d &cursor,
                       const osg::Vec3d &world, const osg::Vec3d &local,
                       Clickable* object, const int modifierMask,
                       WindowInterface* window = NULL){return false;}

};

} /* namespace osgviz */

#endif /* OSGVIZ_OSGVIZ_SRC_INTERFACES_CLICKABLE_H_ */
