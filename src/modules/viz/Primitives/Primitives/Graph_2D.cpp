/*!@file Implemenation of Graph_2D primitive
* Graph_2D.cpp
*
*  Created on: 10.07.2017
*      Author: tkoller
*/
#include "Graph_2D.hpp"
#include <iostream>
#include <osg/LineWidth>
#include <iomanip> // setprecision
#include <sstream> // stringstream
namespace osgviz {
    Graph_2D::Graph_2D(const osg::Vec3 &world_to_plane_pose,
        const osg::Quat &world_to_plane_rot, double width, double height) :
    Graph_2D(width, height) {
        setPosition(world_to_plane_pose);
        setOrientation(world_to_plane_rot);

    }
    Graph_2D::Graph_2D(double width, double height) :
        Graph_2D() {
            setupGraph(width, height);
    }
    Graph_2D::Graph_2D() :
        width(-1), height(-1), geode(new osg::Geode) {
            addChild(geode);
            gotSetup = false;
    }
    void Graph_2D::clearGraph() {

        geode->removeDrawables(0, geode->getNumDrawables() - 1);

    }
    inline void Graph_2D::setup_warning(std::string msg) {
        warning(msg, !gotSetup);
    }
    inline void Graph_2D::warning(std::string  msg, bool condition) {
        if (condition)
            std::cerr << "Graph_2D Warning:  " << msg << std::endl;

    }
    std::string Graph_2D::roundToString(double number, int precision) {
        std::stringstream stream;
        stream << std::setprecision(precision) << number;
        return stream.str();

    }
    void Graph_2D::drawBoundary() {
        setup_warning(
            "called Graph2D::drawBoundary() without setting width and height");
        std::vector < osg::Vec2 > corners;
        corners.push_back(osg::Vec2(0, 0));
        corners.push_back(osg::Vec2(getWidth(), 0));
        corners.push_back(osg::Vec2(getWidth(), getHeight()));
        corners.push_back(osg::Vec2(0, getHeight()));
        corners.push_back(osg::Vec2(0, 0));
        addPath (corners);
    }

    void Graph_2D::setupGraph(double width, double height, bool clear) {
        this->width = width;
        this->height = height;
        gotSetup = true;
        if (clear)
            clearGraph();

    }



    void Graph_2D::addPath(const std::vector<osg::Vec2> &corners, float lineWidth,
        const osg::Vec4 & color) {
            osg::ref_ptr < osg::Geometry > geometry = createGeom(lineWidth,color);
            this->addPath(corners, geometry);
    }
    void Graph_2D::addLine(const osg::Vec2 &start, const osg::Vec2 &end,
        float lineWidth, const osg::Vec4 & color) {
            osg::ref_ptr < osg::Geometry > geometry = createGeom(lineWidth,color);
            this->addLine(start, end, geometry);
    }

    void Graph_2D::addLine(const osg::Vec2 &start, const osg::Vec2 &end,
        osg::ref_ptr<osg::Geometry> &geom) {
            osg::Vec3Array* vertices = (osg::Vec3Array*) geom->getVertexArray();

            vertices->push_back(osg::Vec3(start.x(), start.y(), 0));
            vertices->push_back(osg::Vec3(end.x(), end.y(), 0));
            geom->addPrimitiveSet(
                new osg::DrawArrays(GL_LINES, vertices->size() - 2, 2));
    }

    void Graph_2D::addPath(const std::vector<osg::Vec2> &corners,
        osg::ref_ptr<osg::Geometry> &geom) {
            osg::Vec3Array* vertices = (osg::Vec3Array*) geom->getVertexArray();

            for (size_t i = 0; i < corners.size() - 1; i++) {
                vertices->push_back(osg::Vec3(corners[i].x(), corners[i].y(), 0));
                vertices->push_back(
                    osg::Vec3(corners[(i + 1) % corners.size()].x(),
                    corners[(i + 1) % corners.size()].y(), 0));
            }
            geom->addPrimitiveSet(
                new osg::DrawArrays(GL_LINES,
                vertices->size() - (corners.size() - 1) * 2,
                (corners.size() - 1) * 2));
    }

