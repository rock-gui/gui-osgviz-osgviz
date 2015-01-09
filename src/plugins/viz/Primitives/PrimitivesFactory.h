/*
 * Primitives.h
 *
 *  Created on: 09.01.2015
 *      Author: planthaber
 */

#ifndef GUI_OSGVIZ_SRC_PLUGINS_VIZ_PRIMITIVES_PRIMITIVESFACTORY_H_
#define GUI_OSGVIZ_SRC_PLUGINS_VIZ_PRIMITIVES_PRIMITIVESFACTORY_H_

namespace osgviz {

class PrimitivesFactory: public OsgVizVisualizerPlugin {
public:
	PrimitivesFactory();
	virtual ~PrimitivesFactory();

	virtual int getLibVersion() const {return 0;};

	const std::string getLibName() const { return "PrimitivesFactory"; };

};

} /* namespace osgviz */

#endif /* GUI_OSGVIZ_SRC_PLUGINS_VIZ_PRIMITIVES_PRIMITIVESFACTORY_H_ */
