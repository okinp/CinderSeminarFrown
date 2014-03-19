//
//  Particle.cpp
//  Forces
//
//  Created by Nikolas Psaroudakis on 3/19/14.
//
//

#include "Particle.h"

Particle::Particle()
:mPosition(Vec2f::zero())
,mVelocity(Vec2f::zero())
,mAcceleration(Vec2f::zero())
,mRadius(5)
,mShowVelocity(false)
{
    mShowVelocity = true;
}

Particle::Particle(float radius)
:mPosition(Vec2f::zero())
,mVelocity(Vec2f::zero())
,mAcceleration(Vec2f::zero())
,mRadius(radius)
{
    //Using an initialization list
}
void Particle::setPosition(const Vec2f &pos)
{
    mPosition = pos;
}
Vec2f Particle::getPosition()
{
    return mPosition;
}
void Particle::setVelocity( const Vec2f& vel )
{
    mVelocity = vel;
}
void Particle::setRadius(float radius )
{
    mRadius = radius;
}
void Particle::applyForce(const Vec2f& force)
{
    mAcceleration+=force;
}
void Particle::renderVelocity( bool shouldRender )
{
    mShowVelocity = shouldRender;
}
void Particle::update()
{
    mAcceleration.limit(5);
    mVelocity += mAcceleration;
    mPosition+=mVelocity;
    mVelocity.limit(7);
    //Set acceleration to zero
    mAcceleration = Vec2f::zero();
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