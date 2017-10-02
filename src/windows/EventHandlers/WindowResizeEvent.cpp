/*
 * WindowResizeEvent.cpp
 *
 *  Created on: 08.09.2017
 *      Author: Anna Born
 */

#include "WindowResizeEvent.h"

namespace osgviz {

WindowResizeEvent::WindowResizeEvent() {
    // TODO Auto-generated constructor stub

}

WindowResizeEvent::~WindowResizeEvent() {
    // TODO Auto-generated destructor stub
}

bool WindowResizeEvent::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa) {

    //only evaluate following events
    if (ea.getEventType() == osgGA::GUIEventAdapter::RESIZE){

        for (std::vector<WindowResizeCallback*>::iterator cb = callbacks.begin();cb != callbacks.end(); ++cb){
            (*cb)->windowResized(ea.getWindowWidth(), ea.getWindowHeight());
        }

    }
    return false;
}

} /* namespace intercation */
