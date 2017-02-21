//
//  GameScene.h
//  Halloween
//
//  Created by Yuning Jin on 10/25/14.
//
//

#ifndef __Halloween__GameScene__
#define __Halloween__GameScene__

#include "cocos2d.h"
#include "Hero.h"
#include "physics/CCPhysicsShape.h"
#include "Coin.h"
#include "Coin2.h"
#include "Coin3.h"
#include "CCoin.h"
#include "Bat.h"
#include "BBat.h"
#include "Cloud.h"
#include "Constants.h"


class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameScene);
    void setPhysicsWorld(cocos2d::PhysicsWorld *world) {sceneWorld = world;}
    int getScore() const {return m_score;}
    void scrollBk(float dt);
    
    cocos2d::Sprite* bk1;
    cocos2d::Sprite* bk2;
    cocos2d::Sprite* bk3;
    cocos2d::Sprite* bk4;
    cocos2d::Sprite* bk5;
    
    void spawnCloud(float dt);
    Cloud cloud;
    
private:
    cocos2d::PhysicsWorld *sceneWorld;
    cocos2d::Label *scoreLabel;
    Hero *hero;
    Coin Coin;
    Coin2 Coin2;
    Coin3 Coin3;
    CCoin CCoin;
    Bat Bat;
    BBat BBat;
    float bk1_posY = 0;
    void hero_animation();
    
    bool onContactBegin(cocos2d::PhysicsContact &contact);
    bool Touch(cocos2d::Touch *touch, cocos2d::Event *event);
    void TouchMove(cocos2d::Touch *touch, cocos2d::Event *event);
    void TouchEnd(cocos2d::Touch *touch, cocos2d::Event *event);
    void update (float delta);
    void spawnCoin(float delta){Coin.spawnCoin(this);}
    void spawnCCoin(float delta){CCoin.spawnCCoin(this);}
    void spawnCoin2(float delta){Coin2.spawnCoin2(this);}
    void spawnCoin2_2(float delta){Coin2.spawnCoin2_2(this);}
    void spawnCoin3(float delta){Coin3.spawnCoin3(this);}
    void spawnBat(float delta){Bat.spawnBat(this);}
    void spawnBat2(float delta){Bat.spawnBat2(this);}
    void spawnBBat(float delta){BBat.spawnBBat(this,hero->M_hero->getPosition().x,hero->M_hero->getPosition().y);}
    void game_over(float delta);
    void hero_die();
    
    float move_x;
    float move_y;
    int hero_dead=0;//0->alive  1->spike dead 2->fireball dead
    int hero_inv=0;
    int hero_anim=0;//1->left 2->right
    int hero_anim_current=0;
    int m_score=0;

};



#endif /* defined(__Halloween__GameScene__) */
