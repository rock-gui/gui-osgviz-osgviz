#ifndef GUI_OSGVIZ_OSGVIZ_SRC_WINDOWS_EVENTHANDLERS_TRANSLATE_BOX_DRAGGER_H_
#define GUI_OSGVIZ_OSGVIZ_SRC_WINDOWS_EVENTHANDLERS_TRANSLATE_BOX_DRAGGER_H_

#include <osgManipulator/Dragger>
#include <osgManipulator/Export>

namespace osgManipulator
{
    class RotateCylinderDragger;
    class TranslatePlaneDragger;
}

namespace osgviz 
{
/**A translation dragger that draws 4 planes around the object */
class TranslateBoxDragger : public osgManipulator::CompositeDragger
{
    public:
        META_OSGMANIPULATOR_Object(osgManipulator, TranslateBoxDragger);
        TranslateBoxDragger();

        /** Setup default geometry for dragger. */
        void setupDefaultGeometry();

        /**resets the position relative to the origin/object to default */
        void resetPosition();

    protected:

        virtual ~TranslateBoxDragger();
        std::vector<osg::ref_ptr<osgManipulator::RotateCylinderDragger> > rotatateDraggers;
        std::vector< osg::ref_ptr<osgManipulator::TranslatePlaneDragger > > planeDraggers;
};
}

#endif