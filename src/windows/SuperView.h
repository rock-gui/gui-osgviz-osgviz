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

#include <osgDB/WriteFile>

#include "config/WindowConfig.h"
#include "ObjectSelector.h"

#include "../graphics/interfaces/data/GraphicData.h"
#include "../graphics/interfaces/data/LightData.h"

#include "../graphics/wrapper/OSGLightStruct.h"

namespace osgviz {

    /**
     * internal struct to manage lights
     */
    struct lightmanager {
      osg::ref_ptr<osg::LightSource> lightSource;
      osg::ref_ptr<osg::Light> light;
      interfaces::LightData lStruct;
      bool free;
    };	

class SuperView : public osgViewer::View, public WindowInterface {

	public:
		SuperView();

		SuperView(ViewConfig viewConfig, osg::GraphicsContext* graphicsContext, osg::Group* viewScene = NULL);

		~SuperView();

		virtual void activeObjectSelector();
		virtual void deactivateObjectSelector();

		virtual void enableCameraControl();
		virtual void disableCameraControl();

	 	virtual void setCursorShape(int cursor);
	 	virtual void setCursorPos(int x, int y);

	 	void addChild(osg::ref_ptr<osg::Group> scene) {
	 		root->addChild(scene);
	 	}

	 	void setRoot(osg::ref_ptr<osg::Group> scene){
	 		root = scene;
	 	}

	 	void setFogSettings(const osgviz::interfaces::GraphicData &graphicOptions);

	 	inline osg::ref_ptr<osgGA::KeySwitchMatrixManipulator> getKeyswitchMatrixManipulator(){
	 		return keyswitchManipulator;
	 	}

	 	void disableCameraManipulator(){
	 		setCameraManipulator(NULL);
	 	}

	 	void enableCameraManipulator(){
	 		setCameraManipulator(keyswitchManipulator);
	 	}

	private:
		ViewConfig viewConfig;

		osg::ref_ptr<ObjectSelector> objectSelector;

		osg::ref_ptr<osgParticle::PrecipitationEffect> snow;
		osg::ref_ptr<osgParticle::PrecipitationEffect> rain;
		osg::ref_ptr<osg::Fog> fog;

		osg::ref_ptr<osgGA::KeySwitchMatrixManipulator> keyswitchManipulator;

		osg::ref_ptr<osg::Group> root;

		osg::ref_ptr<osg::StateSet> globalStateset;	

		// includes osg::lights, osg::lightsource, lightstruct and flag to check if full
		std::vector<lightmanager> myLights;		

		osg::ref_ptr<osg::Group> lightGroup;

		lightmanager defaultLight;	

		osgviz::interfaces::GraphicData graphicData;

		void initDefaultLight();
};

} /* namespace osgviz */

#endif /* OSGVIZ_OSGVIZ_SRC_WINDOWS_VIEW_H_ */
