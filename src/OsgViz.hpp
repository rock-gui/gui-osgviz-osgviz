#ifndef _OSGVIZ_HPP_
#define _OSGVIZ_HPP_

#include <iostream>
#include <lib_manager/LibManager.hpp>
#include <osg/Group>
#include <osgViewer/Viewer>
#include <osgDB/WriteFile>

//#include "graphics/interfaces/GraphicsManagerInterface.h"
#include "plugins/OsgVizPlugin.h"
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


/**
 * @class OsgViz
 * This is the main class to 3d Visualisaztions, it uses the lib_manager::LibManager to load plugins
 * this allows to load plugins as shared so all plugins can access each other on the same instances
 * In case this is not wanted, the plugin should implement a "Factory"
 */
	class OsgViz: public Updatable, public osg::Referenced
	{

		public: 

	    /**
	     * This instance Methods should be called on normal main programs
	     * osgviz does not have any args, but they are forwarded to the plugins loaded by getPlugin()
	     * @param argc
	     * @param argv
	     * @return
	     */
		static osg::ref_ptr<OsgViz> getInstance(int argc = 0,char** argv = NULL);
		static osg::ref_ptr<OsgViz> getInstance(lib_manager::LibManager * manager);

		/**
		 * This methos is meant for plugins to obtain the instance which is already loaded
		 * @return the osgviz main
		 */
		static osg::ref_ptr<OsgViz> getExistingInstance();

		private:
		OsgViz(lib_manager::LibManager * manager);
		OsgViz(int argc, char** argv);

		public:
		~OsgViz();


	    void init(int argc,char** argv);

	    /**
	     * starts a thread calling update
	     */
	    void startThread();
	    void stopThread();

	    int tryLockThread();
	    void lockThread();
	    void unlockThread();


	    /**
	     *
	     */
		virtual void update();

		/**
		 * creates a new window to display a scene
		 *
		 * the globel scene of osgviz is always displayed addChild()
		 * you can also add scenes to a single window by using the returned id and
		 * getWindowManager()->getWindowByID(int id)->
		 *
		 * @param windowConfig window configuration, if a graphicsContext is given only ViewConfig settings are applied
		 * @param graphicsContext set an external osg::GraphicsContext for example a osgQt::GraphicsWindowQt
		 * @return
		 */
		unsigned int createWindow(WindowConfig windowConfig = WindowConfig(), osg::ref_ptr<osg::GraphicsContext> graphicsContext = NULL);
        void destroyWindow(unsigned int id);


		virtual int addUpdateCallback(Updatable* callback, int priority = 0);


		template <class PLUGINTYPE> PLUGINTYPE* getPlugin(std::string classname){
		    PLUGINTYPE* viz = (PLUGINTYPE*)getVizPlugin(classname,classname);
			return viz;
		}

		OsgVizPlugin* loadPlugin(std::string classname);

		inline osg::ref_ptr<osg::Group> getRootNode(){
			return root;
		}


		inline void addChild(osg::Node * node){
			root->addChild(node);
		}

        inline void setScene(osg::Node * node){
            root->removeChildren(0,root->getNumChildren());
            root->addChild(node);
        }

        inline osg::Node* getScene(int index = 0){
            return root->getChild(index);
        }

		inline void write(const char* name){
			osgDB::writeNodeFile(*root, name);
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

		lib_manager::LibManager * libManager;


		std::map<int, Updatable*> updateCallbacks;

	};




} // end namespace osgviz

#endif // _DUMMYPROJECT_DUMMY_HPP_
