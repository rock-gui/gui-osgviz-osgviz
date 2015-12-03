/*
 * ObjectSelector.cpp
 *
 *  Created on: 09.03.2015
 *      Author: planthaber
 */

#include "ObjectSelector.h"

#include "../OsgViz.hpp"
#include "../interfaces/Clickable.h"
#include "SuperView.h"

#include <osgUtil/LineSegmentIntersector>
#include <iostream>


namespace osgviz {

ObjectSelector::ObjectSelector(osgviz::SuperView *view):osgGA::GUIEventHandler(),view(view) {
	draggedObject= NULL;

}

ObjectSelector::~ObjectSelector() {
	// TODO Auto-generated destructor stub
}

Clickable* ObjectSelector::getIntersection(const osgGA::GUIEventAdapter& ea, osg::Vec3 &p, osg::Vec3 &w, osg::Vec2d &c){

	osg::ref_ptr<osgUtil::LineSegmentIntersector> ray = new osgUtil::LineSegmentIntersector(osgUtil::Intersector::PROJECTION, ea.getXnormalized(), ea.getYnormalized());
	osgUtil::IntersectionVisitor visitor(ray);

	view->getCamera()->accept(visitor);

	osgUtil::LineSegmentIntersector::Intersection intersection = ray->getFirstIntersection();

	if( ray->containsIntersections()){
		p = intersection.getLocalIntersectPoint();
		w = intersection.getWorldIntersectPoint();
		c = osg::Vec2d(ea.getX(),ea.getY());

		for (osg::NodePath::iterator node = intersection.nodePath.begin(); node != intersection.nodePath.end(); node++){
			Clickable* obj = dynamic_cast<Clickable*>(*node);
			if (obj){
					return obj;
			}
		}
		return NULL;
	}

	return NULL;
}


bool ObjectSelector::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
	thisEvent = ea.getEventType();

	//only evaluate following events
	if (	   thisEvent == osgGA::GUIEventAdapter::PUSH
			|| thisEvent == osgGA::GUIEventAdapter::RELEASE
			|| thisEvent == osgGA::GUIEventAdapter::DRAG
	){


		//save the buttonmask (not available in release event)
		if (thisEvent == osgGA::GUIEventAdapter::PUSH){
			pushedButtonsMask = ea.getButtonMask();
		}

		//normal click
		if(thisEvent & osgGA::GUIEventAdapter::RELEASE && lastEvent & osgGA::GUIEventAdapter::PUSH){
			lastEvent = thisEvent;

			Clickable* obj = getIntersection(ea,p,w,c);
			if (obj){
				if (obj->clicked(pushedButtonsMask,c,w,p,obj,view)){
					return true;
				}
			}
		}

		//drag

		if (thisEvent & osgGA::GUIEventAdapter::DRAG && lastEvent & osgGA::GUIEventAdapter::PUSH){
			//get the first Clickabe Object in path
			draggedObject = NULL;

			Clickable* obj = getIntersection(ea,p,w,c);
			if (obj){
				if (obj->dragged(pushedButtonsMask,c,w,p,obj,view)){
					//there is a receiving obj,
					view->disableCameraControl();
					draggedObject = obj;
					lastEvent = thisEvent;
					return true;
				}
			}
		}

		if (thisEvent & osgGA::GUIEventAdapter::DRAG){
			//don't need checks, the initial object is used
			lastEvent = thisEvent;
			if (draggedObject){
				if (getIntersection(ea,p,w,c)){

					return draggedObject->dragged(pushedButtonsMask,c,w,p,draggedObject,view);
				}
			}
			return false;
		}

		if (thisEvent & osgGA::GUIEventAdapter::RELEASE && lastEvent & osgGA::GUIEventAdapter::DRAG){
			view->enableCameraControl();
			lastEvent = thisEvent;
			if (draggedObject){
				//dragging stopped call calback with 0 as buttom mask
				int buttons = 0;
				getIntersection(ea,p,w,c);
				bool res = draggedObject->dragged(buttons,c,w,p,draggedObject,view);
				draggedObject = NULL;
				return res;
			}
		}



		lastEvent = thisEvent;

		if (draggedObject){
			//no intersection, but still dragging
			return true;
		}
		return false;
	}
	return false;
}

} /* namespace osgviz */
