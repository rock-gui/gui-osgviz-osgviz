/*
 * SearchNodes.h
 *
 *  Created on: 05.08.2015
 *      Author: planthaber
 */

#ifndef SearchNodes_H_
#define SearchNodes_H_

#include <osg/Geode>
#include <osg/Group>
#include <deque>
#include <map>


/**
 * @class GraphPrinter
 * provides some tools for runtime measurements
 */

class SearchNodes{

public:

	static void printAll(osg::Node* start, bool complete = false){
		std::deque< osg::Node* > nodes;
		std::map< osg::Node*, bool > knownNodes;
		nodes.push_back(start);


		while (!nodes.empty()){

			osg::Node* node = nodes.front();

			if (node->getName().size()>0){
				printf("%s\n",node->getName().c_str());
			}

			osg::Group * group = dynamic_cast< osg::Group * >(node);

			if (group){

				for (unsigned int i=0;i< group->getNumChildren();++i){
					osg::Node* child = group->getChild(i);
					if (child){
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
			nodes.pop_front();
		}

	}

	static osg::Node* searchByName(std::string name, osg::Node* start, bool complete = false){
		std::deque< osg::Node* > nodes;
		std::map< osg::Node*, bool > knownNodes;
		nodes.push_back(start);


		while (!nodes.empty()){

			osg::Node* node = nodes.front();

			if (node->getName() == name){
				return node;
			}

			osg::Group * group = dynamic_cast< osg::Group * >(node);

			if (group){

				for (unsigned int i=0;i< group->getNumChildren();++i){
					osg::Node* child = group->getChild(i);
					if (child){
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
			nodes.pop_front();

		}

		printf("node %s not found, available nodes\n",name.c_str());
		printAll(start,complete);

		return NULL;
	}


	static std::vector<osg::Node*> searchAllByName(std::string name, osg::Node* start, bool complete = false){
		std::deque< osg::Node* > nodes;
		std::map< osg::Node*, bool > knownNodes;
		nodes.push_back(start);
		std::vector<osg::Node*> foundNodes;


		while (!nodes.empty()){

			osg::Node* node = nodes.front();

			if (node->getName() == name){
				foundNodes.push_back(node);
			}

			osg::Group * group = dynamic_cast< osg::Group * >(node);

			if (group){

				for (unsigned int i=0;i< group->getNumChildren();++i){
					osg::Node* child = group->getChild(i);
					if (child){
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
			nodes.pop_front();

		}

		printf("node %s not found, available nodes\n",name.c_str());
		printAll(start,complete);

		return foundNodes;
	}


};


#endif /* STOPWATCH_H_ */
