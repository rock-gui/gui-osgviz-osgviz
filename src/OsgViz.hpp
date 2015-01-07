#ifndef _OSGVIZ_HPP_
#define _OSGVIZ_HPP_

#include <iostream>
#include <mars/lib_manager/LibManager.h>
#include <osg/Node>
#include <osg/Group>
#include <osgViewer/Viewer>

namespace osgviz
{
	class OsgViz
	{
		public: 

		OsgViz();


		void createWindow();

		bool loadPlugin();



		private:
		mars::lib_manager::LibManager libmanager;

		osg::Group *root;

		osgViewer::Viewer viewer;


	};

} // end namespace osgviz

#endif // _DUMMYPROJECT_DUMMY_HPP_
