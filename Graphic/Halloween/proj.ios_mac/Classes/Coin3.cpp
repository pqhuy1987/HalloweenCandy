//
//  Coin.cpp
//  Halloween
//
//  Created by Yuning Jin on 10/25/14.
//
//

#include "Coin3.h"
#include "Constants.h"

USING_NS_CC;


Coin3::Coin3()
{
    visibleSize=Director::getInstance()->getVisibleSize();
    origin=Director::getInstance()->getVisibleOrigin();
}


void Coin3::spawnCoin3(cocos2d::Layer * layer)
{
    auto coin=Sprite::create("Candy (3).png");
    coin->setScale(2, 2);
    auto ran=CCRANDOM_0_1();
    auto posi_x=origin.x+coin->getContentSize().width/2+ran*(visibleSize.width-coin->getContentSize().width);
    auto posi_y=origin.y+visibleSize.height;
    
    auto body=PhysicsBody::createBox(coin->getContentSize()*2);
    
    body->setDynamic(false);
    body->setCollisionBitmask(COIN3_COLLISION_BITMASK);
    body->setContactTestBitmask(COIN3_CONTACT_BITMASK);
    coin->setPhysicsBody(body);
    
    coin->setPosition(Point(posi_x,posi_y));
    layer->addChild(coin,7);
    auto move_dis=visibleSize.height+coin->getContentSize().height+50;
    auto move_duration=COIN3_SPEED*move_dis;
    auto coin_move=MoveBy::create(move_duration,Point(0,-move_dis));
    coin->runAction(Sequence::create(coin_move,RemoveSelf::create(true),nullptr));
    
}
