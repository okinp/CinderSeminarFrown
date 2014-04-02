//
//  Boid.cpp
//  Flocking
//
//  Created by Nikolas Psaroudakis on 3/19/14.
//
//

#include "Boid.h"
#include "cinder/Rand.h"
using namespace ci::gl;
namespace oem {
    float Boid::seperationWeight = 1.5f;
    float Boid::alignmentWeight = 1.0f;
    float Boid::coherenceWeight = 1.0f;
    Boid::Boid( const Vec2f &pos)
    {
        mAcceleration = Vec2f::zero();
        mVelocity = Rand::randVec2f();
        mLocation = pos;
        mR = 1.2;
        mMaxspeed = 2;
        mMaxforce = 0.03;
        mNumNodes = 7;
        mSpacing = 4.5;
        mMaxLength = mSpacing*(mNumNodes - 1)+2*mR;
        init();
    }
    void Boid::run(vector<BoidRef> &boids)
    {
        flock(boids);
        update();
        borders();
    }
    
    void Boid::applyForce( const Vec2f &force )
    {
        mAcceleration+=force;
    }
    
    void Boid::flock(vector<BoidRef> &boids)
    {
        Vec2f sep = seperate(boids);
        Vec2f ali = align(boids);      // Alignment
        Vec2f coh = cohesion(boids);   // Cohesion
        // Arbitrarily weight these forces
        sep*=seperationWeight;
        ali*=alignmentWeight;
        coh*=coherenceWeight;
        // Add the force vectors to acceleration
        applyForce(sep);
        applyForce(ali);
        applyForce(coh);
    }
    void Boid::update()
    {
        // Update velocity
        mVelocity += mAcceleration;
        // Limit speed
        mVelocity.limit(mMaxspeed);
        mLocation+=mVelocity;
        // Reset acceleration to 0 each cycle
        mAcceleration*=0.f;
        moveTo(mLocation);
    }
    Vec2f Boid::seek(const Vec2f& target )
    {
        // A vector pointing from the location to the target
        Vec2f desired = target - mLocation;
        // Scale to maximum speed
        desired.normalize();
        desired*=mMaxspeed;
        
        // Steering = Desired minus Velocity
        Vec2f steer = desired - mVelocity;
        // Limit to maximum steering force
        steer.limit(mMaxforce);
        return steer;
    }
    void Boid::render()
    {
        // C++11 Range based for loop
        for ( auto& node : mNodes )
        {
            gl::drawSolidCircle(node, mR);
        }
    }
    
    void Boid::moveTo( const ci::Vec2f& pos )
    {
        mNodes[0] = pos;
        for ( int i=1; i<mNumNodes; i++ )
        {
            Vec2f diff = mNodes[i] - mNodes[i-1];
            diff.safeNormalize();
            diff*=mSpacing;
            mNodes[i] = mNodes[i-1] + diff;
        }
    }
    
    void Boid::init()
    {
        mNodes = vector<Vec2f>(mNumNodes, Vec2f::zero() );
        for ( int i=0; i<mNumNodes; i++ )
        {
            mNodes[i].x = -mSpacing*i;
        }
    }
    
    void Boid::borders()
    {
        int width = app::getWindowWidth();
        int height = app::getWindowHeight();
        if (mLocation.x < -mMaxLength) mLocation.x = width+mMaxLength;
        if (mLocation.y < -mMaxLength) mLocation.y = height+mMaxLength;
        if (mLocation.x > width+mMaxLength) mLocation.x = -mMaxLength;
        if (mLocation.y > height+mMaxLength) mLocation.y = -mMaxLength;
    }

    Vec2f Boid::seperate(vector<BoidRef> &boids )
    {
        float desiredseparation = 25.0f;
        Vec2f steer = Vec2f::zero();
        int count = 0;
        // For every boid in the system, check if it's too close
        for (int i=0; i< boids.size(); i++ )
        {
            Vec2f diff = mLocation - boids[i]->mLocation;
            float d = diff.length();
            // If the distance is greater than 0 and less than an arbitrary amount (0 when you are yourself)
            if ((d > 0) && (d < desiredseparation)) {
                diff.normalize();
                diff/=d;        // Weight by distance
                steer+=diff;
                count++;            // Keep track of how many
            }
        }
        // Average -- divide by how many
        if (count > 0) {
            steer/=(float)count;
        }
        
        // As long as the vector is greater than 0
        if (steer.length() > 0) {
            // First two lines of code below could be condensed with new PVector setMag() method
            // Not using this method until Processing.js catches up
            // steer.setMag(maxspeed);
            
            // Implement Reynolds: Steering = Desired - Velocity
            steer.normalize();
            steer*= mMaxspeed;
            steer -= mVelocity;
            steer.limit(mMaxforce);
        }
        return steer;
    }
    Vec2f Boid::align(vector<BoidRef> &boids )
    {
        float neighbordist = 50;
        Vec2f sum = Vec2f::zero();
        int count = 0;
        for (int i=0; i< boids.size(); i++ )
        {
            Vec2f diff = mLocation - boids[i]->mLocation;
            float d = diff.length();
            if ((d > 0) && (d < neighbordist)) {
                sum+= boids[i]->mVelocity;
                count++;
            }
        }
        if (count > 0) {
            sum/=(float)count;
            // Implement Reynolds: Steering = Desired - Velocity
            sum.normalize();
            sum*=mMaxspeed;
            Vec2f steer = sum - mVelocity;
            steer.limit(mMaxforce);
            return steer;
        } 
        else {
            return Vec2f::zero();
        }
    }
    Vec2f Boid::cohesion(vector<BoidRef> &boids )
    {
        float neighbordist = 50;
        Vec2f sum(0, 0);   // Start with empty vector to accumulate all locations
        int count = 0;
        for (int i=0; i<boids.size(); i++)
        {
            Vec2f diff = mLocation - boids[i]->mLocation;
            float d = diff.length();
            if ((d > 0) && (d < neighbordist)) {
                sum+=boids[i]->mLocation;
                count++;
            }
        }
        if (count > 0) {
            sum/=(float)count;
            return seek(sum);  // Steer towards the location
        } 
        else {
            return Vec2f::zero();
        }
    }
}