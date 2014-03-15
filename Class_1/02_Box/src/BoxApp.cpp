#include "cinder/app/AppNative.h"
// Lets include the gl header and the texture header, since we will need them
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
// This is the header for video capture
#include "cinder/Capture.h"
// This is the header for OpenGL "camera". It has nothing to do with a
// video camera
#include "cinder/Camera.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class BoxApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
    void resize();
	void draw();
    
    //CaptureRef is a shared pointer pointing to Capture
    CaptureRef          mCapture;
    CameraPersp         mCamera;
    //Lets hold 2 matrices that we are going to use for rotations;
    Matrix44f           mRotationA;
    Matrix44f           mRotationB;
    // TextureRef is a shared pointer to a Texture ( a typedef )
    // Command-click on TextureRef to see where it is defined.
    gl::TextureRef      mTexture;
};

void BoxApp::setup()
{
    // C++ try catch statement
    //
    // First try to do something, and if an exception is thrown
    // "Catch" it. i.e run what is inside catch
    
    // More info here:
    // http://www.tutorialspoint.com/cplusplus/cpp_exceptions_handling.htm
    
    try {
        // Capture::create is a Cinder  method of Capture ( actually a static
        // method )that accepts the resolution and returns a CaptureRef.
        mCapture = Capture::create(640, 480);
        //Start capturing video from the webcam
        mCapture->start();
        // Reminder: pointers and shared pointers use -> instead of .
    } catch (...) {
        //Print out an error message to the xcode output.
        console() << "There was a problem initializing the camera" << std::endl;
    }
    //set the position and the direction at which our perspective camera looks
    mCamera.lookAt(ci::Vec3f(0,0,-5), ci::Vec3f::zero());
    // Set the rotation to the identity matrix ( no rotation )
    // its like multiplying by one.
    mRotationA.setToIdentity();

    
    gl::enableDepthRead(); // this calls glEnable( GL_DEPTH_TEST );
    gl::enableDepthWrite(); //this calls glDepthMask( GL_TRUE );
    // glEnable and glDepthMask are OpenGL Commands
    //
    //*********Look at page 104 of the OpenGL SuperBible book (pdf)
    //for extra info on depth testing etc.
}

void BoxApp::mouseDown( MouseEvent event )
{
    
}

void BoxApp::resize()
{
    //Update camera parameters
    mCamera.setPerspective(60, getWindowAspectRatio(), 1, 1000);
    //Let opengl know that we have a new camera
    gl::setMatrices(mCamera);
    //
    //********To understand whats happening with the matrices
    // you should read this:
    // http://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/
}

void BoxApp::update()
{
    //Perform a rotation around the z axis of 0.02 radians
    //Command-Click on "rotate" to see more.
    
    mRotationA.rotate(Vec3f( 0, 0, 1 ), 0.02f);
    
    //Perform a rotation around the z axis of 0.08 radians
    //Command-Click on "rotate" to see more.
    mRotationB.rotate(Vec3f( 0, 0, 1 ), 0.08f);
    
    //Check if there is a new frame
    if ( mCapture->checkNewFrame() )
    {
        // Get the new frame in the form of a cinder Surface
        // and construct a TextureRef out of it.
        mTexture = gl::Texture::create(mCapture->getSurface());
    }
}

void BoxApp::draw()
{
    // clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    
    //If texture is empty, draw nothing ( return  )
    if ( !mTexture )
        return;

    //Let opengl know that what follows after this, will be
    //textured using mTexture ( enableAndBind )
    
    // ******* Try commenting out the following line to
    // see what happens
    
    mTexture->enableAndBind();
    
    // ******* Did you try it? Uncomment it now so that we see the video texture

    //-------TEST A-----------//
    // Rotates a cube around its z axis
    
    
    gl::pushMatrices();
    gl::multModelView(mRotationA); //Rotate the cube around its z Axis by 0.02rad
    //Draw a cube with center at zero with dimensions 2,2,2
    gl::drawCube(ci::Vec3f::zero(), ci::Vec3f(2,2,2));
    gl::popMatrices();
    
    
    //-------TEST B-----------//
    // Rotates its cube around its z-axis
    // Translates the cube and rotates again with a different angle
    // the translated cube around the z axis

    // ******* Comment out Test A
    // and uncomment the following:
    
//    gl::pushMatrices();
//    gl::multModelView(mRotationA);
//    gl::translate(Vec3f(2.5, 0 ,0 ));
//    //Draw a cube with center at zero with dimensions 2,2,2
//    gl::pushMatrices();
//    gl::multModelView(mRotationB);
//    gl::drawCube(ci::Vec3f::zero(), ci::Vec3f(2,2,2));
//    gl::popMatrices();
//    gl::popMatrices();
    
    // Do you understand whats going on??

}

CINDER_APP_NATIVE( BoxApp, RendererGl )
