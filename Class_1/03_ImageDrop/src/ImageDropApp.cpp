#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/Clipboard.h"
#include "cinder/Url.h"
using namespace ci;
using namespace ci::app;
using namespace std;

class ImageDropApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );
    void fileDrop( FileDropEvent event );
    void resize();
	void update();
	void draw();
    gl::Texture          mTexture;
    Surface              mImage;
    Rectf                mRect;
    std::string          mUrlString;
};

void ImageDropApp::setup()
{
    //Get the window rect
    mRect = getWindowBounds();
}

void ImageDropApp::mouseDown( MouseEvent event )
{

}

void ImageDropApp::update()
{
    // If there is a string in the clipboard
    if ( Clipboard::hasString()  )
    {
         //store the string
        std::string  currentValue = Clipboard::getString();
        //Check if the current values is equal to mUrlString
        if ( currentValue != mUrlString)
        {
            // If its not, set mUrlString to hold the current
            // clipboard value
            mUrlString = currentValue;
            // Load the image using the clipboard string
            // if the string is a url pointing to an image
            try
            {
                console() << "Trying to load image" << std::endl;
                mImage = loadImage(loadUrl(mUrlString));
                mTexture = gl::Texture(mImage);
            }
            catch ( ... )
            {
                console() << "Something went wrong with the url provided" << std::endl;
            }
        }
    }
}
void ImageDropApp::fileDrop(FileDropEvent event)
{
    // If you drag and drop an image to the window, load it
    try {
        mImage = loadImage(loadFile(event.getFile(0)));
        mTexture = gl::Texture(mImage);
    }
    catch ( const ImageIoException& e )
    {
        console() << "Dropped file was not an image: " << e.what() << std::endl;
    }
    catch ( ... )
    {
        console() << "Something else happened" << std::endl;
    }
}
void ImageDropApp::resize()
{
    // window rect changed, so get the current rect
    mRect = getWindowBounds();
}
void ImageDropApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    if ( mTexture )
    {
        //----------Test A
        
        //******* Copy to the osx clipboard the url of an image so that it
        //gets loaded in cinder
        
        mTexture.enableAndBind();
        gl::drawSolidRect(mRect);
        mTexture.unbind();
        mTexture.disable();
        
        //----------Test B
        
        // This should display exactly the same thing as Test A
        
        //******* Comment out the 4 lines of Test A:
        // and uncomment the following line:
        
        
        //gl::drawSolidRect(mRect, mTexture);
        
        
        //----------Test C
        
        // Centered fit of Texture into the window rect
    
        //******* Comment out the gl::drawSolidRect line of Test C
        // and uncomment the following
        
        //gl::draw(mTexture, Rectf(mTexture.getBounds()).getCenteredFit(mRect, true));
        
        //***** Try resizing the window. What happens?
        
        //----------Test D
        
        //******* Comment out the gl::draw line of Test C
        // and uncomment the following
        
        //gl::draw(mTexture, Area( mRect.getCenteredFit(mTexture.getBounds(), true) ), mRect);
        
        //***** Try resizing the window. What happens?
        
        //You can see the definitions of the respective gl::draw s etc
        //by command-clicking on them
        
    }
}

CINDER_APP_NATIVE( ImageDropApp, RendererGl )
