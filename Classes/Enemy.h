#ifndef __BarfGame__Enemy__
#define __BarfGame__Enemy__

#include <iostream>
#include "cocos2d.h"
#include <math.h>     
using namespace cocos2d;

class Enemy : public CCLayer
{
    
public:
    
    virtual bool init();
    CREATE_FUNC(Enemy);
    void Ai_move(CCSprite*Player); // moves relative to the Player
    void update(float dt);
private:
    CCSprite* _enemy;
    CCSprite* _player;
    bool checkvalidXmove(float posx);
    bool checkvalidYmove(float posy);

};


#endif /* defined(__BarfGame__Enemy__) */
