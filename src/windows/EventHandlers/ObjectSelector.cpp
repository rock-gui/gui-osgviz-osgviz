/*
 * ObjectSelector.cpp
 *
 *  Created on: 09.03.2015
 *      Author: planthaber
 */

#include "ObjectSelector.h"

#include <osgViz/OsgViz.hpp>
#include <osgViz/interfaces/Clickable.h>
#include <osgViz/windows/SuperView.h>
#include <osgViz/windows/HUD.h>

#include <osgUtil/LineSegmentIntersector>
#include <iostream>

namespace osgviz {

ObjectSelector::ObjectSelector(osgviz::SuperView *view):osgGA::GUIEventHandler(),view(view) {
    draggedObject= NULL;
}

ObjectSelector::~ObjectSelector() {}

std::deque<ObjectSelector::IntersectionResult> ObjectSelector::getIntersections(const osgGA::GUIEventAdapter& ea){

    /* If a hud is clicked, return the node path to the hud, otherwise return
     * the path to the closest clicked object. */
  
    //projection space is [-1 ... 1], thus we can directly use the normalized
    //mouse coordinates
    double mx = ea.getXnormalized();
    double my = ea.getYnormalized();
    double w = 0.01; //width and height of the polytope, that is shot into the scene
    double h = 0.01;
    osg::ref_ptr<osgUtil::PolytopeIntersector> intersector;
    intersector = new osgUtil::PolytopeIntersector( osgUtil::Intersector::PROJECTION, mx-w, my-h, mx+w, my+h );
    intersector->setIntersectionLimit(osgUtil::Intersector::LIMIT_ONE_PER_DRAWABLE);// a single drawable will appear at most once while calculating intersections.

    osgUtil::IntersectionVisitor iv(intersector);
    view->getCamera()->accept(iv);
    
    std::deque<IntersectionResult> results;
    
    if(intersector->containsIntersections())
    {
        osgUtil::PolytopeIntersector::Intersections intersections = intersector->getIntersections();
        IntersectionResult result;
        result.c = osg::Vec2d(ea.getX(),ea.getY());
        
        osgUtil::PolytopeIntersector::Intersections::iterator intersection = intersections.begin();
        result.p = intersection->localIntersectionPoint;
        result.w = intersection->localIntersectionPoint * (*intersection->matrix.get());

        //get the node path to the first intersection
        results = getclickablePath(intersection->nodePath, result);
        
        //If a hud is present, it may be anywhere in the intersection list because
        //sorting is done by z-buffer value and the hud doesn't have one.
        //Therefore all remaining intersections need to be checked
        
        ++intersection;
        for(;intersection != intersections.end(); ++intersection)
        {
            if(containsHud(intersection->nodePath))
            {
                result.p = intersection->localIntersectionPoint;
                result.w = intersection->localIntersectionPoint * (*intersection->matrix.get());
                results = getclickablePath(intersection->nodePath, result);
                break;
            }
        }
    }
    return results;
}

bool ObjectSelector::containsHud(const osg::NodePath& nodePath) const
{
    osg::NodePath::const_iterator it;
    for (it = nodePath.begin(); it != nodePath.end(); ++it){
        HUD* hud = dynamic_cast<HUD*>(*it);
        if (hud){
            return true;
        }      
    }
    return false;
}

std::deque<ObjectSelector::IntersectionResult> ObjectSelector::getclickablePath(const osg::NodePath& nodePath,
                                                                                  ObjectSelector::IntersectionResult tmplate)
{
    std::deque<ObjectSelector::IntersectionResult> results;
    for (osg::NodePath::const_iterator it = nodePath.begin(); it != nodePath.end(); it++){
        Clickable* obj = dynamic_cast<Clickable*>(*it);
        if(obj != NULL) {
            tmplate.clickable = obj;
            results.push_back(tmplate);  
        }
    }
    return results;
}


bool ObjectSelector::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa){
    thisEvent = ea.getEventType();

    //only evaluate following events
    if (	   thisEvent == osgGA::GUIEventAdapter::PUSH
            || thisEvent == osgGA::GUIEventAdapter::RELEASE
            || thisEvent == osgGA::GUIEventAdapter::DRAG
    ){


        //save the buttonmask (not available in release event)
        if (thisEvent == osgGA::GUIEventAdapter::PUSH){
            pushedButtonsMask = ea.getButtonMask();
            modKeyMask = ea.getModKeyMask();
        }

        //normal click
        if(thisEvent & osgGA::GUIEventAdapter::RELEASE && lastEvent & osgGA::GUIEventAdapter::PUSH){
            lastEvent = thisEvent;

            std::deque<IntersectionResult> intersections = getIntersections(ea);

            if (!intersections.empty()){
                std::deque<IntersectionResult>::reverse_iterator it;
                for (it = intersections.rbegin(); it != intersections.rend(); it++){
                        if (it->clickable->clicked(pushedButtonsMask, it->c, it->w,
                                                   it->p, it->clickable, modKeyMask,
                                                   view)){
                            return true;
                        }
                }
            }
        }

        //drag

        if (thisEvent & osgGA::GUIEventAdapter::DRAG && lastEvent & osgGA::GUIEventAdapter::PUSH){
            //get the first Clickabe Object in path
            draggedObject = NULL;

            std::deque<IntersectionResult> intersections = getIntersections(ea);

            if (!intersections.empty()){
                std::deque<IntersectionResult>::reverse_iterator it;
                for (it = intersections.rbegin(); it != intersections.rend(); it++){
                    if (it->clickable->dragged(pushedButtonsMask, it->c, it->w,
                                               it->p, it->clickable, modKeyMask,
                                               view)){
                        //there is a receiving obj,
                        view->disableCameraControl();
                        draggedObject = it->clickable;
                        lastEvent = thisEvent;
                        return true;
                    }
                }
            }

        }

        if (thisEvent & osgGA::GUIEventAdapter::DRAG){
            //don't need checks, the initial object is used
            lastEvent = thisEvent;
            if (draggedObject){

                std::deque<IntersectionResult> intersections = getIntersections(ea);
                std::deque<IntersectionResult>::iterator it;
                for (it = intersections.begin(); it != intersections.end(); it++){
                    if (it->clickable == draggedObject){
                        return draggedObject->dragged(pushedButtonsMask, it->c, it->w,
                                                      it->p, draggedObject, modKeyMask,
                                                      view);
                    }
                }
            }
            return false;
        }

        if (thisEvent & osgGA::GUIEventAdapter::RELEASE && lastEvent & osgGA::GUIEventAdapter::DRAG){
            view->enableCameraControl();
            lastEvent = thisEvent;
            if (draggedObject){
                //dragging stopped call calback with 0 as buttom mask and modkey mask
                int buttons = 0;
                int modkey = 0;
                bool res = draggedObject->dragged(buttons,osg::Vec2d(0,0),osg::Vec3(0,0,0),osg::Vec3(0,0,0),draggedObject,modkey,view);
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
