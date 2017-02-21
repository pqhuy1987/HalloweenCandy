//
//  Credits.h
//  Halloween
//
//  Created by Yuning Jin on 10/26/14.
//
//

#ifndef __Halloween__Credits__
#define __Halloween__Credits__

#include "cocos2d.h"
#include "MainMenuScene.h"

class GuideScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GuideScene);
    
private:
    void goToMainMenu(cocos2d::Ref *sender);
    void Guide_move();
};
#endif /* defined(__Halloween__Credits__) */
