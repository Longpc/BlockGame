#include "StartScene.h"
USING_NS_CC;
Scene* StartScene::createScene() {
	auto scene = cocos2d::Scene::create();
	auto layer = StartScene::create();
	scene->addChild(layer);
	return scene;
}
StartScene* StartScene::create() {
	StartScene *layer = new StartScene();
	if (layer->init()) {
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return NULL;
}
bool StartScene::init() {
	if (!Layer::init()) {
		return false;
	}
	size = Director::getInstance()->getWinSize();

	cocos2d::Label* modeLabel = Label::create("GAME MODE : ", "fonts/3.ttf", 35);
	modeLabel->setPosition(Vec2(size.width / 2 - 200, size.height - 200));
	this->addChild(modeLabel, 1);
	easyMode = Label::create("EASY", "fonts/3.ttf", 35);
	easyMode->setPosition(Vec2(size.width / 2, size.height-200));
	//easyMode->setTextColor(ccc4(14,225,14,0));
	this->addChild(easyMode, 1);
	hardMode = Label::create("HARD", "fonts/3.ttf", 35);
	hardMode->setPosition(Vec2(size.width / 2 + 200, size.height-200));
	//hardMode->setTextColor(ccc4(225, 14, 14, 0));
	this->addChild(hardMode, 1);
	selectModeBoxSprite = SimpleSpriteCreator::create("select.png");
	selectModeBoxSprite->setPosition(Vec2(size.width / 2, size.height - 215));
	addChild(selectModeBoxSprite, 1);
	cocos2d::Label* speedLabel = Label::create("GAME SPEED : ", "fonts/3.ttf", 35);
	speedLabel->setPosition(Vec2(size.width / 2 - 200, size.height - 300));
	this->addChild(speedLabel, 1);
	slowSpeed = Label::create("SLOW", "fonts/3.ttf", 35);
	slowSpeed->setPosition(Vec2(size.width / 2, size.height - 300));
	this->addChild(slowSpeed, 1);
	fastSpeed = Label::create("FAST", "fonts/3.ttf", 35);
	fastSpeed->setPosition(Vec2(size.width / 2 + 200, size.height - 300));
	this->addChild(fastSpeed, 1);
	selectSpeedBoxSprite = SimpleSpriteCreator::create("select2.png");
	selectSpeedBoxSprite->setPosition(Vec2(size.width / 2, size.height - 315));
	addChild(selectSpeedBoxSprite, 1);
	startButton = Sprite::create("startBig.png");
	startButton->setPosition(Vec2(size.width / 2, size.height / 2 - 200));
	this->addChild(startButton);
	/*auto startListener = cocos2d::EventListenerTouchOneByOne::create();
	startListener->setSwallowTouches(true);
	startListener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event) {
		cocos2d::Vec2 p = touch->getLocation();
		cocos2d::Rect buttonRect = startButton->getBoundingBox();
		if (buttonRect.containsPoint(p)) {
			return true;
		}
		else {
			return false;
		}
	};
	startListener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* evt) {
		StartScene::checkAndStartGame();
	};
	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(startListener, 30);
	*///this->checkAndStartGame();
	//this->startgame();
	auto touchListener = EventListenerTouchOneByOne::create();

	touchListener->onTouchBegan = CC_CALLBACK_2(StartScene::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(StartScene::onTouchEnded, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(StartScene::onTouchMoved, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(StartScene::onTouchCancelled, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	return true;
}

bool StartScene::onTouchBegan(Touch* touch, Event* event)
{ 
	cocos2d::Vec2 point = touch->getLocation();
	cocos2d::Rect rect = startButton->getBoundingBox();
	if (rect.containsPoint(point)) {
		cocos2d::log("touch In button");
		StartScene::touchButtonFlg = true;
		return true;
	}
	rect = easyMode->getBoundingBox();
	if (rect.containsPoint(point)) {
		cocos2d::log("touch In Easy");
		gameMode = 1;
		auto pos = selectModeBoxSprite->getPosition();
		pos.x = size.width / 2;
		selectModeBoxSprite->setPosition(pos);
		//StartScene::touchButtonFlg = true;
		return true;
	}
	rect = hardMode->getBoundingBox();
	if (rect.containsPoint(point)) {
		cocos2d::log("touch In Hard");
		gameMode = 2;
		auto pos = selectModeBoxSprite->getPosition();
		pos.x = size.width / 2 + 200;
		selectModeBoxSprite->setPosition(pos);
		//StartScene::touchButtonFlg = true;
		return true;
	}
	rect = slowSpeed->getBoundingBox();
	if (rect.containsPoint(point)) {
		cocos2d::log("touch In Slow");
		gameSpeed = 1;
		auto pos = selectSpeedBoxSprite->getPosition();
		pos.x = size.width / 2;
		selectSpeedBoxSprite->setPosition(pos);
		//StartScene::touchButtonFlg = true;
		return true;
	}
	rect = fastSpeed->getBoundingBox();
	if (rect.containsPoint(point)) {
		cocos2d::log("touch In Fast");
		gameSpeed = 2;
		auto pos = selectSpeedBoxSprite->getPosition();
		pos.x = size.width / 2 + 200;
		selectSpeedBoxSprite->setPosition(pos);
		//StartScene::touchButtonFlg = true;
		return true;
	}
	cocos2d::log("touch else begin");
	return false;;
}

void StartScene::onTouchEnded(Touch* touch, Event* event)
{
	//cocos2d::log("touch ended");
	if (touchButtonFlg == true) {
		touchButtonFlg = false;
		StartScene::checkAndStartGame();
	}
}

void StartScene::onTouchMoved(Touch* touch, Event* event)
{
	//cocos2d::log("touch moved");
}

void StartScene::onTouchCancelled(Touch* touch, Event* event)
{
	//cocos2d::log("touch cancelled");
}
void StartScene::checkAndStartGame() {
	//check Status
	//gameMode = 1;
	//gameSpeed = 1;
	StartScene::startgame();
}
void StartScene::startgame() {
	auto scene = HelloWorld::createScene(gameMode,gameSpeed);
	Director::getInstance()->replaceScene(scene);
}