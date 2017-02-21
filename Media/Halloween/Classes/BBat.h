//
//  Bat.h
//  Halloween
//
//  Created by Yuning Jin on 10/25/14.
//
//

#ifndef __Halloween__BBat__
#define __Halloween__BBat__

#include "cocos2d.h"

class BBat
{
public:
    BBat();
    void spawnBBat(cocos2d::Layer * layer,float x,float y);

    
private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
};


#endif /* defined(__Halloween__Bat__) */
