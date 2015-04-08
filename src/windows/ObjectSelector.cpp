/*
 * ObjectSelector.cpp
 *
 *  Created on: 09.03.2015
 *      Author: planthaber
 */

#include "ObjectSelector.h"

#include "../interfaces/Clickable.h"
#include "SuperView.h"

#include <osgUtil/LineSegmentIntersector>
#include <iostream>


namespace osgviz {

ObjectSelector::ObjectSelector(osgviz::SuperView *view):osgGA::GUIEventHandler(),view(view) {


}

ObjectSelector::~ObjectSelector() {
	// TODO Auto-generated destructor stub
}


bool ObjectSelector::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
   {
	   thisEvent = ea.getEventType();

	   //ignored events (for the lastEvent setting)
	   if (thisEvent != osgGA::GUIEventAdapter::FRAME && thisEvent != osgGA::GUIEventAdapter::MOVE ){

		   //save the buttonmask (not available in release event)
		   if (thisEvent == osgGA::GUIEventAdapter::PUSH){
			   pushedButtonsMask = ea.getButtonMask();
		   }

		   osg::ref_ptr<osgUtil::LineSegmentIntersector> ray = new osgUtil::LineSegmentIntersector(osgUtil::Intersector::PROJECTION, ea.getXnormalized(), ea.getYnormalized());
		   osgUtil::IntersectionVisitor visitor(ray);
		   view->getCamera()->accept(visitor);
		   osgUtil::LineSegmentIntersector::Intersection intersection = ray->getFirstIntersection();

		   const osg::Vec3 &p = intersection.getLocalIntersectPoint();
		   const osg::Vec3 &w = intersection.getWorldIntersectPoint();

		   if (ray->containsIntersections()){

			   if(thisEvent == osgGA::GUIEventAdapter::RELEASE && lastEvent == osgGA::GUIEventAdapter::PUSH){
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

			   if (thisEvent == osgGA::GUIEventAdapter::DRAG){
				   //get the first Clickabe Object in path
				   for (osg::NodePath::iterator node = intersection.nodePath.begin(); node != intersection.nodePath.end(); node++){
					   Clickable* obj = dynamic_cast<Clickable*>(*node);
					   if (obj){
						   if (obj->dragged(pushedButtonsMask,w,p,obj)){
							   //there is a receiving obj,
							   if (lastEvent == osgGA::GUIEventAdapter::PUSH){
								   view->disableCameraControl();
							   }
							   lastEvent = thisEvent;
							   return true;
						   }
					   }
				   }
			   }

			   if (thisEvent == osgGA::GUIEventAdapter::RELEASE && lastEvent == osgGA::GUIEventAdapter::DRAG){
				   view->enableCameraControl();
			   }

		   }

		   lastEvent = thisEvent;
		   return false;
	   }
	   return false;
   }

} /* namespace osgviz */
