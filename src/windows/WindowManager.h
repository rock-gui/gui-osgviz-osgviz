/*
* WindowManager.h
*
*  Created on: 17.02.2015
*      Author: planthaber
*/

#ifndef OSGVIZ_OSGVIZ_SRC_WINDOWS_WINDOWMANAGER_H_
#define OSGVIZ_OSGVIZ_SRC_WINDOWS_WINDOWMANAGER_H_

#include <stdexcept>
#include <OpenThreads/Thread>

#include "config/WindowConfig.h"

#include "Window.h"

namespace osgviz {

    class WindowManager: public osg::Referenced {
    public:


        WindowManager();
        virtual ~WindowManager();

        unsigned int createWindow(WindowConfig& windowConfig, osg::ref_ptr<osg::Node> windowScene = NULL, osg::ref_ptr<osg::GraphicsContext> graphicsContext = NULL);

        unsigned int addWindow(osg::ref_ptr<Window> window);

        inline osg::ref_ptr<Window> getWindowByID(const unsigned int& id){
            if (id < windows.size()){
                return windows.at(id);
            }
            return NULL;
        }

        inline std::vector< osg::ref_ptr<Window> > getWindows() const{
            return windows;
        }

        void frame();

        bool done() const;

        /**
        * removed a window
        * @param id the id of the window to remove
        */
        void destroyWindow(unsigned int id);

        //osg::ref_ptr<osg::GraphicsContext::Traits> genetrateTraits(WindowConfig& windowConfig);


    private:
        OpenThreads::Mutex windowsMutex;
        std::vector< osg::ref_ptr<Window> > windows;


    };

} /* namespace osgviz */

#endif /* OSGVIZ_OSGVIZ_SRC_WINDOWS_WINDOWMANAGER_H_ */
