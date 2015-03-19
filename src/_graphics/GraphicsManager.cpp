/*
 *  Copyright 2011, 2012 DFKI GmbH Robotics Innovation Center
 *
 *  This file is part of the MARS simulation framework.
 *
 *  MARS is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License
 *  as published by the Free Software Foundation, either version 3
 *  of the License, or (at your option) any later version.
 *
 *  MARS is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *   You should have received a copy of the GNU Lesser General Public License
 *   along with MARS.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/*
 *  GraphicsManager.cpp
 *  Simulator
 *
 *  Created by borchers on 27.05.08.
 */

#include "GraphicsManager.h"

#include <osgUtil/Optimizer>

#include <osgDB/WriteFile>
#include <osg/Fog>
#include <osg/LightModel>

#include <osgParticle/FireEffect>
#include <osgParticle/SmokeEffect>
#include <osgParticle/SmokeTrailEffect>
#include <osgParticle/FireEffect>



#include "wrapper/OSGLightStruct.h"
#include "wrapper/OSGMaterialStruct.h"
//#include "wrapper/OSGDrawItem.h"
//#include "wrapper/OSGHudElementStruct.h"
//#include "wrapper/OSGNodeStruct.h"

#include "GraphicsViewer.h"
//#include "HUD.h"



#include <iostream>
#include <cassert>
#include <stdexcept>
#include "GraphicsWindow.h"

#define SINGLE_THREADED

namespace osgviz {
  namespace graphics {

    using namespace std;

    using namespace interfaces;

    static int ReceivesShadowTraversalMask = 0xffff;
    static int CastsShadowTraversalMask = 0xffff;


    GraphicsManager::GraphicsManager(lib_manager::LibManager *theManager,
                                     void *myQTWidget):GraphicsManagerInterface(theManager),
        osgWidget(NULL),
        next_hud_id(1),
        next_draw_object_id(1),
        next_window_id(1),
        nextPreviewID(1),
        viewer(0),
        scene(new osg::Group),
        shadowedScene(new osgShadow::ShadowedScene),
        lightGroup(new osg::Group),
        globalStateset(new osg::StateSet),
        useFog(true),
        useNoise(false),
        drawLineLaser(false),
        ignore_next_resize(0),
        set_window_prop(0)

    {
      //osg::setNotifyLevel( osg::WARN );

      // first check if we have the cfg_manager lib

    	//      cfgW_top = cfg->getOrCreateProperty("Graphics", "window1Top", (int)40,
    	//                                          cfgClient);
    	//
    	//      cfgW_left = cfg->getOrCreateProperty("Graphics", "window1Left", (int)700,
    	//                                           cfgClient);
    	//
    	//      cfgW_width = cfg->getOrCreateProperty("Graphics", "window1Width", (int)720,
    	//                                            cfgClient);
    	//
    	//      cfgW_height = cfg->getOrCreateProperty("Graphics", "window1Height", (int)405,
    	//                                             cfgClient);
    	//
    	      draw_normals = false;
    	      drawRain = false;
    	      drawSnow = false;
    	      drawMainCamera = true;
    	      backfaceCulling = true;


      if(libManager == NULL) return;

    }

    GraphicsManager::~GraphicsManager() {
//      if(cfg) {
//        string saveFile = configPath.sValue;
//        saveFile.append("/mars_Graphics.yaml");
//        cfg->writeConfig(saveFile.c_str(), "Graphics");
//        libManager->releaseLibrary("cfg_manager");
//      }
      fprintf(stderr, "Delete mars_graphics\n");
    }

    void GraphicsManager::initializeOSG(void *data, bool createWindow) {
//      cfg = libManager->getLibraryAs<cfg_manager::CFGManagerInterface>("cfg_manager");
//      if(!cfg) {
//        fprintf(stderr, "******* mars_graphics: couldn't find cfg_manager\n");
//        return;
//      }
//
//      resources_path.propertyType = cfg_manager::stringProperty;
//      resources_path.propertyIndex = 0;
      //resources_path = MARS_GRAPHICS_DEFAULT_RESOURCES_PATH;

//      if(cfg) {


        // have to handle multisampling here

        multisamples = 0;
        setMultisampling(multisamples);

        useNoise = true;

        drawLineLaser = false;

        hudWidth = 1920;

        hudHeight = 1080;

        marsShadow = false;

        globalStateset->setGlobalDefaults();

      // with backface culling backfaces are not processed,
      // else front and back faces are always processed.
      // Its a good idea to turn this on for perfomance reasons,
      // 2D objects in 3D scene may want to overwrite this setting, or
      // walk through indices front to back and vice versa
      // to get two front faces.
      cull = new osg::CullFace();
      cull->setMode(osg::CullFace::BACK);

      { // setup LIGHT
        globalStateset->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);
        globalStateset->setMode(GL_LIGHTING, osg::StateAttribute::ON);

        globalStateset->setMode(GL_LIGHT0, osg::StateAttribute::OFF);
        globalStateset->setMode(GL_LIGHT1, osg::StateAttribute::OFF);
        globalStateset->setMode(GL_LIGHT2, osg::StateAttribute::OFF);
        globalStateset->setMode(GL_LIGHT3, osg::StateAttribute::OFF);
        globalStateset->setMode(GL_LIGHT4, osg::StateAttribute::OFF);
        globalStateset->setMode(GL_LIGHT5, osg::StateAttribute::OFF);
        globalStateset->setMode(GL_LIGHT6, osg::StateAttribute::OFF);
        globalStateset->setMode(GL_LIGHT7, osg::StateAttribute::OFF);
        globalStateset->setMode(GL_BLEND,osg::StateAttribute::OFF);
      }

