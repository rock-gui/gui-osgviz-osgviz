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
	Window* wnd = new Window(posx,posy,width,height);
	if (scene){
		wnd->setScene(scene);
	}
	wnd->setName(name);
	windows.push_back(wnd);
	return wnd;
}

void WindowManager::frame() {
	for (std::vector<Window*>::iterator win = windows.begin();win != windows.end();win++){
		(*win)->frame();
	}
}

} /* namespace osgviz */
