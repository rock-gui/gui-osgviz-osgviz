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
#include "config/WindowConfig.h"
#include "HUD.h"

namespace osgviz {

class Window : public osgViewer::CompositeViewer {

public:
	
	Window(WindowConfig windowConfig, osg::ref_ptr<osg::Node> windowScene, osg::ref_ptr<osg::GraphicsContext> graphicsContext = NULL);
	virtual ~Window();

//	void setScene(osg::Group *scene);

//	osg::Group* getScene();

	//void setName(const std::string& name);

	osgViewer::View* addView(ViewConfig viewConfig, osg::Group* viewScene = NULL);

	osg::ref_ptr<osgviz::HUD> addHUD(int width,int height, unsigned int window = 0);


	osg::ref_ptr<osgViewer::GraphicsWindow> getGraphicsWindow();

    void addChild(osg::ref_ptr<osg::Node> scene) {
    	root->addChild(scene);
    }    

	void setWindowGeometry(int posX, int posY, int width, int height, int window=0);

	void setFullscreen(bool state = true, int window=0, int screen = 0);

	void showRain(const bool &val = true);
	void showSnow(const bool &val = true);
	//void showFog(const bool &val = true);    

/*	void frame();

	void enableCameraControl();
	void disableCameraControl();





	inline osg::ref_ptr<osgViewer::CompositeViewer> getViewer(){
		return viewer;
	}*/

    inline osgViewer::View* getView(unsigned int index = 0){
        if (index < views.size()){
            return views[index];
        }
        return NULL;
    }

	inline osg::ref_ptr<osg::Group> getRootNode(){
		return root;
	}

	inline void clear(){
		root->removeChild(0,root->getNumChildren());
	}

protected:
	osg::ref_ptr<osg::Group> root;

private:
	WindowConfig windowConfig;

	osg::ref_ptr<osg::GraphicsContext> graphicsContext;

	osg::ref_ptr<osgViewer::GraphicsWindow> gw;

	osg::ref_ptr<osgParticle::PrecipitationEffect> snow, rain;

	std::vector < osg::ref_ptr<osgviz::SuperView> > views;
	std::vector < osg::ref_ptr<osgviz::HUD> > huds;

};

} /* namespace osgviz */

#endif /* OSGVIZ_OSGVIZ_SRC_WINDOWS_WINDOW_H_ */
