#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#include <stdlib.h>
#include <cstdlib>
#include "cocos2d.h"
#include <vector>
#include "LeftArrowSprite.h"
#include "RightArrowSprite.h"
#include "ChangeButtonSprite.h"
#include "SimpleSpriteCreator.h"
#include "SimpleDraw.h"
#include "StartScene.h"
//#include "sqlite3\include\sqlite3.h"

using namespace std;
using namespace cocos2d;
class HelloWorld : public cocos2d::CCLayer
{
public:
	/*
	@param: gameMode can be value 1 or 2. This is the difficulty level
	@param: gameSPeed can be value 1 or 2. 1 is SLOW and 2 is FASTER
	*/
    static cocos2d::Scene* createScene(int gameMode, int gameSpeed);
	struct Item
	{
		cocos2d::Sprite* sprite;
		int	type;
		int skipped;
	}; 
	//Image Sprite
	static cocos2d::Sprite* marioSprite;
	static cocos2d::Sprite* fbSprite;
	static int countPosition;
	static int moveSpeed;
	//SimpleDraw* drawAction;
	//Move Sprite
	CCActionInterval* moveRight();

	static HelloWorld* create(int gameMode, int gameSpeed);
    bool init(int gameMode, int gameSpeed);  
    
	void update(float) override;
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	static bool pubLossGameFlg;
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void checkForSwap();
	virtual bool checkLossGame();
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
    // implement the "static create()" method manually
    //CREATE_FUNC(HelloWorld,int gameMode, int gameSpeed);
private:
	cocos2d::Label* touchInfo;
	cocos2d::Sprite* baseLine;
	cocos2d::Sprite* _leftArrow;
	cocos2d::Sprite* _rightArrow;
	cocos2d::Sprite* _changeButton;
	cocos2d::Sprite* _pauButton;
	cocos2d::Sprite* _resumeButton;
	int gameScore;
	/*define the base X position of column*/
	 int baseY;
	 int baseX1;
	 int baseX2;
	 int baseX3;
	 int baseX4;
	 /*For track the min values of column*/
	 int minY1;
	 int minY2;
	 int minY3;
	 int minY4;
	 int fallingItemNumber;
	 int topItemNumber;
	 int saveCollisionIndexItem1;
	 int saveCollisionIndexItem2;
	 bool stopFallingItem1;
	 bool stopFallingItem2;
	 bool initCompletedFlg;
	 bool lossGameFlg;
	 bool swappingFlg;
	 bool onPauseFlg;
	 bool remove1Flg;
	 bool remove2Flg;
	 std::vector<Item> fallingItemArray;
	 std::vector<Item> stoppedItemArray;

	 std::vector<int> leftToRightIndexArray;
	 std::vector<int> rightToLeftIndexArray;

	 Item topItem1;
	 Item topItem2;
	 Item fallingItem1;
	 Item fallingItem2;
	 int oldRandomPosition;
	 //Function
	virtual bool checkCollision(cocos2d::Sprite* target, cocos2d::Sprite* target2);
	virtual int checkColisionWithStopeditem(cocos2d::Sprite* target); //return index of collision item
	virtual cocos2d::Sprite* createSprite(int type);
	virtual HelloWorld::Item addNewItem();
	virtual Vec2 randomPosition(int topItemFlg); //topItemFLg: 0->TOP ITEM, 1->FALLING ITEM
	virtual void initFallingItem();
	virtual void createTopItem();
	virtual void checkSwapFallingItem();
	virtual void convertTopToFalling();
	virtual void showLossGameInfo();
	virtual bool checkToGetScore(int saveCossionIndex,Item fallingItem);
	virtual void increaseBaseY(Item fallingItem);
	//virtual bool checkSQL();
};

#endif // __HELLOWORLD_SCENE_H__