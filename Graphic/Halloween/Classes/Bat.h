//
//  Bat.h
//  Halloween
//
//  Created by Yuning Jin on 10/25/14.
//
//

#ifndef __Halloween__Bat__
#define __Halloween__Bat__

#include "cocos2d.h"

class Bat
{
public:
    Bat();
    void spawnBat(cocos2d::Layer * layer);
    void spawnBat2(cocos2d::Layer * layer);
    void startBat(cocos2d::Layer * layer);
    
private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
};


#endif /* defined(__Halloween__Bat__) */
