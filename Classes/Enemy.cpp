//
//  Enemy.cpp
//  BarfGame
//
//  Created by Usman  on 28/05/2014.
//
//

#include "Enemy.h"
#include "Joystick.h"
#define enemyvel 70
bool Enemy::init() {
    
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    _enemy = CCSprite::create("monkey-real.png");
    this->addChild(_enemy);
    _enemy ->setPosition(ccp(300,400));
    return true;
}

void Enemy::Ai_move(CCSprite*Player){
    
_player = Player;
 this->scheduleUpdate();
}

void Enemy::update(float dt) {
    float player_posx = _player->getPositionX();
    float player_posy = _player->getPositionY();
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCLog("X pos of enemy is %f", _enemy->getPositionX());
    CCLog ("Y pos of enemy is %f ", _enemy->getPositionY());
    float dist = sqrtf(pow((_enemy->getPositionX() - player_posx),2) + pow((_enemy->getPositionY() - player_posy),2));
    CCLog("the dist is %f",dist);
    
    if(dist < 200){
        float enemyposx =_enemy->getPositionX();
        float enemyposy = _enemy->getPositionY();
        
        float dely = enemyvel * 0.1;
        float delx = enemyvel * 0.1;
        int _xstate = Joystick::_xstate;
        int _ystate = Joystick::_ystate;
        
        if( _xstate == -1){
            delx = -delx;
        }
        
        if (_ystate == -1) {
            dely = -dely;
        }
        
        CCLog("Enemy x pos is %f ",enemyposx );
        
        
        CCLog("Enemy delx is %f ",delx );
        CCLog("Enemy delx is %f ",delx );
        
        if(checkvalidXmove(enemyposx+delx)) {
            _enemy->setPositionX(enemyposx+delx);
        }
        else {
               if(checkvalidXmove(enemyposx-delx))
                   _enemy->setPositionX(enemyposx-delx);
            
        }
        
        if(checkvalidYmove(enemyposy+dely)){
            _enemy->setPositionY(enemyposy+dely);
        }
        else {
            if(checkvalidYmove(enemyposy-dely))
                _enemy->setPositionY(enemyposy-dely);
        }
        
        
        //_enemy->setPosition(ccp(enemyposx + delx,enemyposy+dely));

    }
    
}


bool Enemy::checkvalidXmove(float posx){
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    if(posx > (_enemy->getContentSize().width/2) && posx < (winSize.width - (_enemy->getContentSize().width/2))) {
       float posy = _enemy ->getPositionY();
        if( posx < 155 && posy < 155 ) {
            return false;
        }
        
        return true;
    }
    return false;
}


bool Enemy::checkvalidYmove(float posy) {
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    if(posy > (_enemy->getContentSize().height/2) && posy < (winSize.height - (_enemy->getContentSize().height/2))) {
        
        float posx = _enemy->getPositionX();
        if( posx < 155 && posy < 155 ) {
            return false;
        }

        
        return true;
    }
    return false;
}

