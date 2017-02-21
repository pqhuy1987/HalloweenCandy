//
//  GameOverScene.h
//  Halloween
//
//  Created by Yuning Jin on 10/26/14.
//
//

#ifndef __Halloween__GameOverScene__
#define __Halloween__GameOverScene__

#include "cocos2d.h"
#include "MainMenuScene.h"
#include "GameGuide.h"

class GameOverScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene(int score, float off_Y);
    virtual bool init();
    CREATE_FUNC(GameOverScene);
    void backScrollBk(float dt);
    cocos2d::Sprite* bk1;
    cocos2d::Sprite* bk2;
    cocos2d::Sprite* bk3;
    cocos2d::Sprite* bk4;
    cocos2d::Sprite* bk5;
    
private:
    void goToMainMenu(cocos2d::Ref *sender);
    void goToGameScene(cocos2d::Ref *sender);
    cocos2d::Label *scoreLabel;
    cocos2d::Label *highScoreLabel;
    int m_score;
};




#endif /* defined(__Halloween__GameOverScene__) */
