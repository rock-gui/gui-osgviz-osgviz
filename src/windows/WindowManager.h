/*
 * WindowManager.h
 *
 *  Created on: 17.02.2015
 *      Author: planthaber
 */

#ifndef OSGVIZ_OSGVIZ_SRC_WINDOWS_WINDOWMANAGER_H_
#define OSGVIZ_OSGVIZ_SRC_WINDOWS_WINDOWMANAGER_H_

#include <stdexcept>

#include "Window.h"

namespace osgviz {

class WindowManager {
public:
	WindowManager();
	virtual ~WindowManager();

	Window* createWindow(int posx,int posy, int width, int height, osg::Group* scene = NULL, std::string name = "Env");

	inline Window* getWindowByID(const unsigned int& id){
		if (id < windows.size()){
			return windows[id];
		}
		return NULL;
	}


	void frame();

private:
	std::vector<Window*> windows;

};

} /* namespace osgviz */

#endif /* OSGVIZ_OSGVIZ_SRC_WINDOWS_WINDOWMANAGER_H_ */
