//
//  Square.h
//  Inheritance
//
//  Created by Nikolas Psaroudakis on 3/14/14.
//
//

#ifndef __Inheritance__Square__
#define __Inheritance__Square__

#include "Shape.h"

class Square : public Shape {
public:
    Square();
    Square( ci::Vec2i pos, float radius );
    virtual ~Square();
    void draw();
};




#endif /* defined(__Inheritance__Square__) */
