#ifndef GUI_OSGVIZ_OSGVIZ_SRC_WINDOWS_EVENTHANDLERS_MANIPULATION_CLICK_HANDLER_H_
#define GUI_OSGVIZ_OSGVIZ_SRC_WINDOWS_EVENTHANDLERS_MANIPULATION_CLICK_HANDLER_H_

#include <boost/signals2.hpp>
#include <osgViz/interfaces/Clickable.h>
#include <osgViz/plugins/Object.h>
#include <osgManipulator/Dragger>
#include <osgViz/windows/EventHandlers/NullClickObject.h>
#include <osg/Referenced>

namespace osgviz {

/** A click handler that aggregates TranslateInPlaneCommands and Rotate3DCommands
 *  and forwards them once the user has finished dragging.

 *  
 * FIXME small usage example */
class ManipulationClickHandler : public osgviz::Clickable, public osgManipulator::DraggerCallback
{
  //TODO verschiedene Dragger unterstüzen, user auswählen lassen
public:
    ManipulationClickHandler();
    
    /**Called when the user clicks on the object */
    virtual bool clicked(const int& buttonMask, const osg::Vec2d& cursor,
                        const osg::Vec3d& world, const osg::Vec3d& local,
                        Clickable* object, osgviz::WindowInterface* window = 0);

    virtual bool dragged(const int& buttonMask, const osg::Vec2d& cursor,
                        const osg::Vec3d& world, const osg::Vec3d& local, 
                        Clickable* object, osgviz::WindowInterface* window = 0);
    
    //are called whenever the user moves the dragger
    virtual bool receive(const osgManipulator::TranslateInLineCommand& command);
    virtual bool receive(const osgManipulator::TranslateInPlaneCommand& command);
    virtual bool receive(const osgManipulator::Scale1DCommand& command);
    virtual bool receive(const osgManipulator::Scale2DCommand& command);
    virtual bool receive(const osgManipulator::ScaleUniformCommand& command);
    virtual bool receive(const osgManipulator::Rotate3DCommand& command);
    
    /**This signal will be emitted once the translation process is complete.
     * I.e. the user has clicked the object, dragged it and released it*/
    boost::signals2::signal<void (const osgviz::Object*, const osg::Vec3d& translation)>
        objectTranslated;
    
private:
    /**Removes the dragger from clickedObject */
    void deselectCurrentObject();
    void selectObject(osgviz::Object* obj);
    
    
    
    osgviz::Object* clickedObject;
    osg::ref_ptr<osgManipulator::Dragger> dragger;
    /**NullClickObject is used a parent for the dragger to avoid propagating
     * click events from the dragger to the dragged node*/
    osg::ref_ptr<NullClickObject> draggerParent;
    
    osg::Vec3d currentTranslation; /**< buffers the current translation to emit it when the drag is finished */
    
};

}

#endif