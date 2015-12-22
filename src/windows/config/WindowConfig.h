#ifndef OSGVIZ_WINDOW_CONFIG_H
#define OSGVIZ_WINDOW_CONFIG_H

#include <string>
#include <vector>

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
      WindowConfig() : title("Env"), 
                      posX(0),
                      posY(0),      
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
    };




} // end of namespace osgviz

#endif /* OSGVIZ_WINDOW_CONFIG_H */
