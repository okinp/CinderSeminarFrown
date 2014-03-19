//
//  Particle.h
//  Flocking
//
//  Created by Nikolas Psaroudakis on 3/16/14.
//
//

#ifndef __Flocking__Particle__
#define __Flocking__Particle__

#include "cinder/Vector.h"
namespace oem {
    class Particle {
    public:
        Particle();
        void applyForce( const ci::Vec3f& force);
    protected:
        ci::Vec3f mPosition;
        ci::Vec3f mVelocity;
    private:
        
    };
};
#endif /* defined(__Flocking__Particle__) */
