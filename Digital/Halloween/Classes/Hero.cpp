//
//  Hero.cpp
//  Halloween
//
//  Created by Yuning Jin on 10/25/14.
//
//

#include "Hero.h"
#include "Constants.h"
#include "GameScene.h"

USING_NS_CC;

Hero::~Hero()
{
    dead();
}

Hero::Hero(cocos2d::Layer *layer)
{
    const float SCALE_TO_DEVICE = Director::getInstance()->getVisibleSize().width / DES_RES_X;
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    move_x=origin.x+visibleSize.width/2;
    move_y=origin.y+visibleSize.height/2;
    M_hero=Sprite::create("Jump (1).png");
    M_hero->setScale(SCALE_TO_DEVICE);
    M_hero->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 0.2));
    auto size=M_hero->getContentSize() * SCALE_TO_DEVICE;
    size.height=size.height*0.62;
    size.width=size.width*0.62;
    auto hero_b = PhysicsBody::createBox(size);
    //hero_b->setDynamic(false);
    hero_b->setRotationEnable(false);
    M_hero->setPhysicsBody(hero_b);
    hero_b->setCollisionBitmask(HERO_COLLISION_BITMASK);
    hero_b->setContactTestBitmask(HERO_CONTACT_BITMASK);
    Vector<SpriteFrame*> trix_ani(4);
    trix_ani.pushBack(SpriteFrame::create("Jump (1).png", Rect(0,0,140,192)));
    trix_ani.pushBack(SpriteFrame::create("Jump (2).png", Rect(0,0,140,192)));
    trix_ani.pushBack(SpriteFrame::create("Jump (3).png", Rect(0,0,140,192)));
    trix_ani.pushBack(SpriteFrame::create("Jump (4).png", Rect(0,0,140,192)));
    auto ani=Animation::createWithSpriteFrames(trix_ani,0.1f);
    auto anim_rr=Animate::create(ani);
    auto anim_r=RepeatForever::create(anim_rr);
    M_hero->runAction(anim_r);
    
    layer->addChild(M_hero, 100000);
    
    
}

void Hero::dead()
{
    stop_ani();
    Vector<SpriteFrame*> trix_ani_dead;
    trix_ani_dead.pushBack(SpriteFrame::create("Trix_dead.png", Rect(0,0,40,72)));
    auto ani_dead=Animation::createWithSpriteFrames(trix_ani_dead,0.1f);
    auto anim_dead=Animate::create(ani_dead);
    auto anim_d=RepeatForever::create(anim_dead);
    M_hero->runAction(anim_d);
}

void Hero::dead_fire()
{
    stop_ani();
    Vector<SpriteFrame*> trix_ani_dead;
    trix_ani_dead.pushBack(SpriteFrame::create("Trix_Fire.png", Rect(0,0,40,72)));
    auto ani_dead=Animation::createWithSpriteFrames(trix_ani_dead,0.1f);
    auto anim_dead=Animate::create(ani_dead);
    auto anim_d=RepeatForever::create(anim_dead);
    M_hero->runAction(anim_d);
    
}
void Hero::move()
{
    const float SCALE_TO_DEVICE = Director::getInstance()->getVisibleSize().width / DES_RES_X;

    if ((M_hero->getPositionX()-(M_hero->getContentSize().width * SCALE_TO_DEVICE)/2)<origin.x)
    {
        hero_atside=1;
    }
    else if ((M_hero->getPositionX()+(M_hero->getContentSize().width * SCALE_TO_DEVICE)/2)>(origin.x+visibleSize.width))
    {
        hero_atside=2;
    }
    else if ((M_hero->getPositionY()-(M_hero->getContentSize().height * SCALE_TO_DEVICE)/2)<origin.y)
    {
        hero_atside=3;
    }
    else if((M_hero->getPositionY()+(M_hero->getContentSize().height * SCALE_TO_DEVICE)/2)<(origin.y+visibleSize.height))
    {
        hero_atside=4;
    }
    else
    {
        hero_atside=0;
    }
    
    
    float xtoy=(move_y-M_hero->getPosition().y)/(move_x-M_hero->getPosition().x);
    M_hero->setPositionX(M_hero->getPositionX()+HERO_SPEED *(move_x-M_hero->getPosition().x));
    M_hero->setPositionY(M_hero->getPositionY()+HERO_SPEED*(move_y-M_hero->getPosition().y));
    
    
    /*
    if(move_y>M_hero->getPosition().y)
    {
        hero_move_ud=1;
    }
    else
    {
        hero_move_ud=2;
    }
    
    if (move_x>M_hero->getPosition().x)
    {
        hero_move_lr=2;
    }
    else
    {
        hero_move_lr=1;
    }

    
    if (hero_atside!=1&&hero_move_lr==1)
    {
        M_hero->setPositionX(M_hero->getPositionX()-HERO_SPEED *visibleSize.width);
        
    }
    else if (hero_atside!=2&&hero_move_lr==2)
    {
        M_hero->setPositionX(M_hero->getPositionX()+HERO_SPEED *visibleSize.width);
        
    }

    
    if (hero_atside!=3&&hero_move_ud==2)
    {
        M_hero->setPositionY(M_hero->getPositionY()-HERO_SPEED *xtoy*visibleSize.height);
        
    }
    else if (hero_atside!=4&&hero_move_ud==1)
    {
        M_hero->setPositionY(M_hero->getPositionY()+HERO_SPEED *xtoy*visibleSize.height);
        
    }
    /*
    else
    {
        M_hero->stopAllActions();
        
    }
     */
}