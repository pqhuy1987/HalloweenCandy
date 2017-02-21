//
//  Coin.h
//  Halloween
//
//  Created by Yuning Jin on 10/25/14.
//
//

#ifndef __Halloween__Coin2__
#define __Halloween__Coin2__

#include "cocos2d.h"

class Coin2
{
public:
    Coin2();
    void spawnCoin2(cocos2d::Layer * layer);
    void spawnCoin2_2(cocos2d::Layer * layer);
    
private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
};



#endif /* defined(__Halloween__Coin__) */
