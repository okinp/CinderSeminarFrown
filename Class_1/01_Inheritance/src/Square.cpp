//
//  Square.cpp
//  Inheritance
//
//  Created by Nikolas Psaroudakis on 3/14/14.
//
//

#include "Square.h"
#include "cinder/Rect.h"
#include "cinder/gl/gl.h"
using namespace std;
using namespace ci;
Square::Square()
{
    cout << "Default Constructor Called: Square" << endl;
}
Square::Square( ci::Vec2i pos, float radius )
{
    cout << "Non-default Constructor Called: Square" << endl;
    setPosition(pos);
    setSize(radius);
}
Square::~Square()
{
     cout << "Destructor Called: Square" << endl;
}
void Square::draw()
{
    float size = getSize();
    ci::Rectf myRect  = ci::Rectf(-size/2.f,-size/2.f,size/2.f,size/2.f);
    myRect.offsetCenterTo(getPosition());
    gl::drawStrokedRect(myRect);
}