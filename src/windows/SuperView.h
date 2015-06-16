/*
 * Window.h
 *
 *  Created on: 17.02.2015
 *      Author: planthaber
 */

#ifndef OSGVIZ_OSGVIZ_SRC_WINDOWS_VIEW_H_
#define OSGVIZ_OSGVIZ_SRC_WINDOWS_VIEW_H_

#include <iostream>
#include <stdexcept>

#include <osgViewer/View>
#include <osgParticle/PrecipitationEffect>

#include <osgGA/KeySwitchMatrixManipulator>
#include <osgGA/TerrainManipulator>
#include <osgGA/FlightManipulator>

#include "config/WindowConfig.h"
#include "ObjectSelector.h"

namespace osgviz {

class SuperView : public osgViewer::View, public WindowInterface {

	public:
		SuperView();

		SuperView(ViewConfig viewConfig, osg::GraphicsContext* graphicsContext, osg::Group* scene = NULL);

		virtual void activeObjectSelector();
		virtual void deactivateObjectSelector();

		virtual void enableCameraControl();
		virtual void disableCameraControl();

	 	virtual void setCursorShape(int cursor);
	 	virtual void setCursorPos(int x, int y);

	private:
		ViewConfig viewConfig;

		osg::ref_ptr<ObjectSelector> objectSelector;

		osg::ref_ptr<osgParticle::PrecipitationEffect> snow;
		osg::ref_ptr<osgParticle::PrecipitationEffect> rain;
		osg::ref_ptr<osg::Fog> fog;

		osg::ref_ptr<osgGA::KeySwitchMatrixManipulator> keyswitchManipulator;
};

} /* namespace osgviz */

#endif /* OSGVIZ_OSGVIZ_SRC_WINDOWS_VIEW_H_ */
