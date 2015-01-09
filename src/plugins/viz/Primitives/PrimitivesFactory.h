/*
 * Primitives.h
 *
 *  Created on: 09.01.2015
 *      Author: planthaber
 */

#ifndef GUI_OSGVIZ_SRC_PLUGINS_VIZ_PRIMITIVES_PRIMITIVESFACTORY_H_
#define GUI_OSGVIZ_SRC_PLUGINS_VIZ_PRIMITIVES_PRIMITIVESFACTORY_H_

#include "../../OsgVizVisualizerPlugin.h"
#include "Primitive.h"

namespace osgviz {

class PrimitivesFactory: public OsgVizVisualizerPlugin {
public:
	PrimitivesFactory(mars::lib_manager::LibManager *theManager);
	virtual ~PrimitivesFactory();

	virtual int getLibVersion() const {return 0;};

	virtual const std::string getLibName() const { return "PrimitivesFactory"; };


	enum PrimitiveEnum {GRID,AXES};


	virtual Primitive* createAxes();
	virtual Primitive* createGrid(int rows = 20,int cols = 20,float dx =1, float dy=1, bool show_coordinates=false, const ::osg::Vec4 &color = ::osg::Vec4(120,120,120,255));

private:
	Primitive* createPrimitive();


};

} /* namespace osgviz */

#endif /* GUI_OSGVIZ_SRC_PLUGINS_VIZ_PRIMITIVES_PRIMITIVESFACTORY_H_ */
