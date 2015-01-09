/*
 * ModelView.h
 *
 *  Created on: 08.01.2015
 *      Author: planthaber
 */

#include "../OsgVizVisualizerPlugin.h"

#include <osg/Node>
#include <osg/PositionAttitudeTransform>

#ifndef SRC_PLUGINS_MODELVIEW_H_
#define SRC_PLUGINS_MODELVIEW_H_

namespace osgviz {

class ModelView{
public:
	ModelView();

	virtual ~ModelView();


	virtual void setModel(osg::ref_ptr<osg::Node> object);

	virtual void setPosition(osg::Vec3 pos);

	virtual void setAttitude(osg::Quat attitude);

protected:
    friend class ModelViewFactory;

    inline void setRootNode(osg::Group* node){
      	root = node;
    }

private:
    osg::ref_ptr<osg::Group> root;
    osg::ref_ptr<osg::Node> object;
    osg::ref_ptr<osg::PositionAttitudeTransform> patransform;

};


class ModelViewFactory : public OsgVizVisualizerPlugin {
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
	std::vector< ModelView* > instances;
};

} /* namespace osgviz */

#endif /* SRC_PLUGINS_MODELVIEW_H_ */
