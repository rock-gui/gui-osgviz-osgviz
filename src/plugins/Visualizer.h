/*
 * Visualizer.h
 *
 *  Created on: 07.01.2015
 *      Author: planthaber
 */

#ifndef SRC_PLUGINS_VISUALIZER_H_
#define SRC_PLUGINS_VISUALIZER_H_

#include <osg/Group>
#include <mars/lib_manager/LibManager.h>

namespace osgviz {

#define VISUALIZER_PLUGIN(NAME) \
	CREATE_LIB(NAME); \
	DESTROY_LIB(NAME);


class Visualizer: public mars::lib_manager::LibInterface  {
public:

	Visualizer(mars::lib_manager::LibManager *theManager):LibInterface(theManager){
		root = NULL;
		libmanager = theManager;
	};

	virtual ~Visualizer(){};

	/**
	 * Return a lib name used to reference the lib via the libmanager
	 */
	virtual const std::string getLibName() const = 0;

    virtual int getLibVersion() const = 0;

    inline osg::Group* getRootNode(){
    	return root;
    };

    inline mars::lib_manager::LibManager* getLibManager(){
    	return libmanager;
    }

protected:
    friend class OsgViz;

    inline void setRootNode(osg::Group* node){
      	root = node;
    }



private:

    osg::Group *root;
	mars::lib_manager::LibManager *libmanager;


};

} /* namespace osgviz */

#endif /* SRC_PLUGINS_VISUALIZER_H_ */
