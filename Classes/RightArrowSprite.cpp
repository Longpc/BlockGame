#include "RightArrowSprite.h"

using namespace cocos2d;
RightArrowSprite::RightArrowSprite() {}
RightArrowSprite::~RightArrowSprite(){}

RightArrowSprite* RightArrowSprite::create() {
	RightArrowSprite* rightArrow = new RightArrowSprite();
	if (rightArrow->initWithFile("rightBig.png")) {
		rightArrow->autorelease();
		rightArrow->initOption();
		rightArrow->addEvent();
		return rightArrow;
	}
	CC_SAFE_DELETE(rightArrow);
	return NULL;
}
void RightArrowSprite::initOption() {

}
void RightArrowSprite::addEvent() {
	auto listener = cocos2d::EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		cocos2d::Vec2 p = touch->getLocation();
		cocos2d::Rect rect = this->getBoundingBox();

		if (rect.containsPoint(p))
		{
			return true; 
		}


		return false; 
	};

	listener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		//RightArrowSprite::touchEvent(touch, touch->getLocation());
	};

	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 30);
}
/*
*Right Button CLick Event
*/
void RightArrowSprite::touchEvent(cocos2d::Touch* touch, cocos2d::Vec2 _po) {
	//HelloWorld * checker = new HelloWorld();
	//if (checker->checkLossGame()) return;
	if (HelloWorld::pubLossGameFlg) return;
	cocos2d::log("touch right Button");
	if (HelloWorld::countPosition < 3) {
		auto moveRightAction = MoveTo::create(0.5f, Vec2(HelloWorld::marioSprite->getPositionX() + 100, HelloWorld::marioSprite->getPositionY()));
		HelloWorld::marioSprite->runAction(moveRightAction);
		HelloWorld::countPosition++;
	}
	
}