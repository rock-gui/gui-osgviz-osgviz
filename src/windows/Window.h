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

#include <osg/GraphicsContext>
#include <osg/Group>
#include <osg/StateSet>

#include "config/WindowConfig.h"

namespace osgviz {

class Window : public osgViewer::CompositeViewer {

public:
	typedef osg::ref_ptr<Window> Ptr;
	
	Window(WindowConfig windowConfig);
	virtual ~Window();

	osgViewer::View* addView(ViewConfig viewConfig, osg::Group* scene);

private:
	WindowConfig windowConfig;

	osg::ref_ptr<osg::GraphicsContext> graphicsContext;

	osg::ref_ptr<osg::Group> root;

	osg::ref_ptr<osg::StateSet> globalStateset;
};

} /* namespace osgviz */

#endif /* OSGVIZ_OSGVIZ_SRC_WINDOWS_WINDOW_H_ */
