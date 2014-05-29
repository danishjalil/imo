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
    float minCornerdist();
    float distofpoints(float x1 , float y1 , float x2 , float y2 );
    enum Corners {corner1, corner2, corner3,corner4};
    Corners closest_corner;
};


#endif /* defined(__BarfGame__Enemy__) */
