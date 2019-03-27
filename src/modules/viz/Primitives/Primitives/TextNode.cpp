#include "TextNode.hpp"
#include <osgText/Text>

namespace osgviz {

    TextNode::TextNode(const std::string& textStr, double fontSize) : geode(new osg::Geode()),
        text(new osgText::Text())
    {
        text->setCharacterSize(fontSize);
        text->setText(textStr);
        text->setColor(osg::Vec4(1, 1, 1, 1));
        geode->addDrawable(text);
        addChild(geode);
    }

    void TextNode::setColor(const osg::Vec4& color)
    {
        text->setColor(color);
    }

}