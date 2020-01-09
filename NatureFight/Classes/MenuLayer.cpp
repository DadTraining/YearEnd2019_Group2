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

	Quest(); // nhan

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
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto ButtonAttack = ResourceManager::GetInstance()->GetButtonById(5);
	ButtonAttack->setAnchorPoint(Vec2(1,0));
	ButtonAttack->setPosition(Vec2(visibleSize.width,0));
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

	auto particleSystem = ParticleSystemQuad::create("Particles/power.plist");
	particleSystem->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));
	particleSystem->setDuration(ParticleSystem::DURATION_INFINITY);
	particleSystem->setScale(0.3f);
	addChild(particleSystem, 10);

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
/////////////////////////begin nhan

int count1 = 0;//nhan
void MenuLayer::Quest()
{
	quest = Sprite::create("frames/paused3.png");
	quest->setPosition(600, 400);
	quest->setScale(0.2);
	quest->setAnchorPoint(Point(0.0f, 1.0f));
	addChild(quest, 80);
	quest->setOpacity(0);
	//
	//Quest 1 of Yolo
	//for (int i = 0; i < 4; i++)
	//{
	//	label1 = Label::createWithSystemFont("Danh 3 con quai Goblin (" + std::to_string(i) + " / 3)", "Arial", 16);
	//	label1->setAnchorPoint(Vec2(0, 1));
	//	label1->setPositionX(quest->getPositionX() + 20);
	//	label1->setPositionY(quest->getPositionY() - 20);
	//	label1->setTextColor(Color4B::BLACK);
	//	label1->setVisible(false);
	//	this->addChild(label1, 97 + i);
	//	vlabel1.push_back(label1);
	//}
	////Quest 2 of Solo

	//for (int i = 0; i <= 6; i++)
	//{
	//	label2 = Label::createWithSystemFont("Danh 6 con quai Goblin (" + std::to_string(i) + " / 6)", "Arial", 16);
	//	label2->setAnchorPoint(Vec2(0, 1));
	//	label2->setPositionX(quest->getPositionX() + 20);
	//	label2->setPositionY(label1->getPositionY() - 30);
	//	label2->setTextColor(Color4B::BLACK);
	//	label2->setVisible(false);
	//	this->addChild(label2, 102 + i);
	//	vlabel.push_back(label2);
	//}


	auto buttonQuest = ui::Button::create("Button/buttons/normal/records.png", "Button/buttons/click/records.png", "Button/buttons/hover/records.png");
	auto visibleSize = Director::getInstance()->getVisibleSize();
	buttonQuest->setAnchorPoint(Vec2(1, 1));
	buttonQuest->setPosition(Vec2(visibleSize));
	buttonQuest->setScale(0.06);
	buttonQuest->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
		{
			count1 += 1;
			break;
		}

		case ui::Widget::TouchEventType::ENDED:
		{
			auto fadeIn = FadeIn::create(0.1f);
			auto fadeOut = FadeOut::create(0.1f);
			if (count1 == 1) {

				quest->runAction(fadeIn);
				///*if (questYolo == 1) {
				//	for (int i = 0; i < 4; i++)
				//	{
				//		if (d == 0 && i == 0)
				//		{
				//			vlabel1[i]->setVisible(true);
				//		}
				//		else if (d == i && i > 0) {
				//			vlabel1[i]->setVisible(true);
				//			vlabel1[i - 1]->setVisible(false);
				//		}
				//	}*/


				//}
				/*if (questSolo == 2) {
					for (int i = 0; i < 7; i++)
					{
						if (c == 0 && i == 0)
						{
							vlabel[i]->setVisible(true);
						}
						else if (c == i && i > 0) {
							vlabel[i]->setVisible(true);
							vlabel[i - 1]->setVisible(false);
						}
					}

				}*/
			}
			else {

				quest->runAction(fadeOut);
				/*for (int i = 0; i <= 6; i++)
				{

					vlabel[i]->setVisible(false);
				}
				for (int i = 0; i <= 3; i++)
				{

					vlabel1[i]->setVisible(false);
				}*/
				count1 = 0;
			}
			break;
		}
		default:
			break;
		}
	});
	addChild(buttonQuest,2);

}
//end nhan