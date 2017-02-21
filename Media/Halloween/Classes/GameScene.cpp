//
//  GameScene.cpp
//  Halloween
//
//  Created by Yuning Jin on 10/25/14.
//
//

#include "GameScene.h"
#include "GameOverScene.h"
#include "Constants.h"
#include "audio/include/SimpleAudioEngine.h"
//#include "GameOverScene.h"
#include "Hero.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    auto scene = Scene::createWithPhysics();
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setGravity(Vect(0,0));
    auto layer = GameScene::create();
    layer->setPhysicsWorld(scene->getPhysicsWorld());
    scene->addChild(layer);
    
    return scene;
}

bool GameScene::init()
{
    const float SCALE_TO_DEVICE = Director::getInstance()->getVisibleSize().width / DES_RES_X;
    
    if ( !Layer::init() )
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    move_x=origin.x+visibleSize.width/2;
    move_y=origin.y+visibleSize.height/2;
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("main.mp3", true);
    
    Size edge_box=visibleSize;
    
    auto edgeBody = PhysicsBody::createEdgeBox(edge_box, PHYSICSBODY_MATERIAL_DEFAULT, 1);
    edgeBody->isResting();
    edgeBody->setCollisionBitmask(WALL_COLLISION_BITMASK);
    edgeBody->setContactTestBitmask(WALL_CONTACT_BITMASK);
    auto edgeNode = Node::create();
    edgeNode->setPosition(Point( visibleSize.width / 2 + origin.x,  visibleSize.height / 2+ origin.y ));
    edgeNode->setPhysicsBody(edgeBody);
    this->addChild(edgeNode);
    
    hero=new Hero(this);
    this->schedule(schedule_selector(GameScene::spawnCoin),visibleSize.height*COIN_SPAWN_FREQ);
    this->schedule(schedule_selector(GameScene::spawnCCoin),visibleSize.height*CCOIN_SPAWN_FREQ,kRepeatForever,25);
    this->schedule(schedule_selector(GameScene::spawnCoin2),visibleSize.height*COIN2_SPAWN_FREQ);
    this->schedule(schedule_selector(GameScene::spawnCoin2_2),visibleSize.height*COIN2_SPAWN_FREQ);
    this->schedule(schedule_selector(GameScene::spawnCoin3),visibleSize.height*COIN3_SPAWN_FREQ);
    this->schedule(schedule_selector(GameScene::spawnBat),visibleSize.height*BAT_SPAWN_FREQ);
    this->schedule(schedule_selector(GameScene::spawnBat2),visibleSize.height*BAT_SPAWN_FREQ);
    this->schedule(schedule_selector(GameScene::spawnBBat),visibleSize.height*BBAT_SPAWN_FREQ,kRepeatForever,30);
    auto MM=Sprite::create("Launch (5).png");
    MM->setScale(SCALE_TO_DEVICE);
    MM->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height*0.2));
    this->addChild(MM,10);
    Vector<SpriteFrame*> trix_ani(5);
    trix_ani.pushBack(SpriteFrame::create("Launch (5).png", Rect(0,0,280,289)));
    trix_ani.pushBack(SpriteFrame::create("Launch (6).png", Rect(0,0,280,289)));
    trix_ani.pushBack(SpriteFrame::create("Launch (7).png", Rect(0,0,280,289)));
    trix_ani.pushBack(SpriteFrame::create("Launch (8).png", Rect(0,0,280,289)));
    trix_ani.pushBack(SpriteFrame::create("Launch (9).png", Rect(0,0,280,289)));
    auto ani=Animation::createWithSpriteFrames(trix_ani,0.1f);
    auto anim_rr=Animate::create(ani);
    auto anim_r=Repeat::create(anim_rr,1);
    MM->runAction(Sequence::create(anim_r,RemoveSelf::create(true),nullptr));
    
    bk1 = Sprite::create("BG1.png");
    float scaleRatio = visibleSize.width / bk1->getContentSize().width;
    bk1->setScale(scaleRatio, scaleRatio);
    
    bk1->setAnchorPoint(Point(0,0));
    bk1->setPosition(Point(0, 0));
    
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
    
    this->schedule(schedule_selector(GameScene::scrollBk), 0.0001f, kRepeatForever, 0);
    
    
    
    auto touchListener = EventListenerTouchOneByOne::create();
    //touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::Touch, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GameScene::TouchMove, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GameScene::TouchEnd, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    auto score_bar=Sprite::create("score-bar.png");
    score_bar->setScale(SCALE_TO_DEVICE);
    score_bar->setPosition(score_bar->getContentSize().width * SCALE_TO_DEVICE / 2 + origin.x, visibleSize.height * 0.8 + origin.y);
    this->addChild(score_bar,50);
    
    __String *tempScore = cocos2d::__String::createWithFormat("%i", m_score);
    scoreLabel = Label::createWithTTF(tempScore->getCString(), "Lucky7.otf", visibleSize.width * SCORE_FONT*0.3);
    scoreLabel->setColor(Color3B::WHITE);
    scoreLabel->setPosition(score_bar->getContentSize().width * SCALE_TO_DEVICE / 2+ score_bar->getContentSize().width * SCALE_TO_DEVICE * 0.1 + origin.x, visibleSize.height * 0.795 + origin.y);
    this->addChild(scoreLabel, 51);
    
    this->scheduleUpdate();
    return true;
}

