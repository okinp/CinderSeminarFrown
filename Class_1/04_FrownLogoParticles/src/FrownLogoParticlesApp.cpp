#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Text.h"
#include "cinder/gl/Texture.h"
#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class FrownLogoParticlesApp : public AppNative {
  public:
    void prepareSettings( Settings* settings);
	void setup();
    void keyDown( KeyEvent event );
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    //Lets define a TextLayout
    TextLayout              mLayout;
    Font                    mFont;
    Surface                 mSurface;
    std::vector<ci::Vec2f>  mCurrentPositions;
    std::vector<ci::Vec2f>  mInitialPositions;
    std::vector<Color>      mPixelColors;
    bool                    mKeyPressed;
    bool                    mPaused;
};

void FrownLogoParticlesApp::prepareSettings(Settings* settings)
{
    
}
void FrownLogoParticlesApp::keyDown( KeyEvent event )
{

    if ( event.getChar() == ' ')
    {
        //Pressing the spacebar causes the particles to change direction
        // in one case they are making up the word "Frown"
        // and in the other case "Frown" explodes into particles.
        
        mKeyPressed = !mKeyPressed;
    } else if ( ( event.getChar() == 'P' ) || ( event.getChar() == 'p' ) )
    {
        // Pause and "unpause" using the p ( or P ) key
        mPaused = !mPaused;
    }
}

void FrownLogoParticlesApp::setup()
{
    mKeyPressed = false;
    // Lets load a font from the the installed fonts of the OS
    // and set its size to 90

    mFont = Font("Arial",90 );
    
    //Clear the layout to black
    
    mLayout.clear(Color::black() );
    //Set the text color of the layout
    mLayout.setColor(Color(1,1,1));
    
    //Set the font of the layout
    mLayout.setFont(mFont);
    
    //Add the following line to the layout
    mLayout.addLine("FROWN");
    
    //Render the layout into a cinder Surface
    mSurface = mLayout.render();

    //We will now iterate through every pixel in the surface:
    //First get the iterator
    Surface::Iter iter = mSurface.getIter();
    // For every line in the surface
    //
    while ( iter.line() )
    {
        // For every pixel in the line
        while (iter.pixel()) {
            //Check if the color of the current pixel is not black
            if ( ( iter.r() != 0.0f ) && ( iter.g() != 0.0f ) && ( iter.b() != 0.0f ) )
            {
                //If its not black, push the position of the pixel into
                // the initial positions
                mInitialPositions.push_back(ci::Vec2f(iter.x(), iter.y()));
                // Also, lets make the current positions equal to the initial
                // ones
                mCurrentPositions.push_back(ci::Vec2f(iter.x(), iter.y()));
                //lets also keep the color of every pixel
                mPixelColors.push_back(Colorf(iter.r(), iter.g(), iter.b()));
            }
        }
    }
    //Print the size of non-black pixels found in the surface
    console() << "We found " << mInitialPositions.size() <<
    " non black pixels" << endl;
    
    console() << "Spacebar changes: explode /move back" << endl;
    console() << "P or p changes: whether the particles are paused or not" << endl;
}

void FrownLogoParticlesApp::mouseDown( MouseEvent event )
{

}

void FrownLogoParticlesApp::update()
{
    //If the app is paused update nothing
    

    if ( mPaused )
        return;
    
    if( mKeyPressed )
    {
        // If the spacebar is pressed:
        // Move the particles back to their original positions;
        for ( int i=0; i< mCurrentPositions.size(); ++i )
        {
            ci::Vec2f difference = mInitialPositions[i] - mCurrentPositions[i];
            float dist = difference.length();
            if ( dist <= 3)
            {
                //If the particle is 3 pixels away from the target position
                // move to the target
                mCurrentPositions[i] = mInitialPositions[i];
            } else {
                //Make the difference vector have a length of one
                difference.normalize();
                // Multiply the difference vector by 0.8 so that it has
                // a length of 0.8
                mCurrentPositions[i] += 0.8*difference;
            }
        }

    } else  {
        //Else if the spacebar is not pressed
        //Explode
        for ( int i=0; i< mCurrentPositions.size(); ++i )
        {
            //Move the current positions by a random vector
            //in the range(-5,-5) -> (5, 5)
            mCurrentPositions[i] += 5*Rand::randVec2f();
        }

    }
}

void FrownLogoParticlesApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    glPointSize(1);
    glEnable(GL_POINT_SMOOTH);
    gl::enableAlphaBlending();
    //******  Try changing GL_POINTS to:
    // GL_LINES  or other OpenGL primitives
    glBegin(GL_POINTS);
    
    for ( int i=0; i< mCurrentPositions.size(); i++ )
    {
        glColor3f(mPixelColors[i]);
        glVertex2f(mCurrentPositions[i].x, mCurrentPositions[i].y);
    }
    glEnd();
    gl::disableAlphaBlending();
    
    
    //gl::draw(gl::Texture(mSurface));
 }

CINDER_APP_NATIVE( FrownLogoParticlesApp, RendererGl )
