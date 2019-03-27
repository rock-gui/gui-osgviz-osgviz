/*
* ArrowNode.h
*
*  Created on: 27.03.2015
*      Author: planthaber
*/

#ifndef GUI_OSGVIZ_OSGVIZ_SRC_MODULES_VIZ_PRIMITIVES_PRIMITIVES_ARROWNODE_H_
#define GUI_OSGVIZ_OSGVIZ_SRC_MODULES_VIZ_PRIMITIVES_PRIMITIVES_ARROWNODE_H_

#include <osg/Shape>
#include <osg/ShapeDrawable>

#include "../../../../Object.h"
//#include <osg/Cylinder>

namespace osgviz {

    class ArrowNode : public osgviz::Object{
    public:
        ArrowNode();
        ArrowNode(bool invert);
        virtual ~ArrowNode();


        osg::ref_ptr<osg::Cone> Cone(){
            return cone;
        }

        osg::ref_ptr<osg::Cylinder> Cylinder(){
            return cylinder;
        }

        virtual void setColor(const float &r,const float &g,const float &b,const float &a = 1){
            coneDrawable->setColor(osg::Vec4(r,g,b,a));
            cylinderDrawable->setColor(osg::Vec4(r,g,b,a));

            if (a<1){
                this->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN |
                    osg::StateAttribute::OVERRIDE |
                    osg::StateAttribute::PROTECTED);
                this->getOrCreateStateSet()->setMode( GL_BLEND, osg::StateAttribute::ON );
            }
        }

    private:
        osg::ref_ptr<osg::Geode> geode;

        osg::ref_ptr<osg::Cone> cone;
        osg::ref_ptr<osg::ShapeDrawable> coneDrawable;

        osg::ref_ptr<osg::Cylinder> cylinder;
        osg::ref_ptr<osg::ShapeDrawable> cylinderDrawable;

    };

} /* namespace robot_manager */

#endif /* GUI_OSGVIZ_OSGVIZ_SRC_MODULES_VIZ_PRIMITIVES_PRIMITIVES_ARROWNODE_H_ */
