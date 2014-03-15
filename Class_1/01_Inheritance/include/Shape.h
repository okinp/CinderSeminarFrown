//
//  Shape.h
//  Inheritance
//
//  Created by Nikolas Psaroudakis on 3/14/14.
//
//

#ifndef __Inheritance__Shape__
#define __Inheritance__Shape__

#include "cinder/Vector.h"

class Shape {
public:
    // This constructor accepts no arguments and is called the
    // default constructor.
    Shape();
    //
    // This is the destructor ( it has the tilde symbol ~ ).
    // It is called when the object goes out of scope
    // or if we call delete in case we have a pointer.
    // This is where we cleanup the members of the created object
    // that need "cleaning up". Eg if we have a member that is a pointer,
    // we could call delete here.
    //
    // Although you can have all kinds of
    // constructors there is only one destructor.
    // As a rule of thumb, we ALWAYS write the keyword virtual before the destructor.
    //
    
     virtual ~Shape();
    
    void                setPosition( ci::Vec2i pos );
    void                setSize( float size );
    ci::Vec2i           getPosition();
    float               getSize();
    // We intend to have a base class called Shape ( this class )
    // and then have other classes that inherit ( extend ) Shape
    // We want these classes to have their own version of draw, so we have to
    // write the keyword virtual at the beginning.
    virtual void        draw();
private:
    
    //Private members are not directly accessible
    //
    // So in our code we cannot do the following:
    //
    // Shape myShape;
    // myShape.mPosition = ci::Vec2i( 30, 40 );
    //
    // But if we made mPosition public we would be able to do this.
    ci::Vec2i  mPosition;
    float      mSize;
};


#endif /* defined(__Inheritance__Shape__) */
