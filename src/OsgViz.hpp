#ifndef _OSGVIZ_HPP_
#define _OSGVIZ_HPP_

#include <iostream>
#include <mars/lib_manager/LibManager.h>
#include <osg/Group>
#include <osgViewer/Viewer>

#include <cxxabi.h>

#include "plugins/Visualizer.h"

namespace osgviz
{
	class OsgViz: public mars::lib_manager::LibInterface
	{
		public: 

		OsgViz(mars::lib_manager::LibManager * manager = NULL);

		~OsgViz();


		virtual const std::string getLibName() const;

	    virtual int getLibVersion() const;


		void createWindow();

		template <class VIZPLUGIN> VIZPLUGIN* getVizPlugin(std::string classname){
			return (VIZPLUGIN*)getVizPlugin(classname,classname);
		}

//		inline Visualizer* getVizPlugin(std::string name){
//			return getVizPlugin(name,name);
//		}
		Visualizer* getVizPlugin(std::string path, std::string name);



		private:
		bool createdOwnManager;
		mars::lib_manager::LibManager *libmanager;

		osg::Group *root;

		osgViewer::Viewer viewer;


		private:

		std::vector< Visualizer* >loaded_plugins;


	};

} // end namespace osgviz

#endif // _DUMMYPROJECT_DUMMY_HPP_
