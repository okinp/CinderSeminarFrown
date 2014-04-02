//
//  Tail.h
//  SimpleTails
//
//  Created by Nikolas Psaroudakis on 3/25/14.
//
//

#ifndef __SimpleTails__Tail__
#define __SimpleTails__Tail__

#include <vector>
#include "cinder/Vector.h"
namespace oem {
    class Tail {
    public:
        Tail();
        Tail( int numNodes, float spacing );
        void                    moveTo( const ci::Vec3f& pos );
        void                    draw();
    private:
        float                   mSpacing;
        uint                    mNumNodes;
        std::vector<ci::Vec3f>  mNodes;
        void init();
    };
}
#endif /* defined(__SimpleTails__Tail__) */
