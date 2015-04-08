/*
* Window.cpp
*
*  Created on: 17.02.2015
*      Author: planthaber
*/

#include "Window.h"

#include <stdio.h>

#include <osg/GraphicsContext>

#include "SuperView.h"

namespace osgviz {

Window::Window(WindowConfig windowConfig) : osgViewer::CompositeViewer(),
         windowConfig(windowConfig) {

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
    
    graphicsContext = osg::GraphicsContext::createGraphicsContext( traits.get() );

    globalStateset = new osg::StateSet();

    globalStateset->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);
    globalStateset->setMode(GL_LIGHTING, osg::StateAttribute::ON);
    globalStateset->setMode(GL_LIGHT0, osg::StateAttribute::ON);
    globalStateset->setMode(GL_LIGHT1, osg::StateAttribute::OFF);
    globalStateset->setMode(GL_LIGHT2, osg::StateAttribute::OFF);
    globalStateset->setMode(GL_LIGHT3, osg::StateAttribute::OFF);
    globalStateset->setMode(GL_LIGHT4, osg::StateAttribute::OFF);
    globalStateset->setMode(GL_LIGHT5, osg::StateAttribute::OFF);
    globalStateset->setMode(GL_LIGHT6, osg::StateAttribute::OFF);
    globalStateset->setMode(GL_LIGHT7, osg::StateAttribute::OFF);
    globalStateset->setMode(GL_BLEND,osg::StateAttribute::OFF);

    root = new osg::Group;
    root->setStateSet(globalStateset.get()); 
}

Window::~Window() {

}

osgViewer::View* Window::addView(ViewConfig viewConfig, osg::Group* scene) {
    // if the size of view is not specified,
    // than the view covers the whole window
    if (viewConfig.width == 0 || viewConfig.width == 0) {
        const osg::GraphicsContext::Traits* traits = graphicsContext->getTraits();
        viewConfig.width = traits->width;
        viewConfig.height = traits->height;
    }

    osg::ref_ptr<SuperView> view = new SuperView(viewConfig, scene);
    view->setGraphicContext(graphicsContext);

    osgViewer::CompositeViewer::addView((osgViewer::View*) view.release());
    root->addChild(scene);

    return view.release();
}

} /* namespace osgviz */


