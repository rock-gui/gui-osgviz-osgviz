/*
 * ObjectSelector.h
 *
 *  Created on: 09.03.2015
 *      Author: planthaber
 */

#ifndef OSGVIZ_OSGVIZ_SRC_PLUGINS_OBJECTSELECTOR_H_
#define OSGVIZ_OSGVIZ_SRC_PLUGINS_OBJECTSELECTOR_H_


#include <osgGA/GUIEventHandler>
#include "../../interfaces/Clickable.h"
//#include <osgViewer/View>

namespace osgviz {

class SuperView;


class ObjectSelector : public osgGA::GUIEventHandler{
public:
    ObjectSelector(osgviz::SuperView *view);

    virtual ~ObjectSelector();

    virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

    struct IntersectionResult{
        osg::Vec3 p;
        osg::Vec3 w;
        osg::Vec2d c;
        Clickable* clickable;
    };

private:



    osgviz::SuperView *view;
    Clickable *draggedObject;
    osgGA::GUIEventAdapter::EventType thisEvent,lastEvent;
    int pushedButtonsMask;



    std::vector<IntersectionResult> getIntersections(const osgGA::GUIEventAdapter& ea);



};

} /* namespace osgviz */

#endif /* OSGVIZ_OSGVIZ_SRC_PLUGINS_OBJECTSELECTOR_H_ */
