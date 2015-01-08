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


class ModelView : public Visualizer {
public:
	ModelView(mars::lib_manager::LibManager *theManager);

	virtual ~ModelView();


	void loadModel(std::string path);

	void setPosition(osg::Vec3 pos);

	void setAttitude(osg::Quat attitude);


    virtual int getLibVersion() const {return 0;};

    const std::string getLibName() const { return "ModelView"; };

private:
    osg::Node *object;
    osg::PositionAttitudeTransform *patransform;

};



} /* namespace osgviz */

#endif /* SRC_PLUGINS_MODELVIEW_H_ */
