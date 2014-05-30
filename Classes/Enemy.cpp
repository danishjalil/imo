//
//  Enemy.cpp
//  BarfGame
//
//  Created by Usman  on 28/05/2014.
//
//

#include "Enemy.h"
#include "Joystick.h"
#include "time.h"
#define enemyvel 70
bool Enemy::init() {
    
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    _enemy = CCSprite::create("new_enemy.png");
    this->addChild(_enemy);
    _enemy ->setPosition(ccp(300,400));
    //freezedEnemy = false;
    _enemystate = evasion;
    return true;
}

void Enemy::Ai_move(CCSprite*Player , CCArray * array){
    
_player = Player;
enemies_array = array;
 this->scheduleUpdate();
}

void Enemy::update(float dt) {
    
    if(_enemystate == frozen){
        
        return;
    }
    
    test_enemystates();
    
    
    float player_posx = _player->getPositionX();
    float player_posy = _player->getPositionY();
    float mincornerdist = minCornerdist();
    auto r = ((double) rand() / (RAND_MAX));
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    //CCLog("X pos of enemy is %f", _enemy->getPositionX());
    //CCLog ("Y pos of enemy is %f ", _enemy->getPositionY());
    float dist = sqrtf(pow((_enemy->getPositionX() - player_posx),2) + pow((_enemy->getPositionY() - player_posy),2));
    //CCLog("the dist is %f",dist);
    //CCFadeOut *fadeout = CCFadeOut::create(1.0f);
    
    if(_enemystate == evasion) {
    
    if (dist < 85) {
        
        _enemy->setOpacity(100);
    }
    
    else {
        
        _enemy->setOpacity(255);
        
    }
    
    if(dist < 200 && mincornerdist > 135){
        float enemyposx =_enemy->getPositionX();
        float enemyposy = _enemy->getPositionY();
        
        float dely = enemyvel * 0.2 * r;
        float delx = enemyvel * 0.2 * r;
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
        
        float dely = enemyvel * 0.1 * r;
        float delx = enemyvel * 0.15 * r;
        
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

    if (_enemystate == unfreezingFriend) {
        float myfriendx;
        float myfriendy;
        for(int i = 0 ; i<enemies_array->count(); i++){
            Enemy * myfriend = (Enemy*)enemies_array->objectAtIndex(i);
            if(myfriend->_enemystate == frozen) {
                myfriendx = myfriend->getPositionX();
                myfriendy = myfriend->getPositionY();
                break;
            }
        }
        float _enemyposx = _enemy->getPositionX();
        float _enemyposy = _enemy->getPositionY();
        
        float dely = enemyvel * 0.25 * r;
        float delx = enemyvel * 0.25 * r;
        /*
        if ((myfriendx - _enemyposx) < 0 ){
            delx = -delx;
        }
        
        if ((myfriendy - _enemyposy) > 0 ){
            dely = -dely;
        }
        */
        
        float distx = myfriendx - _enemyposx;
        float disty = myfriendy - _enemyposy;
        
        if( distx > 10) {
            
            _enemyposx = _enemyposx + delx;
            
        }
        
        if(distx < - 10) {
            _enemyposx = _enemyposx - delx;
        }
        
        
        CCLog("the delx is %f " , delx);
        CCLog("the dely is %f " , dely);
        
        
        


        //_enemy->cocos2d::CCNode::setPosition( (_enemyposx + delx), (_enemyposy + dely) );
    
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


void Enemy::setSpritePosition(float x , float y) {
    _enemy->setPositionX(x);
    _enemy->setPositionY(y);
}


GLubyte Enemy::getEnemyOpacity() {
   return (_enemy->getOpacity());
    
}

Enemy_states Enemy::getEnemyState(){
    
    return _enemystate;
}

void Enemy::test_enemystates() {
    for(int i = 0 ; i < enemies_array->count(); i++){
        auto myfriend = (Enemy*)enemies_array->objectAtIndex(i);
        if(myfriend->_enemystate == frozen){
            CCLog("Frozen");
        }
        if(myfriend->_enemystate == evasion){
            CCLog("evasion");
        }
        
        if(myfriend->_enemystate == unfreezingFriend){
            CCLog("unfreezing friend");
        }
        
    
    }
    
    
}










