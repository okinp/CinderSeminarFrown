#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "Tail.h"
using namespace ci;
using namespace ci::app;
using namespace std;
using namespace oem;
class MouseTailApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );
    void mouseMove( MouseEvent event );
	void update();
	void draw();
    Tail mTail;
};

void MouseTailApp::setup()
{
    
}

void MouseTailApp::mouseDown( MouseEvent event )
{
}
void MouseTailApp::mouseMove( MouseEvent event )
{
    mTail.moveTo(Vec3f(event.getX(), event.getY(), 0));
}
void MouseTailApp::update()
{
}

void MouseTailApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    mTail.draw();
}

CINDER_APP_NATIVE( MouseTailApp, RendererGl )
