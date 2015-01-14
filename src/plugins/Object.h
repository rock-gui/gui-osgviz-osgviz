/*
 * Object.h
 *
 *  Created on: 08.01.2015
 *      Author: planthaber
 */


#include <osg/Node>
#include <osg/PositionAttitudeTransform>

#ifndef SRC_PLUGINS_MODELVIEW_H_
#define SRC_PLUGINS_MODELVIEW_H_

namespace osgviz {

class Object: public osg::PositionAttitudeTransform{
public:
	Object();

	virtual ~Object();

	virtual void setObject(osg::ref_ptr<osg::Node> object);

    virtual void setRootNode(osg::Group* node);

    inline void setName(std::string name){
    	this->name = name;
    }

protected:
    friend class ModelViewFactory;



private:
    osg::ref_ptr<osg::Group> root;
    osg::ref_ptr<osg::Node> object;
    std::string name;

};

} /* namespace osgviz */

#endif /* SRC_PLUGINS_MODELVIEW_H_ */
