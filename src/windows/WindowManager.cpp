/*
 * WindowManager.cpp
 *
 *  Created on: 17.02.2015
 *      Author: planthaber
 */

#include "WindowManager.h"

namespace osgviz {

WindowManager::WindowManager() {
	// TODO Auto-generated constructor stub

}

WindowManager::~WindowManager() {
	// TODO Auto-generated destructor stub
}

Window* WindowManager::createWindow(int posx, int posy, int width, int height, osg::Group* scene, std::string name) {
	if (scene) {
		Window* wnd = new Window(scene, posx, posy, width, height);
		wnd->setName(name);
		windows.push_back(wnd);
		return wnd;		
	}
	else {
		std::runtime_error("WindowManager::createWindow: try to create window, but the scene pointer is not set.");
		return 0;
	}
}

void WindowManager::frame() {
	for (std::vector<Window*>::iterator win = windows.begin();win != windows.end();win++){
		(*win)->frame();
	}
}

} /* namespace osgviz */
