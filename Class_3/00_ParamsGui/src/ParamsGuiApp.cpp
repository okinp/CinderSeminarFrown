#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/params/Params.h"
#include "cinder/Utilities.h"
using namespace ci;
using namespace ci::app;
using namespace std;

class ParamsGuiApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
private:
    
    Color mColor;
    float mRadius;
    params::InterfaceGlRef mParams;
};

void ParamsGuiApp::setup()
{
    // Setup the parameters
	mParams = params::InterfaceGl::create( getWindow(), "App parameters", toPixels( Vec2i( 200, 400 ) ) );
    
	mParams->addParam( "Color", &mColor);
    mParams->addParam( "Radius", &mRadius, "min=0.1 max=200.5 step=0.5 keyIncr=z keyDecr=Z" );
    //Give some initial values
    mColor = Color::white();
    mRadius = 20;
}

void ParamsGuiApp::mouseDown( MouseEvent event )
{
    
}

void ParamsGuiApp::update()
{
    
}

void ParamsGuiApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    gl::color(mColor);
    gl::drawSolidCircle(getWindowCenter(), mRadius);
    mParams->draw();
    gl::drawString(toString(getAverageFps()), ci::Vec2f(0,300));
}

CINDER_APP_NATIVE( ParamsGuiApp, RendererGl )
