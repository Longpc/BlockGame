#include "HelloWorldScene.h"
/*define for game speed*/
#define FAST 1.0f
#define SLOW 2.0f
USING_NS_CC;
/*Struct store image and type of item*/
struct Item
{
	cocos2d::Sprite* sprite;
	int	type;
	int skipped = 0;
};

/*Mario sprite*/
cocos2d::Sprite* HelloWorld::marioSprite = NULL;
/*Default position of mario sprite*/
int HelloWorld::countPosition = 2;
/*Item fall down speed */
int HelloWorld::moveSpeed = 150; //NO LONGER USE
/*Left arrow to move mario to the left*/
cocos2d::Sprite* _leftArrow;
/*Right arrow to move mario to the right*/
cocos2d::Sprite* _rightArrow;
/*Button to swap collum*/
cocos2d::Sprite* _changeButton;
//image Sprite
cocos2d::Sprite* HelloWorld::fbSprite = NULL;
bool HelloWorld::pubLossGameFlg = false;

Scene* HelloWorld::createScene(int gameMode, int gameSpeed)
{
    // 'scene' is an autorelease object
	auto scene = cocos2d::Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create(gameMode, gameSpeed);
    // add layer as a child to scene
    scene->addChild(layer);

	//cocos2d::log("param GM: %d, GS: %d", gameMode, gameSpeed);
    // return the scene
    return scene;
}
HelloWorld* HelloWorld::create(int gameMode, int gameSpeed) {
	HelloWorld *layer = new HelloWorld();
	if (layer->init(gameMode, gameSpeed)) {
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return NULL;
}
	/*init function*/
bool HelloWorld::init(int gameMode, int gameSpeed)
{
	//cocos2d::log("param GM: %d, GS: %d", gameMode, gameSpeed);
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	HelloWorld::gameScore = 0;
	HelloWorld::baseY = visibleSize.height - 100;
	HelloWorld::fallingItemNumber = 2;
	HelloWorld::topItemNumber = 0;
	HelloWorld::oldRandomPosition = 1;
	HelloWorld::initCompletedFlg = false;
	HelloWorld::lossGameFlg = false;
	HelloWorld::stopFallingItem1 = false;
	HelloWorld::stopFallingItem2 = false;
	HelloWorld::swappingFlg = false;
	HelloWorld::onPauseFlg = false;
	HelloWorld::saveCollisionIndexItem1 = -1;
	HelloWorld::saveCollisionIndexItem2 = -1;
	baseX1 = visibleSize.width / 2 - 150;
	baseX2 = visibleSize.width / 2 - 50;
	baseX3 = visibleSize.width / 2 + 50;
	baseX4 = visibleSize.width / 2 + 150;
	/*reset min Y*/
	minY1 = 0;
	minY2 = 0;
	minY3 = 0;
	minY4 = 0;
   /* auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2)); 

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1); */
	cocos2d::log("Visibale Size: Width: %d, Height: %d", int(visibleSize.width), int(visibleSize.height));
	//Add button
	_leftArrow = LeftArrowSprite::create();
	_leftArrow->setPosition(Vec2(visibleSize.width/2 - 400, visibleSize.height/2));
	addChild(_leftArrow, 1);
	_pauButton = SimpleSpriteCreator::create("pause.png");
	_pauButton->setPosition(Vec2(visibleSize.width / 2 - 400, visibleSize.height - 150));
	addChild(_pauButton, 1);
	_resumeButton = SimpleSpriteCreator::create("resume.png");
	_resumeButton->setPosition(Vec2(visibleSize.width / 2 - 400, visibleSize.height - 150));
	_resumeButton->setVisible(false);
	addChild(_resumeButton, 1);
	_rightArrow = RightArrowSprite::create();
	_rightArrow->setPosition(Vec2(visibleSize.width/2 + 400, visibleSize.height/2));
	addChild(_rightArrow, 1);
	_changeButton = ChangeButtonSprite::create();
	_changeButton->setPosition(Vec2(visibleSize.width / 2 + 400, visibleSize.height - 150));
	addChild(_changeButton);
	//Create Sprite and Add to scene
	
	baseLine = SimpleSpriteCreator::create("line.png");
	baseLine->setPosition(Vec2(visibleSize.width/2, 120));
	addChild(baseLine, 1);
	marioSprite = SimpleSpriteCreator::create("mario.png");
	marioSprite->setPosition(Vec2(visibleSize.width / 2, 50));
	addChild(marioSprite, 2);
	/*FIrstItem */
	
	srand(time(NULL));
	createTopItem();
	initFallingItem();
	int mode;
	//cocos2d::log("game Speed: %d", gameSpeed);
	switch (gameSpeed)
	{
	case 1: mode = SLOW;
		break;
	case 2: mode = FAST;
		break;
	default:
		mode = SLOW;
		break;
	}
	this->schedule(schedule_selector(HelloWorld::update),mode);
	//cocos2d::log("schedule speed: %d", mode);
	//Mouse event
	auto touchListener = EventListenerTouchOneByOne::create();

	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(HelloWorld::onTouchCancelled, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	//Key Event
	auto keyEvent = EventListenerKeyboard::create();
	keyEvent->setEnabled(true);
	keyEvent->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	keyEvent->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyEvent, this);
    return true;

}
void HelloWorld::initFallingItem() {
	if (initCompletedFlg) return;
	fallingItem1 = addNewItem();
	fallingItem1.sprite->setPosition(randomPosition(1));
	addChild(fallingItem1.sprite,1);
	fallingItem2 = addNewItem();
	fallingItem2.sprite->setPosition(randomPosition(1));
	addChild(fallingItem2.sprite, 1);
	initCompletedFlg = true;
}
void HelloWorld::createTopItem() {
	//if (HelloWorld::topItemNumber == 2) return;
	topItem1 = addNewItem();
	topItem1.sprite->setPosition(randomPosition(0));
	addChild(topItem1.sprite, 1);
	topItem2 = addNewItem();
	topItem2.sprite->setPosition(randomPosition(0));
	addChild(topItem2.sprite, 1);
	topItemNumber = 2;
}
void HelloWorld::update(float frameNumber) {
	//cocos2d::log("frame is %f", frameNumber);
	//cocos2d::log("StopedItem Array size: %d", stoppedItemArray.size());
	///BUG WHEN SET TOP --> FALLING
	if (initCompletedFlg != true || swappingFlg == true || onPauseFlg == true/* || (int(frameNumber) %2000 != 0):*/) return;
	if (checkLossGame()) {
		showLossGameInfo();
		return;
	}
	saveCollisionIndexItem1 = checkColisionWithStopeditem(fallingItem1.sprite);
	if (!checkCollision(fallingItem1.sprite, baseLine) &&  saveCollisionIndexItem1 == -1){
			auto position = fallingItem1.sprite->getPosition();
			position.y -= 50;
			fallingItem1.sprite->setPosition(position);
		
	}
	else {
		stopFallingItem1 = true;
	}
	saveCollisionIndexItem2 = checkColisionWithStopeditem(fallingItem2.sprite);
	if (!checkCollision(fallingItem2.sprite, baseLine) && saveCollisionIndexItem2 == -1 ){
			auto position = fallingItem2.sprite->getPosition();
			position.y -= 50;
			fallingItem2.sprite->setPosition(position);
	}
	else {
		stopFallingItem2 = true;
	}
	if (stopFallingItem1 && stopFallingItem2) {
		convertTopToFalling();
		stopFallingItem1 = false;
		stopFallingItem2 = false;
		Item *p = &topItem1;
		p = NULL;
		Item *p2 = &topItem2;
		p2 = NULL;
		createTopItem();
		return;
	}
	
}
bool HelloWorld::checkToGetScore(int saveIndex, Item fallingItem) {
	cocos2d::log("Save Index: %d, Array length: %d", saveIndex, stoppedItemArray.size());
	if (saveIndex >=0) {
		if (stoppedItemArray[saveIndex].type == fallingItem.type) {
			removeChild(stoppedItemArray[saveIndex].sprite);
			removeChild(fallingItem.sprite);
			stoppedItemArray.erase(stoppedItemArray.begin() + saveIndex);
			gameScore += 5;
			return true;
		}
		}
	return false;
	}

void HelloWorld::convertTopToFalling() {
	if (checkLossGame()) {
		showLossGameInfo();
		return;
	}	
	/*
	if (saveCollisionIndexItem1 != -1) {
		if (stoppedItemArray[saveCollisionIndexItem1].type == fallingItem1.type) {
			removeChild(stoppedItemArray[saveCollisionIndexItem1].sprite);
			removeChild(fallingItem1.sprite);
			stoppedItemArray.erase(stoppedItemArray.begin() + saveCollisionIndexItem1);
			gameScore += 5;
		}
		else {
			stoppedItemArray.push_back(fallingItem1);
		}
	}
	else {
		stoppedItemArray.push_back(fallingItem1);
	}
	*/
	bool noRemoveFlg = false;
	if (checkToGetScore(saveCollisionIndexItem1, fallingItem1) == false) {
		noRemoveFlg = true;
		stoppedItemArray.push_back(fallingItem1);

	}

	Item *p = &fallingItem1;
	//CC_SAFE_DELETE(p);
	p = NULL;
	fallingItem1 = topItem1;
	Vec2 pos = fallingItem1.sprite->getPosition();
	pos.y = baseY;
	fallingItem1.sprite->setPosition(pos);

	/*if (saveCollisionIndexItem2 != -1) {
		if (stoppedItemArray[saveCollisionIndexItem2].type == fallingItem2.type) {
			removeChild(stoppedItemArray[saveCollisionIndexItem2].sprite);
			removeChild(fallingItem2.sprite);
			stoppedItemArray.erase(stoppedItemArray.begin() + saveCollisionIndexItem2);
			gameScore += 5;
		}
		else {
			stoppedItemArray.push_back(fallingItem2);
		}
	} */
	if (noRemoveFlg == false && saveCollisionIndexItem1 < saveCollisionIndexItem2) saveCollisionIndexItem2 -= 1;
	if (checkToGetScore(saveCollisionIndexItem2, fallingItem2) == false) {
		stoppedItemArray.push_back(fallingItem2);
	}	
	Item *p2 = &fallingItem2;
	//CC_SAFE_DELETE(p2);
	p2 = NULL;
	fallingItem2 = topItem2;
	Vec2 pos2 = fallingItem2.sprite->getPosition();
	pos2.y = baseY;
	fallingItem2.sprite->setPosition(pos2);
		
	saveCollisionIndexItem1 = -1;
	saveCollisionIndexItem2 = -1;
}
void HelloWorld::increaseBaseY(Item item) {
	auto pos = item.sprite->getPositionX();
	/*if (pos == baseX1) {
		//min 
	} */
}
void HelloWorld::showLossGameInfo() {
	auto label = LabelTTF::create("GAME OVER\n:", "ARIAL", 40);
	CCUserDefault *def = CCUserDefault::sharedUserDefault();
	int highScore = def->getIntegerForKey("HIGH_SCORE");
	cocos2d::log("Hscore in key: %d", highScore);
	if (gameScore > highScore) {
		highScore = gameScore;
		def->setIntegerForKey("HIGH_SCORE", highScore);
		def->flush();
	}
	std::stringstream ss;
	ss << "GAME OVER\nSCORE: " << gameScore <<"\nHIGH SCORE : "<<highScore;
	label->setString(ss.str().c_str());
	unschedule(schedule_selector(HelloWorld::update));
	cocos2d::log("Score: %d", gameScore);
	label->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2 +100));
	addChild(label, 10);
	return;
}

