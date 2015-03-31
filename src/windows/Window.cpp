/*
* Window.cpp
*
*  Created on: 17.02.2015
*      Author: planthaber
*/

#include "Window.h"

#include <osgGA/TerrainManipulator>
#include <osg/Fog>
#include <stdio.h>

#include <osg/GraphicsContext>

namespace osgviz {

Window::Window(WindowConfig windowConfig) :
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
    osg::ref_ptr<osgViewer::View> view = new osgViewer::View;

    view->getCamera()->setGraphicsContext(graphicsContext);

    view->getCamera()->setClearColor(osg::Vec4(viewConfig.clearColorRed,
                                        viewConfig.clearColorGreen,
                                        viewConfig.clearColorBlue,
                                        viewConfig.clearColorAlpha));

    // if width and height is not set, than show view in full window
    if (viewConfig.width == -1 || viewConfig.height == -1) {
        const osg::GraphicsContext::Traits* traits = graphicsContext->getTraits();
        view->getCamera()->setViewport(0, 0, traits->width, traits->height);
    } else {
        view->getCamera()->setViewport(viewConfig.posX, viewConfig.posY, viewConfig.width, viewConfig.height);
    }

    view->setCameraManipulator(new osgGA::TerrainManipulator());

    view->setSceneData(scene);

    ObjectSelector* objectSelector = new ObjectSelector(this);
    view->addEventHandler(objectSelector);
    objectSelectors.push_back(objectSelector);

    views.push_back(view);
    root->addChild(scene);

    return view.release();
}

void Window::setScene(osg::Group* scene) {
    root->addChild(scene);
    mainView->setSceneData(root);
}

osg::Group* Window::getScene() {
    return this->root;
}

void Window::enableCameraControl() {
//	keyswitchManipulator->selectMatrixManipulator('1');
}

void Window::disableCameraControl() {
//	keyswitchManipulator->selectMatrixManipulator('0');
}

} /* namespace osgviz */


