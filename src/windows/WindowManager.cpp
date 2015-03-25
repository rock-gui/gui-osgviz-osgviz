/*
 * WindowManager.cpp
 *
 *  Created on: 17.02.2015
 *      Author: planthaber
 */

#include "WindowManager.h"

namespace osgviz {

WindowManager::WindowManager() : osgViewer::CompositeViewer() {
	// TODO Auto-generated constructor stub

}

WindowManager::~WindowManager() {
	// TODO Auto-generated destructor stub
}

Window* WindowManager::createWindow(interfaces::GraphicData graphicData, osg::Group* scene, std::string name) {
	if (scene) {
		Window* wnd = new Window(scene, graphicData, name);
		osgViewer::View* view = wnd->getView(0); 
		wnd->setName(name);
		windows.push_back(wnd);

		//osgViewer::View* view = wnd->getMainView();
		addView(view);

		return wnd;		
	}
	else {
		std::runtime_error("WindowManager::createWindow: try to create window, but the scene pointer is not set.");
		return 0;
	}
}

} /* namespace osgviz */
