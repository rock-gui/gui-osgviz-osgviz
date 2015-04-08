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
		//osgViewer::View* view = wnd->getView(0); 
		windows.push_back(wnd);

		if (windowConfig.dummyTwoViews == false) {
			osgViewer::View* view = wnd->addView(ViewConfig(), scene);
		} else {
			osgViewer::View* viewLeft = wnd->addView(ViewConfig(0, 0, 300, 402), scene);
			osgViewer::View* viewRight = wnd->addView(ViewConfig(300, 0, 420, 402), scene);		
		}

		return wnd;		
	}
	else {
		std::runtime_error("WindowManager::createWindow: try to create window, but the scene pointer is not set.");
		return 0;
	}
}

void WindowManager::frame() {
	for(RefWindows::iterator witr = windows.begin();
        witr != windows.end();
        ++witr)
    {
		witr->get()->frame();
    }
}

} /* namespace osgviz */
