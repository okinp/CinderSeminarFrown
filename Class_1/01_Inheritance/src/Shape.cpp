//
//  Shape.cpp
//  Inheritance
//
//  Created by Nikolas Psaroudakis on 3/14/14.
//
//


//We need to include the Shape header:
#include "Shape.h"
//Lets include the c++ header that lets us print things
//on screen
#include <iostream>


// Lets include the std namespace so that we don't have
// to write std before the iostream methods we are going to
// use

using namespace std;

//Lets also add the cinder namespace:

using namespace ci;

// This is the implementation of our default constructor
Shape::Shape()
{
    cout << "Default Constructor Called: Shape" << endl;
    //Without the: using namspace std;
    //we would have to write:
    // std::cout << "Shape ....   " << std::endl;
}
Shape::~Shape()
{
    cout << "Destructor Called: Shape" << endl;
    // Cinder has a convenience method called console()
    // Instead of using cout we could write:
    // console() << "Destructor Called: Shape" << endl;
    // Cinder has this to allow printing on the IDE's output
    // using the same way on windows and os x
    // To print to the Visual Studio output
    // using cout you would have to do some extra steps,
    // that direct cout to the Visual Studio output.
    // To use the cinder console() we would need to include
    // the cinder header App.h by typing at the top:
    // #include "cinder/app/App.h"
}
// returning void means that our method doesn't return
// a value. Only methods have to return a value or void.
// Constructors and the destructor return nothing.
void Shape::setPosition( Vec2i pos )
{
    mPosition = pos;
}
void Shape::setSize( float size )
{
    mSize = size;
    
    for (int i =0; i <100; i++ )
    {
        
        
    }
}
Vec2i Shape::getPosition()
{
    //Vec2i is a cinder vector in 2 dimensions holding integers
    // i.e it holds x & y
    return mPosition;
}
float Shape::getSize()
{
    return mSize;
}

void Shape::draw( )
{
    cout << "Draw method: Shape" << endl;
}