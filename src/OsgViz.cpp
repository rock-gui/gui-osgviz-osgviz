#include "OsgViz.hpp"

#include "graphics/GraphicsManager.h"

#include <stdio.h>
#include <osgGA/TerrainManipulator>
#include <X11/Xlib.h>

#include "windows/WindowManager.h"


CREATE_LIB(osgviz::OsgViz);
DESTROY_LIB(osgviz::OsgViz);

namespace osgviz
{

OsgViz* instance = NULL;

OsgViz* OsgViz::getInstance(int argc,char** argv){
	if (!instance){
		instance = new OsgViz(argc,argv);
	}
	return instance;
}




void FrameUpdateThread::run()
{
	mutex.lock();
	running = true;
	mutex.unlock();

	while (running){
		mutex.unlock();
		usleep(10000);
		mutex.lock();
		//int result = _viewerBase->run();
		osgviz->updateContent();
		mutex.unlock();
		//give others a chance to lock
		usleep(10000);
		mutex.lock();
	}
}





OsgViz::OsgViz(lib_manager::LibManager * manager): lib_manager::LibInterface(manager)
{
	createdOwnManager = false;
	libmanager = manager;
	init(0,NULL);

}

OsgViz::OsgViz(int argc, char** argv): lib_manager::LibInterface(NULL){
	createdOwnManager = true;
	libmanager = new lib_manager::LibManager();
	init(argc,argv);
}


void OsgViz::init(int argc,char** argv){
	graphicsManager = new graphics::GraphicsManager(libmanager);

	thread = NULL;
	m_argc = argc;
	m_argv = argv;
	root = new osg::Group();
	XInitThreads();
	instance = this;

	Window* wnd = windows.createWindow(0,0,640,480,root);
	wnd->showRain();

//	viewer.setUpViewInWindow(0,0,640,480);
//	viewer.setSceneData(root);
//	viewer.setCameraManipulator( new osgGA::TerrainManipulator() );
//	viewer.realize();

//	graphicsManager->initializeOSG(NULL,true);
//	graphicsManager->addOSGNode(root);

}

OsgViz::~OsgViz(){

	for (std::vector< OsgVizPlugin* >::iterator it = loadedPlugins.begin();it!=loadedPlugins.end();it++){
		libmanager->releaseLibrary((*it)->getLibName());
	}

	if (createdOwnManager){
		delete libmanager;
	}

	if (graphicsManager){
		delete graphicsManager;
	}

}

int OsgViz::createWindow(bool threaded) {

	int id = graphicsManager->new3DWindow();
	//mars::interfaces::GraphicsWindowInterface* window = this->get3DWindow(1);

	return id;
}

void OsgViz::destroyWindow(int id){
	graphicsManager->remove3DWindow(id);
}


OsgVizPlugin* OsgViz::getVizPlugin(std::string path, std::string name) {
	OsgVizPlugin* viz = NULL;
	viz = (OsgVizPlugin*)libmanager->getLibrary(name);
	if (viz){
		return viz;
	}else if (libmanager->loadLibrary(path) == lib_manager::LibManager::LIBMGR_NO_ERROR){
		OsgVizPlugin* viz = (OsgVizPlugin*)libmanager->acquireLibrary(name);
		if (!viz){
			fprintf(stderr,"unable to load lib %s\n",name.c_str());
			return NULL;
		}
		viz->setParent(this);
		loadedPlugins.push_back(viz);
		return viz;

	}
	return NULL;
}



void OsgViz::updateContent(){
	graphicsManager->draw();
//	viewer.frame();

	windows.frame();
	//graphicsManager->get3DWindow();

//	osgViewer::ViewerBase::Views views;
//	viewer.getViews(views);
//	int num = views[0]->getEventHandlers().size();
//
//	printf("event handlers %i\n ",num);


}

void OsgViz::startThread(){
	if (!thread){
		thread = new FrameUpdateThread(this);
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
	}
}

void OsgViz::unlockThread(){
	if (thread){
		thread->unlock();
	}
}

const std::string OsgViz::getLibName() const {
	return "OsgViz";
}

int OsgViz::getLibVersion() const{
	return 1;
}

}
