#ifndef __LEFTARRAW_H__
#define __LEFTARRAW_H__

#include "cocos2d.h"
#include "HelloWorldScene.h"
using namespace cocos2d;
class LeftArrowSprite : public cocos2d::Sprite
{
public:
	LeftArrowSprite();
	~LeftArrowSprite();

	static LeftArrowSprite * create();

	void initOption();

	void addEvent();
	void touchEvent(cocos2d::Touch* touch, cocos2d::Vec2 _po);


private:
};

#endif