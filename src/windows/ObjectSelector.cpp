/*
 * ObjectSelector.cpp
 *
 *  Created on: 09.03.2015
 *      Author: planthaber
 */

#include "ObjectSelector.h"

#include "../interfaces/Clickable.h"
#include "Window.h"

#include <osgUtil/LineSegmentIntersector>
#include <iostream>
#include <stdio.h>

namespace osgviz {

ObjectSelector::ObjectSelector(osgviz::Window *win):osgGA::GUIEventHandler(),window(win) {


}

ObjectSelector::~ObjectSelector() {
	// TODO Auto-generated destructor stub
}


bool ObjectSelector::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
   {
	   thisEvent = ea.getEventType();

	   //ignored events (for the lastEvent setting)
	   if (thisEvent != osgGA::GUIEventAdapter::FRAME && thisEvent != osgGA::GUIEventAdapter::MOVE ){

		   std::cout << "event " << thisEvent << std::endl;

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

		   if (ray->containsIntersections()){

			   //normal click
			   if(thisEvent & osgGA::GUIEventAdapter::RELEASE && lastEvent & osgGA::GUIEventAdapter::PUSH){
				   lastEvent = thisEvent;
				   //get the first Clickabe Object in path that accepts being clicked
				   for (osg::NodePath::iterator node = intersection.nodePath.begin(); node != intersection.nodePath.end(); node++){
					   Clickable* obj = dynamic_cast<Clickable*>(*node);
					   if (obj){
						   if (obj->clicked(pushedButtonsMask,w,p,obj)){
							   return true;
						   }
					   }
				   };
			   }

			   //drag
			   if (thisEvent & osgGA::GUIEventAdapter::DRAG){



				   //get the first Clickabe Object in path
				   for (osg::NodePath::iterator node = intersection.nodePath.begin(); node != intersection.nodePath.end(); node++){
					   Clickable* obj = dynamic_cast<Clickable*>(*node);
					   if (obj){

						  // window->disableCameraControl();
						   std::cout << "drag obj " << thisEvent << " " << lastEvent << std::endl;
						   fflush(stdout);
						   if (obj->dragged(pushedButtonsMask,w,p,obj)){
							   //there is a receiving obj,
							   std::cout << "dragged obj " << thisEvent << " " << lastEvent << std::endl;
							   fflush(stdout);
							   if (lastEvent == osgGA::GUIEventAdapter::PUSH){
								   std::cout << "disable cam control"<< std::endl;
							   	   window->disableCameraControl();
							   }
							   lastEvent = thisEvent;
							   return true;
						   }else{
							   std::cout << "drag false " << thisEvent << " " << lastEvent << std::endl;
						   }
					   }
				   }
			   }

			   if (thisEvent & osgGA::GUIEventAdapter::RELEASE && lastEvent & osgGA::GUIEventAdapter::DRAG){
				   std::cout << "enable cam control"<< std::endl;
				   window->enableCameraControl();
			   }

		   }

		   lastEvent = thisEvent;
		   return false;
	   }
	   return false;
   }

} /* namespace osgviz */
