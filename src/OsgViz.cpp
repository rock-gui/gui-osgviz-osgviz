#include "OsgViz.hpp"

//#include "graphics/GraphicsManager.h"

#include <stdio.h>
#include <osgGA/TerrainManipulator>
#ifndef WIN32
	#include <X11/Xlib.h>
#endif
#include <osgDB/WriteFile>
#include <osgDB/Registry>

#include "windows/WindowManager.h"
#include "tools/TypeNameDemangling.h"

namespace osgviz
{

osg::ref_ptr<OsgViz> instance = NULL;
std::map<std::string, Module*> OsgViz::modules;

osg::ref_ptr<OsgViz> OsgViz::getInstance(int argc,char** argv){
	if (!instance.valid()){
		instance = new OsgViz(argc,argv);
	}
	return instance;
}


osg::ref_ptr<OsgViz> OsgViz::getExistingInstance(){
	return instance;
}

OsgViz::OsgViz(int argc, char** argv){
	init(argc,argv);
}


void OsgViz::init(int argc,char** argv){
	//graphicsManager = new graphics::GraphicsManager(libmanager);

	mutex = new OpenThreads::Mutex();

	thread = NULL;
	m_argc = argc;
	m_argv = argv;
	root = new osg::Group();
	root->setName("OsgViz root");
	instance = this;

	windowManager = new WindowManager();

}

OsgViz::~OsgViz(){

	for (std::map<std::string, Module*>::iterator it = modules.begin();it!=modules.end();it++){
		delete it->second;
	}

	delete mutex;

	//if (graphicsManager){
	//	delete graphicsManager;
	//}

}

unsigned int OsgViz::createWindow(WindowConfig windowConfig, osg::ref_ptr<osg::GraphicsContext> graphicsContext) {
	//int id = graphicsManager->new3DWindow();
	//mars::interfaces::GraphicsWindowInterface* window = this->get3DWindow(1);
	unsigned int winID = windowManager->createWindow(windowConfig,NULL,graphicsContext);

	// all created windows will share the same osgviz scene
	windowManager->getWindowByID(winID)->addChild(root);

	return winID;

}

void OsgViz::destroyWindow(unsigned int id){
    windowManager->destroyWindow(id);
}

void OsgViz::update(){


    for (std::map<int, Updatable*>::reverse_iterator callback = updateCallbacks.rbegin(); callback != updateCallbacks.rend();++callback){
        callback->second->update();
    }

    mutex->lock();
    windowManager->frame();
    mutex->unlock();


}

int OsgViz::addUpdateCallback(Updatable* callback, int priority) {
    Updatable* existing = updateCallbacks[priority];
    while (existing){
        --priority;
        existing = updateCallbacks[priority];
    }
    updateCallbacks[priority] = callback;
    return priority;
}


void OsgViz::startThread(int microseconds){
	if (!thread){
		#ifndef WIN32
			XInitThreads();
		#endif
		thread = new UpdateThread(this, microseconds);
		thread->startThread();
	}else{
		fprintf(stderr,"thread already running\n");
	}
}

void OsgViz::stopThread(){
	if (thread){
		thread->cancel();
		delete thread;
	}
}


void OsgViz::lockThread(){
	if (thread){
		thread->lock();
	}else{
		mutex->lock();
	}
}

void OsgViz::unlockThread(){
	if (thread){
		thread->unlock();
	}else{
		mutex->unlock();
	}
}

int OsgViz::tryLockThread(){
	if (thread){
		return thread->trylock();
	}else{
		return mutex->trylock();
	}
	return -1;
}

void OsgViz::printModules(){
	for (std::map<std::string, Module*>::iterator it = modules.begin();it!=modules.end();it++){
		printf("%s : %s\n",it->first.c_str(),demangledTypeName(*(it->second)).c_str());
	}
}

}


