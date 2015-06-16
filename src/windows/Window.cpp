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
    osg::ref_ptr<SuperView> view = new SuperView(viewConfig, graphicsContext.get(), scene);

    osgViewer::CompositeViewer::addView((osgViewer::View*) view.get());
    root->addChild(scene);

    return view.release();
}

/*void Window::setScene(osg::Group* scene) {
    this->scene = scene;
    mainView->setSceneData(scene);
    scene->setStateSet(globalStateset.get());
    scene->addChild(lightGroup.get());
    //scene->addChild(shadowedScene.get());
}*/

osg::Group* Window::getScene() {
    return this->scene;
}

void Window::setName(const std::string& name) {
    graphicsWindow->setWindowName(name);
}

void Window::frame() {
    viewer->frame();
}

void Window::initDefaultLight() {
    osg::ref_ptr<osg::LightSource> myLightSource = new graphics::OSGLightStruct(defaultLight.lStruct);

    //add to lightmanager for later editing possibility
    defaultLight.light = myLightSource->getLight();
    defaultLight.lightSource = myLightSource;
    defaultLight.free = false;

    lightGroup->addChild( myLightSource.get() );
    globalStateset->setMode(GL_LIGHT0, osg::StateAttribute::ON);
    myLightSource->setStateSetModes(*globalStateset, osg::StateAttribute::ON);
}


void Window::showRain(const bool &val) {
    if (val) {
        rain = new osgParticle::PrecipitationEffect;
        rain->setWind(osg::Vec3(1, 0, 0));
        rain->setParticleSpeed(0.4);
        rain->rain(0.6); // alternatively, use rain
        scene->addChild(rain.get());
    } else {
        scene->removeChild(rain.get());
    }
}

void Window::showSnow(const bool &val) {
    if (val) {
        snow = new osgParticle::PrecipitationEffect;
        snow->setWind(osg::Vec3(1, 0, 0));
        snow->setParticleSpeed(0.4);
        snow->snow(0.4); // alternatively, use rain
        scene->addChild(snow.get());
    } else {
        scene->removeChild(snow.get());
    }
}

void Window::showFog(const bool &val) {
    if (val) {
        graphicOptions.fogEnabled = true;

        myFog = new osg::Fog;
        myFog->setMode(osg::Fog::LINEAR);
        myFog->setColor(graphicOptions.fogColor);
        myFog->setStart(graphicOptions.fogStart);
        myFog->setEnd(graphicOptions.fogEnd);
        myFog->setDensity(graphicOptions.fogDensity);
        globalStateset->setAttributeAndModes(myFog.get(), osg::StateAttribute::ON);        
    } else {
        graphicOptions.fogEnabled = false;        
    }
}

void Window::enableCameraControl() {
//	keyswitchManipulator->selectMatrixManipulator('1');
}

void Window::disableCameraControl() {
//	keyswitchManipulator->selectMatrixManipulator('0');
}

} /* namespace osgviz */


