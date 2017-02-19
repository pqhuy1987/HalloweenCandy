//
//  GameOverScene.cpp
//  Halloween
//
//  Created by Yuning Jin on 10/26/14.
//
//

#include "GameOverScene.h"
#include "Constants.h"
#include "audio/include/SimpleAudioEngine.h"

USING_NS_CC;

int dispScore = 0;
float bk1_posY;

Scene* GameOverScene::createScene(int score, float off_Y)
{
    dispScore = score;
    bk1_posY = off_Y;
    auto scene = Scene::create();
    auto layer = GameOverScene::create();
    scene->addChild(layer);
    
    return scene;
}


bool GameOverScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    const float REAL_X = cocos2d::Director::getInstance()->getVisibleSize().width;
    const float SCALE_TO_DEVICE_X = cocos2d::Director::getInstance()->getVisibleSize().width / DES_RES_X;
    const float SCALE_TO_DEVICE_Y = cocos2d::Director::getInstance()->getVisibleSize().height / DES_RES_Y;
    //CCLOG("SCALE: %f", SCALE_TO_DEVICE);
    CCLOG("REAL_X: %f", REAL_X);
    
    cocos2d::Vec2 center((cocos2d::Director::getInstance()->getVisibleSize().width / 2 + cocos2d::Director::getInstance()->getVisibleOrigin().x), (cocos2d::Director::getInstance()->getVisibleSize().height / 2 + cocos2d::Director::getInstance()->getVisibleOrigin().y));
    
    // Background
    bk1 = Sprite::create("BG1.png");
    float scaleRatio = visibleSize.width / bk1->getContentSize().width;
    bk1->setScale(scaleRatio, scaleRatio);
    
    bk1->setAnchorPoint(Point(0, 0));
    bk1->setPosition(Point(0, bk1_posY));
    
    bk2 = Sprite::create("BG2.png");
    bk2->setAnchorPoint( Point(0,0) );
    bk2->setPosition( Point(0, bk1->getPositionY() + bk1->boundingBox().size.height -1) );
    bk2->setScale(scaleRatio, scaleRatio);
    
    bk3 = Sprite::create("BG3.png");
    bk3->setAnchorPoint( Point(0,0) );
    bk3->setPosition( Point(0, bk2->getPositionY() + bk2->boundingBox().size.height -1) );
    bk3->setScale(scaleRatio, scaleRatio);
    
    bk4 = Sprite::create("BG4.png");
    bk4->setAnchorPoint( Point(0,0) );
    bk4->setPosition( Point(0, bk3->getPositionY() + bk3->boundingBox().size.height -1) );
    bk4->setScale(scaleRatio, scaleRatio);
    
    bk5 = Sprite::create("BG5.png");
    bk5->setAnchorPoint( Point(0,0) );
    bk5->setPosition( Point(0, bk4->getPositionY() + bk4->boundingBox().size.height -1) );
    bk5->setScale(scaleRatio, scaleRatio);
    
    this->addChild(bk1, 0);
    this->addChild(bk2, 0);
    this->addChild(bk3, 0);
    this->addChild(bk4, 0);
    this->addChild(bk5, 0);
    
    this->schedule(schedule_selector(GameOverScene::backScrollBk), 0.0001f, kRepeatForever, 0);
    
    auto background = Sprite::create("Blank (2).png");
    background->setScale(SCALE_TO_DEVICE_X, SCALE_TO_DEVICE_X);
    background->setPosition(center.x, center.y);
    auto bannerPosX = background->getPositionX();
    auto bannerPosY = background->getPositionY();
    auto bannerSizeX = background->getContentSize().width * SCALE_TO_DEVICE_X;
    auto bannerSizeY = background->getContentSize().height * SCALE_TO_DEVICE_X;
    CCLOG("SCALE_X: %f", SCALE_TO_DEVICE_X);
    CCLOG("bannerSizeY: %f", bannerSizeY);
    //background->setScaleX(visibleSize.width/background->getContentSize().width);
    //background->setScaleY(visibleSize.height/background->getContentSize().height);
    this->addChild(background);
    
    auto game_over=Sprite::create("Title.png");
    game_over->setScale(SCALE_TO_DEVICE_X);
    //game_over->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height * 0.68 + origin.y));
    game_over->setPosition(Point(bannerPosX, bannerPosY + bannerSizeY / 2.5));
    this->addChild(game_over,1);
    
    auto tempScore = cocos2d::__String::createWithFormat("Score: %i", dispScore);
    scoreLabel = Label::createWithTTF(tempScore->getCString(), "FEASFBRG.TTF", visibleSize.width * SCORE_FONT * 0.5);
    scoreLabel->setColor(Color3B::YELLOW);
    //scoreLabel->setPosition(center.x, center.y);
    scoreLabel->setPosition(bannerPosX, bannerPosY);
    this->addChild(scoreLabel);
    
    ///////////////
    // HIGHSCORE //
    ///////////////
    UserDefault *ref = UserDefault::getInstance();
    auto highScore = ref->getIntegerForKey("HIGHSCORE", 0);
    
    
    if (dispScore > highScore)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("highscore.mp3");
        auto gameTitleLabel= Label::createWithTTF("New High Score", "FEASFBRG.TTF", visibleSize.width * SCORE_FONT * 0.5);
        gameTitleLabel->setColor(Color3B::RED);
        gameTitleLabel->setPosition(bannerPosX, bannerPosY + bannerSizeY * 0.78);
        this->addChild(gameTitleLabel,10);
        
    }
    
    if (dispScore > highScore)
    {
        highScore = dispScore;
        ref->setIntegerForKey("HIGHSCORE", highScore);
    }
    
    ref->flush();
    
    auto tempHigh = cocos2d::__String::createWithFormat("Best: %i", highScore);
    highScoreLabel = Label::createWithTTF(tempHigh->getCString(), "FEASFBRG.TTF", visibleSize.width * SCORE_FONT * 0.5);
    highScoreLabel->setColor(Color3B::ORANGE);
    //highScoreLabel->setPosition(Point(visibleSize.width / 2 + origin.x, center.y-background->getContentSize().height*0.28));
    highScoreLabel->setPosition(bannerPosX, bannerPosY - bannerSizeY * 0.28);
    this->addChild(highScoreLabel,2);
    
    
    // Place the menus
    auto retryItem = MenuItemImage::create("Replay (1).png", "Replay (2).png", CC_CALLBACK_1(GameOverScene::goToGameScene, this));
    retryItem->setScale(SCALE_TO_DEVICE_X);
    //retryItem->setPosition(center.x-visibleSize.width*0.2, center.y - visibleSize.height*0.25);
    retryItem->setPosition(bannerPosX - visibleSize.width * 0.2, bannerPosY - bannerSizeY * 0.7);
    
    auto menuItem = MenuItemImage::create("Exit (1).png", "Exit (2).png", CC_CALLBACK_1(GameOverScene::goToMainMenu, this));
    //menuItem->setPosition(center.x+visibleSize.width*0.2, center.y - visibleSize.height*0.25);
    menuItem->setScale(SCALE_TO_DEVICE_X);
    menuItem->setPosition(bannerPosX + visibleSize.width * 0.2, bannerPosY - bannerSizeY * 0.7);
    
    auto menu = Menu::create(retryItem, menuItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu,5);
    
    return true;
}

