/*
 * Object.h
 *
 *  Created on: 08.01.2015
 *      Author: planthaber
 */


#include <osg/Node>
#include <osgText/Font>
#include <osgText/Text>
#include <osg/MatrixTransform>
#include <osg/PositionAttitudeTransform>


#ifndef SRC_PLUGINS_MODELVIEW_H_
#define SRC_PLUGINS_MODELVIEW_H_

namespace osgviz {

class Object: public osg::PositionAttitudeTransform{

protected:
	friend class OsgVizVisualizerPlugin;
	Object();

public:




	virtual ~Object();

	virtual void setContent(osg::ref_ptr<osg::Node> object);

    //virtual void setRootNode(osg::Group* node);




    inline void setName(std::string name){
    	this->name = name;
    }

    inline std::string getName(){
		return this->name;
	}


	inline void setScale(const float &x, const float &y, const float &z){
		scaleTransform->setMatrix(osg::Matrix::scale(x, y, z));
	}

    inline void setPosition(const double &x, const double &y, const double &z){
    	PositionAttitudeTransform::setPosition(osg::Vec3d(x,y,z));
    }

    inline void setPosition(const osg::Vec3d& vec){
    	PositionAttitudeTransform::setPosition(vec);
    }

    inline void setOrientation(const double &x,const double &y,const double &z,const double &w){
    	setAttitude( osg::Quat (x,y,z,w));
    }

    inline void setOrientation(const osg::Quat &quat){
    	PositionAttitudeTransform::setAttitude( quat );
    }

    void switchCullMask();
    void xorCullMask(unsigned int mask);


    void displayName(float font_size = 0.1f);

protected:
    friend class ModelViewFactory;
    unsigned int cull_mask;
    bool visible;

    //osg::ref_ptr<osg::Group> root;
    osg::ref_ptr<osg::Node> object;

    osg::ref_ptr<osg::MatrixTransform> scaleTransform;

private:

    osg::ref_ptr< osg::Geode > textgeode;
    osg::ref_ptr< osgText::Text > text;
    std::string name;

};

} /* namespace osgviz */

#endif /* SRC_PLUGINS_MODELVIEW_H_ */
