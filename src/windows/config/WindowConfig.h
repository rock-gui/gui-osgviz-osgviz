#ifndef OSGVIZ_WINDOW_CONFIG_H
#define OSGVIZ_WINDOW_CONFIG_H

#include <string>
#include <vector>
#include <osg/GraphicsContext>

namespace osgviz {

    class ViewConfig {
    public:
      ViewConfig(float posX = 0.0, float posY = 0.0, float width = 1.0, float height = 1.0) :
                posX(posX), posY(posY), width(width), height(height),
                clearColorRed(0.55),
                clearColorGreen(0.67),
                clearColorBlue(0.88),
                clearColorAlpha(1.0),
                handlesEvents(true) {};


      // TODO: add two possibilities for size: percentage and fix size 
      float posX;
      float posY;
      float width;
      float height;       

      float clearColorRed;
      float clearColorGreen;
      float clearColorBlue;
      float clearColorAlpha;      

      bool handlesEvents;
    };  

    class WindowConfig {
    public:
      WindowConfig() : title("osgviz"),
                      posX(20),
                      posY(20),      
                      width(720),
                      height(405),
                      fullScreen(false),
                      screenNumber(0) {};

      std::string title;

      int posX;
      int posY;
      int width;
      int height;

      bool fullScreen;     //!< if full screen is set to true:
                            //!< the window will take the size of the screen
                            //!< therefore the windowWidth, windowHeight, windowPosX and windowPosY will be ignored

      int screenNumber;

      std::vector<ViewConfig> viewsConfig;

      static osg::ref_ptr<osg::GraphicsContext::Traits> generateTraits(const WindowConfig& windowConfig){
        osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
        traits->readDISPLAY();
        traits->windowName = windowConfig.title;
        traits->supportsResize = true;
        traits->doubleBuffer = true;
        traits->sharedContext = 0;
        traits->screenNum = windowConfig.screenNumber;

        // full screen: the rendering window attributes according to current screen settings
        if (windowConfig.fullScreen == true) {
            unsigned int width = windowConfig.width;
            unsigned int height = windowConfig.height;

            osg::GraphicsContext::WindowingSystemInterface* wsi = osg::GraphicsContext::getWindowingSystemInterface();
            if (wsi){
                osg::GraphicsContext::ScreenIdentifier screenIdentifier = osg::GraphicsContext::ScreenIdentifier();
			    screenIdentifier.readDISPLAY();
                //readDisplay seems to overwrite screenNum
                screenIdentifier.screenNum = windowConfig.screenNumber;
                wsi->getScreenResolution( screenIdentifier, width, height );
            }

            traits->x = 0;
            traits->y = 0;
            traits->width = width;
            traits->height = height;
            traits->windowDecoration = false;
        }
        // user defined window: the size and position of the window are defined in graphicData
        else {
            traits->x = windowConfig.posX;
            traits->y = windowConfig.posY;
            traits->width = windowConfig.width;
            traits->height = windowConfig.height;
            traits->windowDecoration = true;
            traits->screenNum = windowConfig.screenNumber;
        }

        return traits;

    }

    };




} // end of namespace osgviz

#endif /* OSGVIZ_WINDOW_CONFIG_H */
