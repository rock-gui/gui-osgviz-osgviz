#include <iostream>
#include <osgviz/OsgViz.hpp>

#include <unistd.h>//sleep

int main(int argc, char** argv)
{
	osgviz::OsgViz osgViz;


	osgViz.createWindow();

	while (true){
		sleep(1);
	}

	return 0;
}
