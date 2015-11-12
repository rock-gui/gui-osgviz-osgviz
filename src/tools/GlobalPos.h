/*
 * GlobalPos.h
 *
 *  Created on: 11.11.2015
 *      Author: planthaber
 */

#ifndef GUI_OSGVIZ_OSGVIZ_SRC_TOOLS_GLOBALPOS_H_
#define GUI_OSGVIZ_OSGVIZ_SRC_TOOLS_GLOBALPOS_H_

#include <osg/MatrixTransform>
#include <osg/PositionAttitudeTransform>
#include <osgViz/OsgViz.hpp>


class GlobalPos{
public:

	/**
	 *  http://www.movesinstitute.org/Sullivan/OSGTutorials/osgGetWorldCoords.htm
	 */
	class GetWorldCoordOfNodeVisitor : public osg::NodeVisitor
	//http://www.movesinstitute.org/Sullivan/OSGTutorials/osgGetWorldCoords.htm
	{
	public:
		GetWorldCoordOfNodeVisitor(osg::Node* root): osg::NodeVisitor(NodeVisitor::TRAVERSE_PARENTS), finished (false), rootnode(root){
			matrix = osg::Matrixd();
		}
		virtual void apply(osg::Node &node)
		{
			if (!finished)
			{
				if ( &node == rootnode || (rootnode==NULL && 0 == node.getNumParents()) ) // no parents
						{
					matrix.set( osg::computeLocalToWorld(this->getNodePath()) );
					finished = true;
						}
				traverse(node);
			}
		}
		osg::Matrixd getMatrixd()
		{
			return matrix;
		}
	private:
		bool finished;
		osg::Matrixd matrix;
		osg::Node* rootnode;
	};

	static osg::Matrixd getNodePos(osg::ref_ptr<osg::Node> node){

		GetWorldCoordOfNodeVisitor ncv(osgviz::OsgViz::getExistingInstance()->getRootNode());
		node->accept(ncv);
		return ncv.getMatrixd();
	}

	static osg::ref_ptr<osg::PositionAttitudeTransform> getGlobalPATransform(osg::ref_ptr<osg::Node> node){
		osg::Matrixd matrix = getNodePos(node);
		osg::Vec3d translation;
		osg::Quat rotation;
		osg::Vec3d scale;
		osg::Quat so;
		matrix.decompose(translation, rotation, scale, so);
		osg::ref_ptr<osg::PositionAttitudeTransform> patrans = new osg::PositionAttitudeTransform();
		patrans->setPosition(translation);
		patrans->setAttitude(rotation);
		patrans->setScale(scale);
		return patrans;
	}



};

#endif /* GUI_OSGVIZ_OSGVIZ_SRC_TOOLS_GLOBALPOS_H_ */
