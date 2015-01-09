#ifndef _OSGVIZ_HPP_
#define _OSGVIZ_HPP_

#include <iostream>
#include <mars/lib_manager/LibManager.h>
#include <osg/Group>
#include <osgViewer/Viewer>

#include "plugins/OsgVizPlugin.h"

namespace osgviz
{
	class OsgViz: public mars::lib_manager::LibInterface
	{
		public: 

		OsgViz(mars::lib_manager::LibManager * manager);

		OsgViz(int argc, char** argv);

		~OsgViz();


		virtual const std::string getLibName() const;

	    virtual int getLibVersion() const;



	    void init(int argc,char** argv);


		void createWindow();

		template <class VIZPLUGIN> VIZPLUGIN* getVisualizerPlugin(std::string classname){
			VIZPLUGIN* viz = (VIZPLUGIN*)getVizPlugin(classname,classname);
			viz->setRootNode(root);
			return viz;
		}

		template <class VIZPLUGIN> VIZPLUGIN* getDataPlugin(std::string classname){
			VIZPLUGIN* data = (VIZPLUGIN*)getVizPlugin(classname,classname);
			data->init(m_argc,m_argv);
			return data;
		}




		private:

		OsgVizPlugin* getVizPlugin(std::string path, std::string name);

		bool createdOwnManager;
		mars::lib_manager::LibManager *libmanager;

		osg::ref_ptr<osg::Group> root;

		osgViewer::Viewer viewer;


		private:
		bool initialized;
		std::vector< OsgVizPlugin* >loadedPlugins;
		osg::ref_ptr<osgGA::CameraManipulator> cameraManipulator;
		int m_argc;
		char** m_argv;

	};

} // end namespace osgviz

#endif // _DUMMYPROJECT_DUMMY_HPP_
