/*
* MouseMoveEvent.h
*
*  Created on: 01.06.2016
*      Author: planthaber
*/

#ifndef GUI_OSGVIZ_OSGVIZ_SRC_WINDOWS_EVENTHANDLERS_MOUSEMOVEEVENT_H_
#define GUI_OSGVIZ_OSGVIZ_SRC_WINDOWS_EVENTHANDLERS_MOUSEMOVEEVENT_H_


#include <osgGA/GUIEventHandler>
#include "../../interfaces/MouseMoveCallback.h"

#include <vector>


namespace osgviz {

    class MouseMoveEvent : public osgGA::GUIEventHandler {
    public:

        MouseMoveEvent();

        virtual ~MouseMoveEvent();


        virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

        void addCallback(MouseMoveCallback* cb){
            callbacks.push_back(cb);
        }

    private:
        std::vector<MouseMoveCallback*> callbacks;

    };

} /* namespace intercation */

#endif /* GUI_OSGVIZ_OSGVIZ_SRC_WINDOWS_EVENTHANDLERS_MOUSEMOVEEVENT_H_ */
