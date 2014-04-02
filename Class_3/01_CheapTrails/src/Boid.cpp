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
        mR = 0.7;
        mMaxspeed = 2;
        mMaxforce = 0.03;
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
//        // Draw a triangle rotated in the direction of velocity
//        float theta = velocity.heading2D() + radians(90);
//        // heading2D() above is now heading() but leaving old syntax until Processing.js catches up
//        
//        fill(200, 100);
//        stroke(255);
//        pushMatrix();
//        translate(location.x, location.y);
//        rotate(theta);
//        beginShape(TRIANGLES);
//        vertex(0, -r*2);
//        vertex(-r, r*2);
//        vertex(r, r*2);
//        endShape();
//        popMatrix();
        gl::popMatrices();
        gl::drawSolidCircle(mLocation, mR);
    }
    void Boid::borders()
    {
        int width = app::getWindowWidth();
        int height = app::getWindowHeight();
        if (mLocation.x < -mR) mLocation.x = width+mR;
        if (mLocation.y < -mR) mLocation.y = height+mR;
        if (mLocation.x > width+mR) mLocation.x = -mR;
        if (mLocation.y > height+mR) mLocation.y = -mR;
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