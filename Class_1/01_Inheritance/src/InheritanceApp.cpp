#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "Shape.h"
#include "Circle.h"
#include "Square.h"
#include <memory>

using namespace ci;
using namespace ci::app;
using namespace std;

class InheritanceApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    //
    // The following will be used in Step F:
    //vector<Shape*>  myShapes;
    //
    // The following will be used in Step H:
    // vector< shared_ptr<Shape> > myShapes;
};

void InheritanceApp::setup()
{
    //----------Step A ----------//

    //  Lets define a Circle object ( myCircle ) in setup so that it immediately
    //  goes out of scope and  gets deleted ( cinder's setup only runs once )
    
    Circle myCircle;
    
    // ----> Run the App
    
    //  What is printed in the Output of the debug area when we run the app?
    
    //  Construction:
    
    //  The (default) constructor of Shape is called first, since
    //  the base class of Circle is Shape.
    //
    //  The constructor of Circle is called then to finish the
    //  construction of the object.
    //
    //  Destruction
    
    //  The destructor of Circle is called first
    //  and the destructor of the base class ( Shape ) follows.
    
    //----------Step B ----------//
    
    // *********** Now go and delete the keyword "virtual" from the destructor
    // of Shape ( in the header file of Shape  ).
    
    // ----> Run the App

    //  Do you notice any difference in the printed messages??
    
    //  All constructors & destructors were called,
    //  so "virtual" didn't make a difference here, but it will soon :)
    
    //----------Step C ----------//
    
    //
    // POINTERS
    //
    // Pointers ( and shared pointers ) are extremely useful because they
    // are very lightweight to pass around.
    
    // Instead of passing an object around that might be big / expensive
    // to pass / copy, we can pass the pointer to it.
    
    // C++ offers "references" as a modern alternative to pointers.
    // ( Pointers are a C thing )
    // You dont have to "new" and "delete" references,
    // but references are more restrictive than pointers.
    
    // A reference is using the & symbol when defined (pointers use * ) and
    // essentially represents an alias to the original object.
    

    // Remember: Pointers point to the memory address of an object.
    //           References represent an alias to an object.

    // As you can imagine, passing an alias around is very cheap.
    
    // This is how a reference to an integer is defined:
    // int &myInt;
    
    // Don't worry about references.
    // We'll discuss about them later in the seminar.
    
    // *********** Comment out "myCircle" that was defined in Step A
    
    
    //  Lets make a Shape pointer that holds a Circle.
    //  A Shape can hold a Circle since Circle is a Shape - it inherits it
    //
    //  Remember that if we "new" something, we have to eventualy delete it.
    //  Otherwise we'll have memory leaks.
    //
    //
    
    // *********** Uncomment the following 2 lines
    
//    Shape *myCircle = new Circle();
//    delete myCircle;

    //  The * symbol indicates that myCircle is a pointer.
    
    // ----> Run the App
    
    // The construction order was the same
    
    // Do you notice any difference in the destructors called??
    
    // The Circle destructor was never called,
    // since we are holding myCircle as a Shape  - we
    // call delete on a Shape that knows nothing about Circle
    
    
    //----------Step D ----------//

    
    // *********** Now go and put back the keyword "virtual" at the destructor of
    // Shape ( in the Shape's header file ) and run the app.
    
    // ----> Run the App
    
    // Do you notice any difference??
    
    // Now that the Shape destructor is virtual,
    // deleting the Shape pointer of a Circle, also calls the destructor
    // of Circle (as we want).
    
    // ALWAYS put the keyword "virtual" on destructors.
    // Otherwise you could get leaks.
    
    
    //----------Step E ----------//
    //
    // Shared pointers are pointers that delete themselves when needed
    // This means you dont need to delete them!!!
    //
    // They've been around in Boost (library) for a while, but are now part
    // of the latest C++ standard ( C++11 ).
    //
    // Cinder uses shared pointers everywhere!!
    //
    
    // Shared pointers are defined in the c++ memory header
    // So we have to include <memory> ( look at line 5
    // it's already included )
    
    // *********** Comment out the lines from Step C, where we made a
    // Shape pointer holding a Circle and then deleted it.
    
    // *********** Uncomment the following line:


    //std::shared_ptr<Shape> myShape( new Circle() );
    
    
    // This is the correct way to define a shared pointer!!!!
    //
    // So we shouldn't write this:
    //
    // std::shared_ptr<Shape> myShape = new Circle();
    //
    // or this:
    //
    // std::shared_ptr<Shape> myShape = new std::shared_ptr<Shape>( Circle() );
    
    // ----> Run the App
    
    // Again, myShape is defined in setup and once setup exits,
    // myShape will be deleted.
    
    // Do you notice that the destructors of our shared
    // pointer are called without having to
    // call delete?? No memory leaks from forgotten deletes any more
    // and all the added benefits of pointers..
    
    //----------Step F ----------//
    
    // *********** Comment out the myShape shared pointer from the previous
    // step (line 163)
    
    // *********** Uncomment line 20 where a vector of Shape pointers is defined
    
    
    
    // lets push a Circle and a Square to our vector of pointers to Shapes.
    
    // *********** Uncomment the following 2 lines
    
//    myShapes.push_back( new Circle(Vec2i(200,300),80) );
//    myShapes.push_back( new Square(Vec2i(400,100),40) );
    
    // *********** Uncomment the for loop in the draw() method
    
    // As you've noticed, we used the non-default constructor accepting position
    // and size of the object.
    
    // ----> Run the App
    
    // The square and the circle are drawn on screen.
    // This happens because we've made the draw method in Shape  virtual
    // and when we call the draw method on the base class, it forwards the
    // call to the draw method of the derived class ( circle or square)
    
    // As you notice, the draw method of Shape is not called.
    // Otherwise it would print on the output the message we have in the
    // draw method of Shape
    
    
    //---------Step G-------------//
    
    // *********** Uncomment the line containing: mySpapes.clear() from the
    // mouseDown implementation of our InheritanceApp.
    // You can find it further down
    
    // ----> Run the App
    
    // *********** Press the mouse button on the window.
    
    // The shapes are not draw anymore, but the destructors are not called.
    // Calling the method "clear" on a vector, empties the vector but doesn't
    // call the destructors of the contents ( we are holding pointers remember?)
    // We need to delete the contents before clearing.
    
    // Essentially, be calling clear on myShape we have leaked some memory,
    // since after clearing the vector there is no way for us to call delete
    // on its contents.
    
    // *********** Uncomment the for loop in the mouseDown method

    // ----> Run the App
    
    // *********** Press the mouse button on the window.
    
    // Now everything is destructed as needed.

    
    //----------Step H ----------//
    
    
    // Let's do the same using shared pointers
    
    // *********** Comment out line 20 where we have defined
    // a vector containing pointers to Shape
    
    // *********** Uncomment line 23 where myShapes is a vector
    // of shared pointers to Shape
    
    // *********** Comment out the 2 lines where we pushed back
    // some pointers in Step F
    
    
    // *********** Uncomment the following two lines:
    
//    myShapes.push_back( shared_ptr<Shape>( new Circle( Vec2i(200,300),80) ));
//    myShapes.push_back( shared_ptr<Shape>( new Circle( Vec2i(400,100),40) ));
    
    // *********** Comment out the for loop where we were deleting the pointers
    // in mouseDown.
    
    // ----> Run the App
    
    // As you notice, when pressing the mouse button,
    // the vector containing our shapes is cleared, and the detructors
    // are called.
    
    // Shared pointers FTW!! :)
    
}

void InheritanceApp::mouseDown( MouseEvent event )
{

    
//    for ( int i=0; i<myShapes.size(); i++  )
//    {
//        delete myShapes[i];
//    }
    
 //   myShapes.clear();
    
}

void InheritanceApp::update()
{
    
}

void InheritanceApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    // Set our drawing color to white
    gl::color( Color::white());
    
//    for ( int i = 0; i < myShapes.size(); i++ )
//    {
//        myShapes[i]->draw();
//    }
}

CINDER_APP_NATIVE( InheritanceApp, RendererGl )
