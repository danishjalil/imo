//
//  PowerButton.h
//  BarfGame
//
//  Created by Usman  on 29/05/2014.
//
//

#ifndef __BarfGame__PowerButton__
#define __BarfGame__PowerButton__


#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class PowerButton : public CCLayer
{
    
public:
    
    virtual bool init();
    CREATE_FUNC(PowerButton);
    CCSprite * _powerbutton;
    bool getIspressed();
    
    
private:
    
    bool isPressed;
    
    void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
};


#endif /* defined(__BarfGame__PowerButton__) */
