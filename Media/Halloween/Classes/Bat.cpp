//
//  Bat.cpp
//  Halloween
//
//  Created by Yuning Jin on 10/25/14.
//
//

#include "Bat.h"
#include "Constants.h"

USING_NS_CC;

Bat::Bat()
{
    visibleSize=cocos2d::Director::getInstance()->getVisibleSize();
    origin=cocos2d::Director::getInstance()->getVisibleOrigin();
}


void Bat::spawnBat(cocos2d::Layer * layer)
{
    const float SCALE_TO_DEVICE = Director::getInstance()->getVisibleSize().width / DES_RES_X;
    
    auto Bat=cocos2d::Sprite::create("Spike.png");
    Bat->setScale(SCALE_TO_DEVICE * 0.5);
    //Bat->setScale(0.5, 0.5);
    auto ran=CCRANDOM_0_1();
    auto posi_x=ran*(visibleSize.width/2)+origin.x;
    auto posi_y=origin.y+visibleSize.height+Bat->getContentSize().height * SCALE_TO_DEVICE;
    /*
    Vector<SpriteFrame*> an(4);
    an.pushBack(SpriteFrame::create("Bat (1).png", Rect(0,0,174,118)));
    an.pushBack(SpriteFrame::create("Bat (2).png", Rect(0,0,174,118)));
    an.pushBack(SpriteFrame::create("Bat (3).png", Rect(0,0,174,118)));
    an.pushBack(SpriteFrame::create("Bat (4).png", Rect(0,0,174,118)));
    auto ann=Animation::createWithSpriteFrames(an,0.1f);
    auto anim_ll=Animate::create(ann);
    auto anim_l=RepeatForever::create(anim_ll);
    Bat->runAction(anim_l);
    */
    auto size=Bat->getContentSize() * SCALE_TO_DEVICE;
    //size.width=size.width*0.8;
    //size.height=size.height*0.8;
    auto body=cocos2d::PhysicsBody::createCircle(size.height/4);
    
    body->setDynamic(false);
    body->setCollisionBitmask(BAT_COLLISION_BITMASK);
    body->setContactTestBitmask(BAT_CONTACT_BITMASK);
    Bat->setPhysicsBody(body);
    
    Bat->setPosition(Point(posi_x,posi_y));
    layer->addChild(Bat,102);
    auto move_dis=visibleSize.height+Bat->getContentSize().height * SCALE_TO_DEVICE+130;
    auto move_duration=BAT_SPEED*move_dis;
    auto FireBall_move=cocos2d::MoveBy::create(move_duration,Point(0,-move_dis));
    Bat->runAction(Sequence::create(FireBall_move,RemoveSelf::create(true),nullptr));
    
}

void Bat::spawnBat2(cocos2d::Layer * layer)
{
    const float SCALE_TO_DEVICE = Director::getInstance()->getVisibleSize().width / DES_RES_X;

    auto Bat=cocos2d::Sprite::create("Spike.png");
    Bat->setScale(SCALE_TO_DEVICE * 0.5);

    //Bat->setScale(0.5, 0.5);
    auto ran=CCRANDOM_0_1();
    auto posi_x=ran*(visibleSize.width/2)+origin.x+visibleSize.width/2;
    auto posi_y=origin.y+visibleSize.height+Bat->getContentSize().height * SCALE_TO_DEVICE;
    /*
     Vector<SpriteFrame*> an(4);
     an.pushBack(SpriteFrame::create("Bat (1).png", Rect(0,0,174,118)));
     an.pushBack(SpriteFrame::create("Bat (2).png", Rect(0,0,174,118)));
     an.pushBack(SpriteFrame::create("Bat (3).png", Rect(0,0,174,118)));
     an.pushBack(SpriteFrame::create("Bat (4).png", Rect(0,0,174,118)));
     auto ann=Animation::createWithSpriteFrames(an,0.1f);
     auto anim_ll=Animate::create(ann);
     auto anim_l=RepeatForever::create(anim_ll);
     Bat->runAction(anim_l);
     */
    auto size=Bat->getContentSize() * SCALE_TO_DEVICE;
    //size.width=size.width*0.8;
    //size.height=size.height*0.8;
    auto body=cocos2d::PhysicsBody::createCircle(size.height/4);
    
    body->setDynamic(false);
    body->setCollisionBitmask(BAT_COLLISION_BITMASK);
    body->setContactTestBitmask(BAT_CONTACT_BITMASK);
    Bat->setPhysicsBody(body);
    
    Bat->setPosition(Point(posi_x,posi_y));
    layer->addChild(Bat,102);
    auto move_dis=visibleSize.height+Bat->getContentSize().height * SCALE_TO_DEVICE+130;
    auto move_duration=BAT_SPEED*move_dis;
    auto FireBall_move=cocos2d::MoveBy::create(move_duration,Point(0,-move_dis));
    Bat->runAction(Sequence::create(FireBall_move,RemoveSelf::create(true),nullptr));
    
}