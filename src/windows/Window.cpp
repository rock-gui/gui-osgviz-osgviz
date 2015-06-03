/*
* Window.cpp
*
*  Created on: 17.02.2015
*      Author: planthaber
*/

#include "Window.h"

#include <osgGA/TerrainManipulator>
#include <osgGA/TrackballManipulator>
#include <osg/Fog>
#include <osg/LightModel>
#include <osgViewer/ViewerEventHandlers>

#include "../graphics/wrapper/OSGLightStruct.h"
#include <stdio.h>

namespace osgviz {

Window::Window(osg::Group *scene, interfaces::GraphicData graphicData) {
    viewer = new osgViewer::CompositeViewer();
    mainView = new osgViewer::View;


    viewer->addView(mainView);
    views.push_back(mainView);

    objectSelector = new ObjectSelector(this);
    mainView->addEventHandler(objectSelector);

    mainView->setUpViewInWindow(graphicData.windowPosX, graphicData.windowPosY, graphicData.windowWidth, graphicData.windowHeight);
    viewer->realize();
    osgViewer::ViewerBase::Windows m_windows;
    viewer->getWindows(m_windows);
    graphicsWindow = m_windows.front();


    globalStateset = new osg::StateSet();

    globalStateset->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);
    globalStateset->setMode(GL_LIGHTING, osg::StateAttribute::ON);

    globalStateset->setMode(GL_LIGHT0, osg::StateAttribute::OFF);
    globalStateset->setMode(GL_LIGHT1, osg::StateAttribute::OFF);
    globalStateset->setMode(GL_LIGHT2, osg::StateAttribute::OFF);
    globalStateset->setMode(GL_LIGHT3, osg::StateAttribute::OFF);
    globalStateset->setMode(GL_LIGHT4, osg::StateAttribute::OFF);
    globalStateset->setMode(GL_LIGHT5, osg::StateAttribute::OFF);
    globalStateset->setMode(GL_LIGHT6, osg::StateAttribute::OFF);
    globalStateset->setMode(GL_LIGHT7, osg::StateAttribute::OFF);
    globalStateset->setMode(GL_BLEND,osg::StateAttribute::OFF);

    // background color for the scene

    printf("windows %i\n",m_windows.size());

    //graphicsWindow->setClearColor(graphicOptions.clearColor);
    mainView->getCamera()->setClearColor(graphicOptions.clearColor);

    // some fixed function pipeline stuff...
    // i guess the default is smooth shading, that means
    // light influence is calculated per vertex and interpolated for fragments.
    osg::ref_ptr<osg::LightModel> myLightModel = new osg::LightModel;
    myLightModel->setTwoSided(false);
    globalStateset->setAttributeAndModes(myLightModel.get(), osg::StateAttribute::ON);

    // associate scene with global states

    lightGroup = new osg::Group();
    // init light (osg can have only 8 lights enabled at a time)
    for (unsigned int i =0; i<8;i++) {
        lightmanager ltemp;
        ltemp.free=true;
        myLights.push_back(ltemp);
    }

    initDefaultLight();


    keyswitchManipulator = new osgGA::KeySwitchMatrixManipulator;  

    keyswitchManipulator->addMatrixManipulator( '0', "NONE", NULL );
    keyswitchManipulator->addMatrixManipulator( '1', "Terrain", new osgGA::TerrainManipulator() );
    keyswitchManipulator->addMatrixManipulator( '2', "Flight", new osgGA::FlightManipulator() );
    keyswitchManipulator->addMatrixManipulator( '3', "Orbit", new osgGA::OrbitManipulator() );
    keyswitchManipulator->addMatrixManipulator( '4', "Trackball", new osgGA::TrackballManipulator() );

    keyswitchManipulator->selectMatrixManipulator('1');

    mainView->setCameraManipulator(keyswitchManipulator);

    setScene(scene);

    if (graphicOptions.fogEnabled == true)
        showFog(true);

    mainView->addEventHandler(new osgViewer::StatsHandler());

}

Window::~Window() {

}

osgViewer::View* Window::addView(std::string name) {
    osgViewer::View* view = new osgViewer::View;

    //view->setCameraManipulator(keyswitchManipulator);

    viewer->addView(view);
    view->setSceneData(scene);
    //view->setUpViewInWindow(posx,posy,width, height);
    views.push_back(view);
    return view;
}

void Window::setScene(osg::Group* scene) {
    this->scene = scene;
    mainView->setSceneData(scene);
    scene->setStateSet(globalStateset.get());
    scene->addChild(lightGroup.get());
    //scene->addChild(shadowedScene.get());
}

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
	keyswitchManipulator->selectMatrixManipulator('1');
}

void Window::disableCameraControl() {
	keyswitchManipulator->selectMatrixManipulator('0');
}

void Window::setCursorShape(int cursor){
	graphicsWindow->setCursor((osgViewer::GraphicsWindow::MouseCursor)cursor);
}
void Window::setCursorPos(int x, int y){
	graphicsWindow->requestWarpPointer(x,y);
}

} /* namespace osgviz */


