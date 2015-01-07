#include "OsgViz.hpp"



namespace osgviz
{

OsgViz::OsgViz()
{
	root = new osg::Group();
}

void OsgViz::createWindow() {



	// For now, we can initialize with 'standard settings'
	// Standard settings include a standard keyboard mouse
	// interface as well as default drive, fly and trackball
	// motion models for updating the scene.

	viewer.setUpViewInWindow(0,0,640,480);


	//viewer.setUpViewer(osgViewer::Viewer::STANDARD_SETTINGS);

	// Next we will need to assign the scene graph we created
	// above to this viewer:

	viewer.setSceneData( root );

	// create the windows and start the required threads.

	viewer.run();

	// Enter the simulation loop. viewer.done() returns false
	// until the user presses the 'esc' key.
	// (This can be changed by adding your own keyboard/mouse
	// event handler or by changing the settings of the default
	// keyboard/mouse event handler)

//	while( !viewer.done() )
//	{
//	   // wait for all cull and draw threads to complete.
//
//	   //viewer.sync();
//
//	   // Initiate scene graph traversal to update nodes.
//	   // Animation nodes will require update. Additionally,
//	   // any node for which an 'update' callback has been
//	   // set up will also be updated. More information on
//	   // settting up callbacks to follow.
//
//	   //viewer.update();
//
//	   // initiate the cull and draw traversals of the scene.
//
//	   //viewer.frame();
//	}

}

bool OsgViz::loadPlugin() {
	return false;
}

}
