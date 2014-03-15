//
//  Circle.cpp
//  Inheritance
//
//  Created by Nikolas Psaroudakis on 3/14/14.
//
//

#include "Circle.h"


using namespace std;
using namespace ci;

Circle::Circle()
{
    cout << "Default Constructor Called: Circle" << endl;
}

Circle::Circle( Vec2i pos, float radius )
{
    cout << "Non-default Constructor Called: Circle" << endl;

    // These we get from Shape
    // since they are public member methods of Shape
    setPosition(pos);
    setSize(radius);
}
Circle::~Circle()
{
    cout << "Destructor Called: Circle" << endl;
}


void Circle::draw()
{
    gl::drawStrokedCircle(getPosition(), getSize());
}