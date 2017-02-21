//
//  Coin.h
//  Halloween
//
//  Created by Yuning Jin on 10/25/14.
//
//

#ifndef __Halloween__Coin3__
#define __Halloween__Coin3__

#include "cocos2d.h"

class Coin3
{
public:
    Coin3();
    void spawnCoin3(cocos2d::Layer * layer);
    
private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
};



#endif /* defined(__Halloween__Coin__) */
