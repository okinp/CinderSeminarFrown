#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "Flock.h"
#include "cinder/params/Params.h"
using namespace ci;
using namespace ci::app;
using namespace std;
using namespace oem;
class SimpleTailsApp : public AppNative {
  public:
	void setup();
    void keyDown( KeyEvent event);
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
private:
    Flock   mFlock;
    float   mTransparency;
    params::InterfaceGlRef mParams;
};

void SimpleTailsApp::setup()
{
    mTransparency = 1;
    for (int i = 0; i < 150; i++)
    {
        BoidRef b(new Boid(getWindowCenter()));
        mFlock.addBoid(b);
    }
    mParams = params::InterfaceGl::create( getWindow(), "App parameters", toPixels( Vec2i( 200, 100 ) ));
    mParams->addParam("Seperation", &Boid::seperationWeight, "min=0.00 max=25 step=0.25" );
    mParams->addParam("Alignment", &Boid::alignmentWeight,"min=0.00 max=25 step=0.25");
    mParams->addParam("Coherence", &Boid::coherenceWeight,"min=0.00 max=25 step=0.25");
    mParams->addParam("Transparency", &mTransparency,"min=0.00 max=1 step=0.02");
}
void SimpleTailsApp::keyDown(KeyEvent event)
{
    if ( event.getChar() == ' ')
    {
        gl::clear( Color( 0, 0, 0 ) );
    }
}
void SimpleTailsApp::mouseDown( MouseEvent event )
{
    BoidRef b( new Boid(event.getPos()));
    mFlock.addBoid(b);
}

void SimpleTailsApp::update()
{
    mFlock.run();
}

void SimpleTailsApp::draw()
{
    gl::enableAlphaBlending();
    gl::color(ColorAf(0.,0.,0.,mTransparency));
    gl::drawSolidRect(getWindowBounds());
    gl::color(Color::white());
    mFlock.render();
    mParams->draw();
    gl::disableAlphaBlending();
}

CINDER_APP_NATIVE( SimpleTailsApp, RendererGl )
