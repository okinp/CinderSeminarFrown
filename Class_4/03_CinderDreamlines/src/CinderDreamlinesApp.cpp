/*  
 Created by: Nikolas Psaroudakis
 License: Copyleft
 Inspiration: Dreamlines by Leonardo Solaas
 Inspiration URL: http://www.solaas.com.ar/dreamlines/
 */

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Utilities.h"
#include <curl/curl.h>
#include <regex>
#include "cinder/Surface.h"
#include "cinder/gl/Texture.h"
#include "cinder/Text.h"
#include "cinder/Perlin.h"
#include "cinder/Rand.h"
#include <algorithm>
using namespace ci;
using namespace ci::app;
using namespace std;

class CinderDreamlinesApp : public AppNative {
  public:
	void                setup();
	void                update();
	void                draw();
    void                keyDown( KeyEvent event );
    void                mouseDown( MouseEvent event );

private:
    Surface             mSurface;
    vector<Url>         mImageUrls;
    std::string         mBody;
    CURL*               mHandle;
    void                setupQuery(const string& term);
    void                getImageUrls();
    void                prepareTextBox();
    
    static string       mData;
    static size_t       libcurlCallback(char* buf, size_t size, size_t nmemb, void* up);
    
    Rectf               mTextRect;
    TextBox             mTextBox;
    Font                mFont;
    bool                mUserIsEditingQuery;
    string              mQuery;
    //
    void    reset();
    Vec2f   getImageAccel( const Vec2f& pos );
    void    addParticleAtIndex( int idx );
    vector<Vec2f>   mPos;
    vector<int>     mAge;
    int             mMaxParticles = 10000;
    
    
    float s;
    int t, c;
    
    
    int mMaxAge = 50;
    int mRdodge = 30;
    int mOpacity = 40;
    float mSpeed = .2;
    float mZoom = .01;
    bool crayons, soft, dodge = true;
    Perlin  mPerlin;
    bool clear = false;
    bool first = true;
};

string CinderDreamlinesApp::mData("");

void CinderDreamlinesApp::addParticleAtIndex(int idx)
{

    mPos[idx] = Vec2f(Rand::randInt(getWindowWidth()), Rand::randInt(getWindowHeight()));
    mAge[idx] = 0;
}
void CinderDreamlinesApp::reset()
{
    gl::clear( Color::black() );
    s = mSpeed / mZoom;
    c = 0;
}
Vec2f  CinderDreamlinesApp::getImageAccel( const Vec2f& pos )
{
    ColorAf pixel = mSurface.getPixel(pos);
    float b = ( pixel.r + pixel.b +pixel.g )/3.f;
    //console() << b << std::endl;
    return Vec2f( cos(2*M_PI*b), sin(2*M_PI*b));
}
size_t CinderDreamlinesApp::libcurlCallback(char* buf, size_t size, size_t nmemb, void* up)
{
    for (int c = 0; c<size*nmemb; c++)
    {
        mData.push_back(buf[c]);
    }
    return size*nmemb;
}

void CinderDreamlinesApp::setupQuery(const string& term)
{
    string newTerm = term;
    
    std::replace( newTerm.begin(), newTerm.end(), ' ', '+');
    //First clear previous results
    mData.clear();
    //Build search url
    string imageSearchUrl = "https://www.google.gr/search?q=";
    //Add term
    imageSearchUrl+=newTerm;
    //add remaining part of url
    imageSearchUrl+="&source=lnms&tbm=isch&tbs=isz:ex,iszw:640,iszh:480";
    
    curl_global_init(CURL_GLOBAL_ALL);
    mHandle = curl_easy_init();
    curl_easy_setopt(mHandle, CURLOPT_URL, imageSearchUrl.c_str());
    curl_easy_setopt (mHandle, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 6.1; rv:8.0) Gecko/20100101 Firefox/8.0");
    curl_easy_setopt (mHandle, CURLOPT_REFERER, "http://www.google.com/");
    curl_easy_setopt(mHandle, CURLOPT_WRITEFUNCTION, &CinderDreamlinesApp::libcurlCallback);
    curl_easy_setopt(mHandle, CURLOPT_VERBOSE, false);
    curl_easy_perform(mHandle);
    curl_easy_cleanup(mHandle);
    curl_global_cleanup();
}

