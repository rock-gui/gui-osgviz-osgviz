#ifndef _OSGVIZ_HPP_
#define _OSGVIZ_HPP_

#include <iostream>
#include <lib_manager/LibManager.hpp>
#include <osg/Group>
#include <osgViewer/Viewer>
#include <osgDB/WriteFile>
#include <OpenThreads/Thread>

//#include "graphics/interfaces/GraphicsManagerInterface.h"
#include "plugins/OsgVizPlugin.h"
#include "plugins/OsgVizVisualizerPlugin.h"
#include "windows/WindowManager.h"

#include "graphics/interfaces/data/GraphicData.h"


/*namespace osgviz {
	namespace graphics{
		class GraphicsManager;
	}
}*/

#include <stdio.h>

namespace osgviz
{


	class FrameUpdateThread;


	class OsgViz: public lib_manager::LibInterface
	{

		public: 

	    CREATE_MODULE_INFO();

		static OsgViz* getInstance(int argc = 0,char** argv = NULL);

		OsgViz(lib_manager::LibManager * manager);

		OsgViz(int argc, char** argv);

		~OsgViz();


		virtual const std::string getLibName() const;

	    virtual int getLibVersion() const;



	    void init(int argc,char** argv);

	    /**
	     * starts a thread calling updateContent
	     */
	    void startThread();
	    void stopThread();

	    void lockThread();
	    void unlockThread();


		void updateContent();

		int createWindow(interfaces::GraphicData graphicData = interfaces::GraphicData());
		void destroyWindow(int id);

		//inline GraphicsManagerInterface* getGraphicsManagerInterface(){
		//	return (GraphicsManagerInterface*)graphicsManager;
		//}



		template <class VIZPLUGIN> VIZPLUGIN* getVisualizerPlugin(std::string classname){
			VIZPLUGIN* viz = (VIZPLUGIN*)getVizPlugin(classname,classname);
			viz->setRootNode(root);
			OsgVizPlugin* vizplug = (OsgVizPlugin*)viz;
			vizplug->init();
			return viz;
		}

		template <class VIZPLUGIN> VIZPLUGIN* getDataPlugin(std::string classname){
			VIZPLUGIN* data = (VIZPLUGIN*)getVizPlugin(classname,classname);
			data->init(m_argc,m_argv);
			OsgVizPlugin* dataplug = (OsgVizPlugin*)data;
			data->init();
			return data;
		}


		inline osg::ref_ptr<osg::Group> getRootNode(){
			return root;
		}


		inline void addChild(osg::Node * node){
			root->addChild(node);
		}

		inline void write(const char* name){
			osgDB::writeNodeFile(*root, name);
		}

		inline WindowManager* getWindowManager(){
			return &windowManager;
		}


		private:

		OsgVizPlugin* getVizPlugin(std::string path, std::string name);

		bool createdOwnManager;
		lib_manager::LibManager *libmanager;

		osg::ref_ptr<osg::Group> root;


		private:
		bool initialized;
		std::vector< OsgVizPlugin* >loadedPlugins;

		int m_argc;
		char** m_argv;


		FrameUpdateThread* thread;
		//graphics::GraphicsManager* graphicsManager;
		//osgViewer::Viewer viewer;
		//std::vector<osgViewer::Viewer *> viewers;

		WindowManager windowManager;


	};

	class FrameUpdateThread : public OpenThreads::Thread
		{
		    public:

		FrameUpdateThread(OsgViz* osgviz):
		        	osgviz(osgviz){
		        	running = false;
		        }

		        ~FrameUpdateThread()
		        {
		            if (isRunning())
		            {
		                cancel();
		                join();
		            }
		        }

		        int cancel()
		        {
		        	mutex.lock();
		        	running = false;
		        	mutex.unlock();
		            return 0;
		        }

		        void run();

		        void lock(){
		        	mutex.lock();
		        }
		        void unlock(){
		        	mutex.unlock();
		        }

		    private:
		        bool running;
		        OsgViz* osgviz;
		        OpenThreads::Mutex mutex;

		};



} // end namespace osgviz

#endif // _DUMMYPROJECT_DUMMY_HPP_
