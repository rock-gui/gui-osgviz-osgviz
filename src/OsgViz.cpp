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

osg::ref_ptr<OsgViz> OsgViz::getInstance(lib_manager::LibManager * manager){
	if (!instance.valid()){
		instance = new OsgViz(manager);
	}
	return instance;
}

osg::ref_ptr<OsgViz> OsgViz::getExistingInstance(){
	return instance;
}



OsgViz::OsgViz(lib_manager::LibManager * manager)
{
    libManager = manager;
	createdOwnManager = false;
	instance = this;
	init(0,NULL);

}

OsgViz::OsgViz(int argc, char** argv){
	createdOwnManager = true;
	libManager = new lib_manager::LibManager();
	//not loaded by libmanager so we add ourselves
	//libManager->addLibrary(this);
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

	for (std::vector< OsgVizPlugin* >::iterator it = loadedPlugins.begin();it!=loadedPlugins.end();it++){
		libManager->releaseLibrary((*it)->getLibName());
	}

	for (std::map<std::string, Module*>::iterator it = modules.begin();it!=modules.end();it++){
		delete it->second;
	}

	if (createdOwnManager){
		delete libManager;
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


OsgVizPlugin* OsgViz::getVizPlugin(std::string path, std::string name) {
	OsgVizPlugin* viz = NULL;
	viz = dynamic_cast<OsgVizPlugin*>(libManager->getLibrary(name));
	if (viz){
		return viz;
	}else{
		lib_manager::LibManager::ErrorNumber result = libManager->loadLibrary(path);
		//if (result == lib_manager::LibManager::LIBMGR_NO_ERROR){
			OsgVizPlugin* viz = dynamic_cast<OsgVizPlugin*>(libManager->acquireLibrary(name));
			//fprintf(stderr,"trying to load 3%s\n",name.c_str());	fflush(stdout);
			if (!viz){
				fprintf(stderr,"unable to load lib %s\n",name.c_str());	fflush(stdout);
				return NULL;
			}
			// init plugin data
			//viz->setParent(this);
            viz->setRootNode(root);
            viz->init(m_argc,m_argv);

			loadedPlugins.push_back(viz);
			return viz;
		//}else{
		//	fprintf(stderr,"load failed %s\n",name.c_str());	fflush(stdout);
		//}
	}
	return NULL;
}

OsgVizPlugin* OsgViz::loadPlugin(std::string classname){
	OsgVizPlugin* data = getVizPlugin(classname,classname);
	if (data){
		data->init(m_argc,m_argv);
	}
	return data;
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