bool GameScene::Touch(cocos2d::Touch *touch, cocos2d::Event *event)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    // save to x y
    move_x=touch->getLocation().x;
    move_y=touch->getLocation().y;
    
    if (touch->getLocation().x<(hero->M_hero->getPosition().x) && hero_dead==0)
    {
        hero->set_move(move_x, move_y);
        hero_anim=1;
        hero_animation();
    }
    
    if (touch->getLocation().x>(hero->M_hero->getPosition().x) && hero_dead==0)
    {
        hero->set_move(move_x, move_y);
        hero_anim=2;
        hero_animation();
    }
    
    if (hero_dead==1)
    {
        hero->dead();
    }
    if (hero_dead==2)
    {
        hero->dead_fire();
    }
    
    return true;
}

void GameScene::TouchMove(cocos2d::Touch *touch, cocos2d::Event *event)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    // save to x y
    move_x=touch->getLocation().x;
    move_y=touch->getLocation().y;
    
    if (touch->getLocation().x<(hero->M_hero->getPosition().x) && hero_dead==0)
    {
        hero->set_move(move_x, move_y);
        hero_anim=1;
        hero_animation();
    }
    
    if (touch->getLocation().x>(hero->M_hero->getPosition().x) && hero_dead==0)
    {
        hero->set_move(move_x, move_y);
        hero_anim=2;
        hero_animation();
    }
    
    if (hero_dead==1)
    {
        hero->dead();
    }
    if (hero_dead==2)
    {
        hero->dead_fire();
    }
    
}