      // background color for the scene
      graphicOptions.clearColor = Color(0.55, 0.67, 0.88, 1.0);

      { // setup FOG
        graphicOptions.fogColor = Color(0.2, 0.2, 0.2, 1.0);
        graphicOptions.fogEnabled = true;
        graphicOptions.fogDensity = 0.35;
        graphicOptions.fogStart = 10.0;
        graphicOptions.fogEnd = 30.0;

        osg::ref_ptr<osg::Fog> myFog = new osg::Fog;
        myFog->setMode(osg::Fog::LINEAR);
        myFog->setColor(graphicOptions.fogColor);
        myFog->setStart(graphicOptions.fogStart);
        myFog->setEnd(graphicOptions.fogEnd);
        myFog->setDensity(graphicOptions.fogDensity);
        globalStateset->setAttributeAndModes(myFog.get(), osg::StateAttribute::ON);
      }

      // some fixed function pipeline stuff...
      // i guess the default is smooth shading, that means
      // light influence is calculated per vertex and interpolated for fragments.
      osg::ref_ptr<osg::LightModel> myLightModel = new osg::LightModel;
      myLightModel->setTwoSided(false);
      globalStateset->setAttributeAndModes(myLightModel.get(), osg::StateAttribute::ON);

      // associate scene with global states
      scene->setStateSet(globalStateset.get());
      scene->addChild(lightGroup.get());
      scene->addChild(shadowedScene.get());

      // init light (osg can have only 8 lights enabled at a time)
      for (unsigned int i =0; i<8;i++) {
        lightmanager ltemp;
        ltemp.free=true;
        myLights.push_back(ltemp);
      }

      initDefaultLight();


      shadowedScene->setReceivesShadowTraversalMask(ReceivesShadowTraversalMask);
      shadowedScene->setCastsShadowTraversalMask(CastsShadowTraversalMask);
      {
#if USE_LSPSM_SHADOW
        osg::ref_ptr<osgShadow::LightSpacePerspectiveShadowMapDB> sm =
          new osgShadow::LightSpacePerspectiveShadowMapDB;

        //sm->setDebugDraw(true);
        sm->setMinLightMargin( 10.0f );
        sm->setMaxFarPlane( 0.0f );
        sm->setTextureSize( osg::Vec2s( 2028, 2028 ) );
        sm->setShadowTextureCoordIndex( 6 );
        sm->setShadowTextureUnit( 6 );

        shadowedScene->setShadowTechnique( sm.get() );
#elif USE_PSSM_SHADOW
        osg::ref_ptr<osgShadow::ParallelSplitShadowMap> pssm =
          new osgShadow::ParallelSplitShadowMap(NULL,NUM_PSSM_SPLITS);

        pssm->enableShadowGLSLFiltering(false);
        pssm->setTextureResolution(2048);
        pssm->setMinNearDistanceForSplits(0);
        pssm->setMaxFarDistance(100);
        pssm->setMoveVCamBehindRCamFactor(0);
        //pssm->setPolygonOffset(osg::Vec2(-1.0,-4.0));

        shadowedScene->setShadowTechnique(pssm.get());
#endif
        if(marsShadow) {
          shadowMap = new ShadowMap;
          shadowedScene->setShadowTechnique(shadowMap.get());
          //shadowMap->setTextureSize(osg::Vec2s(4096,4096));
          //shadowMap->setTextureUnit(2);
          //shadowMap->clearShaderList();
          //shadowMap->setAmbientBias(osg::Vec2(0.5f,0.5f));
          //shadowMap->setPolygonOffset(osg::Vec2(-1.2,-1.2));
        }
//      }

      // TODO: check this out:
      //   i guess fire.rgb is a 1D texture
      //   there is something to generate these in OGLE
      //osg::ref_ptr<osgParticle::ParticleEffect> effectNode =
      //new osgParticle::FireEffect;
      //effectNode->setTextureFileName("fire.rgb");
      //effectNode->setIntensity(2.5);
      //effectNode->setScale(4);
      //scene->addChild(effectNode.get());

//      grid = new GridPrimitive(osgWidget);
//      showCoords();

      // reset number of frames
      framecount = 0;

      if(createWindow) {
        viewer = new GraphicsViewer((GuiEventInterface*)this);
        viewer->setKeyEventSetsDone(0);
#ifdef SINGLE_THREADED
        viewer->setThreadingModel(osgViewer::CompositeViewer::SingleThreaded);
#else
        viewer->setThreadingModel(osgViewer::CompositeViewer::DrawThreadPerContext);
#endif
        int id = new3DWindow(data);
        osgWidget = (GraphicsWindow*)get3DWindow(id);
      }

      //guiHelper->setGraphicsWidget(graphicsWindows[0]);
      //setupCFG();

      if(backfaceCulling)
        globalStateset->setAttributeAndModes(cull, osg::StateAttribute::ON);
      else
        globalStateset->setAttributeAndModes(cull, osg::StateAttribute::OFF);
    }
}

//    void GraphicsManager::addGraphicsUpdateInterface(GraphicsUpdateInterface *g) {
//      graphicsUpdateObjects.push_back(g);
//    }
//
//    void GraphicsManager::removeGraphicsUpdateInterface(GraphicsUpdateInterface *g) {
//      std::list<interfaces::GraphicsUpdateInterface*>::iterator it;
//      it = find(graphicsUpdateObjects.begin(), graphicsUpdateObjects.end(), g);
//      if(it!=graphicsUpdateObjects.end()) {
//        graphicsUpdateObjects.erase(it);
//      }
//    }

