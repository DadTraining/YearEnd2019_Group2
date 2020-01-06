#include<MenuLayer.h>
MenuLayer::MenuLayer(Player* mainPlayer) {
	this->mainPlayer = mainPlayer;
	init();
}

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
}
float timeCount = 0;
void MenuLayer::update(float deltaTime) {
	mainPlayer->physicsBody->setVelocity(leftJoystick->getVelocity() * 200);
	timeCount += deltaTime;

}
void MenuLayer::createButtonLayer()
{
	auto ButtonAttack = ResourceManager::GetInstance()->GetButtonById(5);
	ButtonAttack->setPosition(Vec2(350, 150));
	ButtonAttack->setScale(0.3f);
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
