//
//  Coin.h
//  Halloween
//
//  Created by Yuning Jin on 10/25/14.
//
//

#ifndef __Halloween__CCoin__
#define __Halloween__CCoin__

#include "cocos2d.h"

class CCoin
{
public:
    CCoin();
    void spawnCCoin(cocos2d::Layer * layer);
    
private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
};



#endif /* defined(__Halloween__Coin__) */
