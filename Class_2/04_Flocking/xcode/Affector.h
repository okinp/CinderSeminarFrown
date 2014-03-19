//
//  Affector.h
//  Flocking
//
//  Created by Nikolas Psaroudakis on 3/16/14.
//
//

#ifndef __Flocking__Affector__
#define __Flocking__Affector__

#include "cinder/Vector.h"
namespace oem {
    class Affector {
        Affector();
        ci::Vec3f apply( const ci::Vec3f& p );
        
    };
    typedef std::shared_ptr<Affector> AffectorRef;
}
#endif /* defined(__Flocking__Affector__) */
