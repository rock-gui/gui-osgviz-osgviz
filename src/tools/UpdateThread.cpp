/*
 * UpdateThread.cpp
 *
 *  Created on: 09.07.2015
 *      Author: planthaber
 */


#include "UpdateThread.h"

#include <unistd.h>
#include <stdio.h>

#ifdef WIN32
	#include <windows.h>
	#define usleep(X) Sleep(X/1000.0)
#endif

namespace osgviz {

	UpdateThread::UpdateThread(Updatable* updatable, unsigned int intervalUsec):
		halfInterval(intervalUsec/2),
		updatable(updatable)
	{
		mutex = new OpenThreads::Mutex();
			running = false;
	}

	UpdateThread::~UpdateThread()
	{
		if (isRunning())
		{
			cancel();
			join();
		}
		delete mutex;
	}

	int UpdateThread::cancel()
	{
		mutex->lock();
		running = false;
		mutex->unlock();
		return 0;
	}

	void UpdateThread::run(){
		mutex->lock();

		//first initial run
		updatable->update();
		mutex->unlock();
		usleep(halfInterval);

		running = true;
		mutex->lock();
		while (running){
			mutex->unlock();
			
			usleep(halfInterval);
			//printf("lock\n");fflush(stdout);
			mutex->lock();
			//int result = _viewerBase->run();
			//printf("update\n");fflush(stdout);
			updatable->update();
			//printf("updateend\n");fflush(stdout);
			mutex->unlock();
			//give others a chance to lock
			usleep(halfInterval);
			//printf("lock2\n");fflush(stdout);
			mutex->lock();
		}
	}

	void UpdateThread::trigger(){
		mutex->lock();
		updatable->update();
		mutex->unlock();
	}

	void UpdateThread::lock(){
		//printf("lock\n");fflush(stdout);
		mutex->lock();
	}
	void UpdateThread::unlock(){
		mutex->unlock();
		//printf("unlock\n");fflush(stdout);
	}
	int UpdateThread::trylock(){
		mutex->trylock();
		//printf("unlock\n");fflush(stdout);
	}


} /* namespace osgviz */
