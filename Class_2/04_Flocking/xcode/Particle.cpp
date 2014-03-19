//
//  Particle.cpp
//  Flocking
//
//  Created by Nikolas Psaroudakis on 3/16/14.
//
//

#include "Particle.h"
using namespace ci;
namespace oem {
    Particle::Particle()
    :mPosition(Vec3f::zero())
    ,mVelocity(Vec3f::zero())
    {
        
    }
    void Particle::applyForce(const ci::Vec3f &force)
    {
        mVelocity+=force;
    }
}