/*
 * Clickable.h
 *
 *  Created on: 09.03.2015
 *      Author: planthaber
 */

#ifndef OSGVIZ_OSGVIZ_SRC_INTERFACES_MOUSEMOVECALLBACK_H_
#define OSGVIZ_OSGVIZ_SRC_INTERFACES_MOUSEMOVECALLBACK_H_


namespace osgviz {

class MouseMoveCallback {
public:

    MouseMoveCallback(){};
	virtual ~MouseMoveCallback(){};

    /**
     *
     * @param cursor current mouse position
     * @param window Interface to the window where this event originates from
     * @return
     */
	virtual bool mouseMoved(const int& x, const int& y, const float& xNorm, const float& yNorm, const int& modifierMask) = 0;

};

} /* namespace osgviz */

#endif /* OSGVIZ_OSGVIZ_SRC_INTERFACES_MOUSEMOVECALLBACK_H_ */
