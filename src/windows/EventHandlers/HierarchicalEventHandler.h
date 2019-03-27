/*
* HierarchicalEventHandler.h
*
*  Created on: 21.12.2015
*      Author: planthaber
*/

#ifndef GUI_OSGVIZ_OSGVIZ_SRC_WINDOWS_EVENTHANDLERS_HIERARCHICALEVENTHANDLER_H_
#define GUI_OSGVIZ_OSGVIZ_SRC_WINDOWS_EVENTHANDLERS_HIERARCHICALEVENTHANDLER_H_

#include <osgGA/GUIEventHandler>

namespace osgviz {

    class HierarchicalEventHandler : public osgGA::GUIEventHandler {
    public:
        HierarchicalEventHandler();
        virtual ~HierarchicalEventHandler();

        /**
        *
        * @param priority lower values are called after high values, it the value is taken, the handler is added below the current
        * @param handler
        * @return the actual precedence set (not equal precedence, if it was taken)
        */
        int addEventHandler(osg::ref_ptr<osgGA::GUIEventHandler> handler, int priority = 0);

        void removeEventHandler(osg::ref_ptr<osgGA::GUIEventHandler> handlerToRemove);

        virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);



    private:
        std::map<int, osg::ref_ptr<osgGA::GUIEventHandler> > handlers;


    };

} /* namespace osgviz */

#endif /* GUI_OSGVIZ_OSGVIZ_SRC_WINDOWS_EVENTHANDLERS_HIERARCHICALEVENTHANDLER_H_ */
