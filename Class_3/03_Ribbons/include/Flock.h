//
//  Flock.h
//  Flocking
//
//  Created by Nikolas Psaroudakis on 3/19/14.
//
//

#ifndef __Flocking__Flock__
#define __Flocking__Flock__
#include "Boid.h"
namespace oem {
    class Flock {
    public:
        Flock();
        void run();
        void render();
        void addBoid( BoidRef b);
    private:
        vector<BoidRef> mBoids;
    };
}
#endif /* defined(__Flocking__Flock__) */
