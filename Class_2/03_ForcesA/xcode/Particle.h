//
//  Particle.h
//  Forces
//
//  Created by Nikolas Psaroudakis on 3/19/14.
//
//

#ifndef __Forces__Particle__
#define __Forces__Particle__

#include  "cinder/Vector.h"
using namespace ci;
class Particle {
public:
    Particle();
    Particle(float radius);
    void        setPosition( const Vec2f& pos );
    Vec2f       getPosition();
    void        setVelocity(const Vec2f& vel);
    Vec2f       getVelocity();
    void        setRadius(float radius);
    void        applyForce(const Vec2f& force);
    void        renderVelocity( bool shouldRender = true);
    void        update();
    void        draw();
private:
    Vec2f       mPosition;
    Vec2f       mVelocity;
    Vec2f       mAcceleration;
    float       mRadius;
    bool        mShowVelocity;
};
#endif /* defined(__Forces__Particle__) */
