#include "WireframeBox.hpp"
#include <osg/Shape>
#include <osg/ShapeDrawable>

#include <osg/PolygonMode>

#include <string>
#include <iostream>

using namespace osg;
using namespace osgviz;


WireframeBox::WireframeBox(const double xPos, const double yPos, const double zPos,
                           const double xSize, const double ySize, const double zSize)
{
    boundingBox = new Box( Vec3(xPos, yPos, zPos), xSize, ySize, zSize);
    ShapeDrawable* boxDrawable = new ShapeDrawable(boundingBox);

    geode = new Geode();
    geode->addDrawable(boxDrawable);
    ref_ptr<StateSet> stateset = new StateSet();
    ref_ptr<PolygonMode> polymode = new PolygonMode;
    polymode->setMode(PolygonMode::FRONT_AND_BACK,PolygonMode::LINE);
    stateset->setAttributeAndModes(polymode,StateAttribute::OVERRIDE|StateAttribute::ON);
    boxDrawable->setStateSet(stateset);
    geode->setStateSet(stateset);

    addChild(geode);
}

WireframeBox::WireframeBox(const double xSize, const double ySize, const double zSize)
    : WireframeBox(0, 0, 0, xSize, ySize, zSize) {}

WireframeBox::~WireframeBox() {
    // TODO Auto-generated destructor stub
}    

void WireframeBox::setDimensions(double xSize, double ySize, double zSize) {
    std::cout << "WireframeBox::setDimensions " << xSize << " " << ySize << " " << zSize << std::endl;

    ((Box*)geode->getDrawable(0)->getShape())->setHalfLengths(Vec3(xSize, ySize, zSize));
    //boundingBox->setHalfLengths(Vec3(xSize, ySize, zSize));
}

