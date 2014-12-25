#include "SimpleSpriteCreator.h"

using namespace cocos2d;
SimpleSpriteCreator::SimpleSpriteCreator() {}
SimpleSpriteCreator::~SimpleSpriteCreator(){}

SimpleSpriteCreator* SimpleSpriteCreator::create(std::string filepath) {
	SimpleSpriteCreator* sprite = new SimpleSpriteCreator();
	if (sprite->initWithFile(filepath)) {
		sprite->autorelease();
		sprite->initOption();
		//sprite->addEvent();
		//sprite->setAnchorPoint(Vec2(0, 0));
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}
void SimpleSpriteCreator::initOption() {
	
}
void SimpleSpriteCreator::addEvent() {
	if (HelloWorld::pubLossGameFlg) return;
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
	listener->onTouchMoved = [=](cocos2d::Touch* touch, cocos2d::Event* event) {

	};
	listener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		SimpleSpriteCreator::touchEvent(touch, touch->getLocation());
	};

	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 30);
}
void SimpleSpriteCreator::touchEvent(cocos2d::Touch* touch, cocos2d::Vec2 _po) {
	//
	cocos2d::log("click to Sprite");
}