//
//  PowerButton.cpp
//  BarfGame
//
//  Created by Usman  on 29/05/2014.
//
//

#include "PowerButton.h"

bool PowerButton::init(){
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    this->setTouchEnabled(true);
    //CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, INT_MIN, true);
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    _powerbutton = CCSprite::create("power.png");
    this->addChild(_powerbutton);
    _powerbutton->cocos2d::CCNode::setPosition(winSize.width - _powerbutton->getContentSize().width/2, _powerbutton->getContentSize().height/2);
    isPressed = false;
    return true;
}


void PowerButton::ccTouchesBegan( CCSet *pTouches, CCEvent *pEvent )
{
    CCTouch *touch = (CCTouch*)pTouches->anyObject();
    
    CCPoint point = touch->getStartLocation();
    
    if (_powerbutton->boundingBox().containsPoint(point)){
        isPressed = true;
        
        
    }
    
}



void PowerButton::ccTouchesEnded (CCSet *pTouches, CCEvent *pEvent )
{
    //isPressed = false;
    
}


bool PowerButton::getIspressed() {
    return isPressed;
}


void PowerButton::setIspressedfalse () {
    isPressed = false;
}


