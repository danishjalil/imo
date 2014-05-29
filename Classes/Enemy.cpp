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
    
    _enemy = CCSprite::create("new_enemy.png");
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
    float mincornerdist = minCornerdist();
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCLog("X pos of enemy is %f", _enemy->getPositionX());
    CCLog ("Y pos of enemy is %f ", _enemy->getPositionY());
    float dist = sqrtf(pow((_enemy->getPositionX() - player_posx),2) + pow((_enemy->getPositionY() - player_posy),2));
    CCLog("the dist is %f",dist);
    
    if(dist < 200 && mincornerdist > 135){
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
    
    if(dist < 200 && mincornerdist <= 135) {
        
        float enemyposx =_enemy->getPositionX();
        float enemyposy = _enemy->getPositionY();
        
        float dely = enemyvel * 0.1;
        float delx = enemyvel * 0.15;
        
        if(closest_corner == corner1){
            if(checkvalidXmove(enemyposx - delx)){
                _enemy->setPositionX(enemyposx-delx);
            }
            
            if(checkvalidYmove(enemyposy - dely)){
                _enemy->setPositionY(enemyposy-dely);
            }
        }
    
        if(closest_corner == corner2){
            if(checkvalidXmove(enemyposx - delx)){
                _enemy->setPositionX(enemyposx-delx);
            }
            
            if(checkvalidYmove(enemyposy + dely)){
                _enemy->setPositionY(enemyposy + dely);
            }
        }
        
        if(closest_corner == corner3){
            if(checkvalidXmove(enemyposx + delx)){
                _enemy->setPositionX(enemyposx+delx);
            }
            
            if(checkvalidYmove(enemyposy + dely)){
                _enemy->setPositionY(enemyposy + dely);
            }
        }
 
        if(closest_corner == corner4){
            if(checkvalidXmove(enemyposx + delx)){
                _enemy->setPositionX(enemyposx+delx);
            }
            
            if(checkvalidYmove(enemyposy - dely)){
                _enemy->setPositionY(enemyposy - dely);
            }
        }
        
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

float Enemy::minCornerdist() {
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    std::vector<float> min_dist_vec;
    float enemyposx = _enemy->getPositionX();
    float enemyposy = _enemy->getPositionY();
    float min_dist3 = distofpoints(enemyposx, enemyposy, 155, 155);
    float min_dist4 = distofpoints(enemyposx, enemyposy, 0,winSize.height);
    float min_dist2 = distofpoints(enemyposx, enemyposy, (winSize.width - 155), 155);
    float min_dist1 = distofpoints(enemyposx, enemyposy, winSize.width, winSize.height);
    min_dist_vec.push_back(min_dist1);
    min_dist_vec.push_back(min_dist2);
    min_dist_vec.push_back(min_dist3);
    min_dist_vec.push_back(min_dist4);
    float min_dist_real =  *std::min_element(min_dist_vec.begin(), min_dist_vec.end());
    if (min_dist_real == min_dist1){
        CCLog("close to corner 1");
        closest_corner = corner1;
    }
    
    if (min_dist_real == min_dist2){
        CCLog("close to corner 2");
        closest_corner = corner2;
    }
    
    if (min_dist_real == min_dist3){
        CCLog("close to corner 3");
        closest_corner = corner3;
    }
    
    if (min_dist_real == min_dist4){
        CCLog("close to corner 4");
        closest_corner = corner4;
    }
    
    CCLog("min dist is %f ", min_dist_real);
    return min_dist_real;
}


float Enemy::distofpoints(float x1 , float y1 , float x2 , float y2 ){
    float dist = sqrtf(pow((x1 - x2),2) + pow((y1 - y2),2));
    return dist;
    
}






