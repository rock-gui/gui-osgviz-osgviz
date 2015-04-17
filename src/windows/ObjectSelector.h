/*
 * ObjectSelector.h
 *
 *  Created on: 09.03.2015
 *      Author: planthaber
 */

#ifndef OSGVIZ_OSGVIZ_SRC_PLUGINS_OBJECTSELECTOR_H_
#define OSGVIZ_OSGVIZ_SRC_PLUGINS_OBJECTSELECTOR_H_


#include <osgGA/GUIEventHandler>
#include "../interfaces/Clickable.h"
//#include <osgViewer/View>

namespace osgviz {

class Window;

class ObjectSelector : public osgGA::GUIEventHandler{
public:
	ObjectSelector(osgviz::Window *win);

	virtual ~ObjectSelector();

	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);


private:
	osgviz::Window *window;
	Clickable *draggedObject;
	osgGA::GUIEventAdapter::EventType thisEvent,lastEvent;
	int pushedButtonsMask;



};

} /* namespace osgviz */

#endif /* OSGVIZ_OSGVIZ_SRC_PLUGINS_OBJECTSELECTOR_H_ */
