/*
 * ModelLoader.h
 *
 *  Created on: 09.01.2015
 *      Author: planthaber
 */

#ifndef GUI_OSGVIZ_SRC_PLUGINS_DATA_MODELLOADER_H_
#define GUI_OSGVIZ_SRC_PLUGINS_DATA_MODELLOADER_H_

#include "../OsgVizDataPlugin.h"
#include "../viz/ModelView.h"

namespace osgviz {

class ModelLoader : public OsgVizDataPlugin{
public:
	ModelLoader(mars::lib_manager::LibManager *theManager);
	virtual ~ModelLoader();

	virtual int getLibVersion() const {return 1;};

	virtual const std::string getLibName() const { return "ModelLoader"; };

	virtual void init(int argc, char** argv);

	virtual void loadModel(std::string path);


private:
	ModelViewFactory *modelfactory;
};

} /* namespace osgviz */

#endif /* GUI_OSGVIZ_SRC_PLUGINS_DATA_MODELLOADER_H_ */