void CinderDreamlinesApp::getImageUrls()
{
    std::regex imagesDivRegEx("imgurl=(.*?)&amp");
    auto it_begin = sregex_iterator(mData.begin(), mData.end(), imagesDivRegEx);
    auto it_end = sregex_iterator();
    std::string match_str ="";
    for (std::sregex_iterator i = it_begin; i != it_end; ++i)
    {
        std::smatch match = *i;
        match_str = match.str();
        match_str= match_str.substr(7, match_str.size() - 11);
        mImageUrls.push_back(Url(match_str));
    }
}
void CinderDreamlinesApp::prepareTextBox()
{
    mFont = Font("Arial",26);
    mTextBox.setAlignment(TextBox::LEFT);
    mTextBox.setColor(Colorf(0.3,0.3,0.3));
    mTextBox.setBackgroundColor(Colorf(1,1,1));
    mTextBox.setFont(mFont);
}
void CinderDreamlinesApp::setup()
{
    mUserIsEditingQuery = true;
    prepareTextBox();
    gl::enableAlphaBlending();
    mPos.reserve(mMaxParticles);
    mAge.reserve(mMaxParticles);
    reset();
}
void CinderDreamlinesApp::keyDown( KeyEvent event )
{
    if ( mUserIsEditingQuery )
    {
        if ( event.getCode() == KeyEvent::KEY_RETURN )
        {
            mUserIsEditingQuery = false;
            gl::clear( Color::black());
            setupQuery(mQuery);
            mImageUrls.clear();
            getImageUrls();
            //Load the first image that can be loaded
            int idx = 0;
            bool found = false;
            while ( !found && (idx < mImageUrls.size() ) )
            {
                try {
                    mSurface = loadImage(loadUrl(mImageUrls[idx]));
                    found = true;
                    
                } catch (...)
                {
                    idx++;
                }
            }
        } else if (event.getCode() == KeyEvent::KEY_BACKSPACE)
        {
            mQuery.pop_back();
        } else {
            mQuery.push_back(event.getChar());
        }
    } else {
        mUserIsEditingQuery = true;
    }
}
void CinderDreamlinesApp::mouseDown( MouseEvent event )
{
    gl::clear(Color::black());
    mPerlin.setSeed(clock() & 65535 );
}

void CinderDreamlinesApp::update()
{
    if ( mUserIsEditingQuery )
        return;
    // create new particles
    int np = mMaxParticles / mMaxAge;
    for(int i=0; i<np && c<mMaxParticles; i++, c++)
    {
        addParticleAtIndex(c);
    }
    // draw particle traces
    for(int i=0; i<c; i++)
    {
        mAge[i]++;
        if (mAge[i] > mMaxAge)
        {
            addParticleAtIndex(i);
        }
    }
}

void CinderDreamlinesApp::draw()
{
	// clear out the window with black
	
    if ( !mUserIsEditingQuery )
    {
        if ( mSurface)
        {
            if ( first )
            {
                gl::draw(gl::Texture(mSurface));
                first = false;
            }
            
            for(int i=0; i<c; i++)
            {
                Vec2f pos = mPos[i];
                Vec2f noise = getImageAccel(mPos[i]);
                float mag = noise.length();
                if (mAge[i] <= mMaxAge)
                {
                    // opacity based on speed (soft mode) or age (hard mode)
                    int m = mMaxAge/2;
                    float op = soft ? mag * 2 * mOpacity : (m - abs(m - mAge[i])) * mOpacity/m;
                    op/=255;
                    // hue based on direction
                    float h =  (atan2(noise.x, noise.y) + M_PI)/(2*M_PI);
                    //            console() << op << std::endl;
                    //gl::color( ColorAf(h,h,h,op/4.f));
                    //gl::color( ColorAf(  h, h, h, op/8.f ));
                    gl::color( ColorAf( CM_HSV, h, 1.0f, 0.8f, op/8.f ));
                    gl::begin(GL_LINES);
                    glVertex2f(mPos[i]);
                    glVertex2f(mPos[i]+=s*noise);
                    gl::end();
                }
            }
        }
    } else {
        gl::clear( Color( 0, 0, 0 ) );
        //Draw the textbox
        gl::color( Colorf(0.8,0.8,0.8) );
        if ( mQuery.size() > 0 )
        {
            mTextBox.setText(mQuery);
            Surface surf = mTextBox.render();
            Rectf textBoxBackgroundRect = Rectf( Vec2f::zero(), surf.getSize()+10*Vec2f::one());
            gl::pushMatrices();
            gl::translate(getWindowCenter() - textBoxBackgroundRect.getSize()/2.f);
            gl::drawSolidRoundedRect(Rectf( Vec2f::zero(), surf.getSize()+10*Vec2f::one()) ,5);
            gl::draw(gl::Texture(surf), 5*Vec2f::one());
            gl::popMatrices();
        }
    }
}
CINDER_APP_NATIVE( CinderDreamlinesApp, RendererGl )
