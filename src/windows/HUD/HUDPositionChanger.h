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

    HUDPositionChanger(osgviz::Object* obj, const osg::Vec3d& screenPosition, HUD *hud);
    virtual ~HUDPositionChanger(){};

    virtual bool windowResized(const int& windowHeight, const int& windowWight);

private:
    osgviz::Object* obj;
    osg::Vec3d screenPosition;//offset to move anchor to center of HUD element
    osg::ref_ptr<HUD> hud;
};

} /* namespace intercation */

#endif /* GUI_OSGVIZ_OSGVIZ_SRC_WINDOWS_HUD_HUDPOSITIONCHANGER_H_ */
