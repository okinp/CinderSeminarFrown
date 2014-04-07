//
//  Particle.h
//  FlowField
//
//  Created by Nikolas Psaroudakis on 4/7/14.
//
//

#ifndef FlowField_Particle_h
#define FlowField_Particle_h
#include "cinder/Vector.h"
#include "cinder/Color.h"
class Particle {
public:
    Particle();
    ~Particle();
    void            update();
    void            setPosition( const ci::Vec2f& pos );
    ci::Vec2f&      getPosition();
    ci::Vec2f&      getPreviousPosition();
    void            setAcceleration( const ci::Vec2f& acc );
    bool            isActive();
    void            setActive( bool isActive = true);
    void            reset();
    void            setColor( const ci::ColorAf& col );
    ci::ColorAf&    getColor();
private:
    ci::Vec2f       mPosition;
    ci::Vec2f       mPreviousPosition;
    ci::Vec2f       mVelocity;
    ci::Vec2f       mAcceleration;
    ci::ColorAf     mColor;

    uint            mAge;
    bool            mIsActive;
    static uint     maxAge;
};
#endif
