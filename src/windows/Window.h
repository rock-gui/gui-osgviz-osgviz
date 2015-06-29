/*
 * Window.h
 *
 *  Created on: 17.02.2015
 *      Author: planthaber
 */

#ifndef OSGVIZ_OSGVIZ_SRC_WINDOWS_WINDOW_H_
#define OSGVIZ_OSGVIZ_SRC_WINDOWS_WINDOW_H_

#include <iostream>
#include <vector>

#include <osgViewer/CompositeViewer>
#include <osgParticle/PrecipitationEffect>

#include <osgGA/KeySwitchMatrixManipulator>
#include <osgGA/TerrainManipulator>
#include <osgGA/FlightManipulator>

#include <osg/GraphicsContext>
#include <osg/Group>
#include <osg/StateSet>

#include "../graphics/interfaces/data/GraphicData.h"
#include "../graphics/interfaces/data/LightData.h"
#include "ObjectSelector.h"
#include "config/WindowConfig.h"

namespace osgviz {

class Window : public osgViewer::CompositeViewer {

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
	typedef osg::ref_ptr<Window> Ptr;
	
	Window(WindowConfig windowConfig, osg::Group* windowScene = NULL);
	virtual ~Window();

//	void setScene(osg::Group *scene);

//	osg::Group* getScene();

	//void setName(const std::string& name);

    osgViewer::View* addView(ViewConfig viewConfig, osg::Group* viewScene = NULL);

    osgViewer::GraphicsWindow* getGraphicsWindow(int index = 0);

    void addChild(osg::Group *scene) {
    	root->addChild(scene);
    }    

	void setWindowGeometry(int posX, int posY, int width, int height);    

	void showRain(const bool &val = true);
	void showSnow(const bool &val = true);
	//void showFog(const bool &val = true);    

/*	void frame();

	void enableCameraControl();
	void disableCameraControl();



	inline osgViewer::View* getView(int index = 0){
		return views[index];
	}

	inline osg::ref_ptr<osgViewer::CompositeViewer> getViewer(){
		return viewer;
	}*/




private:
	WindowConfig windowConfig;

	osg::ref_ptr<osg::GraphicsContext> graphicsContext;
	osg::ref_ptr<osg::StateSet> globalStateset;	

	osg::ref_ptr<osg::Group> root;

	osg::ref_ptr<osgParticle::PrecipitationEffect> snow, rain;

};

} /* namespace osgviz */

#endif /* OSGVIZ_OSGVIZ_SRC_WINDOWS_WINDOW_H_ */
