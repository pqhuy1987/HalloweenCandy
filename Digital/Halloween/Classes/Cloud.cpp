//
//  Cloud.cpp
//  Parallex_1
//
//  Created on 10/25/14.
//
//

#include "Cloud.h"

USING_NS_CC;

// Constructor
Cloud::Cloud()
{
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
}

// Cloud spawn
void Cloud::spawnCloud(cocos2d::Layer * layer)
{
    const float SCALE_TO_DEVICE = Director::getInstance()->getVisibleSize().width / DES_RES_X;
    auto cloudSprite = Sprite::create("Cloud.png");
    cloudSprite->setScale(SCALE_TO_DEVICE);
    auto random = CCRANDOM_0_1();
    auto cloudXPosition = random * visibleSize.width;
    auto cloudYPosition = origin.y+visibleSize.height+cloudSprite->getContentSize().height * SCALE_TO_DEVICE;
    cloudSprite->setPosition(Point(cloudXPosition, cloudYPosition));
    layer->addChild(cloudSprite);
    
    auto cloudMovement = MoveBy::create(0.01f * visibleSize.height * 1.3, Point(0, -visibleSize.height * 1.3));
    
    cloudSprite->runAction(cloudMovement);
}