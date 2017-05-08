#include "WireframeBox.hpp"
#include <osg/Shape>
#include <osg/ShapeDrawable>
#include <osg/Geode>
#include <osg/PolygonMode>

using namespace osg;
using namespace osgviz;



Node* WireframeBox::create(const double xPos, const double yPos, const double zPos,
                           const double xSize, const double ySize, const double zSize)
{
    Box* boundingBox = new Box( Vec3(xPos, yPos, zPos), xSize, ySize, zSize);
    ShapeDrawable* boxDrawable = new ShapeDrawable(boundingBox);
    Geode* geode = new Geode();
    geode->addDrawable(boxDrawable);
    ref_ptr<StateSet> stateset = new StateSet();
    ref_ptr<PolygonMode> polymode = new PolygonMode;
    polymode->setMode(PolygonMode::FRONT_AND_BACK,PolygonMode::LINE);
    stateset->setAttributeAndModes(polymode,StateAttribute::OVERRIDE|StateAttribute::ON);
    boxDrawable->setStateSet(stateset);
    geode->setStateSet(stateset);
    return geode;
}

Node* WireframeBox::create(const double xSize, const double ySize, const double zSize)
{
    return WireframeBox::create(0.0, 0.0, 0.0, xSize, ySize, zSize);
}