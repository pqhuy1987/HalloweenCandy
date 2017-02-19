//
//  MainMenuScene.cpp
//  Halloween
//
//  Created by Yuning Jin on 10/25/14.
//
//

#include "MainMenuScene.h"
#include "Constants.h"
#include "audio/include/SimpleAudioEngine.h"
#include "GameScene.h"
#include "GameGuide.h"
#include "Credits.h"

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    auto scene = Scene::create();
    auto layer = MainMenuScene::create();
    scene->addChild(layer);
    return scene;
}

bool MainMenuScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    const float SCALE_TO_DEVICE = cocos2d::Director::getInstance()->getVisibleSize().width / DES_RES_X;
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("title.mp3", true);
    
    auto background = Sprite::create("BG_cropped.png");
    background->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    background->setScaleX(visibleSize.width/background->getContentSize().width);
    background->setScaleY(visibleSize.height/background->getContentSize().height);
    this->addChild(background);
    
    auto playItem = MenuItemImage::create("Play (1).png", "Play (2).png", CC_CALLBACK_1(MainMenuScene::GoToGuideScene, this));
    playItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height*0.4 + origin.y));
    playItem->setScale(SCALE_TO_DEVICE);
    auto CItem = MenuItemImage::create("credits1.png", "credits2.png", CC_CALLBACK_1(MainMenuScene::GoToCScene, this));
    CItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height*0.2 + origin.y));
    CItem->setScale(SCALE_TO_DEVICE);
    auto menu = Menu::create(playItem,CItem,NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu,11);
    
    auto gameTitleLabel= Label::createWithTTF("Halloween\n  Candy Rush", "FEASFBRG.TTF", visibleSize.width * SCORE_FONT);
    gameTitleLabel->setColor(Color3B::YELLOW);
    gameTitleLabel->setPosition(Point(visibleSize.width/2+origin.x, visibleSize.height*0.75+origin.y));
    this->addChild(gameTitleLabel,10);
    
    
    auto highScore = UserDefault::getInstance()->getIntegerForKey("HIGHSCORE", 0);
    auto tempHigh = cocos2d::__String::createWithFormat("Best Score: %i", highScore);
    auto highScoreLabel = Label::createWithTTF(tempHigh->getCString(), "FEASFBRG.TTF", visibleSize.width * SCORE_FONT * 0.5);
    highScoreLabel->setColor(Color3B::ORANGE);
    highScoreLabel->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height * 0.55 + origin.y));
    this->addChild(highScoreLabel);
    return true;
}

void MainMenuScene::GoToGuideScene(cocos2d::Ref * sender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    auto scene = GameGuide::createScene();
    Director::getInstance()->replaceScene(TransitionFlipX::create(TRANSITION_TIME, scene));

    
}

void MainMenuScene::GoToCScene(cocos2d::Ref * sender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button.mp3");
    auto scene = GuideScene::createScene();
    Director::getInstance()->replaceScene(TransitionPageTurn::create(TRANSITION_TIME, scene,true));

}