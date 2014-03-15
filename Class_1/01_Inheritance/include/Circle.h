//
//  Circle.h
//  Inheritance
//
//  Created by Nikolas Psaroudakis on 3/14/14.
//
//

#ifndef __Inheritance__Circle__
#define __Inheritance__Circle__

#include "Shape.h"
// This is a class called Circle that is a Shape ( extends Shape )
// It has access to all public members and public functions of
// Shape

class Circle : public Shape {
public:
    //Default constructor ( has no arguments )
    Circle();
    //
    Circle( ci::Vec2i pos, float radius );
    // Destructor ( the keyword virtual appears only in the header and
    // not the implementation.
    virtual ~Circle();
    void draw();
};

#endif /* defined(__Inheritance__Circle__) */
