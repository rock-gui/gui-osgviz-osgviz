#include "OsgViz.hpp"


#include <stdio.h>
#include <osgGA/TerrainManipulator>


CREATE_LIB(osgviz::OsgViz);
DESTROY_LIB(osgviz::OsgViz);

namespace osgviz
{


OsgViz::OsgViz(mars::lib_manager::LibManager * manager):LibInterface(manager)
{
	createdOwnManager = false;
	init(0,NULL);
}

OsgViz::OsgViz(int argc, char** argv):LibInterface(NULL){
	createdOwnManager = true;
	libmanager = new mars::lib_manager::LibManager();
	init(argc,argv);
}


void OsgViz::init(int argc,char** argv){
	m_argc = argc;
	m_argv = argv;
	root = new osg::Group();
	cameraManipulator = new osgGA::TerrainManipulator;
}

OsgViz::~OsgViz(){

	for (std::vector< OsgVizPlugin* >::iterator it = loadedPlugins.begin();it!=loadedPlugins.end();it++){
		libmanager->releaseLibrary((*it)->getLibName());
	}

	if (createdOwnManager){
		delete libmanager;
	}

}

void OsgViz::createWindow() {
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

	viewer.run();



}

OsgVizPlugin* OsgViz::getVizPlugin(std::string path, std::string name) {
	OsgVizPlugin* viz = NULL;
	viz = (OsgVizPlugin*)libmanager->getLibrary(name);
	if (viz){
		return viz;
	}else if (libmanager->loadLibrary(path) == mars::lib_manager::LibManager::LIBMGR_NO_ERROR){
		OsgVizPlugin* viz = (OsgVizPlugin*)libmanager->acquireLibrary(name);
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
