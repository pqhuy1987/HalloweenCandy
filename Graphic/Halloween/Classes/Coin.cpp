//
//  Coin.cpp
//  Halloween
//
//  Created by Yuning Jin on 10/25/14.
//
//

#include "Coin.h"
#include "Constants.h"

USING_NS_CC;


Coin::Coin()
{
    visibleSize=Director::getInstance()->getVisibleSize();
    origin=Director::getInstance()->getVisibleOrigin();
}


void Coin::spawnCoin(cocos2d::Layer * layer)
{
    const float SCALE_TO_DEVICE = Director::getInstance()->getVisibleSize().width / DES_RES_X;

    auto coin = Sprite::create("Candy (1).png");
    coin->setScale(SCALE_TO_DEVICE);
    auto ran1=CCRANDOM_0_1();
    auto ran2=CCRANDOM_0_1();
    float ran_pos=0.4;
    if(ran1>=0.5&&ran2>=0.5)
    {
        ran_pos=0.2;
    }
    if(ran1<0.5&&ran2<0.5)
    {
        ran_pos=0.4;
    }
    if(ran1>=0.5&&ran2<0.5)
    {
        ran_pos=0.6;
    }
    if(ran1<0.5&&ran2>=0.5)
    {
        ran_pos=0.8;
    }
    auto posi_x=ran_pos*visibleSize.width+origin.x;
    auto posi_y=origin.y+visibleSize.height;
    
    auto body = PhysicsBody::createBox(coin->getContentSize() * SCALE_TO_DEVICE);
    
    body->setDynamic(false);
    body->setCollisionBitmask(COIN_COLLISION_BITMASK);
    body->setContactTestBitmask(COIN_CONTACT_BITMASK);
    coin->setPhysicsBody(body);
    
    coin->setPosition(Point(posi_x,posi_y));
    layer->addChild(coin,5);
    auto move_dis = visibleSize.height + coin->getContentSize().height * SCALE_TO_DEVICE + 50;
    auto move_duration=COIN_SPEED*move_dis;
    auto coin_move=MoveBy::create(move_duration,Point(0,-move_dis));
    coin->runAction(Sequence::create(coin_move,RemoveSelf::create(true),nullptr));
    
}