    /**
     * sets the camera type
     * @param: type
     */
    void GraphicsManager::setCamera(int type){
      osgWidget->getCameraInterface()->setCamera(type);
    }

    /**
     * returns actual camera information
     */
    void GraphicsManager::getCameraInfo(cameraStruct *cs) const {
      osgWidget->getCameraInterface()->getCameraInfo(cs);
    }

    void* GraphicsManager::getScene() const {
      return (void*)scene.get();
    }

    void* GraphicsManager::getScene2() const {
      return (void*)dynamic_cast<osg::Node*>(shadowedScene.get());
    }

    void GraphicsManager::saveScene(const string &filename) const {
      osgDB::writeNodeFile(*(scene.get()), filename);
    }

    void GraphicsManager::exportScene(const string &filename) const {
      osgDB::writeNodeFile(*(scene.get()), filename.data());
    }

    void* GraphicsManager::getStateSet() const {
      return (void*)globalStateset.get();
    }



    const interfaces::GraphicData GraphicsManager::getGraphicOptions(void) const {
      return graphicOptions;
    }

//    void GraphicsManager::setGraphicOptions(const mars::interfaces::GraphicData &options) {
//      osg::Fog *myFog;
//
//      myFog = (osg::Fog*)globalStateset->getAttribute(osg::StateAttribute::FOG);
//
//      graphicOptions = options;
//      for(unsigned int i=0; i<graphicsWindows.size(); i++)
//        graphicsWindows[i]->setClearColor(graphicOptions.clearColor);
//
//      myFog->setColor(osg::Vec4(graphicOptions.fogColor.r,
//                                graphicOptions.fogColor.g,
//                                graphicOptions.fogColor.b, 1.0));
//      myFog->setStart(graphicOptions.fogStart);
//      myFog->setEnd(graphicOptions.fogEnd);
//      myFog->setDensity(graphicOptions.fogDensity);
//
//      if(graphicOptions.fogEnabled) {
//        globalStateset->setMode(GL_FOG, osg::StateAttribute::ON);
//        useFog = true;
//      }
//      else {
//        globalStateset->setMode(GL_FOG, osg::StateAttribute::OFF);
//        useFog = false;
//      }
//
//      map<unsigned long, osg::ref_ptr<OSGNodeStruct> >::iterator iter;
//
//      for(iter=drawObjects_.begin(); iter!=drawObjects_.end(); ++iter)
//        iter->second->object()->setUseFog(useFog);
//
//    }

    void GraphicsManager::setWidget(GraphicsWindow *widget) {
      //guiHelper->setGraphicsWidget(widget);
    }


