/*
 * WindowManager.h
 *
 *  Created on: 17.02.2015
 *      Author: planthaber
 */

#ifndef OSGVIZ_OSGVIZ_SRC_WINDOWS_WINDOWMANAGER_H_
#define OSGVIZ_OSGVIZ_SRC_WINDOWS_WINDOWMANAGER_H_

#include <stdexcept>

#include <osgViewer/CompositeViewer>

#include "config/WindowConfig.h"

#include "Window.h"

namespace osgviz {

class WindowManager : public osgViewer::CompositeViewer {
public:
	WindowManager();
	virtual ~WindowManager();

	Window* createWindow(WindowConfig windowConfig, osg::Group* scene = NULL);

	inline Window* getWindowByID(const unsigned int& id){
		if (id < windows.size()){
			return windows[id];
		}
		return NULL;
	}

private:
	std::vector<Window*> windows;

};

} /* namespace osgviz */

#endif /* OSGVIZ_OSGVIZ_SRC_WINDOWS_WINDOWMANAGER_H_ */
