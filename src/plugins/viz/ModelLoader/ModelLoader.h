/*
 * ModelLoader.h
 *
 *  Created on: 09.01.2015
 *      Author: planthaber
 */

#ifndef GUI_OSGVIZ_SRC_PLUGINS_DATA_MODELLOADER_H_
#define GUI_OSGVIZ_SRC_PLUGINS_DATA_MODELLOADER_H_

#include "../../OsgVizPlugin.h"

namespace osgviz {

class ModelLoader : public OsgVizPlugin{
public:
	ModelLoader(lib_manager::LibManager *theManager);
	virtual ~ModelLoader();

	virtual int getLibVersion() const {return 1;};

	virtual const std::string getLibName() const { return "ModelLoader"; };

	virtual void init(int argc, char** argv);

	virtual osg::ref_ptr<Object> loadModel(std::string path);


private:

};

} /* namespace osgviz */

#endif /* GUI_OSGVIZ_SRC_PLUGINS_DATA_MODELLOADER_H_ */
