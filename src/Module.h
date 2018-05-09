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

struct ModuleBase{
    ModuleBase(){};
    virtual ~ModuleBase(){};
};

template <class T> class Module: public ModuleBase{

public:

    Module(const std::shared_ptr<T>& module):module(module){};
    virtual ~Module(){};

    /**
     * init is called after loading the plugin using
     * osgviz::getPlugin
     */
    //virtual void init(int argc,char** argv){};


protected:
    friend class OsgViz;
    std::shared_ptr<T> module;

private:
    //Module(int argc,char** argv){};
    Module(){};
    

};

}

#endif /* OSGVIZMODULE_H_ */
