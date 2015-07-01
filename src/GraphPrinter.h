/*
 * GraphPrinter.h
 *
 *  Created on: 10.02.2009
 *      Author: planthaber
 */

#ifndef GRAPHPRINTER_H_
#define GRAPHPRINTER_H_

#include <osg/Geode>
#include <osg/Group>
#include <deque>
#include <map>
#include "TypeNameDemangling.h"

/**
 * @class GraphPrinter
 * provides some tools for runtime measurements
 */

class GraphPrinter{

public:

	static void print(osg::Node* root){
		std::deque< osg::Node* > nodes;
		std::map< osg::Node*, bool > knownNodes;
		nodes.push_back(root);

		printf("\n\ndigraph nodes {\n");
		while (!nodes.empty()){

			osg::Node* node = nodes.front();
			osg::Group * group = dynamic_cast< osg::Group * >(node);
			if (group){
				printf("\t \"%p\" [label=\"%s\\n%s\"]\n",node,demangledTypeName(*group).c_str(),node->getName().c_str());
				for (unsigned int i=0;i< group->getNumChildren();++i){
					osg::Node* child = group->getChild(i);
					if (child){
						printf("\t\t \"%p\" -> \"%p\"\n",node,child);
						nodes.push_back(child);
					}
				}
			}

			osg::Geode * geode = dynamic_cast< osg::Geode * >(node);
			if (geode){
				printf("\t \"%p\" [label=\"%s\\n%s\"]\n",node,demangledTypeName(*geode).c_str(),node->getName().c_str());
			}
			nodes.pop_front();

		}

		printf("}\n\n");
	}



};


#endif /* STOPWATCH_H_ */
