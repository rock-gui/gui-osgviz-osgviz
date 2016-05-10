#include "ManipulationClickHandler.h"
#include "TranslateBoxDragger.h"
#include <iostream>
#include <osg/io_utils>
#include <osgManipulator/RotateSphereDragger>
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
    std::cout << "MASK: " << buttonMask << std::endl;
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
}

bool ManipulationClickHandler::receive(const TranslateInLineCommand& command)
{
  std::cout<< "receive TranslateInLineCommand"<< std::endl;
  return false;
}

bool ManipulationClickHandler::receive(const TranslateInPlaneCommand& command)
{
  if(command.getStage() == MotionCommand::START)
  {
      currentTranslation.set(0, 0, 0);
  }
  else if(command.getStage() == MotionCommand::MOVE)
  {
      const osg::Vec3d trans = command.getLocalToWorld().getRotate() * command.getTranslation();
      currentTranslation = trans;
  }
  else if(command.getStage() == MotionCommand::FINISH)
  {
      objectTranslated(clickedObject, currentTranslation);
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

bool ManipulationClickHandler::receive(const Scale1DCommand& command)
{
  std::cout <<"receive Scale1DCommand"<< std::endl;
 // objectTranslated(clickedObject, command);
  return false;
}

bool ManipulationClickHandler::receive(const Scale2DCommand& command)
{
  std::cout<< "receive Scale2DCommand"<< std::endl;
// objectTranslated(clickedObject, command);
  return false;
}

bool ManipulationClickHandler::receive(const ScaleUniformCommand& command)
{
  std::cout<< "receive ScaleUniformCommand"<< std::endl;
 // objectTranslated(clickedObject, command);
  return false;
}

bool ManipulationClickHandler::receive(const Rotate3DCommand& command)
{
  std::cout<< "receive Rotate3DCommand"<< std::endl;
 // objectTranslated(clickedObject, command);
  return false;
}


  
}