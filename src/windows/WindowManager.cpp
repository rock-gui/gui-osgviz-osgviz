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

unsigned int WindowManager::createWindow(WindowConfig& windowConfig, osg::ref_ptr<osg::Node> windowScene) {
	Window::Ptr wnd = new Window(windowConfig, windowScene);
	wnd->setName(windowConfig.title);

	unsigned int wndId = windows.size();

	windowsMutex.lock();
	windows.push_back(wnd);

	// if no view config is given, take the default configs
	if (windowConfig.viewsConfig.size() == 0) {
		wnd->addView(ViewConfig());
	} else {
		for (unsigned int i = 0; i < windowConfig.viewsConfig.size(); ++i) {
			wnd->addView(windowConfig.viewsConfig.at(i));
		}
	}
	windowsMutex.unlock();
	return wndId;		
}

void WindowManager::frame() {
	windowsMutex.lock();
	//printf("WindowManager::frame\n");fflush(stdout);
	for(std::vector<Window::Ptr>::iterator witr = windows.begin();
        witr != windows.end();
        ++witr)
    {
		//printf("WindowManager::frame call\n");fflush(stdout);
		witr->get()->frame();
		//printf("WindowManager::frame call end\n");fflush(stdout);
    }
	//printf("WindowManager::frame end\n");fflush(stdout);
	windowsMutex.unlock();
}

} /* namespace osgviz */
