#include "TerrainZoomManipulator.hpp"

#include <iostream>

#include <osg/io_utils>

using namespace osgviz;

/// Constructor.
TerrainZoomManipulator::TerrainZoomManipulator( int flags )
    : inherited( flags )
{
}


/// Constructor.
TerrainZoomManipulator::TerrainZoomManipulator( const TerrainZoomManipulator& tm, const osg::CopyOp& copyOp )
    : inherited( tm, copyOp )
{
}

bool TerrainZoomManipulator::handleMouseWheel( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us )
{
    // no zooming by intersection is choosed
    if (! (_flags & 0x08))
    {
        setCenterByMousePointer(ea, us);
    }

    switch( ea.getScrollingMotion() )
    {
        // mouse scroll up event
        case osgGA::GUIEventAdapter::SCROLL_UP:
        {
            // perform zoom
            zoomModel( _wheelZoomFactor, true );
            us.requestRedraw();
            us.requestContinuousUpdate( isAnimating() || _thrown );
            return true;
        }

        // mouse scroll down event
        case osgGA::GUIEventAdapter::SCROLL_DOWN:

            zoomModel( -_wheelZoomFactor, true );
            us.requestRedraw();
            us.requestContinuousUpdate( false );
            return true;

        // unhandled mouse scrolling motion
        default:
            return false;
   }
   
}

bool TerrainZoomManipulator::setCenterByMousePointer( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us )
{
    osg::View* view = us.asView();
    if( !view )
        return false;

    osg::Camera *camera = view->getCamera();
    if( !camera )
        return false;

    // prepare variables
    float x = ( ea.getX() - ea.getXmin() ) / ( ea.getXmax() - ea.getXmin() );
    float y = ( ea.getY() - ea.getYmin() ) / ( ea.getYmax() - ea.getYmin() );

    osg::Matrix VPW = camera->getProjectionMatrix()
            * camera->getViewport()->computeWindowMatrix();

    osg::Matrix invVPW;
    bool success = invVPW.invert(VPW);

    osg::Vec3f nearPoint = osg::Vec3f(ea.getX(), ea.getY(), 0.f) * invVPW;
    osg::Vec3f farPoint = osg::Vec3f(ea.getX(), ea.getY(), 1.f) * invVPW;

    // scale
    float scale = 1.0f -_wheelZoomFactor;
    float distance = _distance * scale;

    float x_new = ((_distance - distance) * farPoint.x()) / _distance;
    float y_new = ((_distance - distance) * farPoint.y()) / _distance;


    switch( ea.getScrollingMotion() )
    {
        case osgGA::GUIEventAdapter::SCROLL_DOWN:
        {
            panModel(x_new, y_new, 0);
            return true;
        }
        default:
            return false;
    }    
}