HelloWorld::Item HelloWorld::addNewItem() {
	
	int randomType = rand() % 6 + 1;
	Item temp;
	temp.sprite = createSprite(randomType);
	temp.type = randomType;
	temp.skipped = 0;
	//fallingItem.push_back(temp);
	return temp;
}

Vec2 HelloWorld::randomPosition(int Flg) {
	int randomPosition = rand() % 4 + 1;
	while (randomPosition == HelloWorld::oldRandomPosition)
	{
		randomPosition = rand() % 4 + 1;
	}
	HelloWorld::oldRandomPosition = randomPosition;
	int rtY;
	if (Flg == 0) {
		rtY = baseY + 50; //TOP ITEM
	}
	else {
		rtY = baseY;      //FALLING ITEM BASE Y
	}
	switch (randomPosition)
	{
	case 1:
		return Vec2(baseX1, rtY);
	case 2:
		return Vec2(baseX2, rtY);
	case 3:
		return Vec2(baseX3, rtY);
	case 4:
		return Vec2(baseX4, rtY);
	default:
		return Vec2(0, 0);
		break;
	}
}
int HelloWorld::checkColisionWithStopeditem(cocos2d::Sprite* object) {
	if (stoppedItemArray.size() < 1) return -1;
	if (swappingFlg) return -1;
	for (int i = 0; i < stoppedItemArray.size() ; i++)
	{
		if (checkCollision(object, stoppedItemArray[i].sprite))
			return i;
	}
	return -1;
}
bool HelloWorld::checkCollision(cocos2d::Sprite* target1, cocos2d::Sprite* target2) {
	CCRect target2Box = CCRectMake(target2->getPosition().x-target2->getContentSize().width/2, target2->getPosition().y-target2->getContentSize().height/2, target2->getContentSize().width, target2->getContentSize().height+10);
	if (target1->boundingBox().intersectsRect(target2Box)) {
		return true;
	}
	return false;
}

