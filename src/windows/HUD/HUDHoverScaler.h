/*
* HUDHoverScaler.h
*
*  Created on: 02.06.2016
*      Author: planthaber
*/

#ifndef GUI_OSGVIZ_OSGVIZ_SRC_WINDOWS_HUD_HUDHOVERSCALER_H_
#define GUI_OSGVIZ_OSGVIZ_SRC_WINDOWS_HUD_HUDHOVERSCALER_H_

#include "../../interfaces/MouseMoveCallback.h"
#include "../../Object.h"

namespace osgviz {

    class HUD;

    class HUDHoverScaler: public osgviz::MouseMoveCallback, public osg::Referenced{
    public:

        enum Type{ZOOM,NE,SE,SW,NW};

        HUDHoverScaler(osg::ref_ptr<osgviz::Object> obj, const osg::Vec3d& size, const osg::Vec3d &scale, Type type, osg::Vec3d anchor_offset, HUD* hud);
        virtual ~HUDHoverScaler(){};

        virtual bool mouseMoved(const int& x, const int& y, const float& xNorm, const float& yNorm, const int& modifierMask);

    private:
        osg::ref_ptr<osgviz::Object> obj;
        osg::Vec3d initial_scale,scale,size, totalscale;
        osg::Vec3d position_unscaled;
        osg::Vec3d anchor_offset;//offset to move anchor to center of HUD element
        bool scaled;
        Type type;
        HUD* hud;
    };

} /* namespace intercation */

#endif /* GUI_OSGVIZ_OSGVIZ_SRC_WINDOWS_HUD_HUDHOVERSCALER_H_ */