void GameScene::hero_animation()
{
    if (hero_anim==hero_anim_current||hero_inv>0)
    {
        return;
    }
    
    if (hero_anim==1)
    {
        hero->stop_ani();
        Vector<SpriteFrame*> trix_ani(5);
        trix_ani.pushBack(SpriteFrame::create("Lean Left (1).png", Rect(0,0,140,192)));
        trix_ani.pushBack(SpriteFrame::create("Lean Left (2).png", Rect(0,0,140,192)));
        trix_ani.pushBack(SpriteFrame::create("Lean Left (3).png", Rect(0,0,140,192)));
        trix_ani.pushBack(SpriteFrame::create("Lean Left (4).png", Rect(0,0,140,192)));
        trix_ani.pushBack(SpriteFrame::create("Lean Left (5).png", Rect(0,0,140,192)));
        auto ani=Animation::createWithSpriteFrames(trix_ani,0.1f);
        auto anim_rr=Animate::create(ani);
        auto anim_r=RepeatForever::create(anim_rr);
        hero->M_hero->runAction(anim_r);
        hero_anim_current=1;
    }
    else if (hero_anim==2)
    {
        hero->stop_ani();
        Vector<SpriteFrame*> trix_ani(5);
        trix_ani.pushBack(SpriteFrame::create("Lean Right (1).png", Rect(0,0,140,192)));
        trix_ani.pushBack(SpriteFrame::create("Lean Right (2).png", Rect(0,0,140,192)));
        trix_ani.pushBack(SpriteFrame::create("Lean Right (3).png", Rect(0,0,140,192)));
        trix_ani.pushBack(SpriteFrame::create("Lean Right (4).png", Rect(0,0,140,192)));
        trix_ani.pushBack(SpriteFrame::create("Lean Right (5).png", Rect(0,0,140,192)));
        auto ani=Animation::createWithSpriteFrames(trix_ani,0.1f);
        auto anim_rr=Animate::create(ani);
        auto anim_r=RepeatForever::create(anim_rr);
        hero->M_hero->runAction(anim_r);
        hero_anim_current=2;
    }
    else if (hero_anim==0)
    {
        hero->stop_ani();
        Vector<SpriteFrame*> trix_ani(4);
        trix_ani.pushBack(SpriteFrame::create("Jump (1).png", Rect(0,0,140,192)));
        trix_ani.pushBack(SpriteFrame::create("Jump (2).png", Rect(0,0,140,192)));
        trix_ani.pushBack(SpriteFrame::create("Jump (3).png", Rect(0,0,140,192)));
        trix_ani.pushBack(SpriteFrame::create("Jump (4).png", Rect(0,0,140,192)));
        auto ani=Animation::createWithSpriteFrames(trix_ani,0.1f);
        auto anim_rr=Animate::create(ani);
        auto anim_r=RepeatForever::create(anim_rr);
        hero->M_hero->runAction(anim_r);
        hero_anim_current=0;
    }
    
}

