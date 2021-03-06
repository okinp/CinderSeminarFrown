/**
 * Flocking
 * by Daniel Shiffman.
 *
 * An implementation of Craig Reynold's Boids program to simulate
 * the flocking behavior of birds. Each boid steers itself based on
 * rules of avoidance, alignment, and coherence.
 *
 * Click the mouse to add a new boid.
 *
 * Cinder port: Nikolas Psaroudakis
 *
 */

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "Flock.h"
#include "cinder/params/Params.h"

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace oem;
class FlockingApp : public AppNative {
  public:
	void setup();
    void keyDown( KeyEvent event);
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
  private:
    Flock mFlock;
    params::InterfaceGlRef mParams;
};

void FlockingApp::setup()
{
    for (int i = 0; i < 150; i++)
    {
        BoidRef b(new Boid(getWindowCenter()));
        mFlock.addBoid(b);
    }
    mParams = params::InterfaceGl::create( getWindow(), "App parameters", toPixels( Vec2i( 200, 100 ) ));
    mParams->addParam("Seperation", &Boid::seperationWeight, "min=0.00 max=25 step=0.25" );
    mParams->addParam("Alignment", &Boid::alignmentWeight,"min=0.00 max=25 step=0.25");
    mParams->addParam("Coherence", &Boid::coherenceWeight,"min=0.00 max=25 step=0.25");
}
void FlockingApp::keyDown( KeyEvent event)
{
//    if ( event.getChar() == ' ')
//    {
//        gl::clear( Color( 0, 0, 0 ) );
//    }
}
void FlockingApp::mouseDown( MouseEvent event )
{
    BoidRef b( new Boid(event.getPos()));
    mFlock.addBoid(b);
}

void FlockingApp::update()
{
    mFlock.run();
}

void FlockingApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    mFlock.render();
    mParams->draw();
}

CINDER_APP_NATIVE( FlockingApp, RendererGl )
