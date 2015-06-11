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

#include "../graphics/interfaces/data/GraphicData.h"
#include "../graphics/interfaces/data/LightData.h"
#include "../interfaces/WindowInterface.h"
#include "ObjectSelector.h"

namespace osgviz {

class Window : public WindowInterface {

    /**
     * internal struct to manage lights
     */
    struct lightmanager {
      osg::ref_ptr<osg::LightSource> lightSource;
      osg::ref_ptr<osg::Light> light;
      interfaces::LightData lStruct;
      bool free;
    };


public:
	Window(osg::Group *scene, interfaces::GraphicData graphicData);

	virtual ~Window();

	void setScene(osg::Group *scene);

	osg::Group* getScene();

	void setName(const std::string& name);
	const std::string getName();

	osgViewer::View* addView(std::string name = "3d Window");

	void frame();

	virtual void enableCameraControl();
	virtual void disableCameraControl();

	virtual void setCursorShape(int cursor);
	virtual void setCursorPos(int x, int y);




	void showRain(const bool &val = true);
	void showSnow(const bool &val = true);
	void showFog(const bool &val = true);


	inline osgViewer::GraphicsWindow * getGraphicsWindow(){
		return graphicsWindow;
	}

	inline osgViewer::View* getView(int index = 0){
		return views[index];
	}

	inline osg::ref_ptr<osgViewer::CompositeViewer> getViewer(){
		return viewer;
	}

	inline unsigned int getId(){
		return id;
	}

	inline void setId(unsigned int newid){
		id = newid;
	}

private:

	void initDefaultLight();


	unsigned int id;

	osg::ref_ptr<osgViewer::CompositeViewer> viewer;
	std::vector<osgViewer::View* > views;
	osgViewer::GraphicsWindow * graphicsWindow;

	osgViewer::View* mainView;


	osg::Group *scene;
	osg::ref_ptr<osg::StateSet> globalStateset;
	interfaces::GraphicData graphicOptions;


	osg::ref_ptr<osg::Group> lightGroup;
	lightmanager defaultLight;
    std::vector<lightmanager> myLights;


    osg::ref_ptr<osgParticle::PrecipitationEffect> snow, rain;
    osg::ref_ptr<osg::Fog> myFog;

    osg::ref_ptr<ObjectSelector> objectSelector;

    osg::ref_ptr<osgGA::KeySwitchMatrixManipulator> keyswitchManipulator;
    int lastActiveCameraManipulator;
};

} /* namespace osgviz */

#endif /* OSGVIZ_OSGVIZ_SRC_WINDOWS_WINDOW_H_ */
