#include "WelcomeScene.h"
#include "Constants.h"
#include "audio/include/SimpleAudioEngine.h"
#include "MainMenuScene.h"

USING_NS_CC;

Scene* WelcomeScene::createScene()
{
    auto scene = Scene::create();
    auto layer = WelcomeScene::create();
    scene->addChild(layer);
    return scene;
}

bool WelcomeScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    const float SCALE_TO_DEVICE = Director::getInstance()->getVisibleSize().width / DES_RES_X;
    
    auto welcomePic=Sprite::create("Starter_bg.png");
    welcomePic->setPosition(Point(visibleSize.width/2+origin.x, visibleSize.height/2+origin.y));
    welcomePic->setScaleX(visibleSize.width/welcomePic->getContentSize().width);
    welcomePic->setScaleY(visibleSize.height/welcomePic->getContentSize().height);
    this->addChild(welcomePic);
    
    auto gameTitleLabel= Label::createWithTTF("Halloween\n  Sole", "FEASFBRG.TTF", visibleSize.width * SCORE_FONT);
    gameTitleLabel->setColor(Color3B::YELLOW);
    gameTitleLabel->setPosition(Point(visibleSize.width/2+origin.x, visibleSize.height*0.75+origin.y));
    this->addChild(gameTitleLabel,10);
    
    float scale_x=0.375;
    auto pp1=Sprite::create();
    pp1->setScale(SCALE_TO_DEVICE);
    pp1->setPosition(Point(visibleSize.width*0.2+origin.x, visibleSize.height*scale_x+origin.y));
    this->addChild(pp1,5);
    auto pp2=Sprite::create();
    pp2->setScale(SCALE_TO_DEVICE);
    pp2->setPosition(Point(visibleSize.width*0.4+origin.x, visibleSize.height*scale_x+origin.y));
    this->addChild(pp2,5);
    auto pp3=Sprite::create();
    pp3->setScale(SCALE_TO_DEVICE);
    pp3->setPosition(Point(visibleSize.width*0.6+origin.x, visibleSize.height*scale_x+origin.y));
    this->addChild(pp3,5);
    auto pp4=Sprite::create();
    pp4->setScale(SCALE_TO_DEVICE);
    pp4->setPosition(Point(visibleSize.width*0.8+origin.x, visibleSize.height*scale_x+origin.y));
    this->addChild(pp4,5);
    
    auto coin=Sprite::create("Candy (1).png");
    coin->setScale(SCALE_TO_DEVICE);
    coin->setPosition(visibleSize.width*0.5+origin.x, visibleSize.height*0.5+origin.y);
    Vector<SpriteFrame*> an0(3);
    an0.pushBack(SpriteFrame::create("Candy (1).png", Rect(0,0,64,43)));
    an0.pushBack(SpriteFrame::create("Candy (2) 2.png", Rect(0,0,96,63)));
    an0.pushBack(SpriteFrame::create("Candy (3) 2.png", Rect(0,0,128,84)));
    auto ani0=Animation::createWithSpriteFrames(an0,0.2f);
    auto anim_00=Animate::create(ani0);
    auto anim_0=RepeatForever::create(anim_00);
    coin->runAction(anim_0);
    this->addChild(coin,4);
    for (float x=0;x<1.1;x=x+0.25)
    {
        for (float y=0;y<1.1;y=y+0.25)
        {
            if (y==0.25||y==0.5)
            {
            float pos_x=visibleSize.width*x+origin.x;
            float pos_y=visibleSize.height*y+origin.y;
            candy_matrix(pos_x, pos_y);
            }
        }
    }
    
    Vector<SpriteFrame*> an1(4);
    an1.pushBack(SpriteFrame::create("Idle (1).png", Rect(0,0,140,145)));
    an1.pushBack(SpriteFrame::create("Idle (2).png", Rect(0,0,140,145)));
    an1.pushBack(SpriteFrame::create("Idle (3).png", Rect(0,0,140,145)));
    an1.pushBack(SpriteFrame::create("Idle (4).png", Rect(0,0,140,145)));
    auto ani1=Animation::createWithSpriteFrames(an1,0.1f);
    auto anim_11=Animate::create(ani1);
    auto anim_1=RepeatForever::create(anim_11);
    pp1->runAction(anim_1);
    
    Vector<SpriteFrame*> an2(4);
    an2.pushBack(SpriteFrame::create("Launch Idle (1).png", Rect(0,0,111,139)));
    an2.pushBack(SpriteFrame::create("Launch Idle (2).png", Rect(0,0,101,139)));
    an2.pushBack(SpriteFrame::create("Launch Idle (3).png", Rect(0,0,101,139)));
    an2.pushBack(SpriteFrame::create("Launch Idle (4).png", Rect(0,0,101,139)));
    auto ani2=Animation::createWithSpriteFrames(an2,0.1f);
    auto anim_22=Animate::create(ani2);
    auto anim_2=RepeatForever::create(anim_22);
    pp2->runAction(anim_2);
    
    Vector<SpriteFrame*> an3(4);
    an3.pushBack(SpriteFrame::create("Launch Idle (1) 2.png", Rect(0,0,140,146)));
    an3.pushBack(SpriteFrame::create("Launch Idle (2) 2.png", Rect(0,0,140,146)));
    an3.pushBack(SpriteFrame::create("Launch Idle (3) 2.png", Rect(0,0,140,146)));
    an3.pushBack(SpriteFrame::create("Launch Idle (4) 2.png", Rect(0,0,140,146)));
    auto ani3=Animation::createWithSpriteFrames(an3,0.1f);
    auto anim_33=Animate::create(ani3);
    auto anim_3=RepeatForever::create(anim_33);
    pp3->runAction(anim_3);
    
    Vector<SpriteFrame*> an4(4);
    an4.pushBack(SpriteFrame::create("Launch Idle (1) 3.png", Rect(0,0,133,148)));
    an4.pushBack(SpriteFrame::create("Launch Idle (2) 3.png", Rect(0,0,133,148)));
    an4.pushBack(SpriteFrame::create("Launch Idle (3) 3.png", Rect(0,0,133,148)));
    an4.pushBack(SpriteFrame::create("Launch Idle (4) 3.png", Rect(0,0,133,148)));
    auto ani4=Animation::createWithSpriteFrames(an4,0.1f);
    auto anim_44=Animate::create(ani4);
    auto anim_4=RepeatForever::create(anim_44);
    pp4->runAction(anim_4);
    
    this->scheduleOnce(schedule_selector(WelcomeScene::GoToMainMenuScene), WELCOME_SCREEN_DISP_TIME);
    
    return true;
}

void WelcomeScene::candy_matrix(float x, float y)
{
    const float SCALE_TO_DEVICE = Director::getInstance()->getVisibleSize().width / DES_RES_X;

    auto coin=Sprite::create("Candy (1).png");
    coin->setScale(SCALE_TO_DEVICE);
    coin->setPosition(x, y);
    Vector<SpriteFrame*> an0(3);
    an0.pushBack(SpriteFrame::create("Candy (1).png", Rect(0,0,64,43)));
    an0.pushBack(SpriteFrame::create("Candy (2) 2.png", Rect(0,0,96,63)));
    an0.pushBack(SpriteFrame::create("Candy (3) 2.png", Rect(0,0,128,84)));
    auto ani0=Animation::createWithSpriteFrames(an0,0.2f);
    auto anim_00=Animate::create(ani0);
    auto anim_0=RepeatForever::create(anim_00);
    coin->runAction(anim_0);
    this->addChild(coin,4);
}

void WelcomeScene::GoToMainMenuScene(float delta)
{
    auto scene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}
