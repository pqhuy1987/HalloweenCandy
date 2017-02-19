//
//  Credits.cpp
//  Halloween
//
//  Created by Yuning Jin on 10/26/14.
//
//

#include "Credits.h"
#include "MainMenuScene.h"
#include "Constants.h"
#include "audio/include/SimpleAudioEngine.h"

USING_NS_CC;

Scene* GuideScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GuideScene::create();
    scene->addChild(layer);
    return scene;
}

bool GuideScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    cocos2d::Vec2 center((cocos2d::Director::getInstance()->getVisibleSize().width / 2 + cocos2d::Director::getInstance()->getVisibleOrigin().x), (cocos2d::Director::getInstance()->getVisibleSize().height / 2 + cocos2d::Director::getInstance()->getVisibleOrigin().y));
    
    auto welcomePic=Sprite::create("Starter_bg.png");
    welcomePic->setPosition(Point(visibleSize.width/2+origin.x, visibleSize.height/2+origin.y));
    welcomePic->setScaleX(visibleSize.width/welcomePic->getContentSize().width);
    welcomePic->setScaleY(visibleSize.height/welcomePic->getContentSize().height);
    this->addChild(welcomePic);
    
    auto menuItem = MenuItemImage::create("Exit (1).png", "Exit (2).png", CC_CALLBACK_1(GuideScene::goToMainMenu, this));
    menuItem->setPosition(center.x, center.y - visibleSize.height*0.35);
    auto menu = Menu::create(menuItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);
    
    Guide_move();
    
    return true;
}

void GuideScene::Guide_move()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto gameTitleLabel= Label::createWithTTF("     Halloween\n   Candy Rush\n\n(C) 2014 Noctiz", "Lucky7.otf", visibleSize.height * SCORE_FONT * 0.5);
    gameTitleLabel->setColor(Color3B::WHITE);
    gameTitleLabel->setPosition(Point((visibleSize.width / 2) + origin.x, visibleSize.height * 0.55 + origin.y));
    this->addChild(gameTitleLabel,10);
    auto gameTitle= Label::createWithTTF("music/sfx credit to http://www.freesfx.co.uk", "Lucky7.otf", visibleSize.height * SCORE_FONT * 0.2);
    gameTitle->setColor(Color3B::WHITE);
    gameTitle->setPosition(Point((visibleSize.width / 2) + origin.x, visibleSize.height * 0.4 + origin.y));
    this->addChild(gameTitle,10);
}

void GuideScene::goToMainMenu(cocos2d::Ref *sender)
{
    // create() is static and creates an instance of the class; createScene creates cocos2d::scene*
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button.mp3");
    auto scene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionPageTurn::create(TRANSITION_TIME, scene,false));
}