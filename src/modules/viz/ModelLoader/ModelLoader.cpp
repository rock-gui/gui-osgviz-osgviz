/*
* ModelLoader.cpp
*
*  Created on: 09.01.2015
*      Author: planthaber
*/

#include "ModelLoader.h"
#include <osgDB/ReadFile>
#include <osg/Node>




namespace osgviz {


    ModelLoader::ModelLoader(int argc, char** argv) {



    }

    ModelLoader::~ModelLoader() {
        // TODO Auto-generated destructor stub
    }

    osg::ref_ptr<Object> ModelLoader::loadModel(std::string path){
        printf("load %s\n",path.c_str());
        osg::ref_ptr<osg::Node> object = osgDB::readNodeFile(path);
        osg::ref_ptr<Object> model = new Object();
        model->setName(path);
        model->addChild(object);
        return model;
    }


} /* namespace osgviz */
