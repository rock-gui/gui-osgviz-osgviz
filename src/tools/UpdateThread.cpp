/*
 * UpdateThread.cpp
 *
 *  Created on: 09.07.2015
 *      Author: planthaber
 */


#include "UpdateThread.h"

#include <unistd.h>

namespace osgviz {

	UpdateThread::UpdateThread(Updatable* updatable, unsigned int intervalUsec):
		halfInterval(intervalUsec/2),
		updatable(updatable)
	{
			running = false;
	}

	UpdateThread::~UpdateThread()
	{
		if (isRunning())
		{
			cancel();
			join();
		}
	}

	int UpdateThread::cancel()
	{
		mutex.lock();
		running = false;
		mutex.unlock();
		return 0;
	}

	void UpdateThread::run(){
		mutex.lock();
		running = true;

		while (running){
			mutex.unlock();
			usleep(halfInterval);
			mutex.lock();
			//int result = _viewerBase->run();
			updatable->update();
			mutex.unlock();
			//give others a chance to lock
			usleep(halfInterval);
			mutex.lock();
		}
	}

	void UpdateThread::lock(){
		mutex.lock();
	}
	void UpdateThread::unlock(){
		mutex.unlock();
	}


} /* namespace osgviz */
