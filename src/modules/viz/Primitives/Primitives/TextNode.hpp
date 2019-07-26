#pragma once

#include <osg/Shape>
#include <osg/ShapeDrawable>
#include "../../../../Object.h"
#include <string>

namespace osgText 
{
    class Text;
}

namespace osgviz {

    class TextNode : public osgviz::Object{
    public:
        TextNode(const std::string& text, double fontSize);
        void setColor(const osg::Vec4& color);
    private:
        osg::ref_ptr<osg::Geode> geode;
        osgText::Text* text;
    };

}