    unsigned long GraphicsManager::new3DWindow(void *myQTWidget, bool rtt,
                                               int width, int height, const std::string &name) {
      GraphicsWindow *gw;

//      if (graphicsWindows.size() > 0) {
//        gw = QtOsgMixGraphicsWidget::createInstance(myQTWidget, scene.get(),
//                                                    next_window_id++, rtt,
//                                                    0, this);
//        gw->initializeOSG(myQTWidget, graphicsWindows[0], width, height);
//      }
//      else {
//
//        gw = QtOsgMixGraphicsWidget::createInstance(myQTWidget, scene.get(),
//                                                    next_window_id++, 0,
//                                                    0, this);
//
        // this will open an osg widget without qt wrapping
        
        gw = new GraphicsWindow(myQTWidget, scene.get(),next_window_id++, 0, 0, this);
        gw->initializeOSG(myQTWidget, 0, width, height);
//      }

      gw->setName(name);
      gw->setClearColor(graphicOptions.clearColor);
      viewer->addView(gw->getView());
      graphicsWindows.push_back(gw);

      if(!rtt) {
        gw->setGraphicsEventHandler((GraphicsEventInterface*)this);


        // iterator over hudElements

//        for(HUDElements::iterator iter = hudElements.begin();
//            iter != hudElements.end(); iter++)
//          gw->addHUDElement((*iter)->getHUDElement());

      }
      return next_window_id - 1;
    }

    void* GraphicsManager::getView(unsigned long id){

      GraphicsWindow* gw=getGraphicsWindow(id);

      if(gw == NULL){
        return gw;
      }
      return (void*) gw->getView();
    }

    void GraphicsManager::deactivate3DWindow(unsigned long id) {

      GraphicsWindow* gw=getGraphicsWindow(id);

      if(gw == NULL){
        return;
      }
      //viewer->removeView(gw->getView());
      gw->getCameraInterface()->deactivateCam();
    }

    void GraphicsManager::activate3DWindow(unsigned long id) {

      GraphicsWindow* gw=getGraphicsWindow(id);

      if(gw == NULL){
        return;
      }
      gw->getCameraInterface()->activateCam();
    }

    GraphicsWindowInterface* GraphicsManager::get3DWindow(unsigned long id) const {
      std::vector<GraphicsWindow*>::const_iterator iter;

      for(iter=graphicsWindows.begin(); iter!=graphicsWindows.end(); iter++) {
        if((*iter)->getID() == id) {
          return (GraphicsWindowInterface*)(*iter);
        }
      }
      return 0;
    }

    GraphicsWindowInterface* GraphicsManager::get3DWindow(const std::string &name) const {
      std::vector<GraphicsWindow*>::const_iterator iter;

      for(iter=graphicsWindows.begin(); iter!=graphicsWindows.end(); iter++) {
        if((*iter)->getName().compare(name) == 0) {
          return (GraphicsWindowInterface*)(*iter);
        }
      }
      return 0;
    }


    void GraphicsManager::remove3DWindow(unsigned long id) {
      std::vector<GraphicsWindow*>::iterator iter;

      for(iter=graphicsWindows.begin(); iter!=graphicsWindows.end(); iter++) {
        if((*iter)->getID() == id) {
          delete (*iter);
          break;
        }
      }
    }

    void GraphicsManager::removeGraphicsWidget(unsigned long id) {
      std::vector<GraphicsWindow*>::iterator iter;

      for(iter=graphicsWindows.begin(); iter!=graphicsWindows.end(); iter++) {
        if((*iter)->getID() == id) {
          viewer->removeView((*iter)->getView());
          graphicsWindows.erase(iter);
          break;
        }
      }
    }


    GraphicsWindow* GraphicsManager::getGraphicsWindow(unsigned long id) const {
      std::vector<GraphicsWindow*>::const_iterator iter;

      for(iter=graphicsWindows.begin(); iter!=graphicsWindows.end(); iter++) {
        if((*iter)->getID() == id) {
          return *iter;
        }
      }
      return 0;
    }

    void GraphicsManager::getList3DWindowIDs(std::vector<unsigned long> *ids) const {
      std::vector<GraphicsWindow*>::const_iterator iter;

      for(iter=graphicsWindows.begin(); iter!=graphicsWindows.end(); iter++) {
        ids->push_back((*iter)->getID());
      }
    }

    void GraphicsManager::draw() {
      std::list<GraphicsUpdateInterface*>::iterator it;
      std::vector<GraphicsWindow*>::iterator iter;

      for(it=graphicsUpdateObjects.begin();
          it!=graphicsUpdateObjects.end(); ++it) {
        (*it)->preGraphicsUpdate();
      }

      //TODO
        // object -> update();
      for(iter=graphicsWindows.begin(); iter!=graphicsWindows.end(); iter++) {
        (*iter)->updateView();
      }

      // Render a complete new frame.
      if(viewer) viewer->frame();
      ++framecount;
      for(it=graphicsUpdateObjects.begin();
          it!=graphicsUpdateObjects.end(); ++it) {
        (*it)->postGraphicsUpdate();
      }
    }

