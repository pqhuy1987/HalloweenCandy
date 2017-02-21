//
//  Hero.h
//  Halloween
//
//  Created by Yuning Jin on 10/25/14.
//
//

#ifndef __Halloween__Hero__
#define __Halloween__Hero__

#include "cocos2d.h"
#include "audio/include/SimpleAudioEngine.h"


class Hero
{
public:
    Hero(cocos2d::Layer * layer);
    ~Hero();
    void set_move(float x,float y){move_x=x;move_y=y;}
    void stop(){hero_move_ud=0;hero_move_lr=0;}
    void move();
    void dead();
    void dead_fire();
    void stop_ani(){M_hero->stopAllActions();}
    cocos2d::Sprite *M_hero;
    
    
private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    int hero_move_ud=0;//1 is up,2 is down
    int hero_move_lr=0;//1 is left,2 is right
    int hero_atside=0;
    float move_x;
    float move_y;
};

#endif /* defined(__Halloween__Hero__) */
