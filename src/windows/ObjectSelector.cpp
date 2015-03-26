/*
 * ObjectSelector.cpp
 *
 *  Created on: 09.03.2015
 *      Author: planthaber
 */

#include "ObjectSelector.h"

#include "../interfaces/Clickable.h"

#include <osgUtil/LineSegmentIntersector>
#include <iostream>


namespace osgviz {

ObjectSelector::ObjectSelector(osgViewer::View * view):osgGA::GUIEventHandler(),viewer(view) {


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
		   std::cout << "event " << thisEvent << "mask" << pushedButtonsMask << std::endl;


		   if(thisEvent == osgGA::GUIEventAdapter::RELEASE && lastEvent == osgGA::GUIEventAdapter::PUSH){
			   osg::ref_ptr<osgUtil::LineSegmentIntersector> ray = new osgUtil::LineSegmentIntersector(osgUtil::Intersector::PROJECTION, ea.getXnormalized(), ea.getYnormalized());
			   osgUtil::IntersectionVisitor visitor(ray);

			   viewer->getCamera()->accept(visitor);

			   if (ray->containsIntersections())
			   {
				   osgUtil::LineSegmentIntersector::Intersection intersection = ray->getFirstIntersection();

				   const osg::Vec3 &p = intersection.getLocalIntersectPoint();
				   const osg::Vec3 &w = intersection.getWorldIntersectPoint();


				   for (osg::NodePath::iterator node = intersection.nodePath.begin(); node != intersection.nodePath.end(); node++){
					   Clickable* obj = dynamic_cast<Clickable*>(*node);
					   if (obj){
						   std::cout << "forward " << thisEvent << "mask" << pushedButtonsMask << std::endl;
						   obj->clicked(pushedButtonsMask,w,p,obj);
					   }
				   };
				   lastEvent = thisEvent;
				   return true;
			   }
		   }
		   lastEvent = thisEvent;
		   return false;
	   }
	   return false;
   }

} /* namespace osgviz */
