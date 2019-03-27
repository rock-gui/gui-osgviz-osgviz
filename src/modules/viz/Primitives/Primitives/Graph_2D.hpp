#pragma once
/*! @file Header for the 2D_Graph primitive
*
*/

#include <osgViz/Object.h>
#include "LinesNode.h"
#include <vector>
#include <string>
namespace osgviz {
    /*! @class Primitive to show a 2D Graph in Vizkit 3D
    * @brief This class provides the Implementation to create 2D-Graphs as 2D-line graphs.
    * The User can use the interface functions in 2D coordinates to draw his graph while the container handles translation and rotation into the 3D-plane
    * The container supports text and line drawing
    *
    */
    class Graph_2D: public osgviz::Object {
    private:
        double width, //!< width of the graph
            height; //!< height of the graph
        osg::ref_ptr<osg::Geode> geode; //!< main geode to store drawables
        bool gotSetup; //!< whether the graph is setted up
        /*!
        * @brief Draws parralel coordinates on the graph
        * @param amount number of axes
        * @param minMax min and max values of axes [min_0,min_1,...,min_n,max_0,...]
        */
        void drawParralelCoordinates(const size_t amount,
            std::vector<double> &minMax, float lineWidth,
            const osg::Vec4 & color);

        /*!@brief Writes a warning if condition
        * @param msg the warning message
        * @param condition whether to print the warning
        */
        inline void warning(std::string msg, bool condition = true);

        /* @brief Writes a warning if graph has not been setup
        * @param msg the warning message
        */
        inline void setup_warning(std::string msg);

    public:
        /*!@brief  Width Getter
        * @return the width of the patch
        */
        inline double getWidth() {
            return width;
        }
        /*!@brief  Height Getter
        * @return the height of the patch
        */
        inline double getHeight() {
            return height;
        }
        /*!
        * @brief Calls setupGraph setRotation and setPosition
        * @see setupGraph
        * @see osgviz::Object::setRotation
        * @see osgviz::Object::setPosition
        * @param world_to_plane_pose Midpoint of the plane in world coordinates
        * @param world_to_plane_rot  Rotation of the plane around the midpoint
        * @param width width of the plane
        * @param height height of the plane
        */
        Graph_2D(const osg::Vec3 &world_to_plane_pose,
            const osg::Quat &world_to_plane_rot, double width, double height);

        /*!
        * @brief Calls setupGraph
        * @see setupGraph
        * @param width width of the plane
        * @param height height of the plane
        */
        Graph_2D(double width, double height);

        /*!
        *@brief If used setup_graph needs to be called to set basics for graph rendering
        *@see setupGraph
        */
        Graph_2D();

        /*!@brief Does the basic setup to display the plane
        * @param width width of the plane
        * @param height height of the plane
        * @param clear whether to reset graph or not defaults to true
        */
        void setupGraph(double width, double height, bool clear = true);

        /*!
        * @brief Draws a boundary around the graph
        * only works proper with setupGraph called
        * @see setupGraph
        */
        void drawBoundary();

        /*!@brief Removes all drawn elements
        *
        */
        void clearGraph();

        /*!@brief Creates a geometry object
        *
        * Object can be later used for simple drawing operations
        * Recommended if many lines are drawn with same parameters
        * To store line segments more efficiently
        *
        * @see addLine
        * @see addPath
        *@return pointer to the geometry object
        *@param lineWidth the width for all lines in this geometry
        *@param color color for all lines in this geometry
        */
        osg::ref_ptr<osg::Geometry> createGeom(float lineWidth = 1.0,
            const osg::Vec4 & color = osg::Vec4(0.0f, 0.0f, 0.0f, 1.0f));

        /*!@brief Adds a 2D line to the container
        *
        * Recommended use for single lines
        * @param start The starting point of the line in 2D coordinates
        * @param end The end point of the line in 2D coordinates
        * @param lineWidth width of the line
        * @param color color of the line
        */
        void addLine(const osg::Vec2 &start, const osg::Vec2 &end,
            float lineWidth = 1.0,
            const osg::Vec4 & color = osg::Vec4(0.0f, 0.0f, 0.0f, 1.0f));

