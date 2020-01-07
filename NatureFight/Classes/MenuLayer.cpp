#include<MenuLayer.h>
#include<MainMenuScene.h>
#include<MapTutorialScene.h>
MenuLayer::MenuLayer(Player* mainPlayer) {
	this->mainPlayer = mainPlayer;

	showItemMau(mainPlayer->m_sprite);
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
//	load->getPercent();
}
void MenuLayer::createButtonLayer()
{
	//icon

	auto icon_kiem = Sprite::create("Sprites/Item/icon-kiem.png");
	icon_kiem->setScale(0.3);
	icon_kiem->setOpacity(-150);
	icon_kiem->setPosition(760, 40);
	icon_kiem->setRotation(-60);
	addChild(icon_kiem);
	auto icon_lua = Sprite::create("Sprites/Item/icon-lua.png");
	icon_lua->setScale(0.3);
	icon_lua->setOpacity(-150);
	icon_lua->setRotation(-45);
	icon_lua->setPosition(800, 100);
	addChild(icon_lua);
	auto icon_bang = Sprite::create("Sprites/Item/icon-bang.png");
	icon_bang->setScale(0.3);
	icon_bang->setOpacity(-150);
	icon_bang->setRotation(-25);
	icon_bang->setPosition(870, 140);
	addChild(icon_bang);
	//pause
	auto btnPause = ui::Button::create("pause.png");
	btnPause->setPosition(Vec2(855, 375));
	btnPause->setScale(0.4);
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
void MenuLayer::showItemMau(cocos2d::Sprite * sprite)
{
	auto loadingbar = Sprite::create("loadingbar_bg.png");
	loadingbar->setPosition(455,415);
	loadingbar->setAnchorPoint(Vec2(0.5, 0.5));
	addChild(loadingbar, 1);
	loadingbar->setScaleX(2.4);
	load = ui::LoadingBar::create("progress.png");
	load->setPercent(100);
	load->setScale(0.9);
	load->setScaleX(2.5);
	load->setPosition(loadingbar->getPosition());
	addChild(load, 2);
	load->setDirection(ui::LoadingBar::Direction::LEFT);
}
void MenuLayer::getpersent(int a) {
	load->setPercent(load->getPercent() + a);
}