    void GraphicsManager::setGrabFrames(bool value) {
      graphicsWindows[0]->setGrabFrames(value);
      graphicsWindows[0]->setSaveFrames(value);
    }

    void GraphicsManager::setActiveWindow(unsigned long win_id) {
      get3DWindow(win_id)->grabFocus();
    }

    void* GraphicsManager::getQTWidget(unsigned long id) const {
      std::vector<GraphicsWindow*>::const_iterator iter;

      for (iter = graphicsWindows.begin(); iter != graphicsWindows.end(); iter++) {
        if ((*iter)->getID() == id) {
          return (*iter)->getWidget();
        }
      }
      return 0;
    }

    void GraphicsManager::showQTWidget(unsigned long id) {
      std::vector<GraphicsWindow*>::iterator iter;

      for(iter=graphicsWindows.begin(); iter!=graphicsWindows.end(); iter++) {
        if((*iter)->getID() == id) {
          (*iter)->showWidget();
        }
      }
    }

    void GraphicsManager::setGraphicsWindowGeometry(unsigned long id,
                                                    int top, int left,
                                                    int width, int height) {
      std::vector<GraphicsWindow*>::iterator iter;

      for(iter=graphicsWindows.begin(); iter!=graphicsWindows.end(); iter++) {
        if((*iter)->getID() == id) {
          (*iter)->setWGeometry(top, left, width, height);
        }
      }
    }

    void GraphicsManager::getGraphicsWindowGeometry(unsigned long id,
                                                    int *top, int *left,
                                                    int *width, int *height) const {
      std::vector<GraphicsWindow*>::const_iterator iter;

      for(iter=graphicsWindows.begin(); iter!=graphicsWindows.end(); iter++) {
        if((*iter)->getID() == id) {
          (*iter)->getWGeometry(top, left, width, height);
        }
      }
    }

    ////// DRAWOBJECTS

    unsigned long GraphicsManager::findCoreObject(unsigned long draw_id) const {
      map<unsigned long int, unsigned long int>::const_iterator it;
      it = DrawCoreIds.find(draw_id);
      if (it == DrawCoreIds.end())
        return 0;
      else
        return it->second;
    }




    ///// DEFAULT 3D OBJECTS


    ///// PREVIEW NODES


    ////// EVENTS

    void GraphicsManager::addGuiEventHandler(GuiEventInterface *_guiEventHandler) {
      std::vector<GuiEventInterface*>::iterator iter;
      bool found = false;

      for (iter = guiHandlerList.begin(); iter != guiHandlerList.end(); ++iter) {
        if((*iter) == _guiEventHandler) {
          found = true;
          break;
        }
      }
      if (!found) {
        guiHandlerList.push_back(_guiEventHandler);
      }
    }

    void GraphicsManager::removeGuiEventHandler(GuiEventInterface *_guiEventHandler) {
      std::vector<GuiEventInterface*>::iterator iter;

      for (iter = guiHandlerList.begin(); iter != guiHandlerList.end(); ++iter) {
        if ((*iter) == _guiEventHandler) {
          guiHandlerList.erase(iter);
          break;
        }
      }
    }

    void GraphicsManager::emitKeyDownEvent(int key, unsigned int modKey,
                                           unsigned long win_id) {
      std::vector<GuiEventInterface*>::iterator iter;

      for (iter = guiHandlerList.begin(); iter != guiHandlerList.end(); ++iter) {
        (*iter)->keyDownEvent(key, modKey, win_id);
      }
    }

    void GraphicsManager::emitKeyUpEvent(int key, unsigned int modKey,
                                         unsigned long win_id) {
      std::vector<GuiEventInterface*>::iterator iter;

      for (iter = guiHandlerList.begin(); iter != guiHandlerList.end(); ++iter) {
        (*iter)->keyUpEvent(key, modKey, win_id);
      }
    }

    void GraphicsManager::emitQuitEvent(unsigned long win_id) {
      if(win_id < 1) return;

      std::vector<GuiEventInterface*>::iterator iter;

      for (iter = guiHandlerList.begin(); iter != guiHandlerList.end(); ++iter) {
        (*iter)->quitEvent(win_id);
      }
    }

    void GraphicsManager::emitSetAppActive(unsigned long win_id) {
      if(win_id < 1) return;

      std::vector<GuiEventInterface*>::iterator iter;

      for (iter = guiHandlerList.begin(); iter != guiHandlerList.end(); ++iter) {
        (*iter)->setAppActive(win_id);
      }
    }

