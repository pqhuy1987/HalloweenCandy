//
//  Cloud.h
//  Parallex_1
//
//  Created on 10/25/14.
//
//

#ifndef Parallex_1_Cloud_h
#define Parallex_1_Cloud_h

#include "cocos2d.h"

class Cloud
{
public:
    Cloud();
    
    void spawnCloud(cocos2d::Layer * layer);
    
private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
};

#endif
