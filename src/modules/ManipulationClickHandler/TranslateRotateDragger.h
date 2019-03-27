#ifndef GUI_OSGVIZ_OSGVIZ_SRC_WINDOWS_EVENTHANDLERS_TRANSLATE_BOX_DRAGGER_H_
#define GUI_OSGVIZ_OSGVIZ_SRC_WINDOWS_EVENTHANDLERS_TRANSLATE_BOX_DRAGGER_H_

#include <osgManipulator/Dragger>
#include <osgManipulator/Export>

namespace osgManipulator
{
    class RotateCylinderDragger;
    class TranslatePlaneDragger;
    class CylinderPlaneProjector;
}

namespace osgviz 
{
    /**A translation dragger that draws 4 planes around the object */
    class TranslateRotateDragger : public osgManipulator::CompositeDragger
    {
    public:
        META_OSGMANIPULATOR_Object(osgManipulator, TranslateRotateDragger);
        TranslateRotateDragger();

        /** Setup default geometry for dragger. */
        void setupDefaultGeometry();

        /**resets the position relative to the origin/object to default */
        void resetPosition();

        virtual ~TranslateRotateDragger();

    private:

        /** initializes the default geometry of @p dragger.
        *  This method exists because RotateCylinderDragger::setupDefaultGeometry() 
        *  does not have any parameters to adjust the thickness etc. of the dragger*/
        void setupCylinderDefaultGeometry(osgManipulator::RotateCylinderDragger* dragger) const;

        std::vector<osg::ref_ptr<osgManipulator::RotateCylinderDragger> > rotatateDraggers;
        std::vector< osg::ref_ptr<osgManipulator::TranslatePlaneDragger > > planeDraggers;
        //FIXME not sure if I have to keep the projector around after creating the cylinder
        osg::ref_ptr<osgManipulator::CylinderPlaneProjector> projector; //needed to create the rotation draggers
    };
}

#endif