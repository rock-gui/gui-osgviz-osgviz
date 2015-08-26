/*
 * WindowInterface.h
 *
 *  Created on: 17.04.2015
 *      Author: planthaber
 */

#ifndef OSGVIZ_SRC_INTERFACES_WINDOWINTERFACE_H_
#define OSGVIZ_SRC_INTERFACES_WINDOWINTERFACE_H_

namespace osgviz {

class WindowInterface{

public:
	WindowInterface(){};
	virtual ~WindowInterface(){};

	virtual void enableCameraControl() = 0;
	virtual void disableCameraControl() = 0;

	virtual void activeObjectSelector() = 0;
	virtual void deactivateObjectSelector() = 0;

	virtual void setCursorShape(int cursor) = 0;
	virtual void setCursorPos(int x, int y) = 0;

};



}



#endif /* OSGVIZ_SRC_INTERFACES_WINDOWINTERFACE_H_ */
