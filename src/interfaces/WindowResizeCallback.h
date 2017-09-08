/*
 * WindowResizeCallback.h
 *
 *  Created on: 08.09.2017
 *      Author: Anna Born
 */

#ifndef OSGVIZ_OSGVIZ_SRC_INTERFACES_WINDOWRESIZECALLBACK_H_
#define OSGVIZ_OSGVIZ_SRC_INTERFACES_WINDOWRESIZECALLBACK_H_


namespace osgviz {

class WindowResizeCallback {
public:

    WindowResizeCallback(){};
	virtual ~WindowResizeCallback(){};

    /**
     *
     * @param cursor current mouse position
     * @param window Interface to the window where this event originates from
     * @return
     */
	virtual bool windowResized(const int& windowHeight, const int& windowWight) = 0;

};

} /* namespace osgviz */

#endif /* OSGVIZ_OSGVIZ_SRC_INTERFACES_WINDOWRESIZECALLBACK_H_ */
