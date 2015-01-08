/*
 * ModelView.h
 *
 *  Created on: 08.01.2015
 *      Author: planthaber
 */

#include "Visualizer.h"

#include <osg/Node>
#include <osg/PositionAttitudeTransform>

#ifndef SRC_PLUGINS_MODELVIEW_H_
#define SRC_PLUGINS_MODELVIEW_H_

namespace osgviz {

class ModelView{
public:
	ModelView();

	virtual ~ModelView();


	virtual void loadModel(std::string path);

	virtual void setPosition(osg::Vec3 pos);

	virtual void setAttitude(osg::Quat attitude);

protected:
    friend class ModelViewFactory;

    inline void setRootNode(osg::Group* node){
      	root = node;
    }

private:
    osg::Group *root;
    osg::Node *object;
    osg::PositionAttitudeTransform *patransform;

};


class ModelViewFactory : public Visualizer {
public:
	ModelViewFactory(mars::lib_manager::LibManager *theManager);
	~ModelViewFactory();

	virtual ModelView* createInstance(){
		ModelView *instance = new ModelView();
		instance->setRootNode(getRootNode());
		instances.push_back(instance);
		return instance;
	}

	virtual int getLibVersion() const {return 0;};

	const std::string getLibName() const { return "ModelView"; };

private:
	std::vector<ModelView*> instances;
};

} /* namespace osgviz */

#endif /* SRC_PLUGINS_MODELVIEW_H_ */