bool HelloWorld::checkLossGame() {
	if (lossGameFlg) return true;
	if (stoppedItemArray.size() < 1) return false;
	for (int i = 0; i < stoppedItemArray.size(); i++)
	{
		if (stoppedItemArray[i].sprite->getPosition().y >= baseY) {
			cocos2d::log("Die by item->index: %d", i);
			lossGameFlg = true;
			pubLossGameFlg = true;
			return true;
		}
	}
	return false;
}
/*
bool HelloWorld::checkSQL() {
	sqlite3 *pdb = NULL;
	std::string path = CCFileUtils::sharedFileUtils()->getWritablePath() + "save.db3";
	std::string sql;
	int result;
	result = sqlite3_open(path.c_str(), &pdb);
	if (result != SQLITE_OK) {
		CCLog("open database failed,  number%d", result);
		return false;
	}
	return true;
} */
cocos2d::Sprite* HelloWorld::createSprite(int type) {
	cocos2d::Sprite* temp = cocos2d::Sprite::create("bug.png");
	switch (type)
	{
	case 1:
		temp = SimpleSpriteCreator::create("chrome.png");
		return temp;
		break;
	case 2:
		temp = SimpleSpriteCreator::create("fb.png");
		return temp;
		break;
	case 3: 
		temp = SimpleSpriteCreator::create("fl.png");
		return temp;
		break;
	case 4: 
		temp = SimpleSpriteCreator::create("ie.png");
		return temp;
		break;
	case 6:
		temp = SimpleSpriteCreator::create("youtube.png");
		return temp;
		break;
	case 5: 
		temp = SimpleSpriteCreator::create("twiter.png");
		return temp;
		break;
	default:
		return temp;
		break;
	}
}
void HelloWorld::checkForSwap() {
	int mPos = countPosition;
	
	/*int marioCurPos = marioSprite->getPosition().x;
	int leftX = marioCurPos - 50;
	int rightX = marioCurPos + 50; */
	int leftX;
	int rightX;
	switch (mPos)
	{
	case 1:
		leftX = baseX1;
		rightX = baseX2;
		break;
	case 2:
		leftX = baseX2;
		rightX = baseX3;
		break;
	case 3:
		leftX = baseX3;
		rightX = baseX4;
		break;
	default:
		break;
	}
	for (int i = 0; i < stoppedItemArray.size(); i++)
	{
		auto pos = stoppedItemArray[i].sprite->getPosition();
		if (pos.x == leftX) {
			leftToRightIndexArray.push_back(i);
			pos.x += 100;
			stoppedItemArray[i].sprite->setPosition(pos);
			continue;
		}
		if (pos.x == rightX) {
			rightToLeftIndexArray.push_back(i);
			pos.x -= 100;
			stoppedItemArray[i].sprite->setPosition(pos);
			continue;
		}
	}
	
	checkSwapFallingItem();
}

