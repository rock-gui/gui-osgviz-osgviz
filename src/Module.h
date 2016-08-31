/*
 * OsgVizSingleton.h
 *
 *  Created on: 31.08.2016
 *      Author: Steffen Planthaber
 */

#ifndef OSGVIZMODULE_H_
#define OSGVIZMODULE_H_

#include <string>
#include <map>

#include "Object.h"

namespace osgviz{

class Module{

public:

	virtual ~Module(){};

    /**
     * init is called after loading the plugin using
     * osgviz::getPlugin
     */
    virtual void init(int argc,char** argv){};


protected:
    friend class OsgViz;
    Module(){};

};

}

#endif /* OSGVIZMODULE_H_ */
