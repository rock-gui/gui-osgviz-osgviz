/*
 * Primitives.h
 *
 *  Created on: 09.01.2015
 *      Author: planthaber
 */

#ifndef GUI_OSGVIZ_SRC_PLUGINS_VIZ_PRIMITIVES_PRIMITIVESFACTORY_H_
#define GUI_OSGVIZ_SRC_PLUGINS_VIZ_PRIMITIVES_PRIMITIVESFACTORY_H_

#include "../../OsgVizVisualizerPlugin.h"

namespace osgviz {

class PrimitivesFactory: public OsgVizVisualizerPlugin {
public:
	PrimitivesFactory(lib_manager::LibManager *theManager);
	virtual ~PrimitivesFactory();

	virtual int getLibVersion() const {return 0;};

	virtual const std::string getLibName() const { return "PrimitivesFactory"; };


	virtual osg::ref_ptr<Object> createAxes(float scale=1.0,bool blabels=true);
	virtual osg::ref_ptr<Object> createGrid(int rows = 20,int cols = 20,float dx =1, float dy=1, bool show_coordinates=false, const ::osg::Vec4 &color = ::osg::Vec4(120,120,120,255));
	virtual osg::ref_ptr<Object> createArrow();

	virtual osg::ref_ptr<Object> createBoundingBox(osg::Group* object);


};

} /* namespace osgviz */

#endif /* GUI_OSGVIZ_SRC_PLUGINS_VIZ_PRIMITIVES_PRIMITIVESFACTORY_H_ */
