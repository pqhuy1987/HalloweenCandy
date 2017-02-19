//
//  Coin.cpp
//  Halloween
//
//  Created by Yuning Jin on 10/25/14.
//
//

#include "CCoin.h"
#include "Constants.h"

USING_NS_CC;


CCoin::CCoin()
{
    visibleSize=Director::getInstance()->getVisibleSize();
    origin=Director::getInstance()->getVisibleOrigin();
}


void CCoin::spawnCCoin(cocos2d::Layer * layer)
{
    auto coin=Sprite::create("Shield.png");
    coin->setScale(1.5, 1.5);
    auto ran=CCRANDOM_0_1();
    auto posi_x=origin.x+coin->getContentSize().width/2+ran*(visibleSize.width-coin->getContentSize().width);
    auto posi_y=origin.y+visibleSize.height;

    
    auto body=PhysicsBody::createBox(coin->getContentSize()*1.5);
    
    body->setDynamic(false);
    body->setCollisionBitmask(CCOIN_COLLISION_BITMASK);
    body->setContactTestBitmask(CCOIN_CONTACT_BITMASK);
    coin->setPhysicsBody(body);
    
    coin->setPosition(Point(posi_x,posi_y));
    layer->addChild(coin,8);
    auto move_dis=visibleSize.height+coin->getContentSize().height+50;
    auto move_duration=CCOIN_SPEED*move_dis;
    auto coin_move=MoveBy::create(move_duration,Point(0,-move_dis));
    coin->runAction(Sequence::create(coin_move,RemoveSelf::create(true),nullptr));
    
}