bool GameScene::onContactBegin(cocos2d::PhysicsContact &contact)
{
    auto *a = contact.getShapeA()->getBody();
    auto *b = contact.getShapeB()->getBody();
    if ((a->getContactTestBitmask() == HERO_CONTACT_BITMASK && b->getContactTestBitmask() == COIN_CONTACT_BITMASK)
        ||
        (b->getContactTestBitmask() == HERO_CONTACT_BITMASK && a->getContactTestBitmask() == COIN_CONTACT_BITMASK))
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("candy0.wav");
        if (b->getContactTestBitmask() == COIN_CONTACT_BITMASK)
        {
            b->getNode()->removeFromParent();
            
        }
        if (a->getContactTestBitmask() == COIN_CONTACT_BITMASK)
        {
            a->getNode()->removeFromParent();
        }
        
        //CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Coin.mp3");
        m_score++;
        
        auto tempScore = __String::createWithFormat("%i", m_score);
        scoreLabel->setString(tempScore->getCString());
    }
    if ((a->getContactTestBitmask() == HERO_CONTACT_BITMASK && b->getContactTestBitmask() == COIN2_CONTACT_BITMASK)
        ||
        (b->getContactTestBitmask() == HERO_CONTACT_BITMASK && a->getContactTestBitmask() == COIN2_CONTACT_BITMASK))
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("candy1.mp3");
        if (b->getContactTestBitmask() == COIN2_CONTACT_BITMASK)
        {
            b->getNode()->removeFromParent();
            
        }
        if (a->getContactTestBitmask() == COIN2_CONTACT_BITMASK)
        {
            a->getNode()->removeFromParent();
        }
        
        //CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Coin.mp3");
        m_score=m_score+5;
        
        auto tempScore = __String::createWithFormat("%i", m_score);
        scoreLabel->setString(tempScore->getCString());
    }
    if ((a->getContactTestBitmask() == HERO_CONTACT_BITMASK && b->getContactTestBitmask() == COIN3_CONTACT_BITMASK)
        ||
        (b->getContactTestBitmask() == HERO_CONTACT_BITMASK && a->getContactTestBitmask() == COIN3_CONTACT_BITMASK))
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("candy2.mp3");
        if (b->getContactTestBitmask() == COIN3_CONTACT_BITMASK)
        {
            b->getNode()->removeFromParent();
            
        }
        if (a->getContactTestBitmask() == COIN3_CONTACT_BITMASK)
        {
            a->getNode()->removeFromParent();
        }
        
        //CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Coin.mp3");
        m_score=m_score+10;
        
        auto tempScore = __String::createWithFormat("%i", m_score);
        scoreLabel->setString(tempScore->getCString());
    }
    
    
    if ((a->getContactTestBitmask() == HERO_CONTACT_BITMASK && b->getContactTestBitmask() == CCOIN_CONTACT_BITMASK)
        ||
        (b->getContactTestBitmask() == HERO_CONTACT_BITMASK && a->getContactTestBitmask() == CCOIN_CONTACT_BITMASK))
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("shield.mp3");
        hero_inv=3;
        hero->stop_ani();
        Vector<SpriteFrame*> trix_ani(4);
        trix_ani.pushBack(SpriteFrame::create("Rocket (1).png", Rect(0,0,140,264)));
        trix_ani.pushBack(SpriteFrame::create("Rocket (2).png", Rect(0,0,140,264)));
        trix_ani.pushBack(SpriteFrame::create("Rocket (3).png", Rect(0,0,140,264)));
        trix_ani.pushBack(SpriteFrame::create("Rocket (4).png", Rect(0,0,140,264)));
        auto ani=Animation::createWithSpriteFrames(trix_ani,0.1f);
        auto anim_rr=Animate::create(ani);
        auto anim_r=RepeatForever::create(anim_rr);
        hero->M_hero->runAction(anim_r);
        
        if (b->getContactTestBitmask() == CCOIN_CONTACT_BITMASK)
        {
            b->getNode()->removeFromParentAndCleanup(true);
            
        }
        if (a->getContactTestBitmask() == CCOIN_CONTACT_BITMASK)
        {
            a->getNode()->removeFromParentAndCleanup(true);
        }
    }
    
    if ((a->getContactTestBitmask() == HERO_CONTACT_BITMASK && b->getContactTestBitmask() == BAT_CONTACT_BITMASK)
        ||
        (b->getContactTestBitmask() == HERO_CONTACT_BITMASK && a->getContactTestBitmask() == BAT_CONTACT_BITMASK))
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("explosion.mp3");
        
        Vector<SpriteFrame*> an(8);
        an.pushBack(SpriteFrame::create("Collect (1).png", Rect(0,0,386,386)));
        an.pushBack(SpriteFrame::create("Collect (2).png", Rect(0,0,386,386)));
        an.pushBack(SpriteFrame::create("Collect (3).png", Rect(0,0,386,386)));
        an.pushBack(SpriteFrame::create("Collect (4).png", Rect(0,0,386,386)));
        an.pushBack(SpriteFrame::create("Collect (5).png", Rect(0,0,386,386)));
        an.pushBack(SpriteFrame::create("Collect (6).png", Rect(0,0,386,386)));
        an.pushBack(SpriteFrame::create("Collect (7).png", Rect(0,0,386,386)));
        an.pushBack(SpriteFrame::create("Collect (8).png", Rect(0,0,386,386)));
        auto ann=Animation::createWithSpriteFrames(an,0.1f);
        auto anim_ll=Animate::create(ann);
        auto anim_l=Repeat::create(anim_ll,1);
        if (b->getContactTestBitmask() == BAT_CONTACT_BITMASK)
        {
            b->getNode()->stopAllActions();
            b->getNode()->runAction(Sequence::create(anim_l,RemoveSelf::create(true), nullptr));
        }
        if (a->getContactTestBitmask() == BAT_CONTACT_BITMASK)
        {
            a->getNode()->stopAllActions();
            a->getNode()->runAction(Sequence::create(anim_l,RemoveSelf::create(true), nullptr));
        }
        
        if (hero_inv==0)
        {
            CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
            hero_die();
            this->scheduleOnce(schedule_selector(GameScene::game_over), 1.5f);
            
        }
        else
        {
            hero_inv--;
            if (hero_inv==0)
            {
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("shield_break.mp3");
                hero->stop_ani();
                Vector<SpriteFrame*> trix_ani(4);
                trix_ani.pushBack(SpriteFrame::create("Jump (1).png", Rect(0,0,140,192)));
                trix_ani.pushBack(SpriteFrame::create("Jump (2).png", Rect(0,0,140,192)));
                trix_ani.pushBack(SpriteFrame::create("Jump (3).png", Rect(0,0,140,192)));
                trix_ani.pushBack(SpriteFrame::create("Jump (4).png", Rect(0,0,140,192)));
                auto ani=Animation::createWithSpriteFrames(trix_ani,0.1f);
                auto anim_rr=Animate::create(ani);
                auto anim_r=RepeatForever::create(anim_rr);
                hero->M_hero->runAction(anim_r);
            }
        }

    }
    
    if ((a->getContactTestBitmask() == HERO_CONTACT_BITMASK && b->getContactTestBitmask() == BBAT_CONTACT_BITMASK)
        ||
        (b->getContactTestBitmask() == HERO_CONTACT_BITMASK && a->getContactTestBitmask() == BBAT_CONTACT_BITMASK))
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("bat.mp3");
        Vector<SpriteFrame*> an2(8);
        an2.pushBack(SpriteFrame::create("Smoke (1).png", Rect(0,0,386,386)));
        an2.pushBack(SpriteFrame::create("Smoke (2).png", Rect(0,0,386,386)));
        an2.pushBack(SpriteFrame::create("Smoke (3).png", Rect(0,0,386,386)));
        an2.pushBack(SpriteFrame::create("Smoke (4).png", Rect(0,0,386,386)));
        an2.pushBack(SpriteFrame::create("Smoke (5).png", Rect(0,0,386,386)));
        an2.pushBack(SpriteFrame::create("Smoke (6).png", Rect(0,0,386,386)));
        an2.pushBack(SpriteFrame::create("Smoke (7).png", Rect(0,0,386,386)));
        an2.pushBack(SpriteFrame::create("Smoke (8).png", Rect(0,0,386,386)));
        auto ann2=Animation::createWithSpriteFrames(an2,0.1f);
        auto anim_ll2=Animate::create(ann2);
        auto anim_l2=Repeat::create(anim_ll2,1);
        if (b->getContactTestBitmask() == BBAT_CONTACT_BITMASK)
        {
            b->getNode()->stopAllActions();
            b->getNode()->runAction(Sequence::create(anim_l2,RemoveSelf::create(true), nullptr));
        }
        if (a->getContactTestBitmask() == BBAT_CONTACT_BITMASK)
        {
            a->getNode()->stopAllActions();
            a->getNode()->runAction(Sequence::create(anim_l2,RemoveSelf::create(true), nullptr));
        }
        if (hero_inv==0)
        {
            CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
            hero_die();
            this->scheduleOnce(schedule_selector(GameScene::game_over), 1.5f);
            
        }
        else
        {
            hero_inv--;
            if (hero_inv==0)
            {
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("shield_break.mp3");
                hero->stop_ani();
                Vector<SpriteFrame*> trix_ani(4);
                trix_ani.pushBack(SpriteFrame::create("Jump (1).png", Rect(0,0,140,192)));
                trix_ani.pushBack(SpriteFrame::create("Jump (2).png", Rect(0,0,140,192)));
                trix_ani.pushBack(SpriteFrame::create("Jump (3).png", Rect(0,0,140,192)));
                trix_ani.pushBack(SpriteFrame::create("Jump (4).png", Rect(0,0,140,192)));
                auto ani=Animation::createWithSpriteFrames(trix_ani,0.1f);
                auto anim_rr=Animate::create(ani);
                auto anim_r=RepeatForever::create(anim_rr);
                hero->M_hero->runAction(anim_r);
            }
        }
    }
    
    return true;
}

