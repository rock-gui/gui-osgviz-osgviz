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

        if (!graphicsContext){

            osg::ref_ptr<osg::GraphicsContext::Traits> traits = WindowConfig::generateTraits(windowConfig);
            graphicsContext = osg::GraphicsContext::createGraphicsContext( traits );
        }

        osg::ref_ptr<Window> wnd = new Window(windowConfig, windowScene, graphicsContext);
        wnd->setName(windowConfig.title);

        return addWindow(wnd);
    }

    unsigned int WindowManager::addWindow(osg::ref_ptr<Window> window) {
        windowsMutex.lock();
        unsigned int wndId = windows.size();
        windows.push_back(window);

        const osgviz::WindowConfig& config = window->windowConfig;

        // if no view config is given, take the default configs
        if (config.viewsConfig.size() == 0) {
            window->addView(ViewConfig());
        } else {
            for (unsigned int i = 0; i < config.viewsConfig.size(); ++i) {
                window->addView(config.viewsConfig.at(i));
            }
        }
        windowsMutex.unlock();
        return wndId;
    }

    void WindowManager::destroyWindow(unsigned int id){
        windowsMutex.lock();
        windows[id] = osg::ref_ptr<Window>();
        windowsMutex.unlock();
    }

    void WindowManager::frame() {
        windowsMutex.lock();
        for (std::vector< osg::ref_ptr<Window> >::iterator witr = windows.begin();
            witr != windows.end(); ++witr)
        {
            //windows become invalid but are not removed from the window list
            //thus we have to check if they are valid
            if(witr->valid() && witr->get()->isRealized())
                witr->get()->frame();
        }
        windowsMutex.unlock();
    }

    bool WindowManager::done() const {
        bool d = true;
        for (std::vector< osg::ref_ptr<Window> >::const_iterator witr = windows.begin();
            witr != windows.end(); ++witr)
        {

            if (witr->valid() && !witr->get()->done()) {
                d = false;
                break;
            }
        }
        return d;
    }

} /* namespace osgviz */
