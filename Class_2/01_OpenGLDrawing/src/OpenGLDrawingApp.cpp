#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/params/Params.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class OpenGLDrawingApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );
    void keyDown( KeyEvent event );
	void update();
	void draw();
private:
    vector<Vec3f>               mPoints;
    vector<Color>               mColors;
    int                         mPrimitive;
    params::InterfaceGlRef      mParams;
    Color                       mCurrentColor;
    void                        createCircle(const Vec3f& pos, float radius, uint numSegments);
};

void OpenGLDrawingApp::setup()
{
    mPrimitive = GL_POINTS;
    mCurrentColor = Color::white();
    mParams = params::InterfaceGl::create( getWindow(), "App parameters", toPixels( Vec2i( 200, 400 ) ) );
    mParams->addParam("Pixel Color", &mCurrentColor,"");
    mParams->addParam("OpenGL Primitive", &mPrimitive,"");
}

void OpenGLDrawingApp::mouseDown( MouseEvent event )
{
   // createCircle(Vec3f(event.getX(), event.getY(),0), 30, 50);
    mPoints.push_back(Vec3f(event.getX(), event.getY(),0));
    mColors.push_back(mCurrentColor);
}

void OpenGLDrawingApp::keyDown( KeyEvent event )
{
    if ( event.getChar() == ' ')
    {
        mPoints.clear();
        mColors.clear();
    }
}

void OpenGLDrawingApp::update()
{
    
}
void OpenGLDrawingApp::createCircle( const Vec3f& pos, float radius, uint numSegments )
{
    mPoints.clear();
    mColors.clear();
    for ( int i=0; i<numSegments; i++ )
    {
        float theta = i*2*M_PI/numSegments;
        float x = radius*cos(theta) + pos.x;
        float y = radius*sin(theta) + pos.y;
        mPoints.push_back(Vec3f(x,y,0));
        mColors.push_back(Color::white());
    }
}

void OpenGLDrawingApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    glBegin(mPrimitive);
    for ( int i=0; i< mPoints.size(); ++i )
    {
        //Cinder overload accepting a Vec3f
        glColor3f(mColors[i]);
        glVertex3f(mPoints[i]);
    }
    glEnd();
    // Draw the interface
	mParams->draw();
}

CINDER_APP_NATIVE( OpenGLDrawingApp, RendererGl )
