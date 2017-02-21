//
//  Coin.cpp
//  Halloween
//
//  Created by Yuning Jin on 10/25/14.
//
//

#include "Coin2.h"
#include "Constants.h"

USING_NS_CC;


Coin2::Coin2()
{
    visibleSize=Director::getInstance()->getVisibleSize();
    origin=Director::getInstance()->getVisibleOrigin();
}


void Coin2::spawnCoin2(cocos2d::Layer * layer)
{
    auto coin=Sprite::create("Candy (2).png");
    coin->setScale(1.5, 1.5);
    auto ran=CCRANDOM_0_1();
    auto posi_x=(ran*(visibleSize.width/2-coin->getContentSize().width))+origin.x+coin->getContentSize().width/2;
    auto posi_y=origin.y+visibleSize.height;
    
    auto body=PhysicsBody::createBox(coin->getContentSize()*1.5);
    
    body->setDynamic(false);
    body->setCollisionBitmask(COIN2_COLLISION_BITMASK);
    body->setContactTestBitmask(COIN2_CONTACT_BITMASK);
    coin->setPhysicsBody(body);
    
    coin->setPosition(Point(posi_x,posi_y));
    layer->addChild(coin,6);
    auto move_dis=visibleSize.height+coin->getContentSize().height+50;
    auto move_duration=COIN2_SPEED*move_dis;
    auto coin_move=MoveBy::create(move_duration,Point(0,-move_dis));
    coin->runAction(Sequence::create(coin_move,RemoveSelf::create(true),nullptr));
    
}

void Coin2::spawnCoin2_2(cocos2d::Layer * layer)
{
    auto coin=Sprite::create("Candy (2).png");
    coin->setScale(1.5, 1.5);
    auto ran=CCRANDOM_0_1();
    auto posi_x=(ran*(visibleSize.width/2-coin->getContentSize().width))+origin.x+visibleSize.width/2+coin->getContentSize().width/2;
    auto posi_y=origin.y+visibleSize.height;
    
    auto body=PhysicsBody::createBox(coin->getContentSize()*1.5);
    
    body->setDynamic(false);
    body->setCollisionBitmask(COIN2_COLLISION_BITMASK);
    body->setContactTestBitmask(COIN2_CONTACT_BITMASK);
    coin->setPhysicsBody(body);
    
    coin->setPosition(Point(posi_x,posi_y));
    layer->addChild(coin,6);
    auto move_dis=visibleSize.height+coin->getContentSize().height+50;
    auto move_duration=COIN2_SPEED*move_dis;
    auto coin_move=MoveBy::create(move_duration,Point(0,-move_dis));
    coin->runAction(Sequence::create(coin_move,RemoveSelf::create(true),nullptr));
    
}
