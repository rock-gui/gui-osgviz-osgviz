#ifndef GUI_OSGVIZ_OSGVIZ_PLUGINS_MANIPULATION_CLICK_HANDLER_MANIPULATION_CLICK_HANDLER_H
#define GUI_OSGVIZ_OSGVIZ_PLUGINS_MANIPULATION_CLICK_HANDLER_MANIPULATION_CLICK_HANDLER_H

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
class ManipulationClickHandler : public osgviz::Clickable,
                                 public osgManipulator::DraggerCallback
{
  //TODO verschiedene Dragger unterstüzen, user auswählen lassen
public:
    
    ManipulationClickHandler();
  
    /**Called when the user clicks on the object */
    virtual bool clicked(const int& buttonMask, const osg::Vec2d& cursor,
                         const osg::Vec3d& world, const osg::Vec3d& local,
                         Clickable* object, const int modKeyMask,
                         osgviz::WindowInterface* window = 0);
    
    //is called whenever the user moves the dragger
    virtual bool receive(const osgManipulator::MotionCommand& command);
    
    /** Select the specified object.  */
    void selectObject(osgviz::Object* obj);
    
    /**This signal is emitted once the movement is complete.
     * I.e. the user has clicked the object, dragged it and released it.
     * @param motion the final motion of the object relative to the original object
     *               position.*/
    boost::signals2::signal<void (const osgviz::Object* obj, const osg::Matrix& motion)>
        objectMoved;
        
    /**This signal is emiitted while the user is moving an object. */
    boost::signals2::signal<void (const osgviz::Object* obj, const osg::Matrix& motion)>
        objectMoving;
        
    /**This signal is emitted whenever the user selectes a new object*/
    boost::signals2::signal<void (const osgviz::Object* obj)> objectSelected;
        
        
    
private:
  
    /**Removes the dragger from clickedObject */
    void deselectCurrentObject();
    
    osgviz::Object* clickedObject;
    osg::ref_ptr<osgManipulator::Dragger> translationDragger;
    osg::ref_ptr<osgManipulator::Dragger> rotationDragger;
    /**NullClickObject is used a parent for the draggers to avoid propagating
     * click events from the dragger to the dragged node*/
    osg::ref_ptr<NullClickObject> translationDraggerParent;
    osg::ref_ptr<NullClickObject> rotationDraggerParent;
       
    osg::Matrix initialMotionMatrix;
    osg::Matrix worldToObject; //transformation from world to selected object
    osg::Matrix objectToWorld;
    osg::Matrix currentMotionMatrix;
    bool moved; //inidicates whether the user actually moved an object or just clicked & released
};

}

#endif