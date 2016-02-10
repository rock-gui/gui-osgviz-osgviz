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


#define OSGVIZ_PLUGIN(NAME) \
	CREATE_LIB(NAME); \
	DESTROY_LIB(NAME);


namespace osgviz {

class OsgViz;

class OsgVizPlugin: public lib_manager::LibInterface  {
public:

	OsgVizPlugin(lib_manager::LibManager *theManager):LibInterface(theManager){
		libmanager = theManager;
		this->parent=NULL;
		osgVizFuncPtr = &OsgVizPlugin::osgVizPtrError;
	};

	virtual ~OsgVizPlugin(){};

	/**
	 * Return a lib name used to reference the lib via the libmanager
	 */
	virtual const std::string getLibName() const = 0;

    virtual int getLibVersion() const = 0;

    /**
     * init is calles after loading the plugin using
     * osgviz::getVisualizerPlugin
     */
    virtual void init(){};

    /**
     * in case the plugin want to start its own thread, start can be used
     * @warning: be sure to call parent->lockThread() before changing the scene graph
     */
    virtual void start(){};

    inline lib_manager::LibManager* getLibManager(){
    	return libmanager;
    }

    inline OsgViz* osgViz(){
    	return (this->*osgVizFuncPtr)();
    }


protected:
    friend class OsgViz;
    inline void setParent(OsgViz* par){
    	parent = par;
    	osgVizFuncPtr = &OsgVizPlugin::osgVizPtr;
    }



private:
    OsgViz* osgVizPtr(){
    	return parent;
    }

    OsgViz* osgVizPtrError(){
    	fprintf(stderr,"Unable to use OsgVizPlugin::osgViz() in constructor, parent pointer is still unset\n");
    	fprintf(stderr,"You can use the virtual void init() function to initialize using osgViz()\n");
    	fflush(stderr);
    	return NULL;
    }

private:

    OsgViz* parent;
	lib_manager::LibManager *libmanager;

	//member pointer to osgViz getter
	OsgViz* (OsgVizPlugin::*osgVizFuncPtr)();




};

} /* namespace osgviz */

#endif /* SRC_PLUGINS_VISUALIZER_H_ */
