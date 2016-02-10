#ifndef _OSGVIZ_HPP_
#define _OSGVIZ_HPP_

#include <iostream>
#include <lib_manager/LibManager.hpp>
#include <osg/Group>
#include <osgViewer/Viewer>
#include <osgDB/WriteFile>

//#include "graphics/interfaces/GraphicsManagerInterface.h"
#include "plugins/OsgVizPlugin.h"
#include "plugins/OsgVizVisualizerPlugin.h"
#include "windows/WindowManager.h"

#include "windows/config/WindowConfig.h"

#include <stdio.h>
#include "tools/Timing.h"
#include "tools/UpdateThread.h"


namespace osgDB{
	class ReaderWriter;
}


namespace osgviz
{

	class OsgViz: public lib_manager::LibInterface, public Updatable
	{

		public: 

	    //CREATE_MODULE_INFO();

		static OsgViz* getInstance(int argc = 0,char** argv = NULL);
		static OsgViz* getInstance(lib_manager::LibManager * manager);
		static OsgViz* getExistingInstance();

		OsgViz(lib_manager::LibManager * manager);

		private:
		OsgViz(int argc, char** argv);

		public:
		~OsgViz();


		virtual const std::string getLibName() const;

	    virtual int getLibVersion() const;



	    void init(int argc,char** argv);

	    /**
	     * starts a thread calling update
	     */
	    void startThread();
	    void stopThread();

	    int tryLockThread();
	    void lockThread();
	    void unlockThread();


		virtual void update();

		/**
		 * creates a new window to display a scene
		 *
		 * the globel scene of osgviz is always displayed addChild()
		 * you can also add scenes to a single window by using the returned id and
		 * getWindowManager()->getWindowByID(int id)->
		 *
		 * @param windowConfig
		 * @param graphicsContext
		 * @return
		 */
		unsigned int createWindow(WindowConfig windowConfig = WindowConfig(), osg::ref_ptr<osg::GraphicsContext> graphicsContext = NULL);

		void destroyWindow(unsigned int id);



		//inline GraphicsManagerInterface* getGraphicsManagerInterface(){
		//	return (GraphicsManagerInterface*)graphicsManager;
		//}

		template <class VIZPLUGIN> VIZPLUGIN* getVisualizerPlugin(std::string classname){
			VIZPLUGIN* viz = (VIZPLUGIN*)getVizPlugin(classname,classname);
			if (viz){
				viz->setRootNode(root);
				OsgVizPlugin* vizplug = (OsgVizPlugin*)viz;
				vizplug->init();
			}
			return viz;
		}

//		template <class VIZPLUGIN> VIZPLUGIN* getDataPlugin(std::string classname){
//			VIZPLUGIN* data = (VIZPLUGIN*)getVizPlugin(classname,classname);
//			data->init(m_argc,m_argv);
//
//			return data;
//		}

		/**
		 * root node is not set
		 */
		template <class VIZPLUGIN> VIZPLUGIN* getPlugin(std::string classname){
			VIZPLUGIN* data = (VIZPLUGIN*)loadPlugin(classname);
			return data;
		}

		OsgVizPlugin* loadPlugin(std::string classname);

		inline osg::ref_ptr<osg::Group> getRootNode(){
			return root;
		}


		inline void addChild(osg::Node * node){
			root->addChild(node);
		}

		inline void write(const char* name){
			Timing mtime;
			mtime.start();
			osgDB::writeNodeFile(*root, name);
			mtime.print_loop_time();
		}

		inline WindowManager* getWindowManager(){
			return windowManager.get();
		}


		private:

		OsgVizPlugin* getVizPlugin(std::string path, std::string name);

		bool createdOwnManager;

		osg::ref_ptr<osg::Group> root;


		private:
		bool initialized;
		std::vector< OsgVizPlugin* >loadedPlugins;

		int m_argc;
		char** m_argv;


		UpdateThread* thread;

		OpenThreads::Mutex* mutex;

		//graphics::GraphicsManager* graphicsManager;
		//osgViewer::Viewer viewer;
		//std::vector<osgViewer::Viewer *> viewers;

		osg::ref_ptr<WindowManager> windowManager;


	};




} // end namespace osgviz

#endif // _DUMMYPROJECT_DUMMY_HPP_
