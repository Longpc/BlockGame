#ifndef __CHANGEBUTTON_H__
#define __CHANGEBUTTON_H__
#include "cocos2d.h"
#include "HelloWorldScene.h"
using namespace cocos2d;
class ChangeButtonSprite : public cocos2d::Sprite
{
public:
	ChangeButtonSprite();
	~ChangeButtonSprite();

	static ChangeButtonSprite * create();

	void initOption();

	void addEvent();
	void touchEvent(cocos2d::Touch* touch, cocos2d::Vec2 _po);
};

#endif