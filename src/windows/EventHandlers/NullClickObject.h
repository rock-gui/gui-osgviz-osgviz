#ifndef GUI_OSGVIZ_OSGVIZ_SRC_WINDOWS_EVENTHANDLERS_NULL_CLICK_OBJECT_H_
#define GUI_OSGVIZ_OSGVIZ_SRC_WINDOWS_EVENTHANDLERS_NULL_CLICK_OBJECT_H_

#include "../../Object.h"

namespace osgviz {

/**An osgviz object that does nothing but stop events from propagating up the chain */
class NullClickObject : public osgviz::Object
{
virtual bool clicked(const int& buttonMask, const osg::Vec2d& cursor,
                     const osg::Vec3d& world, const osg::Vec3d& local,
                     Clickable* object, const int modifierMask,
                     osgviz::WindowInterface* window = 0)
{
    return true;
}
virtual bool dragged(const int& buttonMask, const osg::Vec2d& cursor,
                     const osg::Vec3d& world, const osg::Vec3d& local,
                     Clickable* object, const int modifierMask,
                     osgviz::WindowInterface* window = 0)
{
    return true;
}
  
};

}


#endif