void HelloWorld::checkSwapFallingItem() {
	swappingFlg = true;
	auto pos1 = fallingItem1.sprite->getPosition();
	auto pos2 = fallingItem2.sprite->getPosition();
	bool move1 = false;
	bool move2 = false;
	int arraySize = leftToRightIndexArray.size();
	while (arraySize>0)
	{
		if (checkCollision(fallingItem1.sprite, stoppedItemArray[leftToRightIndexArray[0]].sprite) && !move1) {
			pos1.x -= 100;
			fallingItem1.sprite->setPosition(pos1);
			move1 = true;
		}
		if (checkCollision(fallingItem2.sprite, stoppedItemArray[leftToRightIndexArray[0]].sprite) && !move2)
		{
			pos2.x -= 100;
			fallingItem2.sprite->setPosition(pos2);
			move2 = true;
		}
		leftToRightIndexArray.erase(leftToRightIndexArray.begin());
		arraySize = leftToRightIndexArray.size();
	}
	arraySize = rightToLeftIndexArray.size();
	while (arraySize>0)
	{
		if (checkCollision(fallingItem1.sprite, stoppedItemArray[rightToLeftIndexArray[0]].sprite) && !move1) {
			pos1.x += 100;
			fallingItem1.sprite->setPosition(pos1);
			move1 = true;
		}
		if (checkCollision(fallingItem2.sprite, stoppedItemArray[rightToLeftIndexArray[0]].sprite) && !move2)
		{
			pos2.x += 100;
			fallingItem2.sprite->setPosition(pos2);
			move2 = true;
		}
		rightToLeftIndexArray.erase(rightToLeftIndexArray.begin());
		arraySize = rightToLeftIndexArray.size();
	}
	//leftToRightIndexArray.empty();
	//rightToLeftIndexArray.empty();
	//cocos2d::log("LeftArray size: %d",leftToRightIndexArray.size());
	//cocos2d::log("RightArray size: %d", rightToLeftIndexArray.size());
	swappingFlg = false;
}
void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (checkLossGame()) return;
	//log("Key with keycode %d pressed", keyCode);
	if (HelloWorld::countPosition > 1 && int(keyCode) == 23){
		//cocos2d::log("Press Left Button");
		auto moveLeft = MoveTo::create(0.5f, Vec2(HelloWorld::marioSprite->getPositionX() - 100, HelloWorld::marioSprite->getPositionY()));
		HelloWorld::marioSprite->runAction(moveLeft);
		HelloWorld::countPosition--;
	}
	if (HelloWorld::countPosition < 3 && int(keyCode) == 24) {
		//cocos2d::log("Press Right Button");
		auto moveRightAction = MoveTo::create(0.5f, Vec2(HelloWorld::marioSprite->getPositionX() + 100, HelloWorld::marioSprite->getPositionY()));
		HelloWorld::marioSprite->runAction(moveRightAction);
		HelloWorld::countPosition++;
	}
	if (int(keyCode) == 25) {
		//Check and Swap
		checkForSwap();
	}
}

