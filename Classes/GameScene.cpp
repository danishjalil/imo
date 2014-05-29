//
//  GameScene.cpp
//  BarfGame
//
//  Created by Usman  on 28/05/2014.
//
//

#include "GameScene.h"
#define myvelocity 10;

USING_NS_CC;


CCScene* GameScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameScene *layer = GameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
CCSize winSize = CCDirector::sharedDirector()->getWinSize();
Player = CCSprite::create("puck.png");


_enemy = Enemy::create();

//Enemy =  CCSprite::create("puck.png");
this->addChild(Player);
joystick = Joystick::create();
freeze = PowerButton::create();
this->addChild(joystick);
this->addChild(_enemy);
this->addChild(freeze);
//this->addChild(Enemy);

Player->cocos2d::CCNode::setPosition(winSize.width/2,winSize.height/2);
Player->setScale(0.2);


//Enemy->setScale(0.4);
//Enemy->setPosition(ccp(200,400));
//Enemy->setColor(ccc3(200, 200, 255));
_enemy->Ai_move(Player);
this->scheduleUpdate();
return true;

}

int GameScene::getxstate(){
    return _xstate;
}

int GameScene::getystate(){
    return _ystate;
}



void GameScene::update(float dt) {
    
    //CCLOG("dt is %f",dt);
    if(freeze->getIspressed())
        CCLog("power button pressed");
    
    CCPoint cords = joystick->getVelocity();
    if (cords.x !=0  && cords.y != 0) {
    CCLog("x velocity is  %f",cords.x);
    CCLog("y velocity is  %f",cords.y);
    }
    
    float delx = cords.x * myvelocity;
    float dely = cords.y * myvelocity;
    
    _xstate = 0;
    _ystate = 0;
    
    if(delx > 0)
        _xstate = 1;
    
    if(delx < 0)
        _xstate = -1;
    
    if(dely > 0)
        _ystate = 1;
    
    if(dely < 0)
        _ystate = -1;
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    float PlayerSpriteWidth = Player->getContentSize().width/2*Player->getScaleX();
    float PlayerSpriteHeight = Player->getContentSize().height/2 * Player->getScaleY();
    
    float PlayerPosx = Player->getPositionX();
    float PlayerPosy = Player->getPositionY();
    
    float Winwidth = winSize.width;
    float Winheight = winSize.height;
    
    if (PlayerPosx + delx > PlayerSpriteWidth && PlayerPosx + delx < (Winwidth - (PlayerSpriteWidth)))
    {
    Player->cocos2d::CCNode::setPosition((Player->getPosition().x + delx), Player->getPosition().y);
    }
    
   
    if (PlayerPosy + dely > PlayerSpriteHeight && PlayerPosy + dely < (Winheight - (PlayerSpriteHeight)))
    {
    Player->cocos2d::CCNode::setPosition((Player->getPosition().x), Player->getPosition().y+dely);
    }
    
    
    
}
