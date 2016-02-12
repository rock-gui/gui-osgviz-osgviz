/*
 * OsgVizVisualizerPlugin.h
 *
 *  Created on: 07.01.2015
 *      Author: planthaber
 */

#ifndef SRC_PLUGINS_OsgVizPlugin_H_
#define SRC_PLUGINS_OsgVizPlugin_H_

#include <lib_manager/LibManager.hpp>
#include <stdio.h>

#include "Object.h"


#define OSGVIZ_PLUGIN(NAME) \
	CREATE_LIB(NAME); \
	DESTROY_LIB(NAME);


namespace osgviz {

class OsgViz;

class OsgVizPlugin: public lib_manager::LibInterface  {
public:

	OsgVizPlugin(lib_manager::LibManager *theManager):LibInterface(theManager){};

	virtual ~OsgVizPlugin(){};

	/**
	 * Return a lib name used to reference the lib via the libmanager
	 */
	virtual const std::string getLibName() const = 0;

    virtual int getLibVersion() const = 0;

    /**
     * init is calles after loading the plugin using
     * osgviz::getPlugin
     */
    virtual void init(int argc,char** argv){};

    /**
     * in case the plugin want to start its own thread, start can be used
     * @warning: be sure to call parent->lockThread() before changing the scene graph
     */
    virtual void start(){};


protected:
    friend class OsgViz;
    inline void setRootNode(osg::Group* node){
        root = node;
    }

private:

	osg::ref_ptr<osg::Group> root;


};

} /* namespace osgviz */

#endif /* SRC_PLUGINS_VISUALIZER_H_ */
