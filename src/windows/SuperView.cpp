#include "SuperView.h"

#include <stdio.h>

namespace osgviz {

SuperView::SuperView() : osgViewer::View() {}

SuperView::SuperView(ViewConfig viewConfig, osg::GraphicsContext* graphicsContext, osg::Group* viewScene) : osgViewer::View(), viewConfig(viewConfig) {
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

    root = new osg::Group();
	setSceneData(root);
	addChild(viewScene);
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

}
