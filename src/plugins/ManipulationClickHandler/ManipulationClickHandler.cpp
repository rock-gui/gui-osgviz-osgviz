#include "ManipulationClickHandler.h"
#include "TranslateBoxDragger.h"
#include <iostream>
#include <osg/io_utils>
#include <osgManipulator/RotateSphereDragger>
#include <osgManipulator/Dragger>
#include <osgViz/plugins/Object.h>

using namespace osgManipulator;
using namespace osg;
namespace osgviz {
  

ManipulationClickHandler::ManipulationClickHandler() : clickedObject(NULL),
    translationDragger(new TranslateBoxDragger()), rotationDragger(new osgManipulator::RotateSphereDragger()),
    translationDraggerParent(new NullClickObject()), rotationDraggerParent(new NullClickObject)
{
    translationDragger->setupDefaultGeometry();
    translationDragger->setHandleEvents(true);//allow the dragger to move itself when dragged
    translationDragger->addDraggerCallback(this);
    translationDraggerParent->addChild(translationDragger);
    
    rotationDragger->setupDefaultGeometry();
    rotationDragger->setHandleEvents(true);
    rotationDragger->addDraggerCallback(this);
    rotationDraggerParent->addChild(rotationDragger);
    
}

bool ManipulationClickHandler::clicked(const int& buttonMask, const Vec2d& cursor,
                                       const Vec3d& world, const Vec3d& local,
                                       Clickable* object, const int modKeyMask,
                                       WindowInterface* window)
{
    std::cout << "MASK: " << modKeyMask << std::endl;
    osgviz::Object* obj = dynamic_cast<osgviz::Object*>(object);
    if(obj != NULL && obj != clickedObject)
    {
        deselectCurrentObject();
        selectObject(obj);
        return true; 
    }
    else
    {
        //FIXME replace with real logging
        std::cerr << "osgziv: WARNING ManipulationClickHandler can only be attached " 
                  << "to osgviz::Object" << std::endl;
        return false;
    }
}


bool ManipulationClickHandler::dragged(const int& buttonMask, const Vec2d& cursor,
                                       const Vec3d& world, const Vec3d& local,
                                       Clickable* object, const int modKeyMask,
                                       WindowInterface* window)
{
    //dragged events are ignored (they are done by the dragger internally)
    return true;
}

void ManipulationClickHandler::deselectCurrentObject()
{
    if(clickedObject != NULL)
    {
        //dont know which dragger was used, just remove both of them and 
        //ignore the return value :)
        clickedObject->removeChild(translationDraggerParent.get());
        clickedObject->removeChild(rotationDraggerParent.get());
    }
}

void ManipulationClickHandler::selectObject(osgviz::Object* obj)
{
    //FIXME kollidiert das mit dem TransformerGraph weil der davon ausgeht,
    //      dass alle user knoten in der Group sind?
    clickedObject = obj;
    obj->addChild(translationDraggerParent);
    osg::NodePath pathFromObjToRoot;
    osgManipulator::computeNodePathToRoot(*clickedObject, pathFromObjToRoot);
    const osg::Matrix objectToWorld = osg::computeLocalToWorld(pathFromObjToRoot);
    worldToObject = osg::Matrix::inverse(objectToWorld);
}

bool ManipulationClickHandler::receive(const MotionCommand& command)
{
  
  if(command.getStage() == MotionCommand::START)
  {
      //remember initial dragger position in object coordinates.
      //This is important because composit draggers are made up of multiple 
      //sub-draggers. Each sub dragger has a different initial position in the
      //object coordinate system
      initialMotionMatrix = command.getMotionMatrix() * command.getLocalToWorld()
                            * worldToObject;
  }
  else if(command.getStage() == MotionCommand::MOVE)
  {
      //convert current dragger position into object coordinate system
      currentMotionMatrix = command.getMotionMatrix() * command.getLocalToWorld()
                            * worldToObject;
      //calculate relative distance between initial dragger position and current dragger position
      currentMotionMatrix = osg::Matrix::inverse(initialMotionMatrix) * currentMotionMatrix;
  }
  else if(command.getStage() == MotionCommand::FINISH)
  {
       objectMoved(clickedObject, currentMotionMatrix);
       //reset the position of the dragger relative to the object after signaling
       //that the object should be moved,
       translationDragger->setMatrix(Matrixd());
  }
  else
  {
    return false;
  }
  return true;
}
}