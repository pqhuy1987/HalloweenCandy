//
//  GameGuide.cpp
//  Halloween
//
//  Created by Yuning Jin on 10/26/14.
//
//

#include "GameGuide.h"
#include "Constants.h"
#include "audio/include/SimpleAudioEngine.h"
#include "GameScene.h"
//#include "Guide.h"

USING_NS_CC;

Scene* GameGuide::createScene()
{
    auto scene = Scene::create();
    auto layer = GameGuide::create();
    scene->addChild(layer);
    return scene;
}


bool GameGuide::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    const float SCALE_TO_DEVICE = Director::getInstance()->getVisibleSize().width / DES_RES_X;
    
    auto bk1 = Sprite::create("BG1.png");
    float scaleRatio = visibleSize.width / bk1->getContentSize().width;
    bk1->setScale(scaleRatio, scaleRatio);
    
    bk1->setAnchorPoint(Point(0,0));
    bk1->setPosition(Point(0, 0));
    
    auto bk2 = Sprite::create("BG2.png");
    bk2->setAnchorPoint( Point(0,0) );
    bk2->setPosition( Point(0, bk1->getPositionY() + bk1->boundingBox().size.height -1) );
    bk2->setScale(scaleRatio, scaleRatio);
    
    auto bk3 = Sprite::create("BG3.png");
    bk3->setAnchorPoint( Point(0,0) );
    bk3->setPosition( Point(0, bk2->getPositionY() + bk2->boundingBox().size.height -1) );
    bk3->setScale(scaleRatio, scaleRatio);
    
    auto bk4 = Sprite::create("BG4.png");
    bk4->setAnchorPoint( Point(0,0) );
    bk4->setPosition( Point(0, bk3->getPositionY() + bk3->boundingBox().size.height -1) );
    bk4->setScale(scaleRatio, scaleRatio);
    
    auto bk5 = Sprite::create("BG5.png");
    bk5->setAnchorPoint( Point(0,0) );
    bk5->setPosition( Point(0, bk4->getPositionY() + bk4->boundingBox().size.height -1) );
    bk5->setScale(scaleRatio, scaleRatio);
    
    this->addChild(bk1, 0);
    this->addChild(bk2, 0);
    this->addChild(bk3, 0);
    this->addChild(bk4, 0);
    this->addChild(bk5, 0);
    auto MM=Sprite::create("Launch (1).png");
    MM->setScale(SCALE_TO_DEVICE);
    MM->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height*0.2));
    this->addChild(MM,10);
    Vector<SpriteFrame*> trix_ani(4);
    trix_ani.pushBack(SpriteFrame::create("Launch (1).png", Rect(0,0,280,289)));
    trix_ani.pushBack(SpriteFrame::create("Launch (2).png", Rect(0,0,280,289)));
    trix_ani.pushBack(SpriteFrame::create("Launch (3).png", Rect(0,0,280,289)));
    trix_ani.pushBack(SpriteFrame::create("Launch (4).png", Rect(0,0,280,289)));
    auto ani=Animation::createWithSpriteFrames(trix_ani,0.2f);
    auto anim_rr=Animate::create(ani);
    auto anim_r=RepeatForever::create(anim_rr);
    MM->runAction(anim_r);
    
    auto playItem = MenuItemImage::create("Blank.png", "Blank.png", CC_CALLBACK_1(GameGuide::GoToGameScene, this));
    playItem->setScale(SCALE_TO_DEVICE);
    playItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height*0.5 + origin.y));
    playItem->runAction(RotateBy::create(60, 3600));
    auto menu = Menu::create(playItem,NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu,11);
    
    auto game_title=Sprite::create("Launch.png");
    game_title->setPosition(Point(visibleSize.width/2+origin.x, visibleSize.height*0.68 + origin.y));
    game_title->setScale(SCALE_TO_DEVICE);
    this->addChild(game_title,10);
    /*
    auto gameTitleLabel= Label::createWithTTF("Tap/Drag to fly", "FEASFBRG.TTF", visibleSize.height * SCORE_FONT*0.7);
    gameTitleLabel->setColor(Color3B::YELLOW);
    gameTitleLabel->setPosition(Point(visibleSize.width/2+origin.x, visibleSize.height*0.6+origin.y));
    this->addChild(gameTitleLabel,10);
    */
    /*
    auto gameTitle= Label::createWithTTF("->      <-", "FEASFBRG.TTF", visibleSize.height * SCORE_FONT*0.5);
    gameTitle->setColor(Color3B::YELLOW);
    gameTitle->setPosition(Point(visibleSize.width/2+origin.x, visibleSize.height*0.5+origin.y));
    this->addChild(gameTitle,10);
    */
    return true;
}

void GameGuide::GoToGameScene(cocos2d::Ref * sender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("launch.mp3");
    auto scene = GameScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0, scene));
}

