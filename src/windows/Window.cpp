/*
* Window.cpp
*
*  Created on: 17.02.2015
*      Author: planthaber
*/

#include "Window.h"

#include <osgGA/TerrainManipulator>
#include <osg/Fog>
#include <osg/LightModel>
#include "../graphics/wrapper/OSGLightStruct.h"
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
        std::cout << "FULLSCREEN" << std::endl;
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
        std::cout << "NOT FULLSCREEN" << std::endl;
        traits->x = windowConfig.posX;
        traits->y = windowConfig.posY;
        traits->width = windowConfig.width;
        traits->height = windowConfig.height;
        traits->windowDecoration = true;
    }
    
    graphicsContext = osg::GraphicsContext::createGraphicsContext( traits.get() );

    //mainView = new osgViewer::View;
    /*if (graphicData.fullScreen == true) {
        mainView->apply(new osgviz::SingleWindow(0, 0, -1, -1, 0));
    } else {
        mainView->apply(new osgviz::SingleWindow(graphicData.windowPosX, graphicData.windowPosY, graphicData.windowWidth, graphicData.windowHeight, 0));
    }*/
    //mainView->setUpViewInWindow(graphicData.windowPosX, graphicData.windowPosY, graphicData.windowWidth, graphicData.windowHeight);
    //mainView->getCamera()->setGraphicsContext( graphicsContext.get() );
    // TODO: at the moment the main view are set to the full window
    // maybe in the futer we want to divide the window into several views
    //mainView->getCamera()->setViewport( new osg::Viewport(0, 0, traits->width, traits->height) );
    //mainView->setCameraManipulator(new osgGA::TerrainManipulator());
    //views.push_back(mainView);

    //objectSelector = new ObjectSelector(mainView);
    //mainView->addEventHandler(objectSelector);

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

    // background color for the scene
    //mainView->getCamera()->setClearColor(graphicOptions.clearColor);

    //root = new osg::Group;
    //root->setStateSet(globalStateset.get()); 

    //setScene(scene);
}

Window::~Window() {

}

osgViewer::View* Window::addView(ViewConfig viewConfig, osg::Group* scene) {
    osg::ref_ptr<osgViewer::View> view = new osgViewer::View;

    view->getCamera()->setGraphicsContext(graphicsContext);

    // if width and height is not set, than show view in full window
    if (viewConfig.width == -1 || viewConfig.height == -1) {
        std::cout << "view in full window" << std::endl;
        const osg::GraphicsContext::Traits* traits = graphicsContext->getTraits();

        view->getCamera()->setViewport(0, 0, traits->width, traits->height);
    } else {
        std::cout << "crop the view" << std::endl;
        view->getCamera()->setViewport(viewConfig.posX, viewConfig.posY, viewConfig.width, viewConfig.height);
    }

    view->setCameraManipulator(new osgGA::TerrainManipulator());

    view->setSceneData(scene);

    views.push_back(view);

    return view.release();
}

void Window::setScene(osg::Group* scene) {
    root->addChild(scene);
    mainView->setSceneData(root);
}

osg::Group* Window::getScene() {
    return this->root;
}

} /* namespace osgviz */