    void GraphicsManager::addEventClient(GraphicsEventClient* theClient) {
      std::vector<GraphicsEventClient*>::iterator iter;

      for(iter=graphicsEventClientList.begin();
          iter!=graphicsEventClientList.end();
          ++iter) {
        if(*iter == theClient) return;
      }
      graphicsEventClientList.push_back(theClient);
    }

    void GraphicsManager::removeEventClient(GraphicsEventClient* theClient) {
      std::vector<GraphicsEventClient*>::iterator iter;

      for(iter=graphicsEventClientList.begin();
          iter!=graphicsEventClientList.end();
          ++iter) {
        if(*iter == theClient) {
          graphicsEventClientList.erase(iter);
          return;
        }
      }
    }

//    void GraphicsManager::emitNodeSelectionChange(unsigned long win_id, int mode) {
//      if(win_id < 1 || mode == 0) return;
//      std::vector<GraphicsEventClient*>::iterator jter;
//
//      GraphicsWindow* gw = getGraphicsWindow(win_id);
//
//      std::vector<osg::Node*> selectednodes = gw->getPickedObjects();
//      if(selectednodes.empty()) return;
//
//      DrawObjectList::iterator drawListIt;
//      DrawObjects::iterator drawIt;
//      std::vector<osg::Node*>::iterator nodeit;
//
//      bool selection = true;
//
//      switch(mode) {
//      case 0:
//        break;
//        // Pickmode STANDARD
//      case 1:
//        /* Before attempting to add the object as newly selected, check
//         *  if already selected. If yes, remove it from the list.
//         */
//        if(!selectedObjects_.empty()) {
//          // scan for objects to potentially remove
//          for(nodeit=selectednodes.begin(); nodeit!=selectednodes.end(); ++nodeit) {
//            // and try to find them in the list of already selected objects
//            for(drawListIt=selectedObjects_.begin(); drawListIt!=selectedObjects_.end();
//                ++drawListIt) {
//              /* In case we find the object, we have to remove the object
//               *  from the list of selected objects
//               */
//              if((*drawListIt)->object()->containsNode((*nodeit))) {
//
//                for(jter=graphicsEventClientList.begin();
//                    jter!=graphicsEventClientList.end();
//                    ++jter)
//                  (*jter)->selectEvent(findCoreObject((*drawListIt)->object()->getID()), false);
//
//                (*drawListIt)->object()->setSelected(false);
//                selectedObjects_.erase(drawListIt);
//
//                selection = false;
//
//                if(selectedObjects_.empty())
//                  break;
//                else
//                  drawListIt = selectedObjects_.begin();
//
//              }
//            }
//            /* in case we previously erased all objects from the selectedobjects
//             *  list, we want to stop searching
//             */
//            if(selectedObjects_.empty())
//              break;
//          }
//        }
//        /* If we didn't find our picked objects in the list of selected
//         * objects, we can add them to our selections - if they are valid,
//         * of course.
//         */
//        if(selection) {
//          // scan for objects to potentially add
//          for(nodeit=selectednodes.begin(); nodeit!=selectednodes.end(); ++nodeit) {
//            // and try to verify their existance as drawobject
//            for(drawIt=drawObjects_.begin(); drawIt!=drawObjects_.end(); ++drawIt) {
//              /* In case we find the corresponding drawobject, we have to:
//               * add them to the list of selected objects.
//               */
//              if(drawIt->second->object()->containsNode((*nodeit))) {
//                drawIt->second->object()->setSelected(true);
//                selectedObjects_.push_back(drawIt->second.get());
//
//                for(jter=graphicsEventClientList.begin();
//                    jter!=graphicsEventClientList.end();
//                    ++jter)
//                  (*jter)->selectEvent(findCoreObject(drawIt->second->object()->getID()), true);
//
//                // increase nodeit to make sure we do not add this node again.
//                //nodeit++;
//                break;
//              }
//            }
//            // nothing more to add? Fine, let's stop!
//            if(nodeit == selectednodes.end())
//              break;
//          }
//        }
//        break;
//
//        // Pickmode FORCE_ADD
//      case 2:
//        break;
//
//        // Pickmode FORCE_REMOVE
//      case 3:
//        break;
//      }
//
//      gw->clearSelectionVectors();
//
//    }

    void GraphicsManager::showRain(bool val) {
      if(val) {
        rain = new osgParticle::PrecipitationEffect;
        rain->setWind(osg::Vec3(1, 0, 0));
        rain->setParticleSpeed(0.4);
        rain->rain(0.6); // alternatively, use rain
        scene->addChild(rain.get());
      } else {
        scene->removeChild(rain.get());
      }
    }

