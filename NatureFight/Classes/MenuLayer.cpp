#include<MenuLayer.h>
#include<MainMenuScene.h>
#include<MapTutorialScene.h>
#include<SimpleAudioEngine.h>
#include<SettingScene.h>
#include<GameSetting.h>

using namespace CocosDenshion;
MenuLayer::MenuLayer(Player* mainPlayer) {
	this->mainPlayer = mainPlayer;
	init();
}

cocos2d::Sprite* mPauseLayer;
MenuLayer::~MenuLayer() {}

bool MenuLayer::init() {
	if (!Layer::init())
	{
		return false;
	}

	createButtonLayer();
	createJoyStickLayer();
	auto camScene = Camera::create();
	camScene->setCameraFlag(CameraFlag::USER1);
	this->setCameraMask((unsigned short)CameraFlag::USER1);
	this->addChild(camScene);
	return true;

	//

}
float timeCount = 0;
void MenuLayer::update(float deltaTime) {
	mainPlayer->physicsBody->setVelocity(leftJoystick->getVelocity() * 200);
	timeCount += deltaTime;
	item->getpercentBlood(-0.01);
}
void MenuLayer::createButtonLayer()
{
	//
	item = new ItemLayer();
	item->Init();
	item->showIce();
	item->showFire();
	item->showToxic();
	item->showWood();
	item->showIconSword();
	item->showIconFire();
	item->showIconIce();
	item->showItemBlood();
	this->addChild(item);
	//pause
	auto btnPause = ui::Button::create("settings/pausebtn.png");
	btnPause->setPosition(Vec2(880, 400));
	btnPause->addClickEventListener([](Ref* event) {
		auto turn = GameSetting::getInstance()->isSound();
		if (turn == true)
		{
			auto audio = SimpleAudioEngine::getInstance();
			//log("asd");
			audio->playEffect("sounds/212.mp3", false);
			log("2");
		}
		Director::getInstance()->pause();
		mPauseLayer->setVisible(true);
	});
	addChild(btnPause,10);
	mPauseLayer = Sprite::create("settings/bg.png");
	mPauseLayer->setColor(Color3B::BLACK);
	mPauseLayer->setAnchorPoint(Vec2(0.5, 0.5));
	mPauseLayer->setOpacity(-80);
	mPauseLayer->setPosition(Director::getInstance()->getVisibleSize()/2);
	mPauseLayer->setVisible(false);
	addChild(mPauseLayer, 10);
	auto paulb = Sprite::create("settings/header.png");
	paulb->setAnchorPoint(Vec2(0.5, 0.5));
	paulb->setScale(0.6);
	paulb->setPosition(600, 530);
	mPauseLayer->addChild(paulb, 1);
	auto paubg = Sprite::create("settings/tablepause.png");
	paubg->setAnchorPoint(Vec2(0.5, 0.5));
	paubg->setScale(0.7);
	paubg->setPosition(600, 400);
	mPauseLayer->addChild(paubg);

	auto btnHome = ui::Button::create("settings/menu.png");
	btnHome->setPosition(mPauseLayer->getPosition() + Vec2(-20, 150));
	btnHome->setScale(0.5);
	btnHome->addClickEventListener([](Ref* event) {
		
		auto turn = GameSetting::getInstance()->isSound();
		if (turn == true)
		{
			auto audio = SimpleAudioEngine::getInstance();
			//log("asd");
			audio->playEffect("sounds/212.mp3", false);
			log("2");
		}
		Director::getInstance()->resume();
		Director::getInstance()->replaceScene(MainMenuScene::createScene());
	});
	mPauseLayer->addChild(btnHome);

	auto btnResume = ui::Button::create("settings/restart.png");
	btnResume->setPosition(mPauseLayer->getPosition() + Vec2(120, 150));
	btnResume->setScale(0.5);
	btnResume->addClickEventListener([](Ref* event) {
		auto turn = GameSetting::getInstance()->isSound();
		if (turn == true)
		{
			auto audio = SimpleAudioEngine::getInstance();
			//log("asd");
			audio->playEffect("sounds/212.mp3", false);
			log("2");
		}
		Director::getInstance()->resume();
		mPauseLayer->setVisible(false);
	});
	mPauseLayer->addChild(btnResume);


	auto btnSetting = ui::Button::create("settings/settings.png");
	btnSetting->setPosition(mPauseLayer->getPosition() + Vec2(260, 150));
	btnSetting->setScale(0.5);
	btnSetting->addClickEventListener([](Ref* event) {
		auto turn = GameSetting::getInstance()->isSound();
		if (turn == true)
		{
			auto audio = SimpleAudioEngine::getInstance();
			//log("asd");
			audio->playEffect("sounds/212.mp3", false);
			log("2");
		}
		Director::getInstance()->replaceScene(SettingScene::createScene());
	});
	mPauseLayer->addChild(btnSetting);

	//attack
	auto ButtonAttack = ResourceManager::GetInstance()->GetButtonById(5);
	ButtonAttack->setPosition(Vec2(870, 40));
	ButtonAttack->setScale(0.4f);
	ButtonAttack->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		auto turn = GameSetting::getInstance()->isSound();
		if (turn == true)
		{
			
			auto audio = SimpleAudioEngine::getInstance();
			//log("asd");
			audio->playEffect("sounds/dam.wav", false);
			log("2");
		}
		
		switch (type)
		{
			
		case ui::Widget::TouchEventType::BEGAN:
		case ui::Widget::TouchEventType::MOVED:
			
			if (timeCount > 1) {
				mainPlayer->SetState(mainPlayer->ACTION_ATTACK);
				timeCount = 0;
			}
			break;
		case ui::Widget::TouchEventType::ENDED:
			
			break;
		default:
			break;
		}

	});
	ButtonAttack->removeFromParent();
	addChild(ButtonAttack, 1);
}
void MenuLayer::createJoyStickLayer()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Rect joystickBaseDimensions;
	joystickBaseDimensions = Rect(0, 0, 160.0f, 160.0f);
	Point joystickBasePosition;
	joystickBasePosition = Vec2(visibleSize.width * 0.2f, visibleSize.height * 0.2f);

	auto joystickBase = new SneakyJoystickSkinnedBase();
	joystickBase->init();
	joystickBase->setPosition(joystickBasePosition);
	joystickBase->setBackgroundSprite(Sprite::create("res/joystick_bg.png"));
	joystickBase->setThumbSprite(Sprite::create("res/joystick_center.png"));

	SneakyJoystick* aJoystick = new SneakyJoystick();
	aJoystick->initWithRect(joystickBaseDimensions);

	aJoystick->autorelease();
	joystickBase->setJoystick(aJoystick);
	joystickBase->setPosition(joystickBasePosition);

	leftJoystick = joystickBase->getJoystick();
	leftJoystick->retain();
	this->addChild(joystickBase, 5);
}

void MenuLayer::createLabelLayer()
{

}

