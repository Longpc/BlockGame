#ifndef __SPRITECREATOR_H__
#define __SPRITECREATOR_H__
#include "cocos2d.h"
#include "HelloWorldScene.h"
using namespace cocos2d;
class SimpleSpriteCreator : public cocos2d::Sprite {
public:
	SimpleSpriteCreator();
	~SimpleSpriteCreator();

	static SimpleSpriteCreator * create(std::string imgFile);

	void initOption();
	void addEvent();
	void touchEvent(cocos2d::Touch* touch, cocos2d::Vec2 _po);
	static int getType();


private:
	std::string filename;
};
#endif