#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/params/Params.h"
#include "cinder/gl/TextureFont.h"
#include "cinder/Utilities.h"
#include <sstream>
using namespace ci;
using namespace ci::app;
using namespace std;

class VectorsApp : public AppNative {
  public:
	void setup();
    void prepareSettings(Settings* settings);
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    Vec3f                   mVectorA;
    Vec3f                   mVectorB;
    Vec3f                   mVectorAdd;
    Vec3f                   mVectorSub;
    Vec3f                   mVectorCross;
    Vec3f                   mVectorNormalize;
    float                   mAngle;
    params::InterfaceGlRef  mParams;
    Font                    mFont;
};
void VectorsApp::prepareSettings(Settings* settings)
{


}
void VectorsApp::setup()
{
    gl::disableVerticalSync();
    mVectorA = Vec3f(100,15, 2);
    mVectorB = Vec3f(5,50, 2);
    mParams = params::InterfaceGl::create( getWindow(), "App parameters", toPixels( Vec2i( 200, 100 ) ));
    mParams->addParam("VectorA", &mVectorA, "");
    mParams->addParam("VectorB", &mVectorB);
    mFont = Font("Arial",30);
    gl::enableVerticalSync(false);
}

void VectorsApp::mouseDown( MouseEvent event )
{
}

void VectorsApp::update()
{
    mVectorAdd = mVectorA + mVectorB;
    mVectorSub = mVectorA - mVectorB;
    mVectorCross = mVectorA.cross(mVectorB);
    float dotProduct = mVectorA.dot(mVectorB);
    float magA = mVectorA.length();
    float magB = mVectorB.length();
    float cosAngle = dotProduct/magA / magB;
    mAngle = acos(cosAngle);
    mAngle = mAngle*180.f/M_PI;
}

void VectorsApp::draw()
{

//	// clear out the window with black
    gl::clear( Color( 0, 0, 0 ) );
    
    gl::pushMatrices();
    gl::translate(getWindowCenter());
    gl::color( Color(0,1,0));
    gl::drawVector(Vec3f::zero(), mVectorA, 10, 8);
    gl::color( Color(0,0,1));
    gl::drawVector(Vec3f::zero(), mVectorB, 10, 8);
    gl::color( Color(1,1,1));
    gl::drawVector(Vec3f::zero(), mVectorAdd,10,8 );
    gl::color( Color(1,0,0));
    gl::drawVector(Vec3f::zero(), mVectorCross,10,8 );
    gl::popMatrices();

    stringstream ss;
    ss << "The angle is: " ;
    ss << mAngle;
    gl::drawString( ss.str(), Vec2f( 10,  40 ), Color::white(), mFont);
//    gl::drawString( "Framerate: " + toString(getAverageFps()), Vec2f( 10.0f, 10.0f ));
    
    mParams->draw();
}

CINDER_APP_NATIVE( VectorsApp, RendererGl )
