#include "cinder/app/AppNative.h"
#include "cinder/params/Params.h"
#include "cinder/Vector.h"
#include "cinder/MayaCamUI.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/GlslProg.h"

#include "cinder/audio/Io.h"
#include "cinder/audio/Output.h"
#include "cinder/audio/FftProcessor.h"
#include "cinder/audio/PcmBuffer.h"

#include "OscListener.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class SoundSphereApp : public AppNative {
  public:
	void                    setup();
	void                    update();
	void                    draw();
    void                    mouseDown( MouseEvent event );
    
    void                    calculateFFT();
    params::InterfaceGlRef  mParamsUI;
    gl::GlslProg            mShader;
    
    // transformations (translate, rotate, scale) of the model
	Matrix44f               mTransform;
    
    // our camera
	MayaCamUI               mMayaCam;
    
    // keep track of time
	double                  mTime;
    
    //C++11 allows us to initialize a member in definition
    float                   mScale = 0.0;
    
    audio::TrackRef         mTrack;
	audio::PcmBuffer32fRef  mPcmBuffer;
    float*                  mFftBuffer;
    float                   mPrevVal;
    bool                    mShowWireframe = false;
    
    osc::Listener           mListener;
};

void SoundSphereApp::setup()
{
    mListener.setup( 9001 );
    //Set pointer to null at the beginning;
    mFftBuffer = nullptr;
    
    //add the audio track the default audio output
	mTrack = audio::Output::addTrack( audio::load( loadAsset( "Pan_Pacific-Nao_Tokui.mp3" ) ) );
	
	//you must enable enable PCM buffering on the track to be able to call getPcmBuffer on it later
	mTrack->enablePcmBuffering( true );
    
    // initialize stuff
	mTime = getElapsedSeconds();
	mTransform.setToIdentity();
    
    //Build shader
    mShader = gl::GlslProg( loadAsset( "phong_vert.glsl" ), loadAsset( "phong_frag.glsl" ) );
    
    // set up the camera
	CameraPersp cam;
	cam.setEyePoint( Vec3f(5.0f, 10.0f, -5.0f) );
	cam.setCenterOfInterestPoint( Vec3f(0.0f, 0.f, 0.0f) );
	cam.setPerspective( 60.0f, getWindowAspectRatio(), 1.0f, 1000.0f );
	mMayaCam.setCurrentCam( cam );
    
    
    //Create params ui
    mParamsUI = params::InterfaceGl::create(getWindow(), "Light parameters", toPixels(Vec2i(10,20)));
    mParamsUI->addParam("Scale", &mScale,"min=-10. max=+10. step=0.1 keyIncr=z keyDecr=Z");
}

void SoundSphereApp::mouseDown( MouseEvent event )
{
    
}

void SoundSphereApp::calculateFFT()
{
	uint16_t bandCount = 32;
	
	if( ! mPcmBuffer ) return;
	
	//use the most recent Pcm data to calculate the Fft
	std::shared_ptr<float> fftRef = audio::calculateFft( mPcmBuffer->getChannelData( audio::CHANNEL_FRONT_LEFT ), bandCount );
	if( ! fftRef )
    {
        mFftBuffer = nullptr;
		return;
	}
    mFftBuffer = fftRef.get();
}

void SoundSphereApp::update()
{
    //get the latest pcm buffer from the track
	mPcmBuffer = mTrack->getPcmBuffer();
    //
	mTime = getElapsedSeconds();
	mTransform.setToIdentity();
	mTransform.rotate( Vec3f::xAxis(), sinf( (float) getElapsedSeconds() * 3.0f ) * 0.08f );
	mTransform.rotate( Vec3f::yAxis(), (float) getElapsedSeconds() * 0.1f );
	mTransform.rotate( Vec3f::zAxis(), sinf( (float) getElapsedSeconds() * 4.3f ) * 0.09f );
    calculateFFT();
    
    while( mListener.hasWaitingMessages() )
    {
		osc::Message message;
		mListener.getNextMessage( &message );
        mShowWireframe = !mShowWireframe;
    }
}

void SoundSphereApp::draw()
{
    
    GLfloat light_ambient[] = { 1.0,165./255.,0., 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    if ( mShowWireframe )
    {
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    }
    else {
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    }
    
    // gray background
	gl::clear( Color::black());
    // set up the camera
	gl::pushMatrices();
	gl::setMatrices( mMayaCam.getCamera() );
    
	// enable the depth buffer (after all, we are doing 3D)
	gl::enableDepthRead();
	gl::enableDepthWrite();
    
    // bind the shader
	mShader.bind();
    
    //Set attributes
    if ( false )
    {
//        float val =0;
//        for ( int i = 0; i< 32; i++ )
//        {
//            val+=mFftBuffer[i];
//        }
//        val/=64;
        float value = 3.0*(mFftBuffer[1]/64. - 1.0 );
        mShader.uniform("scale", value);
        value =  math<float>::clamp(value,-3,3);
        if ( abs(mPrevVal - value) < 0.8 )
        {
            mPrevVal = value;
            value = 0.f;
            mShader.uniform("scale", value);
        } 
    } else {
        mShader.uniform("scale", mScale);
    }
    
    //Draw the sphere
    gl::color( Color(1.0,165./255.,0. ));
    
	//(note: apply transformations to the model)
	gl::pushModelView();
        gl::multModelView( mTransform );
        gl::drawSphere( Vec3f::zero(), 2.5, 60 );
	gl::popModelView();
    
	// unbind the shader
	mShader.unbind();
    
    gl::popMatrices();
    
    
    //Draw params UI
    mParamsUI->draw();
    
    
    
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    
    
//	// clear out the window with black
//    glEnable( GL_LIGHTING );
//	glEnable( GL_LIGHT0 );
//	gl::clear( Color( 0, 0, 0 ) );
//    gl::enableDepthRead();
//	gl::enableDepthWrite();
////    GLfloat light_position[] = { 100, 100, -80, 1 };
////	glLightfv( GL_LIGHT0, GL_POSITION, light_position );
////	glLightf( GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.0f );
////	glLightf( GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0f );
////	glLightf( GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.00015f );
//    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
//    GLfloat mat_shininess[] = { 50.0 };
//    GLfloat light_position[] = { 1.0, 1.0, -100.0, 0.0 };
//    glClearColor (0.0, 0.0, 0.0, 0.0);
//    glShadeModel (GL_SMOOTH);
//    
//    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
//    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
//    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
//    mPhongShader.bind();
//    gl::color(Color::white());
//    gl::pushMatrices();
//    gl::translate(getWindowWidth()/2, getWindowHeight()/2, 0);
//    gl::drawSphere( Vec3f::zero(), 50, 30 );
//    gl::drawSolidCircle(Vec2f::zero(), 20);
//    gl::popMatrices();
//    mPhongShader.unbind();

}
CINDER_APP_NATIVE( SoundSphereApp, RendererGl )
