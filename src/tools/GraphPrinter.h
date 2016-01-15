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

	static void print(osg::Node* root, bool complete = false, const char* filename = NULL){

		FILE* file = stdout;
		if (filename){
			FILE * out = fopen ( filename, "w" );
			if (out){
				file = out;
			}
		}

		bool firstnode = true;

		std::deque< osg::Node* > nodes;
		std::map< osg::Node*, bool > knownNodes;
		nodes.push_back(root);

		fprintf(file,"\n\ndigraph nodes {\n");
		while (!nodes.empty()){

			osg::Node* node = nodes.front();
			osg::Group * group = dynamic_cast< osg::Group * >(node);
			if (group){
				if (firstnode){
					fprintf(file,"\t \"%p\" [label=\"%s\\n%s\" style=filled, fillcolor=green]\n",node,demangledTypeName(*group).c_str(),node->getName().c_str());
          knownNodes[node] = true;
					firstnode = false;
				}else{
					fprintf(file,"\t \"%p\" [label=\"%s\\n%s\"]\n",node,demangledTypeName(*group).c_str(),node->getName().c_str());
				}
				for (unsigned int i=0;i< group->getNumChildren();++i){
					osg::Node* child = group->getChild(i);
					if (child){
						fprintf(file,"\t\t \"%p\" -> \"%p\"\n",node,child);
						if (!knownNodes[child]){
							nodes.push_back(child);
							knownNodes[child] = true;
						}
					}
				}
				if (complete){
					for (unsigned int i=0;i< group->getNumParents();++i){
						osg::Node* parent = group->getParent(i);
						if (parent){
							//fprintf(file,"\t\t \"%p\" -> \"%p\"\n",parent,node);
							if (!knownNodes[parent]){
								nodes.push_back(parent);
								knownNodes[parent] = true;
							}
						}
					}
				}
			}

			osg::Geode * geode = dynamic_cast< osg::Geode * >(node);
			if (geode){

				if (firstnode){
					fprintf(file,"\t \"%p\" [label=\"%s\\n%s\" style=filled, fillcolor=green]\n",node,demangledTypeName(*geode).c_str(),node->getName().c_str());
					firstnode = false;
				}else{
					fprintf(file,"\t \"%p\" [label=\"%s\\n%s\"]\n",node,demangledTypeName(*geode).c_str(),node->getName().c_str());
				}


			}
			nodes.pop_front();

		}

		fprintf(file,"}\n\n");
		fflush(file);
	}



};


#endif /* STOPWATCH_H_ */
