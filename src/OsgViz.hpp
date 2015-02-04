#ifndef _OSGVIZ_HPP_
#define _OSGVIZ_HPP_

#include <iostream>
#include <lib_manager/LibManager.hpp>
#include <osg/Group>
#include <osgViewer/Viewer>
#include <boost/thread/mutex.hpp>


#include "plugins/OsgVizPlugin.h"
#include "graphics/GraphicsManager.h"

#include <stdio.h>

namespace osgviz
{

class ViewerFrameThread : public OpenThreads::Thread
	{
	    public:

	        ViewerFrameThread(osgViewer::ViewerBase* viewerBase):
	            _viewerBase(viewerBase){

	        	if (!_viewerBase->isRealized()){
	        		_viewerBase->realize();
	        	}

	        }

	        ~ViewerFrameThread()
	        {
	            if (isRunning())
	            {
	                cancel();
	                join();
	            }
	        }

	        int cancel()
	        {
	            _viewerBase->setDone(true);
	            return 0;
	        }

	        void run()
	        {

	        	while (!_viewerBase->done()){
					mutex.lock();
					//int result = _viewerBase->run();
					_viewerBase->frame();
					mutex.unlock();
					//give others a chance to lock
					usleep(10000);
	        	}
	        }

	        void lock(){
	        	mutex.lock();
	        }
	        void unlock(){
	        	 mutex.unlock();
	        }

	    private:
	        osg::ref_ptr<osgViewer::ViewerBase> _viewerBase;
	        OpenThreads::Mutex mutex;

	};


	class OsgViz: public mars::graphics::GraphicsManager
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


		int createWindow(bool threaded = true);

		void destroyWindow(int id);


		void lockWindows();
		void unlockWindows();



		inline int getNumberOfWindows(){
			return numberOfWindows;
		}

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
		lib_manager::LibManager *libmanager;

		osg::ref_ptr<osg::Group> root;

		osgViewer::Viewer viewer;

		private:
		bool initialized;
		std::vector< OsgVizPlugin* >loadedPlugins;
		std::map< int, ViewerFrameThread* >threads;

		osg::ref_ptr<osgGA::CameraManipulator> cameraManipulator;
		int m_argc;
		char** m_argv;

		int numberOfWindows;


		//std::vector<osgViewer::Viewer *> viewers;

	};

} // end namespace osgviz

#endif // _DUMMYPROJECT_DUMMY_HPP_
