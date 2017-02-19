//
//  Bat.cpp
//  Halloween
//
//  Created by Yuning Jin on 10/25/14.
//
//

#include "BBat.h"
#include "Constants.h"

USING_NS_CC;

BBat::BBat()
{
    visibleSize=cocos2d::Director::getInstance()->getVisibleSize();
    origin=cocos2d::Director::getInstance()->getVisibleOrigin();
}


void BBat::spawnBBat(cocos2d::Layer * layer,float x,float y)
{
    const float SCALE_TO_DEVICE = Director::getInstance()->getVisibleSize().width / DES_RES_X;
    
    auto Bat=cocos2d::Sprite::create("Bat (1).png");
    Bat->setScale(SCALE_TO_DEVICE);
    auto ran=CCRANDOM_0_1();
    auto posi_x=ran*(visibleSize.width)+origin.x;
    auto posi_y=origin.y+visibleSize.height+Bat->getContentSize().height * SCALE_TO_DEVICE;
    
    Vector<SpriteFrame*> an(4);
    an.pushBack(SpriteFrame::create("Bat (1).png", Rect(0,0,174,118)));
    an.pushBack(SpriteFrame::create("Bat (2).png", Rect(0,0,174,118)));
    an.pushBack(SpriteFrame::create("Bat (3).png", Rect(0,0,174,118)));
    an.pushBack(SpriteFrame::create("Bat (4).png", Rect(0,0,174,118)));
    auto ann=Animation::createWithSpriteFrames(an,0.1f);
    auto anim_ll=Animate::create(ann);
    auto anim_l=RepeatForever::create(anim_ll);
    anim_l->setTag(1);
    
    Bat->runAction(anim_l);
    
    auto size=Bat->getContentSize() * SCALE_TO_DEVICE;
    //size.width=size.width*0.8;
    //size.height=size.height*0.8;
    auto body=cocos2d::PhysicsBody::createCircle(size.height/4);
    
    body->setDynamic(false);
    body->setCollisionBitmask(BBAT_COLLISION_BITMASK);
    body->setContactTestBitmask(BBAT_CONTACT_BITMASK);
    Bat->setPhysicsBody(body);
    
    Bat->setPosition(Point(posi_x,posi_y));
    layer->addChild(Bat,105);
    auto move_dis=Bat->getContentSize().height * SCALE_TO_DEVICE +visibleSize.height*0.14;
    auto move_duration=BBAT_SPEED*move_dis;
    auto Bat_move=cocos2d::MoveBy::create(move_duration,Point(0,-move_dis));
    auto Bat_pause=cocos2d::DelayTime::create(1.5f);
    auto Bat_pause2=cocos2d::DelayTime::create(0.5f);
    auto attack_dis=sqrt((x-Bat->getPositionX())*(x-Bat->getPositionX())+(y-Bat->getPositionY())*(y-Bat->getPositionY()));
    auto attack_duration=BBAT_SPEED*move_dis;
    auto Bat_attack=cocos2d::MoveTo::create(attack_duration, Point(x,y));
    Bat->runAction(Sequence::create(Bat_move,Bat_pause,Bat_attack,Bat_pause2,RemoveSelf::create(true),nullptr));

    
}
