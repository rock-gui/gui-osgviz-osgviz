#ifndef GUI_OSGVIZ_OSGVIZ_SRC_WINDOWS_EVENTHANDLERS_MANIPULATION_CLICK_HANDLER_H_
#define GUI_OSGVIZ_OSGVIZ_SRC_WINDOWS_EVENTHANDLERS_MANIPULATION_CLICK_HANDLER_H_

#include <boost/signals2.hpp>
#include <osgViz/interfaces/Clickable.h>
#include <osgViz/plugins/Object.h>
#include <osgManipulator/Dragger>
#include <osgViz/windows/EventHandlers/NullClickObject.h>
#include <osg/Referenced>

namespace osgviz {

/** FIXME description
 * FIXME small usage example */
class ManipulationClickHandler : public osgviz::Clickable, public osg::Referenced
{
  //TODO verschiedene Dragger unterstüzen, user auswählen lassen
public:
    ManipulationClickHandler();
    
    virtual bool clicked(const int& buttonMask, const osg::Vec2d& cursor,
                        const osg::Vec3d& world, const osg::Vec3d& local,
                        Clickable* object, osgviz::WindowInterface* window = 0);

    virtual bool dragged(const int& buttonMask, const osg::Vec2d& cursor,
                        const osg::Vec3d& world, const osg::Vec3d& local, 
                        Clickable* object, osgviz::WindowInterface* window = 0);
    
private:
    /**Removes the dragger from clickedObject */
    void deselectCurrentObject();
    void selectObject(Object* obj);
    
  
    Object* clickedObject;
    osg::ref_ptr<osgManipulator::Dragger> dragger;
    /**NullClickObject is used a parent for the dragger to avoid propagating
     * click events from the dragger to the dragged node*/
    osg::ref_ptr<NullClickObject> draggerParent;
    
};

}

#endif