    osg::ref_ptr<osg::Geometry> Graph_2D::createGeom(float lineWidth,const osg::Vec4 & color) {
        osg::ref_ptr < osg::Geometry > geometry = new osg::Geometry();
        geometry->setVertexArray(new osg::Vec3Array());
        geometry->setColorArray(new osg::Vec4Array());
        geometry->setColorBinding(osg::Geometry::BIND_OVERALL);
        ((osg::Vec4Array*)geometry->getColorArray())->push_back(color);
        osg::ref_ptr < osg::LineWidth > lwidth = new osg::LineWidth(lineWidth);
        geometry->getOrCreateStateSet()->setAttribute(lwidth,
            osg::StateAttribute::ON);
        geode->addDrawable(geometry);
        return geometry;
    }
    void Graph_2D::addText(const char * textStr, osg::Vec2 pos, double angle,
        double fontSize, const osg::Vec4& color,
        const osgText::TextBase::AlignmentType align) {
            osgText::Text *text = new osgText::Text();
            text->setCharacterSize(fontSize);
            text->setAlignment(align);
            text->setText(textStr);
            text->setColor(color);
            text->setPosition(osg::Vec3(pos.x(), pos.y(), 0));
            text->setRotation(osg::Quat(angle, osg::Vec3(0, 0, 1)));
            geode->addDrawable(text);
    }

    void Graph_2D::drawParralelCoordinates(const size_t amount,
        std::vector<double> &minMax, float linewidth, const osg::Vec4& color) {
            double x;
            osg::Vec2 bot, top;
            auto geom=createGeom(linewidth,color);
            for (size_t i = 1; i <= amount; i++) {
                x = this->getWidth() * i / (amount + 1);
                top = osg::Vec2(x, this->getHeight() * 0.9);
                bot = osg::Vec2(x, this->getHeight() * 0.1);
                this->addLine(bot, top,geom);
                this->addText(roundToString(minMax[i], 2).c_str(), bot, 0,
                    0.01 * this->getHeight(), osg::Vec4(0.0f, 0.0f, 0.0f, 1.0f),
                    osgText::TextBase::AlignmentType::CENTER_TOP);
                this->addText(roundToString(minMax[i + amount], 2).c_str(), top, 0,
                    0.01 * this->getHeight(), osg::Vec4(0.0f, 0.0f, 0.0f, 1.0f),
                    osgText::TextBase::AlignmentType::CENTER_BOTTOM);
            }

    }

    void Graph_2D::drawAxes(size_t amount, std::vector<double> &minMax, float linewidth, const osg::Vec4& color) {
        setup_warning(
            "called Graph2D::drawAxes() without setting width and height");
        if (amount > 2) {
            drawParralelCoordinates(amount, minMax,linewidth,color);
        } else {
            warning("Kartesian 2D axis not implemented");
        }
    }

    using namespace std;
    void Graph_2D::drawStridedFeatures(vector<double> &minMax,
        vector<vector<double> > &vectors, unsigned int amount, float lineWidth,
        const osg::Vec4 & color) {
            setup_warning(
                "called Graph2D::drawStridedFeatures() without setting width and height");
            if (vectors.size() < 1) {
                warning("drawStridedFeatures: no features vectors given");
                return;
            }
            auto geom = createGeom(lineWidth,color);
            if (minMax.size() != vectors[0].size() * 2) {
                warning(
                    "drawStridedFeatures: minMax does not contain as many values as a feature vector");
                return;
            }
            if (amount < 1) {
                warning("drawStridedFeatures: amount has to be greater 0");
                return;
            }
            double x, y; // for readability
            for (size_t i = 0; i < vectors.size(); i += vectors.size() / amount) {
                vector < osg::Vec2 > corners;
                for (size_t f = 0; f < vectors[0].size(); f++) {
                    x = this->getWidth() * (f + 1) / (vectors[0].size() + 1);
                    y = this->getHeight() * 0.1
                        + (vectors[i][f] - minMax[f])
                        / (minMax[f + vectors[0].size()] - minMax[f]) * 0.8
                        * this->getHeight();
                    corners.push_back(osg::Vec2(x, y));
                }
                this->addPath(corners, geom);
            }
    }
    void Graph_2D::drawMeanFeatures(const vector<double> &minMax,
        const vector<vector<double> > &vectors, float lineWidth,
        const osg::Vec4 & color) {
            setup_warning(
                "called Graph2D::drawMeanFeatures() without setting width and height");
            if (vectors.size() < 1) {
                warning("drawMeanFeatures: no features vectors given");
                return;
            }
            if (minMax.size() != vectors[0].size() * 2) {
                warning(
                    "drawMeanFeatures: minMax does not contain twice as many values as a feature vector");
                return;
            }

            double x, y; // for readability

            vector < osg::Vec2 > corners;
            for (size_t f = 0; f < vectors[0].size(); f++) {
                x = this->getWidth() * (f + 1) / (vectors[0].size() + 1);
                y = 0;
                for (size_t i = 0; i < vectors.size(); i += 1) {
                    y += vectors[i][f];
                }
                y = this->getHeight() * 0.1
                    + (y / vectors.size() - minMax[f])
                    / (minMax[f + vectors[0].size()] - minMax[f]) * 0.8
                    * this->getHeight();
                corners.push_back(osg::Vec2(x, y));
            }
            this->addPath(corners, lineWidth, color);

    }

}

