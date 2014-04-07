//
//  Particle.cpp
//  FlowField
//
//  Created by Nikolas Psaroudakis on 4/7/14.
//
//

#include "Particle.h"

uint Particle::maxAge = 50;

using namespace ci;
Particle::Particle()
:mPosition(Vec2f::zero())
,mPreviousPosition(Vec2f::zero() )
,mVelocity(Vec2f::zero())
,mAcceleration(Vec2f::zero() )
,mAge(0)
,mIsActive(false)
{
    
}
Particle::~Particle()
{
    
}
void Particle::reset()
{
    mAge = 0;
    mIsActive = true;
}
void Particle::setColor( const ci::ColorAf& col )
{
    mColor = col;
}
ci::ColorAf& Particle::getColor()
{
    return mColor;
}

void Particle::setAcceleration( const ci::Vec2f& acc )
{
    mAcceleration = acc;
}
void Particle::update()
{
    if ( mIsActive )
    {
        mAge++;
        if ( mAge >= maxAge )
        {
            mIsActive = false;
            mAge = 0;
        }
    }
    if ( !mIsActive )
        return;
    mVelocity = Vec2f::zero();
    mPreviousPosition = mPosition;
    mVelocity += mAcceleration;
    mPosition += mVelocity;
}
void Particle::setPosition( const Vec2f& pos )
{
    mPosition = pos;
    mPreviousPosition = mPosition;
}
Vec2f& Particle::getPosition()
{
    return mPosition;
}
Vec2f& Particle::getPreviousPosition()
{
    return mPreviousPosition;
}
bool Particle::isActive()
{
    return mIsActive;
}
void Particle::setActive( bool isActive )
{
    mIsActive = isActive;
    mAge = 0;
}