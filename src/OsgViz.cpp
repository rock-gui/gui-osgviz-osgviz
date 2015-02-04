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

OsgViz::OsgViz(lib_manager::LibManager * manager): mars::graphics::GraphicsManager(manager)
{
	createdOwnManager = false;
	init(0,NULL);
}

OsgViz::OsgViz(int argc, char** argv): mars::graphics::GraphicsManager(NULL){
	createdOwnManager = true;
	libmanager = new lib_manager::LibManager();
	init(argc,argv);
}


void OsgViz::init(int argc,char** argv){
	m_argc = argc;
	m_argv = argv;
	root = new osg::Group();
	XInitThreads();
	instance = this;
	this->initializeOSG(NULL,true);
	this->addOSGNode(root);
}

OsgViz::~OsgViz(){

	for (std::vector< OsgVizPlugin* >::iterator it = loadedPlugins.begin();it!=loadedPlugins.end();it++){
		libmanager->releaseLibrary((*it)->getLibName());
	}

	if (createdOwnManager){
		delete libmanager;
	}

}

int OsgViz::createWindow(bool threaded) {

	int id = this->new3DWindow();
	//mars::interfaces::GraphicsWindowInterface* window = this->get3DWindow(1);

	return id;
}

void OsgViz::destroyWindow(int id){
		this->destroyWindow(id);
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
	this->draw();
}


const std::string OsgViz::getLibName() const {
	return "OsgViz";
}

int OsgViz::getLibVersion() const{
	return 1;
}

}