void GameScene::game_over(float delta)
{
    auto scene = GameOverScene::createScene(m_score, bk1_posY);
    Director::getInstance()->replaceScene(TransitionFade::create(0, scene));
    this->removeAllChildrenWithCleanup(true);
}

void GameScene::hero_die()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("dead.mp3");
    this->unscheduleAllSelectors();
    Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
    hero->stop_ani();
    Vector<SpriteFrame*> trix_ani(8);
    trix_ani.pushBack(SpriteFrame::create("Dead (1).png", Rect(0,0,140,192)));
    trix_ani.pushBack(SpriteFrame::create("Dead (2).png", Rect(0,0,140,192)));
    trix_ani.pushBack(SpriteFrame::create("Dead (3).png", Rect(0,0,140,192)));
    trix_ani.pushBack(SpriteFrame::create("Dead (4).png", Rect(0,0,140,192)));
    trix_ani.pushBack(SpriteFrame::create("Dead (5).png", Rect(0,0,140,192)));
    trix_ani.pushBack(SpriteFrame::create("Dead (6).png", Rect(0,0,140,192)));
    trix_ani.pushBack(SpriteFrame::create("Dead (7).png", Rect(0,0,140,192)));
    trix_ani.pushBack(SpriteFrame::create("Dead (8).png", Rect(0,0,140,192)));
    auto ani=Animation::createWithSpriteFrames(trix_ani,0.1f);
    auto anim_rr=Animate::create(ani);
    auto anim_r=RepeatForever::create(anim_rr);
    hero->M_hero->runAction(anim_r);
    this->getScene()->getPhysicsWorld()->setGravity(Vect(0,-1000));
}


