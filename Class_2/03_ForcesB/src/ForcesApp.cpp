#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"
#include "Particle.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class ForcesApp : public AppNative {
  public:
	void                    setup();
    void                    keyDown( KeyEvent event );
	void                    mouseDown( MouseEvent event );
    void                    mouseMove( MouseEvent event );
	void                    update();
	void                    draw();
  private:
    
    Vec2f                   mMousePosition;
    bool                    mShouldUpdate;
    vector<ParticleRef>     mParticles;
};

void ForcesApp::setup()
{
    mShouldUpdate = true;
    //mParticle.renderVelocity();
    gl::enableAlphaBlending();
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
    for ( int i=0; i<10; i++ )
    {
        ParticleRef p( new Particle() );
        p->setPosition(event.getPos());
        float mag = Rand::randFloat(5.f, 10.f);
        float angle = Rand::randFloat(M_PI_4, 3*M_PI_4);
        Vec2f vel = Vec2f(1,0);
        vel.rotate(-angle);
        vel*=mag;
        p->setVelocity(vel);
        mParticles.push_back(p);
    }
    console() << "There are: " << mParticles.size() << " particles." << endl;
}

void ForcesApp::mouseMove( MouseEvent event )
{
    mMousePosition = event.getPos();
}

void ForcesApp::update()
{
    if ( !mShouldUpdate )
        return;
    ci::Vec2f gravity = ci::Vec2f(0, 0.2);
    for ( int i=0; i< mParticles.size(); i++ )
    {
        mParticles[i]->applyForce(gravity);
        mParticles[i]->update();
    }
}

void ForcesApp::draw()
{

    //Draw a black rectangle that covers the window and has some transparency;
    //This is a super easy way to create a trails / motion blur effect
    gl::color(ColorAf(0,0,0,0.35));
    gl::drawSolidRect(getWindowBounds());
    //Set the color to white
    gl::color(1,1,1);
    //Draw the particles
    for ( int i=0; i< mParticles.size(); i++ )
    {
        mParticles[i]->draw();
    }

}

CINDER_APP_NATIVE( ForcesApp, RendererGl )
