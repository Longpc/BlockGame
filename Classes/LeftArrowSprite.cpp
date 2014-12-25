#include "LeftArrowSprite.h"
using namespace cocos2d;

LeftArrowSprite::LeftArrowSprite()
{
}


LeftArrowSprite::~LeftArrowSprite()
{
}
LeftArrowSprite* LeftArrowSprite::create() {
	LeftArrowSprite* leftArrow = new LeftArrowSprite();
	if (leftArrow->initWithFile("leftBig.png")) {
		leftArrow->autorelease();
		leftArrow->initOption();
		leftArrow->addEvent();
		return leftArrow;
	}
	CC_SAFE_DELETE(leftArrow);
	return NULL;
}
void LeftArrowSprite::initOption(){
	//
}
void LeftArrowSprite::addEvent() {
	auto listener = cocos2d::EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		cocos2d::Vec2 p = touch->getLocation();
		cocos2d::Rect rect = this->getBoundingBox();

		if (rect.containsPoint(p))
		{
			return true; // to indicate that we have consumed it.
		}

		return false; // we did not consume this event, pass thru.
	};

	listener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		//LeftArrowSprite::touchEvent(touch,touch->getLocation());
	};

	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 30);
}
void LeftArrowSprite::touchEvent(cocos2d::Touch* touch, cocos2d::Vec2 _po) {
	//Event
	if (HelloWorld::pubLossGameFlg) return;
	if (HelloWorld::countPosition > 1){
		cocos2d::log("Touch Left Button");
		auto moveRightAction = MoveTo::create(0.5f, Vec2(HelloWorld::marioSprite->getPositionX() - 100, HelloWorld::marioSprite->getPositionY()));
		HelloWorld::marioSprite->runAction(moveRightAction);
		HelloWorld::countPosition--;
	}
	
}