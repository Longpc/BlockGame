#include "ChangeButtonSprite.h"
using namespace cocos2d;

ChangeButtonSprite::ChangeButtonSprite()
{
}


ChangeButtonSprite::~ChangeButtonSprite()
{
}
ChangeButtonSprite* ChangeButtonSprite::create() {
	ChangeButtonSprite* changeButton = new ChangeButtonSprite();
	if (changeButton->initWithFile("changeBig.png")) {
		changeButton->autorelease();
		changeButton->initOption();
		changeButton->addEvent();
		return changeButton;
	}
	CC_SAFE_DELETE(changeButton);
	return NULL;
}
void ChangeButtonSprite::initOption(){
	//
}
void ChangeButtonSprite::addEvent() {
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
		ChangeButtonSprite::touchEvent(touch, touch->getLocation());
	};

	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 30);
}
void ChangeButtonSprite::touchEvent(cocos2d::Touch* touch, cocos2d::Vec2 _po) {
	//Event
	//cocos2d::log("Touch Change Button");
	//HelloWorld * checker = new HelloWorld();
	//checker->checkForSwap();
}