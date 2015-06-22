/*
 * WindowManager.h
 *
 *  Created on: 17.02.2015
 *      Author: planthaber
 */

#ifndef OSGVIZ_OSGVIZ_SRC_WINDOWS_WINDOWMANAGER_H_
#define OSGVIZ_OSGVIZ_SRC_WINDOWS_WINDOWMANAGER_H_

#include <stdexcept>

#include "config/WindowConfig.h"

#include "Window.h"

namespace osgviz {

class WindowManager: public osg::Referenced {
public:

	typedef osg::ref_ptr<WindowManager> Ptr;

	WindowManager();
	virtual ~WindowManager();

	unsigned int createWindow(WindowConfig windowConfig, osg::Group* scene = NULL);

	inline Window* getWindowByID(const unsigned int& id){
		if (id < windows.size()){
			return windows.at(id);
		}
		return NULL;
	}

	inline std::vector<Window::Ptr> getWindows() const{
		return windows;
	}

	void frame();

private:
	std::vector<Window::Ptr> windows;

};

} /* namespace osgviz */

#endif /* OSGVIZ_OSGVIZ_SRC_WINDOWS_WINDOWMANAGER_H_ */
