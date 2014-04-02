//
//  Tail.cpp
//  SimpleTails
//
//  Created by Nikolas Psaroudakis on 3/25/14.
//
//

#include "Tail.h"
using namespace std;
using namespace ci;
namespace oem {
    Tail::Tail()
    :mNumNodes(15)
    ,mSpacing(10)
    {
        init();
    }
    Tail::Tail( int numNodes, float spacing )
    :mNumNodes(numNodes)
    ,mSpacing(spacing)
    {
        init();
    }
    void Tail::init()
    {
        mNodes = vector<Vec3f>(mNumNodes, Vec3f::zero() );
        for ( int i=0; i<mNumNodes; i++ )
        {
            mNodes[i].x = -mSpacing*i;
        }
    }
    void Tail::moveTo( const ci::Vec3f& pos )
    {
        mNodes[0] = pos;
        for ( int i=1; i<mNumNodes; i++ )
        {
            Vec3f diff = mNodes[i] - mNodes[i-1];
            diff.safeNormalize();
            diff*=mSpacing;
            mNodes[i] = mNodes[i-1] + diff;
        }
    }
    void Tail::draw()
    {
        for ( auto& node : mNodes )
        {
            gl::drawSolidCircle(node.xy(), 2);
        }
    }
}