//
//  Boid.h
//  Flocking
//
//  Created by Nikolas Psaroudakis on 3/19/14.
//
//

#ifndef __Flocking__Boid__
#define __Flocking__Boid__

#include <iostream>
#include <vector>
#include <memory>
#include "cinder/Vector.h"


using namespace ci;
using  namespace std;

namespace oem {
    //We are using a forward decleration here
    //since Boid is not yet defined.
    typedef shared_ptr<class Boid> BoidRef;
    
    class Boid {
    public:
        Boid();
        Boid( const Vec2f &pos );
        void    run(vector<BoidRef> &boids);
        void    applyForce( const Vec2f &force );
        void    flock(vector<BoidRef> &boids);
        void    update();
        void    render();
        Vec2f   mLocation;
        Vec2f   mVelocity;
        Vec2f   mAcceleration;
        static float seperationWeight;
        static float coherenceWeight;
        static float alignmentWeight;
    private:

        float   mR;
        float   mMaxforce;    // Maximum steering force
        float   mMaxspeed;    // Maximum speed
        
        float                   mMaxLength;
        float                   mSpacing;
        uint                    mNumNodes;
        std::vector<ci::Vec2f>  mNodes;

        void    init();
        void    borders();
        Vec2f   seek(const Vec2f& target );
        Vec2f   seperate(vector<BoidRef> &boids );
        Vec2f   align(vector<BoidRef> &boids );
        Vec2f   cohesion(vector<BoidRef> &boids );
        void    moveTo( const ci::Vec2f& pos );
    };
}

#endif /* defined(__Flocking__Boid__) */
