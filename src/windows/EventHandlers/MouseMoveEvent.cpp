/*
* MouseMoveEvent.cpp
*
*  Created on: 01.06.2016
*      Author: planthaber
*/

#include "MouseMoveEvent.h"

namespace osgviz {

    MouseMoveEvent::MouseMoveEvent() {
        // TODO Auto-generated constructor stub

    }

    MouseMoveEvent::~MouseMoveEvent() {
        // TODO Auto-generated destructor stub
    }

    bool MouseMoveEvent::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa) {

        //only evaluate following events
        if (ea.getEventType() == osgGA::GUIEventAdapter::MOVE){

            for (std::vector<MouseMoveCallback*>::iterator cb = callbacks.begin();cb != callbacks.end(); ++cb){
                (*cb)->mouseMoved(ea.getX(),ea.getY(),ea.getXnormalized(),ea.getYnormalized(),ea.getModKeyMask());
            }

        }
        return false;
    }

} /* namespace intercation */
