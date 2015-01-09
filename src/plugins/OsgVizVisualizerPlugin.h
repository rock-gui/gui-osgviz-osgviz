/*
 * OsgVizVisualizerPlugin.h
 *
 *  Created on: 07.01.2015
 *      Author: planthaber
 */

#ifndef SRC_PLUGINS_OsgVizVisualizerPlugin_H_
#define SRC_PLUGINS_OsgVizVisualizerPlugin_H_

#include "OsgVizPlugin.h"

#include <osg/Group>


namespace osgviz {


class OsgVizVisualizerPlugin: public OsgVizPlugin  {
public:

	OsgVizVisualizerPlugin(mars::lib_manager::LibManager *theManager):OsgVizPlugin(theManager){
		root = NULL;
	};

	virtual ~OsgVizVisualizerPlugin(){};

    inline osg::Group* getRootNode(){
    	return root;
    };


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
