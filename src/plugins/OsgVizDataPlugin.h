/*
 * OsgVizDataPlugin.h.h
 *
 *  Created on: 07.01.2015
 *      Author: planthaber
 */

#ifndef SRC_PLUGINS_OsgVizDataPlugin_H_
#define SRC_PLUGINS_OsgVizDataPlugin_H_

#include "OsgVizPlugin.h"

namespace osgviz {


class OsgVizDataPlugin: public OsgVizPlugin  {
public:

	OsgVizDataPlugin(lib_manager::LibManager *theManager):OsgVizPlugin(theManager){};

	virtual ~OsgVizDataPlugin(){};



	/**
	 * Return a lib name used to reference the lib via the libmanager
	 */
	virtual const std::string getLibName() const = 0;

    virtual int getLibVersion() const = 0;


protected:
    friend class OsgViz;

	virtual void init(int argc,char** argv) = 0;


private:



};

} /* namespace osgviz */

#endif /* SRC_PLUGINS_VISUALIZER_H_ */
