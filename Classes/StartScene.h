#ifndef __START_SCENE_H__
#define __START_SCENE_H__
#include "SimpleSpriteCreator.h"
#include "HelloWorldScene.h"
#include <stdio.h>
#include <cstdlib>
#include <vector>
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class StartScene : public cocos2d::CCLayer
{
public:
	///StartScene();
	///~StartScene();
	
	static cocos2d::Scene* createScene();
	static StartScene* create();
	virtual bool init() override;

	virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*);
	void checkAndStartGame();
	void startgame();
private:
	cocos2d::Sprite* startButton;
	cocos2d::Sprite* selectModeBoxSprite;
	cocos2d::Sprite* selectSpeedBoxSprite;
	cocos2d::Label* easyMode;
	cocos2d::Label* hardMode;
	cocos2d::Label* slowSpeed;
	cocos2d::Label* fastSpeed;
	int gameMode;
	int gameSpeed;
	cocos2d::Size size;
	bool touchButtonFlg = false;
};
#endif 