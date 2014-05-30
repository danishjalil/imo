//
//  GameScene.h
//  BarfGame
//
//  Created by Usman  on 28/05/2014.
//
//

#ifndef __BarfGame__GameScene__
#define __BarfGame__GameScene__


#include "cocos2d.h"
#include "Joystick.h"
#include "Enemy.h"
#include "PowerButton.h"

USING_NS_CC;

class GameScene : public cocos2d::CCLayer
{
    void update(float dt);
    Joystick * joystick;
    CCSprite * Player;
    //const int enemy_array_lenth = 2;
    //std::vector<Enemy*> vec_enemies;
    CCArray * enemies_array;
    PowerButton * freeze;
    int _xstate;
    int _ystate;
    
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    int getxstate();
    
    int getystate();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    bool initialize_enemeies(int num);
    
    ~GameScene();
    
    // implement the "static node()" method manually
    CREATE_FUNC(GameScene);
};

#endif /* defined(__BarfGame__GameScene__) */
