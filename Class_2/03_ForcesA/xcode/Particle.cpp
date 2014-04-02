//
//  Particle.cpp
//  Forces
//
//  Created by Nikolas Psaroudakis on 3/19/14.
//
//

#include "Particle.h"
#include "cinder/app/App.h"
Particle::Particle()
:mPosition(Vec2f::zero())
,mVelocity(Vec2f::zero())
,mAcceleration(Vec2f::zero())
,mRadius(5)
,mShowVelocity(false)
{
    
}

Particle::Particle(float radius)
:mPosition(Vec2f::zero())
,mVelocity(Vec2f::zero())
,mAcceleration(Vec2f::zero())
,mRadius(radius)
{

}
void Particle::setPosition(const Vec2f &pos)
{
    mPosition = pos;
}
Vec2f Particle::getPosition()
{
    return mPosition;
}
void Particle::setVelocity(const Vec2f& vel)
{
    mVelocity = vel;
}
Vec2f Particle::getVelocity()
{
    return mVelocity;
}

void Particle::setRadius(float radius )
{
    mRadius = radius;
}

void Particle::applyForce( const Vec2f& force)
{
    mAcceleration+=force;
}

void Particle::renderVelocity( bool shouldRender )
{
    mShowVelocity = shouldRender;
}
void Particle::update()
{
    //mVelocity = mVelocity + mAcceleration;
    mVelocity += mAcceleration;
    app::console() << "Velocity before: " << mVelocity << std::endl;
    mVelocity.limit(5);
    app::console() << "Velocity after: " << mVelocity << std::endl;
    mPosition+=mVelocity;

    //Set acceleration to zero
    mAcceleration *=0;
}

void Particle::draw()
{
    gl::color(Color::white());
    gl::drawSolidCircle(mPosition, mRadius);
    if ( mShowVelocity )
    {
        gl::color(Color(1,0,0));
        ci::Vec3f start = mPosition.xyx();
        ci::Vec3f end = start + 5*mVelocity.xyx();
        start.z = end.z = 0;
        gl::drawVector( start, end, 10, 3 );
    }
}