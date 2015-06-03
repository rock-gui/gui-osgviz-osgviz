/*
 * ObjectSelector.cpp
 *
 *  Created on: 09.03.2015
 *      Author: planthaber
 */

#include "ObjectSelector.h"

#include "Window.h"

#include <osgUtil/LineSegmentIntersector>
#include <iostream>
#include <stdio.h>

namespace osgviz {

ObjectSelector::ObjectSelector(osgviz::Window *win):osgGA::GUIEventHandler(),window(win) {
	draggedObject= NULL;

}

ObjectSelector::~ObjectSelector() {
	// TODO Auto-generated destructor stub
}


bool ObjectSelector::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
   {
	   thisEvent = ea.getEventType();

	   //ignored events (for the lastEvent setting)
	   if (thisEvent != osgGA::GUIEventAdapter::FRAME && thisEvent != osgGA::GUIEventAdapter::MOVE ){

//		   std::cout << "event " << thisEvent << std::endl;

		   //save the buttonmask (not available in release event)
		   if (thisEvent == osgGA::GUIEventAdapter::PUSH){
			   pushedButtonsMask = ea.getButtonMask();
		   }

		   osg::ref_ptr<osgUtil::LineSegmentIntersector> ray = new osgUtil::LineSegmentIntersector(osgUtil::Intersector::PROJECTION, ea.getXnormalized(), ea.getYnormalized());
		   osgUtil::IntersectionVisitor visitor(ray);
		   window->getView()->getCamera()->accept(visitor);
		   osgUtil::LineSegmentIntersector::Intersection intersection = ray->getFirstIntersection();

		   const osg::Vec3 &p = intersection.getLocalIntersectPoint();
		   const osg::Vec3 &w = intersection.getWorldIntersectPoint();
		   const osg::Vec2d &c = osg::Vec2d(ea.getX(),ea.getY());

		   if (ray->containsIntersections()){

			   //normal click
			   if(thisEvent & osgGA::GUIEventAdapter::RELEASE && lastEvent & osgGA::GUIEventAdapter::PUSH){
				   lastEvent = thisEvent;
				   //get the first Clickabe Object in path that accepts being clicked
				   for (osg::NodePath::iterator node = intersection.nodePath.begin(); node != intersection.nodePath.end(); node++){
					   Clickable* obj = dynamic_cast<Clickable*>(*node);
					   if (obj){
						   if (obj->clicked(pushedButtonsMask,c,w,p,obj,window)){
							   return true;
						   }
					   }
				   };
			   }

			   //drag

			   if (thisEvent & osgGA::GUIEventAdapter::DRAG && lastEvent & osgGA::GUIEventAdapter::PUSH){
				   //get the first Clickabe Object in path
				   draggedObject = NULL;
				   for (osg::NodePath::iterator node = intersection.nodePath.begin(); node != intersection.nodePath.end(); node++){
					   Clickable* obj = dynamic_cast<Clickable*>(*node);
					   if (obj){
						   if (obj->dragged(pushedButtonsMask,c,w,p,obj,window)){
							   //there is a receiving obj,
							   window->disableCameraControl();
							   draggedObject = obj;
							   lastEvent = thisEvent;
							   return true;
						   }
					   }
				   }
			   }

			   if (thisEvent & osgGA::GUIEventAdapter::DRAG){
				   //don't need chacks, the initial
				   if (draggedObject){
					   lastEvent = thisEvent;
					   return draggedObject->dragged(pushedButtonsMask,c,w,p,draggedObject,window);
				   }
				   lastEvent = thisEvent;
				   return false;
			   }

			   if (thisEvent & osgGA::GUIEventAdapter::RELEASE && lastEvent & osgGA::GUIEventAdapter::DRAG){
				   window->enableCameraControl();
				   //printf("drag release \n");
				   if (draggedObject){
					   int buttons = 0;
					   //dragging stopped
					   printf("drag release2 \n");
					   bool res = draggedObject->dragged(buttons,c,w,p,draggedObject,window);
					   draggedObject = NULL;
					   return res;
				   }
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
