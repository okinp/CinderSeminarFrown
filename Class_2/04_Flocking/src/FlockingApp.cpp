#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class FlockingApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    
};

void FlockingApp::setup()
{
    
}

void FlockingApp::mouseDown( MouseEvent event )
{
    
}

void FlockingApp::update()
{
    
}
void FlockingApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_NATIVE( FlockingApp, RendererGl )
