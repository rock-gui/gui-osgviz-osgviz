#include "OsgViz.hpp"

//#include "graphics/GraphicsManager.h"

#include <stdio.h>
#include <osgGA/TerrainManipulator>
#ifndef WIN32
	#include <X11/Xlib.h>
#endif
#include <osgDB/WriteFile>
#include <osgDB/Registry>

#include <osgText/Font>

#include "windows/WindowManager.h"
#include "tools/TypeNameDemangling.h"

namespace osgviz
{

std::map<std::string, Module*> OsgViz::modules;

osg::ref_ptr<OsgViz> OsgViz::getInstance(){
    
    //HACK to work around a static destruction order bug: default font needs to be initialized before
    //     OsgViz. Calling getDefaultFont() here ensures that the font is instanciated before 
    //     OsgViz and thus lives longer than OsgViz and can still be called during OsgViz destruction.
    osgText::Font::getDefaultFont();
    //NOTE it is important that instance is a local static variable because we need a way to 
    //     control static initialization/destruction order.
    //     If instance is global the static initialization order depends on the order in which 
    //     libraries are loaded which leads to strange crashes in combination with osg's own singletons
    static osg::ref_ptr<OsgViz> instance = new OsgViz();
    return instance;
}


OsgViz::OsgViz() : root(new osg::Group()), thread(NULL), mutex(new OpenThreads::Mutex()),
                    windowManager(new WindowManager())
{
    root->setName("OsgViz root");
}


OsgViz::~OsgViz(){

    for (std::map<std::string, Module*>::iterator it = modules.begin();it!=modules.end();it++){
        delete it->second;
    }

    delete mutex;
}

unsigned int OsgViz::createWindow(WindowConfig windowConfig, osg::ref_ptr<osg::GraphicsContext> graphicsContext) {
    unsigned int winID = windowManager->createWindow(windowConfig,NULL,graphicsContext);

    // all created windows will share the same osgviz scene
    windowManager->getWindowByID(winID)->addChild(root);

    return winID;

}

void OsgViz::destroyWindow(unsigned int id){
    windowManager->destroyWindow(id);
}

void OsgViz::update(){
    for (std::map<int, Updatable*>::reverse_iterator callback = updateCallbacks.rbegin(); callback != updateCallbacks.rend();++callback){
        callback->second->update();
    }

    mutex->lock();
    windowManager->frame();
    mutex->unlock();
}

int OsgViz::addUpdateCallback(Updatable* callback, int priority) {
    Updatable* existing = updateCallbacks[priority];
    while (existing){
        --priority;
        existing = updateCallbacks[priority];
    }
    updateCallbacks[priority] = callback;
    return priority;
}


void OsgViz::startThread(int microseconds){
    if (!thread){
        #ifndef WIN32
            XInitThreads();
        #endif
        thread = new UpdateThread(this, microseconds);
        thread->startThread();
    }else{
        fprintf(stderr,"thread already running\n");
    }
}

void OsgViz::stopThread(){
    if (thread){
        thread->cancel();
        delete thread;
    }
}


void OsgViz::lockThread(){
    if (thread){
        thread->lock();
    }else{
        mutex->lock();
    }
}

void OsgViz::unlockThread(){
    if (thread){
        thread->unlock();
    }else{
        mutex->unlock();
    }
}

int OsgViz::tryLockThread(){
    if (thread){
        return thread->trylock();
    }else{
        return mutex->trylock();
    }
    return -1;
}

void OsgViz::printModules(){
    for (std::map<std::string, Module*>::iterator it = modules.begin();it!=modules.end();it++){
        printf("%s : %s\n",it->first.c_str(),demangledTypeName(*(it->second)).c_str());
    }
}
}


