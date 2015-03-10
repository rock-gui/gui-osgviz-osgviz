/*
 * ObjectSelector.h
 *
 *  Created on: 09.03.2015
 *      Author: planthaber
 */

#ifndef OSGVIZ_OSGVIZ_SRC_PLUGINS_OBJECTSELECTOR_H_
#define OSGVIZ_OSGVIZ_SRC_PLUGINS_OBJECTSELECTOR_H_


#include <osgGA/GUIEventHandler>
#include <osgViewer/View>

namespace osgviz {

class ObjectSelector : public osgGA::GUIEventHandler{
public:
	ObjectSelector(osgViewer::View * view);

	virtual ~ObjectSelector();

	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);


private:
	osgViewer::View *viewer;

};

} /* namespace osgviz */

#endif /* OSGVIZ_OSGVIZ_SRC_PLUGINS_OBJECTSELECTOR_H_ */
