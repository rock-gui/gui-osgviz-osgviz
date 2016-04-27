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
//#include "tools/Timing.h"
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
	     * @return the OsgViz instance
	     */
		static osg::ref_ptr<OsgViz> getInstance(int argc = 0,char** argv = NULL);

		/**
		 * In case the context where OsgViz is used is already using libmanager, it can be passed to
		 * the constructor in order not to use an own instance
		 * @param manager a LibManager instance
		 * @return the osgviz instance
		 */
		static osg::ref_ptr<OsgViz> getInstance(lib_manager::LibManager * manager);

		/**
		 * This method is meant for plugins to obtain the instance which is already loaded
		 * @return the OsgViz main
		 */
		static osg::ref_ptr<OsgViz> getExistingInstance();

		private:
		/**
		 * private constructor used by getInstance()
		 * @param argc
		 * @param argv
		 */
		OsgViz(int argc, char** argv);
		/**
		 * private constructor used by getInstance()
		 * @param manager
		 */
		OsgViz(lib_manager::LibManager * manager);

		/**
		 * init function with shared code for both constructors
		 * @param argc
		 * @param argv
		 */
		void init(int argc,char** argv);


		public:
		~OsgViz();

		/**
         * starts a thread calling the update() function.
         * @note This will also initialize the xlib threading (XInitThreads()). This will break
         *       when used together with qt or any other xlib based gui framework.
		 * @param microseconds number of microseconds to wait between the calls on update()
		 */
	    void startThread(int microseconds = 10000);
	    void stopThread();

	    /**
	     * tries to lock osgviz, no matter if threaded or not
	     * calls trylock on a OpenThreads::Mutex
	     * @return 0 if normal, -1 if errno set, errno code otherwise.
	     */
	    int tryLockThread();

	    /**
	     * lock osgviz, no matter if threaded or not
	     */
	    void lockThread();

	    /**
	     * unlock osgviz, no matter if threaded or not
	     */
	    void unlockThread();


	    /**
	     * render a new frame() in each window created by this instance
	     * automatically called if startThread() was called
	     */
		virtual void update();

		/**
		 * creates a new window to display a scene
		 *
		 * the globel scene of osgviz is always displayed addChild()
		 * you can also add scenes to a single window by using the returned id and
		 * getWindowManager()->getWindowByID(int id)
		 *
		 * @param windowConfig window configuration, if a graphicsContext is given only ViewConfig settings are applied
		 * @param graphicsContext set an external osg::GraphicsContext for example a osgQt::GraphicsWindowQt
		 * @return window id, which can be used to obtain a osgviz::Window pointer getWindowManager()->getWindowByID(id);
		 */
		unsigned int createWindow(WindowConfig windowConfig = WindowConfig(), osg::ref_ptr<osg::GraphicsContext> graphicsContext = NULL);

		/**
		 * removed a window
		 * @param id the id of the window to remove
		 */
        void destroyWindow(unsigned int id);


        /**
         * adds a callback which is called on each update() before the scened are rendered
         * @param callback pointer to the  Updatable to be called.
         * @param priority higher numbers are called first, if the priority is taken, the new one is placed after the existing
         * @return the actual priority number the Updatable aquired
         */
		virtual int addUpdateCallback(Updatable* callback, int priority = 0);


		/**
		 * Get a pointer to plugin, if the plugin is not already loaded, this function  also loads the plugin
		 * @param classname the plugin name, which in case of osgviz is also the libraries filename
		 * @return a plugin of the type of the class given by the templae or NULL, if the library does not exist.
		 */
		template <class PLUGINTYPE> PLUGINTYPE* getPlugin(std::string classname){
		    PLUGINTYPE* viz = (PLUGINTYPE*)getVizPlugin(classname,classname);
			return viz;
		}

		/**
		 * Generic plugin loader
		 * @param classname the plugin name, which in case of osgviz is also the libraries filename
		 * @return a valid OsgVizPlugin* id th plugin was found, NULL otherwise
		 */
		OsgVizPlugin* loadPlugin(std::string classname);


		/**
		 * return the osgviz globally shared scene
		 * This node is added by default in each window created
		 * If you want different contents, call osgviz::Window::getRootNode()
		 * @return the global root node
		 */
		inline osg::ref_ptr<osg::Group> getRootNode(){
			return root;
		}

		/**
		 * add a child to the globally shared scene
		 * these nodes are shared across all windows created
		 * If you want different contents, call osgviz::Window::getRootNode()
		 * @param node ht enode to add to the shared scene
		 */
		inline void addChild(osg::Node * node){
			root->addChild(node);
		}

		/**
		 * replace the shred scene
		 * @param node the node to replaced all previous objects
		 */
        inline void setScene(osg::Node * node){
            root->removeChildren(0,root->getNumChildren());
            root->addChild(node);
        }

        /**
         * get a child of the root node
         * @param index
         * @return
         */
        inline osg::Node* getChild(int index = 0){
            return root->getChild(index);
        }

        /**
         * save the (globally shared) scene displayed to a file
         * @param name
         */
		inline void write(const char* name){
			osgDB::writeNodeFile(*root, name);
		}

		/**
		 * get a pointer to the windowManager which gived access to single windows and their scenes
		 * @return the osgviz::WindowManager
		 */
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