    void GraphicsManager::showSnow(bool val) {
      if(val) {
        snow = new osgParticle::PrecipitationEffect;
        snow->setWind(osg::Vec3(1, 0, 0));
        snow->setParticleSpeed(0.4);
        snow->snow(0.4); // alternatively, use rain
        scene->addChild(snow.get());
      } else {
        scene->removeChild(snow.get());
      }
    }

//    void GraphicsManager::setupCFG(void) {
//      cfg_manager::CFGClient* cfgClient = dynamic_cast<cfg_manager::CFGClient*>(this);
//      cfgW_top = cfg->getOrCreateProperty("Graphics", "window1Top", (int)40,
//                                          cfgClient);
//
//      cfgW_left = cfg->getOrCreateProperty("Graphics", "window1Left", (int)700,
//                                           cfgClient);
//
//      cfgW_width = cfg->getOrCreateProperty("Graphics", "window1Width", (int)720,
//                                            cfgClient);
//
//      cfgW_height = cfg->getOrCreateProperty("Graphics", "window1Height", (int)405,
//                                             cfgClient);
//
//      draw_normals = cfg->getOrCreateProperty("Graphics", "draw normals", false,
//                                              cfgClient);
//
//      brightness = cfg->getOrCreateProperty("Graphics", "brightness", 1.0,
//                                            cfgClient);
//
//      grab_frames = cfg->getOrCreateProperty("Graphics", "make movie", false,
//                                             cfgClient);
//
//      marsShader = cfg->getOrCreateProperty("Graphics", "marsShader", true,
//                                            cfgClient);
//
//      drawRain = cfg->getOrCreateProperty("Graphics", "drawRain", false,
//                                          cfgClient);
//
//      drawSnow = cfg->getOrCreateProperty("Graphics", "drawSnow", false,
//                                          cfgClient);
//
//      drawMainCamera = cfg->getOrCreateProperty("Graphics", "drawMainCamera", true,
//                                          cfgClient);
//
//      backfaceCulling = cfg->getOrCreateProperty("Graphics", "backfaceCulling",
//                                                 true, cfgClient);
//
//      setGraphicsWindowGeometry(1, cfgW_top.iValue, cfgW_left.iValue,
//                                cfgW_width.iValue, cfgW_height.iValue);
//      if(drawRain.bValue) showRain(true);
//      if(drawSnow.bValue) showSnow(true);
//      if(!drawMainCamera.bValue){
//            deactivate3DWindow(1);
//      }
//
//    }

//    void GraphicsManager::cfgUpdateProperty(cfg_manager::cfgPropertyStruct _property) {
//      bool change_view = 0;
//
//      if(set_window_prop) return;
//
//      if(_property.paramId == cfgW_top.paramId) {
//        cfgW_top.iValue = _property.iValue;
//        change_view = 1;
//      }
//
//      else if(_property.paramId == cfgW_left.paramId) {
//        cfgW_left.iValue = _property.iValue;
//        change_view = 1;
//      }
//
//      else if(_property.paramId == cfgW_width.paramId) {
//        cfgW_width.iValue = _property.iValue;
//        change_view = 1;
//      }
//
//      else if(_property.paramId == cfgW_height.paramId) {
//        cfgW_height.iValue = _property.iValue;
//        change_view = 1;
//      }
//
//      if(change_view) {
//        // we get four callback on the resize that we want to ignore
//#ifdef QT_OSG_MIX
//        ignore_next_resize += 1;
//#else
//        ignore_next_resize += 4;
//#endif
//        setGraphicsWindowGeometry(1, cfgW_top.iValue, cfgW_left.iValue,
//                                  cfgW_width.iValue, cfgW_height.iValue);
//        return;
//      }
//
//      if(_property.paramId == draw_normals.paramId) {
//        showNormals(_property.bValue);
//        return;
//      }
//
//      if(_property.paramId == drawRain.paramId) {
//        showRain(_property.bValue);
//        return;
//      }
//
//      if(_property.paramId == drawSnow.paramId) {
//        showSnow(_property.bValue);
//        return;
//      }
//
//      if(_property.paramId == drawMainCamera.paramId) {
//          drawMainCamera.bValue = _property.bValue;
//        if(drawMainCamera.bValue){
//            activate3DWindow(1);
//        }else{
//            deactivate3DWindow(1);
//        }
//        return;
//      }
//
//      if(_property.paramId == multisamples.paramId) {
//        setMultisampling(_property.iValue);
//        return;
//      }
//
//      if(_property.paramId == noiseProp.paramId) {
//        useNoise = noiseProp.bValue = _property.bValue;
//        return;
//      }
//
//      if(_property.paramId == drawLineLaserProp.paramId) {
//        drawLineLaser = drawLineLaserProp.bValue = _property.bValue;
//        return;
//      }
//
//      if(_property.paramId == brightness.paramId) {
//        setBrightness(_property.dValue);
//        return;
//      }
//
//      if(_property.paramId == marsShader.paramId) {
//        setUseShader(_property.bValue);
//        return;
//      }
//
//      if(_property.paramId == backfaceCulling.paramId) {
//        if((backfaceCulling.bValue = _property.bValue))
//          globalStateset->setAttributeAndModes(cull, osg::StateAttribute::ON);
//        else
//          globalStateset->setAttributeAndModes(cull, osg::StateAttribute::OFF);
//        return;
//      }
//
//      if(_property.paramId == grab_frames.paramId) {
//        setGrabFrames(_property.bValue);
//        return;
//      }
//    }

//    void GraphicsManager::emitGeometryChange(unsigned long win_id, int left,
//                                             int top, int width, int height) {
//
//      bool update_cfg = false;
//      if(win_id==1) {
//        if(ignore_next_resize>0) {
//          --ignore_next_resize;
//          return;
//        }
//
//        if(top != cfgW_top.iValue) {
//          cfgW_top.iValue = top;
//          update_cfg = true;
//        }
//        if(left != cfgW_left.iValue) {
//          cfgW_left.iValue = left;
//          update_cfg = true;
//        }
//        if(width != cfgW_width.iValue) {
//          cfgW_width.iValue = width;
//          update_cfg = true;
//        }
//        if(height != cfgW_height.iValue) {
//          cfgW_height.iValue = height;
//          update_cfg = true;
//        }
//        if(update_cfg && cfg) {
//          set_window_prop = true;
//          cfg->setProperty(cfgW_top);
//          cfg->setProperty(cfgW_left);
//          cfg->setProperty(cfgW_width);
//          cfg->setProperty(cfgW_height);
//          set_window_prop = false;
//        }
//      }
//    }

