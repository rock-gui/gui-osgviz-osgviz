#include "SuperView.h"

#include <stdio.h>

#include <osg/LightModel>

namespace osgviz {

SuperView::SuperView() : osgViewer::View() {}

SuperView::SuperView(ViewConfig viewConfig, osg::GraphicsContext* graphicsContext, osg::Group* viewScene) 
  	  : osgViewer::View(), 
		viewConfig(viewConfig),
		root(new osg::Group),
		globalStateset(new osg::StateSet),
		lightGroup(new osg::Group) {

	if (graphicsContext == NULL)
		throw std::runtime_error("SuperView: Graphic Context is null pointer.");
	else
		getCamera()->setGraphicsContext(graphicsContext);

	// set background color
	getCamera()->setClearColor(osg::Vec4(viewConfig.clearColorRed,
                                        viewConfig.clearColorGreen,
                                        viewConfig.clearColorBlue,
                                        viewConfig.clearColorAlpha));

	// calculate the size and position of view
	const osg::GraphicsContext::Traits* traits = getCamera()->getGraphicsContext()->getTraits();
    int posX = traits->width * viewConfig.posX;
    int posY = traits->height * viewConfig.posY;
    int width = traits->width * viewConfig.width;
    int height = traits->height * viewConfig.height;

	// set projection matrix
	double fovy, aspectRatio, zNear, zFar;
    getCamera()->getProjectionMatrixAsPerspective(fovy, aspectRatio, zNear, zFar);

    double newAspectRatio = double(width) / double(height);
    double aspectRatioChange = newAspectRatio / aspectRatio;
    if (aspectRatioChange != 1.0) {
        getCamera()->getProjectionMatrix() *= osg::Matrix::scale(1.0 / aspectRatioChange, 1.0, 1.0);
    }	    

    getCamera()->setViewport(new osg::Viewport(posX, posY, width, height));  

	// set buffer
	GLenum buffer = traits->doubleBuffer ? GL_BACK : GL_FRONT;
    getCamera()->setDrawBuffer(buffer);
    getCamera()->setReadBuffer(buffer);	 

    // set camera manipulator
	keyswitchManipulator = new osgGA::KeySwitchMatrixManipulator;  
	keyswitchManipulator->addMatrixManipulator( '0', "NONE", NULL );
    keyswitchManipulator->addMatrixManipulator( '1', "Trackball", new osgGA::TerrainManipulator() );
    keyswitchManipulator->addMatrixManipulator( '2', "Flight", new osgGA::FlightManipulator() );
	keyswitchManipulator->selectMatrixManipulator('1');

    setCameraManipulator(keyswitchManipulator);

	if (viewConfig.hasObjectSelector == true) {
		objectSelector = new ObjectSelector(this);
    	addEventHandler(objectSelector);
    }    

	setSceneData(root);
	addChild(viewScene);

    globalStateset->setGlobalDefaults();
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
    root->setStateSet(globalStateset.get());

    // some fixed function pipeline stuff...
    // i guess the default is smooth shading, that means
    // light influence is calculated per vertex and interpolated for fragments.
    osg::ref_ptr<osg::LightModel> myLightModel = new osg::LightModel;
    myLightModel->setTwoSided(false);
    globalStateset->setAttributeAndModes(myLightModel.get(), osg::StateAttribute::ON);    

    root->addChild(lightGroup.get());

    // init light (osg can have only 8 lights enabled at a time)
    for (unsigned int i =0; i<8;i++) {
      lightmanager ltemp;
      ltemp.free=true;
      myLights.push_back(ltemp);
    }

    initDefaultLight();    
}

SuperView::~SuperView() {
    //delete globalStateset;
    //delete root;
}

void SuperView::activeObjectSelector() {
	if (objectSelector.valid() != true) {
		objectSelector = new ObjectSelector(this);		
	}
	addEventHandler(objectSelector);
}

void SuperView::deactivateObjectSelector() {
	if (objectSelector.valid() == true) {
		removeEventHandler(objectSelector.get());
	} else {
		OSG_WARN << "SuperView::deactivateObjectSelector: No object selector was active at the moment." << std::endl;
	}
}

void SuperView::enableCameraControl() {
	keyswitchManipulator->selectMatrixManipulator('1');
}

void SuperView::disableCameraControl() {
	keyswitchManipulator->selectMatrixManipulator('0');
}

void SuperView::setCursorShape(int cursor){
	printf("not implemented : %s\n", __PRETTY_FUNCTION__);
	//graphicsWindow->setCursor((osgViewer::GraphicsWindow::MouseCursor)cursor);
}
void SuperView::setCursorPos(int x, int y){
	printf("not implemented : %s\n", __PRETTY_FUNCTION__);
 	//graphicsWindow->requestWarpPointer(x,y);
//	keyswitchManipulator->selectMatrixManipulator('0');
}


void SuperView::initDefaultLight() {
	defaultLight.lStruct.pos = Vector(0.0, 0.0, 10.0);
	defaultLight.lStruct.ambient = osgviz::Color(0.0, 0.0, 0.0, 1.0);
	defaultLight.lStruct.diffuse = osgviz::Color(1.0, 1.0, 1.0, 1.0);
	defaultLight.lStruct.specular = osgviz::Color(1.0, 1.0, 1.0, 1.0);
	defaultLight.lStruct.constantAttenuation = 0.0;
	defaultLight.lStruct.linearAttenuation = 0.0;
	defaultLight.lStruct.quadraticAttenuation = 0.00001;
	defaultLight.lStruct.directional = false;
	defaultLight.lStruct.type = osgviz::OMNILIGHT;
	defaultLight.lStruct.index = 0;
	defaultLight.lStruct.angle = 0;
	defaultLight.lStruct.exponent = 0;

	osg::ref_ptr<osg::LightSource> myLightSource = new osgviz::graphics::OSGLightStruct(defaultLight.lStruct);

	//add to lightmanager for later editing possibility
	defaultLight.light = myLightSource->getLight();
	defaultLight.lightSource = myLightSource;
	defaultLight.free = false;

	lightGroup->addChild( myLightSource.get() );
	globalStateset->setMode(GL_LIGHT0, osg::StateAttribute::ON);
	myLightSource->setStateSetModes(*globalStateset, osg::StateAttribute::ON);
}

}
