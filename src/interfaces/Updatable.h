/*
 * Updatable.h
 *
 *  Created on: 02.02.2016
 *      Author: planthaber
 */

#ifndef GUI_OSGVIZ_OSGVIZ_SRC_INTERFACES_UPDATABLE_H_
#define GUI_OSGVIZ_OSGVIZ_SRC_INTERFACES_UPDATABLE_H_

namespace osgviz {

class Updatable{
public:
    Updatable(){};
    virtual ~Updatable(){};

    /**
     * update called eiter by an osgviz::UpdateThread or the osgVit classed main thread
     */
    virtual void update() = 0;

};

}//namespace

#endif /* GUI_OSGVIZ_OSGVIZ_SRC_INTERFACES_UPDATABLE_H_ */
