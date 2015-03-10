/*
 * Clickable.h
 *
 *  Created on: 09.03.2015
 *      Author: planthaber
 */

#ifndef OSGVIZ_OSGVIZ_SRC_INTERFACES_CLICKABLE_H_
#define OSGVIZ_OSGVIZ_SRC_INTERFACES_CLICKABLE_H_

namespace osgviz {

class Clickable {
public:

	virtual bool clicked(int buttonMask, float x, float y, float z = 0) = 0;

};

} /* namespace osgviz */

#endif /* OSGVIZ_OSGVIZ_SRC_INTERFACES_CLICKABLE_H_ */
