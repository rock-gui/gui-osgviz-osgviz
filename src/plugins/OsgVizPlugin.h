/*
 * OsgVizVisualizerPlugin.h
 *
 *  Created on: 07.01.2015
 *      Author: planthaber
 */

#ifndef SRC_PLUGINS_OsgVizPlugin_H_
#define SRC_PLUGINS_OsgVizPlugin_H_

#include <mars/lib_manager/LibManager.h>

#define OSGVIZ_PLUGIN(NAME) \
	CREATE_LIB(NAME); \
	DESTROY_LIB(NAME);


namespace osgviz {

class OsgViz;

class OsgVizPlugin: public mars::lib_manager::LibInterface  {
public:

	OsgVizPlugin(mars::lib_manager::LibManager *theManager):LibInterface(theManager){
		libmanager = theManager;
		parent=NULL;
	};

	virtual ~OsgVizPlugin(){};

	/**
	 * Return a lib name used to reference the lib via the libmanager
	 */
	virtual const std::string getLibName() const = 0;

    virtual int getLibVersion() const = 0;

    inline mars::lib_manager::LibManager* getLibManager(){
    	return libmanager;
    }

    inline OsgViz* getParent(){
    	return parent;
    }

protected:
    friend class OsgViz;
    inline void setParent(OsgViz* par){
    	parent = par;
    }



private:

    OsgViz* parent;
	mars::lib_manager::LibManager *libmanager;


};

} /* namespace osgviz */

#endif /* SRC_PLUGINS_VISUALIZER_H_ */
