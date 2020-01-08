#include<MenuLayer.h>
#include<MainMenuScene.h>
#include<MapTutorialScene.h>
#include<item-1.h>
MenuLayer::MenuLayer(Player* mainPlayer) {
	this->mainPlayer = mainPlayer;
	//showItemMau(mainPlayer->m_sprite);
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
}
void MenuLayer::createButtonLayer()
{
	//icon
	item = new ItemLayer();
	item->Init();
	this->addChild(item);
	
	//pause
	auto btnPause = ui::Button::create("pause.png");
	btnPause->setPosition(Vec2(855, 375));
	btnPause->setScale(0.35);
	btnPause->addClickEventListener([](Ref* event) {
		Director::getInstance()->pause();
		mPauseLayer->setVisible(true);
	});
	addChild(btnPause);
	mPauseLayer = Sprite::create("settings/bg.png");
	mPauseLayer->setAnchorPoint(Vec2(0.5, 0.5));
	mPauseLayer->setOpacity(-125);
	mPauseLayer->setPosition(400, 225);
	mPauseLayer->setVisible(false);
	addChild(mPauseLayer, 3);
	auto paulb = Sprite::create("header.png");
	paulb->setAnchorPoint(Vec2(0.5, 0.5));
	paulb->setScale(0.6);
	paulb->setPosition(620, 520);
	mPauseLayer->addChild(paulb, 1);
	auto paubg = Sprite::create("table.png");
	paubg->setAnchorPoint(Vec2(0.5, 0.5));
	paubg->setScale(0.7);
	paubg->setPosition(630, 400);
	mPauseLayer->addChild(paubg);

	auto btnHome = ui::Button::create("menu.png");
	btnHome->setPosition(mPauseLayer->getPosition() + Vec2(150, 150));
	btnHome->setScale(0.5);
	btnHome->addClickEventListener([](Ref* event) {
		Director::getInstance()->resume();
		Director::getInstance()->replaceScene(MainMenuScene::createScene());
	});
	mPauseLayer->addChild(btnHome);

	auto btnResume = ui::Button::create("restart.png");
	btnResume->setPosition(mPauseLayer->getPosition() + Vec2(320, 150));
	btnResume->setScale(0.5);
	btnResume->addClickEventListener([](Ref* event) {
		Director::getInstance()->resume();
		mPauseLayer->setVisible(false);
	});
	mPauseLayer->addChild(btnResume);

	//attack
	auto ButtonAttack = ResourceManager::GetInstance()->GetButtonById(5);
	ButtonAttack->setPosition(Vec2(870, 40));
	ButtonAttack->setScale(0.4f);
	ButtonAttack->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
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
	this->addChild(joystickBase, 10);
}

void MenuLayer::createLabelLayer()
{

}

