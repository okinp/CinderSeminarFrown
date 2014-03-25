//
//  Flock.cpp
//  Flocking
//
//  Created by Nikolas Psaroudakis on 3/19/14.
//
//

#include "Flock.h"

namespace oem {
    Flock::Flock()
    {
        
    }
    void Flock::run()
    {
        int sz= mBoids.size();
        for ( int i=0; i<sz; i++)
        {
            mBoids[i]->run(mBoids);
        }
    }
    void Flock::render()
    {
        int sz= mBoids.size();
        for ( int i=0; i<sz; i++)
        {
            mBoids[i]->render();
        }
    }
    void Flock::addBoid(BoidRef b)
    {
        mBoids.push_back(b);
    }
}