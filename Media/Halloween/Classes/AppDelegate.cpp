#include "AppDelegate.h"
#include "WelcomeScene.h"
#include "audio/include/SimpleAudioEngine.h"

USING_NS_CC;

AppDelegate::AppDelegate() {
    
}

AppDelegate::~AppDelegate()
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    
    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("My Game");
        director->setOpenGLView(glview);
    }
    
    // turn on display FPS
    director->setDisplayStats(false);
    
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    // MULTI RESOLUTION SUPPORT FOR V3
    // Credits: http://becomingindiedev.blogspot.com/2014/05/multi-resolution-support-in-ios-with.html
    auto screenSize = glview->getFrameSize();
    
    auto fileUtils = FileUtils::getInstance();
    std::vector<std::string> searchPaths;
    
    if (screenSize.width == 2048 || screenSize.height == 2048)
    {
        glview -> setDesignResolutionSize(1536, 2048, ResolutionPolicy::NO_BORDER);
        searchPaths.push_back("ipadhd");
        searchPaths.push_back("ipadsd");
        searchPaths.push_back("iphone5");
        searchPaths.push_back("iphonehd");
        searchPaths.push_back("iphonesd");
    }
    else if (screenSize.width == 1024 || screenSize.height == 1024)
    {
        glview -> setDesignResolutionSize(768, 1024, ResolutionPolicy::NO_BORDER);
        searchPaths.push_back("ipadsd");
        searchPaths.push_back("iphone5");
        searchPaths.push_back("iphonehd");
        searchPaths.push_back("iphonesd");
        
    }
    else if (screenSize.width == 1136 || screenSize.height == 1136)
    {
        glview -> setDesignResolutionSize(640, 1136, ResolutionPolicy::NO_BORDER);
        searchPaths.push_back("iphone5");
        searchPaths.push_back("iphonehd");
        searchPaths.push_back("iphonesd");
        
    }
    else if (screenSize.width == 960 || screenSize.height == 960)
    {
        glview -> setDesignResolutionSize(640, 960, ResolutionPolicy::NO_BORDER);
        searchPaths.push_back("iphonehd");
        searchPaths.push_back("iphonesd");
    }
    else
    {
        searchPaths.push_back("iphonesd");
        glview -> setDesignResolutionSize(320, 480, ResolutionPolicy::NO_BORDER);
    }
    
    fileUtils->setSearchPaths(searchPaths);
    
    // create a scene. it's an autorelease object
    
    // run
    auto scene = WelcomeScene::createScene();
    director->runWithScene(scene);
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
    CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
    CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}