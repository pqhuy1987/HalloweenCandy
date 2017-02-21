//
//  MainMenuScene.h
//  Halloween
//
//  Created by Yuning Jin on 10/25/14.
//
//

#ifndef __Halloween__MainMenuScene__
#define __Halloween__MainMenuScene__

#include "cocos2d.h"


class MainMenuScene : public cocos2d::Layer
{
public:
    
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    CREATE_FUNC(MainMenuScene);
    
private:
    void GoToCScene (cocos2d::Ref * sender);
    void GoToGuideScene (cocos2d::Ref * sender);
    
};


#endif /* defined(__Halloween__MainMenuScene__) */