    void GraphicsManager::setMultisampling(int num_samples) {
      //Antialiasing
      if(num_samples < 0) {
        printf("\"num multisamples\" have to be a positiv number!");
        num_samples = 0;
      }
      osg::DisplaySettings::instance()->setNumMultiSamples(num_samples);
    }


    void GraphicsManager::initDefaultLight() {
      defaultLight.lStruct.pos = Vector(0.0, 0.0, 10.0);
      defaultLight.lStruct.ambient = Color(0.0, 0.0, 0.0, 1.0);
      defaultLight.lStruct.diffuse = Color(1.0, 1.0, 1.0, 1.0);
      defaultLight.lStruct.specular = Color(1.0, 1.0, 1.0, 1.0);
      defaultLight.lStruct.constantAttenuation = 0.0;
      defaultLight.lStruct.linearAttenuation = 0.0;
      defaultLight.lStruct.quadraticAttenuation = 0.00001;
      defaultLight.lStruct.directional = false;
      defaultLight.lStruct.type = OMNILIGHT;
      defaultLight.lStruct.index = 0;
      defaultLight.lStruct.angle = 0;
      defaultLight.lStruct.exponent = 0;

      osg::ref_ptr<osg::LightSource> myLightSource = new OSGLightStruct(defaultLight.lStruct);

      //add to lightmanager for later editing possibility
      defaultLight.light = myLightSource->getLight();
      defaultLight.lightSource = myLightSource;
      defaultLight.free = false;

      lightGroup->addChild( myLightSource.get() );
      globalStateset->setMode(GL_LIGHT0, osg::StateAttribute::ON);
      myLightSource->setStateSetModes(*globalStateset, osg::StateAttribute::ON);
    }

    void*  GraphicsManager::getWindowManager(int id){


      GraphicsWindow* gw=getGraphicsWindow(id);

      if(gw == NULL){
        std::cerr<<"window does not exist!"<<std::endl;
        return gw;
      }
      return (void*) gw->getOrCreateWindowManager();

    }



//    interfaces::LoadMeshInterface* GraphicsManager::getLoadMeshInterface(void) {
//      return guiHelper;
//    }
//
//    interfaces::LoadHeightmapInterface* GraphicsManager::getLoadHeightmapInterface(void) {
//      return guiHelper;
//    }



    void GraphicsManager::addOSGNode(void* node) {
      scene->addChild((osg::Node*)node);
    }

    void GraphicsManager::removeOSGNode(void* node) {
      scene->removeChild((osg::Node*)node);
    }


  } // end of namespace graphics
} // end of namespace mars