void GameScene::scrollBk(float delta)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    float scaleRatio = Director::getInstance()->getVisibleSize().width / bk5->getContentSize().width;
    
    float cloudSpawnDelay = bk1->getContentSize().height * 3.5 / (SCROLL_PIXEL * 60);
    
    // changed from 60
    this->schedule(schedule_selector(GameScene::spawnCloud), CLOUD_SPAWN_FREQ * visibleSize.height,kRepeatForever,cloudSpawnDelay);
    
    if (bk5->getPositionY() + bk5->getContentSize().height * scaleRatio <= Director::getInstance()->getVisibleSize().height + SCROLL_PIXEL)
        return;
    
    
    bk1->setPosition( Point(bk1->getPosition().x, bk1->getPosition().y - SCROLL_PIXEL));
    bk2->setPosition( Point(bk2->getPosition().x, bk2->getPosition().y - SCROLL_PIXEL));
    bk3->setPosition( Point(bk3->getPosition().x, bk3->getPosition().y - SCROLL_PIXEL));
    bk4->setPosition( Point(bk4->getPosition().x, bk4->getPosition().y - SCROLL_PIXEL));
    bk5->setPosition( Point(bk5->getPosition().x, bk5->getPosition().y - SCROLL_PIXEL));
    
    // Update position of bk1
    bk1_posY = bk1->getPositionY();
    
    /*
     if( bk1->getPosition().y < -bk1->boundingBox().size.height){
     bk1->setPosition( Point( bk2->getPosition().x, bk1->getPosition().y + bk2->boundingBox().size.height));
     }
     if( bk2->getPosition().y < -bk2->boundingBox().size.height){
     bk2->setPosition( Point( bk1->getPosition().x, bk2->getPosition().y + bk1->boundingBox().size.height));
     }
     */
}

void GameScene::spawnCloud(float dt)
{
    cloud.spawnCloud(this);
}

void GameScene::TouchEnd(cocos2d::Touch *touch, cocos2d::Event *event)
{
    hero_anim=0;
    hero_animation();
}

void GameScene::update(float delta)
{
    hero->move();
}

