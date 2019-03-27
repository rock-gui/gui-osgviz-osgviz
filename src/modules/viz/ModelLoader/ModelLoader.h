/*
* ModelLoader.h
*
*  Created on: 09.01.2015
*      Author: planthaber
*/

#ifndef GUI_OSGVIZ_SRC_PLUGINS_DATA_MODELLOADER_H_
#define GUI_OSGVIZ_SRC_PLUGINS_DATA_MODELLOADER_H_

#include "../../../Object.h"

namespace osgviz {

    class ModelLoader{
    public:
        ModelLoader(int argc = 0, char** argv = nullptr);
        virtual ~ModelLoader();

        virtual osg::ref_ptr<Object> loadModel(std::string path);


    private:

    };

} /* namespace osgviz */

#endif /* GUI_OSGVIZ_SRC_PLUGINS_DATA_MODELLOADER_H_ */
