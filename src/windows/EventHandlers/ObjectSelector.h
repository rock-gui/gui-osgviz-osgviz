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

#include <deque>
//#include <osgViewer/View>

namespace osgviz {

    class SuperView;


    class ObjectSelector : public osgGA::GUIEventHandler{
    public:
        ObjectSelector(osgviz::SuperView *view);

        virtual ~ObjectSelector();

        virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

        struct IntersectionResult{
            osg::Vec3 p; /**< local intersection point */
            osg::Vec3 w; /**< world intersection point */
            osg::Vec2d c;/**< click coordinates */
            Clickable* clickable;
        };

        void setCamera(const osg::ref_ptr<osg::Camera>& cam){
            camera = cam;
        }

    private:



        osgviz::SuperView *view;
        Clickable *draggedObject;
        osgGA::GUIEventAdapter::EventType thisEvent,lastEvent;
        int pushedButtonsMask;
        int modKeyMask;
        osg::ref_ptr<osg::Camera> camera;

        /** @return a queue containing all clickables that have been hit by the click
        *          sorted by distance to the camera.*/
        std::deque<IntersectionResult> getIntersections(const osgGA::GUIEventAdapter& ea);

        /**returns true if the given nodepath contains a hud element */
        bool containsHud(const osg::NodePath& NodePath) const;

        /**returns a path from top to bottom containing all clickables in the given path.
        * @param tmplate is used as blueprint for the entries. p, w, c will remain
        *                constant, only the clickable is changed. */
        std::deque<IntersectionResult> getclickablePath(const osg::NodePath& NodePath,
            IntersectionResult tmplate);


    };

} /* namespace osgviz */

#endif /* OSGVIZ_OSGVIZ_SRC_PLUGINS_OBJECTSELECTOR_H_ */
