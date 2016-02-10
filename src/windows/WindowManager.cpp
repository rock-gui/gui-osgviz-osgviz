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

unsigned int WindowManager::createWindow(WindowConfig& windowConfig, osg::ref_ptr<osg::Node> windowScene, osg::ref_ptr<osg::GraphicsContext> graphicsContext) {

    if (!graphicsContext.valid()){

        osg::ref_ptr<osg::GraphicsContext::Traits> traits = genetrateTraits(windowConfig);

        graphicsContext = osg::GraphicsContext::createGraphicsContext( traits );
    }

	osg::ref_ptr<Window> wnd = new Window(windowConfig, windowScene, graphicsContext);
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
	for(std::vector< osg::ref_ptr<Window> >::iterator witr = windows.begin();
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


osg::ref_ptr<osg::GraphicsContext::Traits> WindowManager::genetrateTraits(WindowConfig& windowConfig){
    osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
    traits->windowName = windowConfig.title;
    traits->supportsResize = false;
    traits->doubleBuffer = true;
    traits->sharedContext = 0;

    // full screen: the rendering window attributes according to current screen settings
    if (windowConfig.fullScreen == true) {
        // TODO: allow to choose the screen
        int screenNum = 0;
        unsigned int width = windowConfig.width;
        unsigned int height = windowConfig.height;

        osg::GraphicsContext::WindowingSystemInterface* wsi = osg::GraphicsContext::getWindowingSystemInterface();
        if (wsi)
            wsi->getScreenResolution( osg::GraphicsContext::ScreenIdentifier(screenNum), width, height );

        traits->x = 0;
        traits->y = 0;
        traits->width = width;
        traits->height = height;
        traits->windowDecoration = false;
    }
    // user defined window: the size and position of the window are defined in graphicData
    else {
        traits->x = windowConfig.posX;
        traits->y = windowConfig.posY;
        traits->width = windowConfig.width;
        traits->height = windowConfig.height;
        traits->windowDecoration = true;
    }

    return traits;

}


} /* namespace osgviz */
