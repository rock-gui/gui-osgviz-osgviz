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

Window* WindowManager::createWindow(WindowConfig windowConfig, osg::Group* scene) {
	if (scene) {
		Window* wnd = new Window(windowConfig);
		wnd->setName(windowConfig.title);
		windows.push_back(wnd);

		wnd->setId(windows.size());
		if (windowConfig.dummyTwoViews == false) {
			wnd->addView(ViewConfig(), scene);
		} else {
			wnd->addView(ViewConfig(0, 0, 0.5, 1.0), scene);
			wnd->addView(ViewConfig(0.5, 0, 0.5, 1.0), scene);		
		}
		return wnd;		
	}
	else {
		std::runtime_error("WindowManager::createWindow: try to create window, but the scene pointer is not set.");
		
	}
	return 0;
}

void WindowManager::frame() {
	for(std::vector<Window::Ptr>::iterator witr = windows.begin();
        witr != windows.end();
        ++witr)
    {
		witr->get()->frame();
    }
}

} /* namespace osgviz */