void GameOverScene::backScrollBk(float dt)
{
    float scaleRatio = Director::getInstance()->getVisibleSize().width / bk5->getContentSize().width;
    
    if (bk1->getPositionY() >= Director::getInstance()->getVisibleOrigin().y - BACK_SCROLL_PIXEL)
    {
        bk1->setPosition(Director::getInstance()->getVisibleOrigin());
        bk2->setPosition( Point(0, bk1->getPositionY() + bk1->boundingBox().size.height -1) );
        bk3->setPosition( Point(0, bk2->getPositionY() + bk2->boundingBox().size.height -1) );
        return;
    }
    
    bk1->setPosition( Point(bk1->getPosition().x, bk1->getPosition().y + BACK_SCROLL_PIXEL) );
    bk2->setPosition( Point(bk2->getPosition().x, bk2->getPosition().y + BACK_SCROLL_PIXEL) );
    bk3->setPosition( Point(bk3->getPosition().x, bk3->getPosition().y + BACK_SCROLL_PIXEL) );
    bk4->setPosition( Point(bk4->getPosition().x, bk4->getPosition().y + BACK_SCROLL_PIXEL) );
    bk5->setPosition( Point(bk5->getPosition().x, bk5->getPosition().y + BACK_SCROLL_PIXEL) );
    
}

void GameOverScene::goToMainMenu(cocos2d::Ref *sender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button.mp3");
    auto scene = MainMenuScene::createScene();
    
    Director::getInstance()->replaceScene(TransitionCrossFade::create(TRANSITION_TIME, scene));
}

void GameOverScene::goToGameScene(cocos2d::Ref *sender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button.mp3");
    auto scene = GameGuide::createScene();
    Director::getInstance()->replaceScene(TransitionFadeBL::create(TRANSITION_TIME, scene));
}