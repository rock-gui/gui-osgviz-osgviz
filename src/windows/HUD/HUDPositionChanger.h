/*
* HUDPositionChanger.h
*
*  Created on: 08.09.2017
*      Author: Anna Born
*/

#ifndef GUI_OSGVIZ_OSGVIZ_SRC_WINDOWS_HUD_HUDPOSITIONCHANGER_H_
#define GUI_OSGVIZ_OSGVIZ_SRC_WINDOWS_HUD_HUDPOSITIONCHANGER_H_

#include "../../interfaces/WindowResizeCallback.h"
#include "../../Object.h"

namespace osgviz {

    class HUD;

    class HUDPositionChanger: public osgviz::WindowResizeCallback, public osg::Referenced{
    public:

        HUDPositionChanger(osg::ref_ptr<osgviz::Object> obj, const osg::Vec3d& init_pos, const osg::Vec2d init_size, HUD *hud);
        virtual ~HUDPositionChanger(){};

        virtual bool windowResized(const int& windowHeight, const int& windowWidth);

    private:
        osg::ref_ptr<osgviz::Object> obj;
        osg::Vec3d init_pos;//offset to move anchor to center of HUD element
        osg::Vec2d init_size;
        osg::ref_ptr<HUD> hud;
    };

} /* namespace intercation */

#endif /* GUI_OSGVIZ_OSGVIZ_SRC_WINDOWS_HUD_HUDPOSITIONCHANGER_H_ */
