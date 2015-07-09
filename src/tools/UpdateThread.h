/*
 * UpdateThread.h
 *
 *  Created on: 09.07.2015
 *      Author: planthaber
 */

#ifndef GUI_OSGVIZ_OSGVIZ_SRC_TOOLS_UPDATETHREAD_H_
#define GUI_OSGVIZ_OSGVIZ_SRC_TOOLS_UPDATETHREAD_H_

#include <OpenThreads/Thread>

namespace osgviz {


class Updatable{
public:
	Updatable(){};
	~Updatable(){};
	virtual void update() = 0;

};


class UpdateThread : public OpenThreads::Thread{
public:

	UpdateThread(Updatable* updatable, unsigned int intervalUsec);
	virtual ~UpdateThread();

		int cancel();
		void lock();
		void unlock();

	private:
		void run();

		bool running;
		unsigned int halfInterval;
		Updatable* updatable;
		OpenThreads::Mutex mutex;


};

} /* namespace osgviz */

#endif /* GUI_OSGVIZ_OSGVIZ_SRC_TOOLS_UPDATETHREAD_H_ */
