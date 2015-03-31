/*
 * Window.h
 *
 *  Created on: 17.02.2015
 *      Author: planthaber
 */

#ifndef OSGVIZ_OSGVIZ_SRC_WINDOWS_WINDOW_H_
#define OSGVIZ_OSGVIZ_SRC_WINDOWS_WINDOW_H_

#include <iostream>

#include <osgViewer/CompositeViewer>
#include <osgParticle/PrecipitationEffect>

#include <osgGA/KeySwitchMatrixManipulator>
#include <osgGA/TerrainManipulator>
#include <osgGA/FlightManipulator>

#include "config/WindowConfig.h"

#include "ObjectSelector.h"

namespace osgviz {

class Window {

public:
	Window(WindowConfig windowConfig);

	virtual ~Window();

	void setScene(osg::Group *scene);
	osg::Group* getScene();

	osgViewer::View* addView(ViewConfig viewConfig, osg::Group* scene);

	void enableCameraControl();
	void disableCameraControl();

	void showRain(const bool &val = true);
	void showSnow(const bool &val = true);
	void showFog(const bool &val = true);

	inline osgViewer::View* getView(int index = 0) {
		if (views.size() == 0)
			return NULL;
		else
			return views[index];
	}

private:
	WindowConfig windowConfig;

	osg::ref_ptr<osg::GraphicsContext> graphicsContext;

	std::vector<osg::ref_ptr<osgViewer::View> > views;
	osgViewer::View* mainView;	

	osg::ref_ptr<osg::Group> root;

	osg::ref_ptr<osg::StateSet> globalStateset;

    std::vector<osg::ref_ptr<ObjectSelector> > objectSelectors;

    osg::ref_ptr<osgGA::KeySwitchMatrixManipulator> keyswitchManipulator;
    int lastActiveCameraManipulator;
};

} /* namespace osgviz */

#endif /* OSGVIZ_OSGVIZ_SRC_WINDOWS_WINDOW_H_ */
