#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"
#include "cinder/Perlin.h"
#include "Particle.h"
using namespace ci;
using namespace ci::app;
using namespace std;

class FlowFieldApp : public AppNative {
public:
	void                prepareSettings( Settings * settings);
    void                setup();
	void                update();
	void                draw();
	void                mouseDown( MouseEvent event );
    void                keyDown(KeyEvent event);
    
private:
    void                reset();
    Vec2f               getPerlin( const Vec2f& pos);
    
    int                 mMaxParticles = 100000;
    int                 mMaxAge = 50;
    int                 mOpacity = 40;
    Perlin              mPerlin;
    vector<Particle>    mParticles;
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


void FlowFieldApp::setup()
{
    Particle p;
    mParticles = vector<Particle>(mMaxParticles, p );
    gl::enableAlphaBlending();
    for ( auto& particle : mParticles )
    {
        Vec2f pos( Rand::randInt(getWindowWidth())
                  ,Rand::randInt(getWindowHeight()) );
        particle.setPosition(pos);
    }
    reset();
}
void FlowFieldApp::reset()
{
    gl::clear( Color::black() );
}
void FlowFieldApp::mouseDown( MouseEvent event )
{
    gl::clear(Color::black());
    mPerlin.setSeed(clock() & 65535 );
}

Vec2f FlowFieldApp::getPerlin(const Vec2f& pos )
{
    float nz = mPerlin.noise(pos.x/getWindowWidth(),pos.y/getWindowHeight());
    return Vec2f( cos(2.f*M_PI*nz) -.5, sin(2.f*M_PI*nz) -.5);
}

void FlowFieldApp::update()
{
    //Update and count all active ones
    int count = 0;
    for ( auto& particle : mParticles )
    {
        if ( particle.isActive() )
        {
            Vec2f noise = getPerlin(particle.getPosition());
            float mag = noise.length();
            float op = mag * 2 * mOpacity;
            op/=255;
            float h =  (atan2(noise.x, noise.y) + M_PI)/(2*M_PI);
            particle.setColor(ColorAf( CM_HSV, h, 1.0f, 0.8f, op/8.f ));
            particle.setAcceleration(20*noise);
            particle.update();
            count++;
        }
    }
    //Start up to "needed" inactive ones
    int needed = 0.01*(mMaxParticles - count);
    for ( auto& particle : mParticles )
    {
        if ( needed == 0 )
            break;
        if ( !particle.isActive() )
        {
            particle.reset();
            Vec2f pos( Rand::randInt(getWindowWidth())
                      ,Rand::randInt(getWindowHeight()) );
            particle.setPosition(pos);
            needed--;
        }
    }
    
}

void FlowFieldApp::draw()
{
    gl::enableAlphaBlending();
    gl::begin(GL_LINES);
    for ( auto& particle : mParticles )
    {
        if ( !particle.isActive() )
            continue;
        gl::color( particle.getColor());
        glVertex2f(particle.getPreviousPosition());
        glVertex2f(particle.getPosition());
    }
    gl::end();
    gl::disableAlphaBlending();
}

CINDER_APP_NATIVE( FlowFieldApp, RendererGl )
