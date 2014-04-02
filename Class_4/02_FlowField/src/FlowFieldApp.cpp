#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"
#include "cinder/Perlin.h"
using namespace ci;
using namespace ci::app;
using namespace std;

class FlowFieldApp : public AppNative {
  public:
	void setup();
    void prepareSettings( Settings * settings);
    void keyDown(KeyEvent event);
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    
    Vec2f   getPerlin( const Vec2f& pos);
    void    reset();
    void    addParticleAtIndex( int idx );
    
    
    vector<Vec2f>   mPos;
    vector<int>     mAge;
    int             mMaxParticles = 10000;
    

    float s;
    int t, c;
    
    
    int mMaxAge = 50;
    int mOpacity = 40;
    float mSpeed = .2;
    float mZoom = .01;
    Perlin  mPerlin;
    bool clear = false;
};
void FlowFieldApp::keyDown(KeyEvent event)
{
    gl::clear(Color::white());
    mPerlin.setSeed(clock() & 65535 );
}
void FlowFieldApp::prepareSettings( Settings * settings)
{
    settings->setWindowSize(640, 480);
}

void FlowFieldApp::addParticleAtIndex(int idx)
{
    mPos[idx] = Vec2f(Rand::randInt(getWindowWidth()), Rand::randInt(getWindowHeight()));
    mAge[idx] = 0;
}

void FlowFieldApp::setup()
{
    gl::enableAlphaBlending();
    mPos.reserve(mMaxParticles);
    mAge.reserve(mMaxParticles);
    reset();
}
void FlowFieldApp::reset()
{
    gl::clear( Color::black() );
    s = mSpeed / mZoom;
    c = 0;
}
void FlowFieldApp::mouseDown( MouseEvent event )
{
    gl::clear(Color::black());
    mPerlin.setSeed(clock() & 65535 );
}

// noise based flow field
Vec2f FlowFieldApp::getPerlin(const Vec2f& pos )
{
    return Vec2f( mPerlin.noise(t, pos.x * mZoom, pos.y * mZoom)-.5, mPerlin.noise(t+1, pos.x * mZoom, pos.y * mZoom) - .5 );
}
void FlowFieldApp::update()
{
    // create new particles
    int np = mMaxParticles / mMaxAge;
    for(int i=0; i<np && c<mMaxParticles; i++, c++)
    {
        addParticleAtIndex(c);
    }
    // draw particle traces
    for(int i=0; i<c; i++)
    {
        mAge[i]++;
        if (mAge[i] > mMaxAge)
        {
            addParticleAtIndex(i);
        }
    }
}

void FlowFieldApp::draw()
{
    for(int i=0; i<c; i++)
    {
        Vec2f pos = mPos[i];
        Vec2f noise = getPerlin(mPos[i]);
        float mag = noise.length();
        if (mAge[i] <= mMaxAge)
        {
            float op = mag * 2 * mOpacity;
            op/=255;
            float h =  (atan2(noise.x, noise.y) + M_PI)/(2*M_PI);
            gl::color( ColorAf( CM_HSV, h, 1.0f, 0.8f, op/8.f ));
            gl::begin(GL_LINES);
            glVertex2f(mPos[i]);
            glVertex2f(mPos[i]+=s*noise);
            gl::end();
        }
    }
}

CINDER_APP_NATIVE( FlowFieldApp, RendererGl )
