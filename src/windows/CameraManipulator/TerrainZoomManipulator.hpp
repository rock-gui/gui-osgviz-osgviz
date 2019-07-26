#ifndef OSGVIZ_OSGVIZ_SRC_WINDOWS_CAMERAMANIPULATOR_TERRAINZOOMMANIPULATOR_H_
#define OSGVIZ_OSGVIZ_SRC_WINDOWS_CAMERAMANIPULATOR_TERRAINZOOMMANIPULATOR_H_

#include <osgGA/TerrainManipulator>
#include <osg/CopyOp>
#include <osgGA/GUIEventAdapter>

namespace osgviz {


    class TerrainZoomManipulator : public osgGA::TerrainManipulator
    {
        typedef osgGA::TerrainManipulator inherited;

    public:

        TerrainZoomManipulator( int flags = DEFAULT_SETTINGS );
        TerrainZoomManipulator( const TerrainZoomManipulator& tm,
            const osg::CopyOp& copyOp = osg::CopyOp::SHALLOW_COPY );

    protected:

        virtual bool handleMouseWheel( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us );
        virtual bool setCenterByMousePointer( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us);

    private:
    };


}

#endif /* OSGVIZ_OSGVIZ_SRC_WINDOWS_CAMERAMANIPULATOR_TERRAINZOOMMANIPULATOR_H_ */