        /*!@brief Adds a 2D line to the container
        *
        * Recommended if multiple lines with same parameters should be drawn
        * Pass a parametrized geometry
        *
        * @see createGeom
        *
        * @param start The starting point of the line in 2D coordinates
        * @param end The end point of the line in 2D coordinates
        * @param geom geometry containing the line parameters as color and with
        */
        void addLine(const osg::Vec2 &start, const osg::Vec2 &end,
            osg::ref_ptr<osg::Geometry> &geom);

        /*!@brief Adds a 2D path to the container
        *
        * Recommended use for single paths
        *
        * @param corners vector list with all corner points of the path
        * @param lineWidth
        * @param color color of the drawn path
        */
        void addPath(const std::vector<osg::Vec2> &corners, float lineWidth = 1.0,
            const osg::Vec4 & color = osg::Vec4(0.0f, 0.0f, 0.0f, 1.0f));

        /*!@brief Adds a 2D path to the container
        *
        * Recommended if multiple paths with same parameters should be drawn
        * Pass a parametrized geometry
        *
        * @see createGeom
        *
        * @param corners vector list with all corner points of the path
        * @param geom geometry to draw the path
        */
        void addPath(const std::vector<osg::Vec2> &corners,
            osg::ref_ptr<osg::Geometry> &geom);

        /*!@brief  Adds a text Element to the graph
        * @param textStr the shown text
        * @param pos the position in 2d coordinates
        * @param fontSize size of the displayed text
        * @param color text color
        * @param align alignment of the text
        */
        void addText(const char * textStr, osg::Vec2 pos, double angle,
            double fontSize, const osg::Vec4& color = osg::Vec4(1, 1, 1, 1),
            const osgText::TextBase::AlignmentType align = osgText::TextBase::AlignmentType::LEFT_BOTTOM);

        /*!@brief  Draws axes in on the plot
        *
        * parralel coordinates are used if amount > 2
        * @param amount amount of axis to draw
        * @param minMax min and max values of axes [min_0,min_1,...,min_n,max_0,...]
        */
        void drawAxes(size_t amount, std::vector<double> &minMax,
            float lineWidth = 1.0,
            const osg::Vec4 & color = osg::Vec4(0.0f, 0.0f, 0.0f, 1.0f));

        /*!
        * @brief Draws the mean of feature vectors on the graph
        * @param minMax the min and max values of the features (min_0,min_1,...min_n-1,max_0,max_1,max_n-1)
        * @param lineWidth the width of the lines
        * @param vectors the vectors to draw
        * @param color color of the lines
        */
        void drawMeanFeatures(const std::vector<double> &minMax,
            const std::vector<std::vector<double> > &vectors,
            float lineWidth = 1.0,
            const osg::Vec4 & color = osg::Vec4(0.0f, 0.0f, 0.0f, 1.0f));

        /*!
        * @brief Draws feature vectors on the graph
        * @param minMax the min and max values of the features (min_0,min_1,...min_n-1,max_0,max_1,max_n-1)
        * @param vectors the vectors to draw
        * @param amount only shows amount members of vectors stepsize=N/amount,
        * @param lineWidth the witdh of the lines
        * @param color the color of the lines
        */
        void drawStridedFeatures(std::vector<double> &minMax,
            std::vector<std::vector<double> > &vectors, unsigned int amount,
            float lineWidth = 1.0,
            const osg::Vec4 & color = osg::Vec4(0.0f, 0.0f, 0.0f, 1.0f));

        /*! @brief  rounds a number to a given precision and returns it as const char*
        * @param number the number to round
        * @param precision digits after decimal ,
        * @return the rounded number as char *
        */
        std::string roundToString(double number, int precision);
    };
}
