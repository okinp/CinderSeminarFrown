#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "Particle.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class ForcesApp : public AppNative {
  public:
	void        setup();
    void        keyDown( KeyEvent event );
	void        mouseDown( MouseEvent event );
    void        mouseMove( MouseEvent event );
	void        update();
	void        draw();
    Particle    mParticle;
    Vec2f       mMousePosition;
    bool        mShouldUpdate;
};

void ForcesApp::setup()
{
    mShouldUpdate = true;
}

void ForcesApp::keyDown(KeyEvent event)
{
    if ( event.getChar() == ' ' )
    {
        mShouldUpdate = !mShouldUpdate;
    }
}

void ForcesApp::mouseDown( MouseEvent event )
{
    
}
void ForcesApp::mouseMove( MouseEvent event )
{
    mMousePosition = event.getPos();
}

void ForcesApp::update()
{
    if ( !mShouldUpdate )
        return;
    ci::Vec2f mouseForce = mMousePosition - mParticle.getPosition();
    if ( mouseForce.length() > 5 )
    {
        mouseForce.safeNormalize();
        mouseForce*=2.2; //Some random scaling factor
        mParticle.applyForce(mouseForce);
    } else {
        mParticle.setVelocity(Vec2f::zero());
        mParticle.setPosition(mMousePosition);
    }
    mParticle.update();
}

void ForcesApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    mParticle.draw();
}

CINDER_APP_NATIVE( ForcesApp, RendererGl )
