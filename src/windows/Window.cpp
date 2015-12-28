/*
* Window.cpp
*
*  Created on: 17.02.2015
*      Author: planthaber
*/

#include "Window.h"

#include <stdio.h>

#include <osg/GraphicsContext>
#include <osgViewer/ViewerEventHandlers>
#include "EventHandlers/ObjectSelector.h"

#include "SuperView.h"

namespace osgviz {

Window::Window(WindowConfig windowConfig, osg::ref_ptr<osg::Node> windowScene)
       : osgViewer::CompositeViewer(),
         windowConfig(windowConfig),
         root(new osg::Group) {

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

    root->setName("Window root");
    addChild(windowScene);
}

Window::~Window() {
}

void Window::setWindowGeometry(int posX, int posY, int width, int height, int window) {
	osgViewer::GraphicsWindow* gw =getGraphicsWindow(window);
	windowConfig.posX = posX;
	windowConfig.posY = posY;
	windowConfig.width = width;
	windowConfig.height = height;
	if (gw){
		gw->setWindowDecoration(true);
		gw->setWindowRectangle(windowConfig.posX,windowConfig.posY,windowConfig.width,windowConfig.height);
	}else{
		fprintf(stderr, "window %i unknown\n", window);
	}
	//graphicsContext->resizedImplementation(posX,posY,width,height);
}

osgViewer::View* Window::addView(ViewConfig viewConfig, osg::Group* viewScene) {
    // set the view with its own scene
    osg::ref_ptr<SuperView> view = new SuperView(viewConfig, graphicsContext.get(), viewScene);
    osgViewer::CompositeViewer::addView((osgViewer::View*) view.get());

    // set also window scene to the view
    // so all views in the window share the same window scene
    view->addChild(root);

    view->addEventHandler(new ObjectSelector(view),0);

    view->addEventHandler(new osgViewer::StatsHandler(),-100);


    views.push_back(view);

    return view;
}

osgviz::HUD* Window::addHUD(int width,int height){

    osgviz::HUD* hud = new HUD(this,width,height);

    root->addChild(hud);

    huds.push_back(hud);

    return hud;
}

/*void Window::setScene(osg::Group* scene) {
    this->scene = scene;
    mainView->setSceneData(scene);
    scene->setStateSet(globalStateset.get());
    scene->addChild(lightGroup.get());
    //scene->addChild(shadowedScene.get());
}*/

//osg::Group* Window::getScene() {
//    return this->scene;
//}

//void Window::setName(const std::string& name) {
//	graphicsWindow->setWindowName(name);
//}

//void Window::frame() {
//    viewer->frame();
//}

//void Window::initDefaultLight() {
//    osg::ref_ptr<osg::LightSource> myLightSource = new graphics::OSGLightStruct(defaultLight.lStruct);
//
//    //add to lightmanager for later editing possibility
//    defaultLight.light = myLightSource->getLight();
//    defaultLight.lightSource = myLightSource;
//    defaultLight.free = false;
//
//    lightGroup->addChild( myLightSource.get() );
//    globalStateset->setMode(GL_LIGHT0, osg::StateAttribute::ON);
//    myLightSource->setStateSetModes(*globalStateset, osg::StateAttribute::ON);
//}


void Window::setFullscreen(bool state, int window, int screen){
  printf("calling : %s state = %i win %i screen %i\n", __PRETTY_FUNCTION__,state,window,screen);fflush(stdout);
	osgViewer::GraphicsWindow* gw = getGraphicsWindow(window);

  if (gw){
    if (state){
      unsigned int width = 0;
      unsigned int height = 0;
      osg::GraphicsContext::WindowingSystemInterface* wsi = osg::GraphicsContext::getWindowingSystemInterface();
      if (wsi){
        wsi->getScreenResolution( osg::GraphicsContext::ScreenIdentifier(screen), width, height );
      }
      printf("set fullscreen %ix%x\n", width, height);
      gw->setWindowDecoration(false);
      gw->setWindowRectangle(0,0,width,height);
      //gw->useCursor(false);
    }else{
      gw->setWindowDecoration(true);
      gw->setWindowRectangle(windowConfig.posX,windowConfig.posY,windowConfig.width,windowConfig.height);
      //gw->useCursor(true);
    }
  }else{
    printf("no getGraphicsWindow");
  }
}


void Window::showRain(const bool &val) {
    if (val) {
        rain = new osgParticle::PrecipitationEffect;
        rain->setWind(osg::Vec3(1, 0, 0));
        rain->setParticleSpeed(0.4);
        rain->rain(0.6); // alternatively, use rain
        root->addChild(rain.get());
    } else {
        root->removeChild(rain.get());
    }
}


void Window::showSnow(const bool &val) {
    if (val) {
        snow = new osgParticle::PrecipitationEffect;
        snow->setWind(osg::Vec3(1, 0, 0));
        snow->setParticleSpeed(0.4);
        snow->snow(0.4); // alternatively, use rain
        root->addChild(snow.get());
    } else {
        root->removeChild(snow.get());
    }
}

// void Window::showFog(const bool &val) {
//     if (val) {
//         myFog = new osg::Fog;
//         myFog->setMode(osg::Fog::LINEAR);
//         myFog->setColor(graphicOptions.fogColor);
//         myFog->setStart(graphicOptions.fogStart);
//         myFog->setEnd(graphicOptions.fogEnd);
//         myFog->setDensity(graphicOptions.fogDensity);
//         globalStateset->setAttributeAndModes(myFog.get(), osg::StateAttribute::ON);
//     } else {
//         globalStateset->setAttributeAndModes(myFog.get(), osg::StateAttribute::OFF);
//     }
// }

//
//void Window::enableCameraControl() {
////	keyswitchManipulator->selectMatrixManipulator('1');
//}
//
//void Window::disableCameraControl() {
////	keyswitchManipulator->selectMatrixManipulator('0');
//}

osgViewer::GraphicsWindow* Window::getGraphicsWindow(unsigned int index) {
	osgViewer::ViewerBase::Windows m_windows;
	this->getWindows(m_windows);
	if (m_windows.size() > index){
		return m_windows[index];
	}
	return NULL;
}

} /* namespace osgviz */
