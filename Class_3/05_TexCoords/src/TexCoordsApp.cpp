#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Surface.h"
#include "cinder/gl/Texture.h"
using namespace ci;
using namespace ci::app;
using namespace std;
using namespace ci::gl;
class TexCoordsApp : public AppNative {
  public:
	void setup();
    void keyDown( KeyEvent event );
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    Surface mSurface;
    Texture mTexture;
    vector<Vec2i> mPoints;
};

void TexCoordsApp::setup()
{
    mSurface = loadImage(loadAsset("dog.jpg"));
    mTexture = Texture(mSurface);
}

void TexCoordsApp::keyDown(KeyEvent event)
{
    mPoints.clear();
}
void TexCoordsApp::mouseDown( MouseEvent event )
{
    
    if ( mPoints.size() >= 4 )
    {
        mPoints.clear();
    }
    
    mPoints.push_back(event.getPos());
}

void TexCoordsApp::update()
{
    
}

void TexCoordsApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    gl::color(Color(1.f,1.f,1.f));
    mTexture.enableAndBind();
    if ( mPoints.size() == 4 )
    {
        glBegin(GL_QUADS);
        glTexCoord2f(0.3, 0.3);
        glVertex2f(mPoints[0]);
        glTexCoord2f(1.5, 0.3);
        glVertex2f(mPoints[1]);
        glTexCoord2f(1.5, 1.5);
        glVertex2f(mPoints[2]);
        glTexCoord2f(0.3, 1.5);
        glVertex2f(mPoints[3]);
        glEnd();
    }
    
}

CINDER_APP_NATIVE( TexCoordsApp, RendererGl )
