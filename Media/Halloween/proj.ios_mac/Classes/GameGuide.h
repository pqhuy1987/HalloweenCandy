//
//  GameGuide.h
//  Halloween
//
//  Created by Yuning Jin on 10/26/14.
//
//

#ifndef __Halloween__GameGuide__
#define __Halloween__GameGuide__

#include "cocos2d.h"


class GameGuide : public cocos2d::Layer
{
public:
    
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    CREATE_FUNC(GameGuide);
    
private:
    void GoToGameScene (cocos2d::Ref * sender);
    
};

#endif /* defined(__Halloween__GameGuide__) */
