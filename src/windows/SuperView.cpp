#include "SuperView.h"

namespace osgviz {

SuperView::SuperView() : osgViewer::View() {}

SuperView::SuperView(ViewConfig viewConfig, osg::Group* scene) : osgViewer::View(), viewConfig(viewConfig) {

	// set background color
	getCamera()->setClearColor(osg::Vec4(viewConfig.clearColorRed,
                                        viewConfig.clearColorGreen,
                                        viewConfig.clearColorBlue,
                                        viewConfig.clearColorAlpha));

	double fovy, aspectRatio, zNear, zFar;
    getCamera()->getProjectionMatrixAsPerspective(fovy, aspectRatio, zNear, zFar);

    double newAspectRatio = double(viewConfig.width) / double(viewConfig.height);
    double aspectRatioChange = newAspectRatio / aspectRatio;
    if (aspectRatioChange != 1.0)
    {
        getCamera()->getProjectionMatrix() *= osg::Matrix::scale(1.0/aspectRatioChange,1.0,1.0);
    }	

	// TODO: check the width and height, should be > 0
	getCamera()->setViewport(new osg::Viewport(viewConfig.posX, viewConfig.posY, viewConfig.width, viewConfig.height));    

	keyswitchManipulator = new osgGA::KeySwitchMatrixManipulator;  
	keyswitchManipulator->addMatrixManipulator( '0', "NONE", NULL );
    keyswitchManipulator->addMatrixManipulator( '1', "Trackball", new osgGA::TerrainManipulator() );
    keyswitchManipulator->addMatrixManipulator( '2', "Flight", new osgGA::FlightManipulator() );
	keyswitchManipulator->selectMatrixManipulator('1');

    setCameraManipulator(keyswitchManipulator);

	setSceneData(scene);

	if (viewConfig.hasObjectSelector == true) {
		objectSelector = new ObjectSelector(this);
    	addEventHandler(objectSelector);
    }
}

void SuperView::setGraphicContext(osg::GraphicsContext* graphicsContext) {
	if (graphicsContext == NULL)
		// TODO: throw exception
		std::cout << "graphic context is null" << std::endl;
	else
		getCamera()->setGraphicsContext(graphicsContext);
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
		std::cout << "no object selector was active at the moment" << std::endl;
	}
}

void SuperView::enableCameraControl() {
	keyswitchManipulator->selectMatrixManipulator('1');
}

void SuperView::disableCameraControl() {
	keyswitchManipulator->selectMatrixManipulator('0');
}

}