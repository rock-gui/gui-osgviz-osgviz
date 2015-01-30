#include "OsgViz.hpp"


#include <stdio.h>
#include <osgGA/TerrainManipulator>
#include <X11/Xlib.h>

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

OsgViz::OsgViz(lib_manager::LibManager * manager):LibInterface(manager)
{
	createdOwnManager = false;
	init(0,NULL);
	viewerThread = NULL;
}

OsgViz::OsgViz(int argc, char** argv):LibInterface(NULL){
	createdOwnManager = true;
	libmanager = new lib_manager::LibManager();
	init(argc,argv);
}


void OsgViz::init(int argc,char** argv){
	m_argc = argc;
	m_argv = argv;
	numberOfWindows = 0;
	root = new osg::Group();
	cameraManipulator = new osgGA::TerrainManipulator;
	XInitThreads();
	instance = this;
}

OsgViz::~OsgViz(){

	for (std::vector< OsgVizPlugin* >::iterator it = loadedPlugins.begin();it!=loadedPlugins.end();it++){
		libmanager->releaseLibrary((*it)->getLibName());
	}

	if (createdOwnManager){
		delete libmanager;
	}

	if (viewerThread){
		delete viewerThread;
	}

}

void OsgViz::createWindow(bool threaded) {

	numberOfWindows++;

	// For now, we can initialize with 'standard settings'
	// Standard settings include a standard keyboard mouse
	// interface as well as default drive, fly and trackball
	// motion models for updating the scene.

	viewer.setUpViewInWindow(0,0,640,480);


	//viewer.setUpViewer(osgViewer::Viewer::STANDARD_SETTINGS);

	// Next we will need to assign the scene graph we created
	// above to this viewer:

	viewer.setSceneData( root );



	viewer.setCameraManipulator(cameraManipulator);


	// create the windows and start the required threads.

	if (threaded){
		viewerThread = new ViewerFrameThread (&viewer);
		viewerThread->startThread();
	}else{
		viewer.run();
	}



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

const std::string OsgViz::getLibName() const {
	return "OsgViz";
}

int OsgViz::getLibVersion() const{
	return 1;
}

}
