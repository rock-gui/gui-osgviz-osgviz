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

#include "../interfaces/Clickable.h"

#include <stdio.h>

#ifndef SRC_PLUGINS_OBJECT_H_
#define SRC_PLUGINS_OBJECT_H_

namespace osgviz {

class Object: public osg::PositionAttitudeTransform, public Clickable{

public:
	Object();

	virtual ~Object();

	//virtual void setContent(osg::ref_ptr<osg::Node> object);

	virtual bool clicked(const int &buttonMask, const osg::Vec2d &cursor, const osg::Vec3d &world, const osg::Vec3d &local, osgviz::Clickable* object, WindowInterface* window = NULL);

	virtual bool dragged(const int &buttonMask, const osg::Vec2d &cursor, const osg::Vec3d &world, const osg::Vec3d &local, osgviz::Clickable* object, WindowInterface* window = NULL);

	virtual bool pointerEvent(int buttonMask, const osg::Vec3d &world, const osg::Vec3d &local){return false;}

	virtual bool keyEvent(int key, bool keyDown){return false;}

    //virtual void setRootNode(osg::Group* node);

	void addClickableCallback(Clickable * cb);


    inline void setName(std::string name){
    	this->name = name;
    }

    inline std::string getName(){
		return this->name;
	}

    /**
     * override osg::PositionAttitudeTransform addChild
     */
    virtual bool addChild(osg::Node *child){
    	return scaleTransform->addChild(child);
    }

    virtual bool getNumChildren() const{
    	return scaleTransform->getNumChildren();
    }

    Node* getChild(unsigned int i){
    	return scaleTransform->getChild(i);
    }

    const Node* getChild(unsigned int i) const{
    	return scaleTransform->getChild(i);
    }


	inline void setScale(const float &x, const float &y, const float &z){
		scaleTransform->setMatrix(osg::Matrix::scale(x, y, z));
	}

	inline osg::Vec3d getScale()const {
		return scaleTransform->getMatrix().getScale();
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

    inline void setOrientation(const double &angle, const osg::Vec3d &vec){
    	PositionAttitudeTransform::setAttitude( osg::Quat(angle, vec) );
    }

    inline void rotate(const double &angle, const osg::Vec3d &vec){
    	setAttitude( getAttitude() * osg::Quat(angle, vec) );
    }


    void switchCullMask();
    void xorCullMask(unsigned int mask);


    void displayName(float font_size = 0.1f);

protected:
    friend class ModelViewFactory;
    unsigned int cull_mask;
    bool visible;

    //osg::ref_ptr<osg::Group> root;
    //osg::ref_ptr<osg::Node> object;

    osg::ref_ptr<osg::MatrixTransform> scaleTransform;

private:

    osg::ref_ptr< osg::Geode > textgeode;
    osg::ref_ptr< osgText::Text > text;
    std::string name;

	std::vector< Clickable* > clickablecb;

};

} /* namespace osgviz */

#endif /* SRC_PLUGINS_MODELVIEW_H_ */
