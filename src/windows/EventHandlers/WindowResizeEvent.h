/*
* WindowResizeEvent.h
*
*  Created on: 08.09.2017
*      Author: Anna Born
*/

#ifndef GUI_OSGVIZ_OSGVIZ_SRC_WINDOWS_EVENTHANDLERS_WINDOWRESIZEEVENT_H_
#define GUI_OSGVIZ_OSGVIZ_SRC_WINDOWS_EVENTHANDLERS_WINDOWRESIZEEVENT_H_


#include <osgGA/GUIEventHandler>
#include "../../interfaces/WindowResizeCallback.h"

#include <vector>


namespace osgviz {

    class WindowResizeEvent : public osgGA::GUIEventHandler {
    public:

        WindowResizeEvent();

        virtual ~WindowResizeEvent();


        virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

        void addCallback(WindowResizeCallback* cb){
            callbacks.push_back(cb);
        }

    private:
        std::vector<WindowResizeCallback*> callbacks;

    };

} /* namespace intercation */

#endif /* GUI_OSGVIZ_OSGVIZ_SRC_WINDOWS_EVENTHANDLERS_WINDOWRESIZEEVENT_H_ */
