//
//  SparkleEngine.h
//  Flocking
//
//  Created by Nikolas Psaroudakis on 3/16/14.
//
//

#ifndef __Flocking__SparkleEngine__
#define __Flocking__SparkleEngine__

#include <vector>
#include "System.h"

namespace oem
{
    typedef class SparkleEngine Sparkle;
    class SparkleEngine {
    public:
        SparkleEngine();
        void    setup( int numParticles );
        void    update();
        void    draw();
        
        
        void    addSystem(SystemRef particleSystem);
    protected:
        //Offset
        // reinterpret_cast
        
        std::vector<void*>          mVboData;

    };
}
#endif /* defined(__Flocking__SparkleEngine__) */
