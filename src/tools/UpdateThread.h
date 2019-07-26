/*
* UpdateThread.h
*
*  Created on: 09.07.2015
*      Author: planthaber
*/

#ifndef GUI_OSGVIZ_OSGVIZ_SRC_TOOLS_UPDATETHREAD_H_
#define GUI_OSGVIZ_OSGVIZ_SRC_TOOLS_UPDATETHREAD_H_

#include <OpenThreads/Thread>
#include "../interfaces/Updatable.h"


namespace osgviz {

    class UpdateThread : public OpenThreads::Thread{
    public:

        UpdateThread(Updatable* updatable, unsigned int intervalUsec);
        virtual ~UpdateThread();

        /**
        * Triggers update manually (thread save)
        */
        void trigger();

        int cancel();
        void lock();
        void unlock();
        int trylock();

    private:
        void run();


        bool running;
        unsigned int halfInterval;
        Updatable* updatable;
        OpenThreads::Mutex* mutex;


    };

} /* namespace osgviz */

#endif /* GUI_OSGVIZ_OSGVIZ_SRC_TOOLS_UPDATETHREAD_H_ */
