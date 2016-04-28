#include "ManipulationClickHandler.h"
#include "TranslateBoxDragger.h"
#include <iostream>

using namespace osgManipulator;
using namespace osg;
namespace osgviz {
  
  
class PlaneConstraint : public osgManipulator::Constraint
{
public:
        PlaneConstraint() {}

        virtual bool constrain(osgManipulator::TranslateInLineCommand& command) const
        {
          std::cout << "translate line" << std::endl;
            return true;
        }
        virtual bool constrain(osgManipulator::TranslateInPlaneCommand& command) const
        {
          std::cout << "translate plane" << std::endl;
            return true;
        }
        virtual bool constrain(osgManipulator::Scale1DCommand& command) const
        {
          std::cout << "scale 1d" << std::endl;
            return true;
        }
        virtual bool constrain(osgManipulator::Scale2DCommand& command) const
        {
            std::cout << "scale 2d" << std::endl;
            return true;
        }
        virtual bool constrain(osgManipulator::ScaleUniformCommand& command) const
        {
          std::cout << "scale uniform" << std::endl;
            return true;
        }
};
 
ManipulationClickHandler::ManipulationClickHandler() : clickedObject(NULL),
    dragger(new TranslateBoxDragger()), draggerParent(new NullClickObject())
{
    dragger->setupDefaultGeometry();
    dragger->addConstraint(new PlaneConstraint());
    dragger->setHandleEvents(false);
    draggerParent->addChild(dragger);
}

bool ManipulationClickHandler::clicked(const int& buttonMask, const Vec2d& cursor,
                                       const Vec3d& world, const Vec3d& local,
                                       Clickable* object, WindowInterface* window)
{
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
                                       Clickable* object, WindowInterface* window)
{
    //dragged events are ignored (they are done by the dragger internally)
    return true;
}

void ManipulationClickHandler::deselectCurrentObject()
{
    if(clickedObject != NULL)
    {
        clickedObject->removeChild(draggerParent.get());
    }
}

void ManipulationClickHandler::selectObject(Object* obj)
{
    //FIXME kollidiert das mit dem TransformerGraph weil der davon ausgeht,
    //      dass alle user knoten in der Group sind?
    clickedObject = obj;
    obj->addChild(draggerParent);
}



  
}