#ifndef OSGVIZ_WINDOW_CONFIG_H
#define OSGVIZ_WINDOW_CONFIG_H

#include <string>

namespace osgviz {

    class WindowConfig {
    public:
      WindowConfig() : title("Env"), 
                      posX(0),
                      posY(0),      
                      width(720),
                      height(405),
                      fullScreen(false),
                      screenNumber(0),
                      dummyTwoViews(false) {};

      std::string title;

      int posX;
      int posY;
      int width;
      int height;

      bool fullScreen;     //!< if full screen is set to true:
                            //!< the window will take the size of the screen
                            //!< therefore the windowWidth, windowHeight, windowPosX and windowPosY will be ignored

      int screenNumber;

      bool dummyTwoViews;
    };


    class ViewConfig {
    public:
      ViewConfig(int posX, int posY, int width, int height) :
        posX(posX), posY(posY), width(width), height(height) {};

      ViewConfig(): ViewConfig(0, 0, -1 ,-1) {};

      int posX;
      int posY;
      int width;
      int height;       //!< if width or height are set to -1,
                        //!< than view will take the config (width and height) of window

    };

} // end of namespace osgviz

#endif /* OSGVIZ_WINDOW_CONFIG_H */
