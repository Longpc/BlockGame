#ifndef __RIGHTARRAW_H__
#define __RIGHTARRAW_H__
#include "cocos2d.h"
#include "HelloWorldScene.h"

using namespace cocos2d;
class RightArrowSprite : public cocos2d::Sprite
{
public:
	RightArrowSprite();
	~RightArrowSprite();
	static RightArrowSprite * create();

	void initOption();

	void addEvent();
	void touchEvent(cocos2d::Touch* touch, cocos2d::Vec2 _point);


private:
	cocos2d::Sprite* target;
};

#endif