void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	//log("Key with keycode %d released", keyCode);
}

bool HelloWorld::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	//touchInfo->setPosition(touch->getLocation());
	//touchInfo->setString("You Touched Here");
	// moveAction2 = MoveBy::create(1.f, touch->getLocation());
	//marioSprite->runAction(moveAction2);
	cocos2d::log("touch");
	if (lossGameFlg == true) return false;
	cocos2d::Vec2 point = touch->getLocation();
	cocos2d::Rect rect = _leftArrow->getBoundingBox();
	if (rect.containsPoint(point)) {
		if (HelloWorld::countPosition > 1 && onPauseFlg == false) {
			auto moveLeft = MoveTo::create(0.5f, Vec2(HelloWorld::marioSprite->getPositionX() - 100, HelloWorld::marioSprite->getPositionY()));
			HelloWorld::marioSprite->runAction(moveLeft);
			HelloWorld::countPosition--;
		}
		return true;
	}
	rect = _rightArrow->getBoundingBox();
	if (rect.containsPoint(point)) {
		if (HelloWorld::countPosition < 3 && onPauseFlg == false) {
			auto moveRightAction = MoveTo::create(0.5f, Vec2(HelloWorld::marioSprite->getPositionX() + 100, HelloWorld::marioSprite->getPositionY()));
			HelloWorld::marioSprite->runAction(moveRightAction);
			HelloWorld::countPosition++;
		}
		return true;
	}
	rect = _changeButton->getBoundingBox();
	if (rect.containsPoint(point)) {
		if(onPauseFlg == false) checkForSwap();
		return true;
	}rect = _pauButton->getBoundingBox();
	if (rect.containsPoint(point)) {
		if (onPauseFlg == false) {
			onPauseFlg = true;
			_pauButton->setVisible(false);
			_resumeButton->setVisible(true);
			return true;
		}
		else {
			onPauseFlg = false;
			_resumeButton->setVisible(false);
			_pauButton->setVisible(true);
			return true;
		}
	}
	return false;;
}

void HelloWorld::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
	//cocos2d::log("touch ended");
	//auto location = touch->getLocation();

	//auto moveAction = MoveTo::create(1.f, location);
	
	//marioSprite->runAction(moveAction);
}

void HelloWorld::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
	//cocos2d::log("touch moved");
}

void HelloWorld::onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event)
{
	//cocos2d::log("touch cancelled");
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
/*#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0); 

#endif */
	//auto scene = StartScene::createScene();
	//Director::getInstance()->replaceScene(scene);
}
