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
       switch (ea.getEventType())
       {
           case(osgGA::GUIEventAdapter::PUSH):
           {
               std::cout << "Keydown!" << std::endl;

               osg::ref_ptr<osgUtil::LineSegmentIntersector> ray = new osgUtil::LineSegmentIntersector(osgUtil::Intersector::PROJECTION, ea.getXnormalized(), ea.getYnormalized());
               osgUtil::IntersectionVisitor visitor(ray);

               viewer->getCamera()->accept(visitor);

               if (ray->containsIntersections())
               {
            	   osgUtil::LineSegmentIntersector::Intersection intersection = ray->getFirstIntersection();

                   //if (m_selector->handle(intersection))
                   //{
            	   std::cout << ("intersection") << std::endl;

                   //const osg::Vec3 &p = intersection.getLocalIntersectPoint();
            	   const osg::Vec3 &p = intersection.getGlobalIntersectPoint();
                   std::cout << "Point: " << p[0] << " " << p[1] << " " << p[2] << std::endl;

                   int mask = ea.getButtonMask();

                   for (osg::NodePath::iterator node = intersection.nodePath.begin(); node != intersection.nodePath.end(); node++){
                	   Clickable* obj = dynamic_cast<Clickable*>(*node);
                       if (obj){
                    	   obj->clicked(mask,p[0],p[1],p[2]);
                       }
                   };


                       return true;
                   //}
               }
           }
           default:
               return false;
       }
   }

} /* namespace osgviz */
