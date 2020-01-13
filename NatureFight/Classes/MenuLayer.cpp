#include<MenuLayer.h>
#include<SimpleAudioEngine.h>
using namespace CocosDenshion;
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
	createSkillFire();
	createSkillIce();

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

cocos2d::Sprite* mPauseLayer;
void MenuLayer::createButtonLayer()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
		//
		item = new ItemLayer();
		item->Init();
		item->showToxic();
		item->showWood();
		item->showIconSword();
		item->showIce();
		item->showFire();
		item->showItemBlood();
		this->addChild(item);
		//pause
		auto btnPause = ui::Button::create("settings/pause.png");
		btnPause->setPosition(Vec2(visibleSize));
		btnPause->setAnchorPoint(Vec2(1,1));
		btnPause->setOpacity(-50);
		btnPause->setScale(0.2);
		btnPause->addClickEventListener([](Ref* event) {
			
			Director::getInstance()->pause();
			mPauseLayer->setVisible(true);
		});
		addChild(btnPause, 10);
		mPauseLayer = Sprite::create("settings/bg.png");
		//mPauseLayer->setAnchorPoint(Vec2(0.5, 0.5));
		//mPauseLayer->setOpacity(-125);
		mPauseLayer->setScale(0.4);
		mPauseLayer->setPosition(visibleSize/2);
		mPauseLayer->setVisible(false);
		addChild(mPauseLayer, 50);
		auto paulb = Sprite::create("settings/header.png");
		//paulb->setAnchorPoint(Vec2(0.5, 0.5));
		paulb->setScale(0.6);
		paulb->setPosition(mPauseLayer->getPosition() + Vec2(200,380));
		mPauseLayer->addChild(paulb, 1);
		auto paubg = Sprite::create("settings/tablepause.png");
		//paubg->setAnchorPoint(Vec2(0.5, 0.5));
		paubg->setScale(1.4);
		paubg->setPosition(Vec2(visibleSize/2) + Vec2(170,230));
		mPauseLayer->addChild(paubg);

		auto btnHome = ui::Button::create("settings/menu.png");
		btnHome->setPosition(mPauseLayer->getPosition() +Vec2(150,50) );
		//btnHome->setScale(0.5);
		btnHome->addClickEventListener([](Ref* event) {
			
			Director::getInstance()->resume();
			Director::getInstance()->replaceScene(MainMenuScene::createScene());
		});
		mPauseLayer->addChild(btnHome);

		auto btnResume = ui::Button::create("settings/restart.png");
		btnResume->setPosition(mPauseLayer->getPosition() + Vec2(mPauseLayer->getContentSize().width * 1 / 3+50, 50));
		//btnResume->setScale(0.5);
		btnResume->addClickEventListener([](Ref* event) {
			
			Director::getInstance()->resume();
			mPauseLayer->setVisible(false);
		});
		mPauseLayer->addChild(btnResume);

		auto btnSetting = ui::Button::create("settings/settings.png");
		btnSetting->setPosition(mPauseLayer->getPosition() + Vec2(-210, 50));
		//btnSetting->setScale(0.5);
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
////////

	auto ButtonAttack = ResourceManager::GetInstance()->GetButtonById(5);
	
	ButtonAttack->setPosition(Vec2(visibleSize.width,0));
	ButtonAttack->setAnchorPoint(Vec2(1, 0));
	ButtonAttack->setScale(0.3f);
	ButtonAttack->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
		case ui::Widget::TouchEventType::MOVED:
			if (timeCount > 2.0f - mainPlayer->AttackSpeed) {
				mainPlayer->m_CurrentSkill = mainPlayer->SKILL_DEFAULT;
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

	auto particleSystem = ParticleSystemQuad::create("Particles/move2.plist");
	particleSystem->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2 - 20));
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

void MenuLayer::createSkillIce()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto icon_ice = ui::Button::create("Sprites/Item/icon-bang.png");
	icon_ice->setScale(0.25);
	icon_ice->setOpacity(-150);
	icon_ice->setRotation(-25);
	icon_ice->setTouchEnabled(false);
	icon_ice->setAnchorPoint(Vec2(1, 0));
	icon_ice->setPosition(Vec2(visibleSize.width+30,100));
	this->addChild(icon_ice);
	icon_ice->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
		case ui::Widget::TouchEventType::MOVED:
			if (timeCount > 2.0f - mainPlayer->AttackSpeed) {
				mainPlayer->m_CurrentSkill = mainPlayer->SKILL_ICE;
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
	auto fin = FadeIn::create(3.0f);
	icon_ice->setTouchEnabled(true);
	icon_ice->runAction(fin);
}
void MenuLayer::createSkillFire() {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto icon_fire = ui::Button::create("Sprites/Item/icon-lua.png");
	icon_fire->setScale(0.25);
	icon_fire->setOpacity(-150);
	icon_fire->setTouchEnabled(false);
	icon_fire->setRotation(-45);
	icon_fire->setAnchorPoint(Vec2(1,0));
	icon_fire->setPosition(Vec2(visibleSize.width-40,90));
	this->addChild(icon_fire); 
	icon_fire->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
		case ui::Widget::TouchEventType::MOVED:
			if (timeCount > 2.0f - mainPlayer->AttackSpeed) {
				mainPlayer->m_CurrentSkill = mainPlayer->SKILL_FIRE;
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
	auto fin = FadeIn::create(3.0f);
	icon_fire->runAction(fin);
	icon_fire->setTouchEnabled(true);
}
/////////////////////////begin nhan
std::vector<Label*> vlabel1,vlabel2;
int count1 = 0;//nhan
void MenuLayer::Quest()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	quest = Sprite::create("frames/paused3.png");
	quest->setPosition(visibleSize-Size(350,50));
	quest->setScale(0.2);
	quest->setAnchorPoint(Point(0.0f, 1.0f));
	addChild(quest, 80);
	quest->setOpacity(0);
	
	//Quest 1 of Yolo
	for (int i = 0; i < 4; i++)
	{
		label1 = Label::createWithSystemFont("Danh 3 con quai Goblin (" + std::to_string(i) + " / 3)", "Arial", 16);
		label1->setAnchorPoint(Vec2(0, 1));
		label1->setPositionX(quest->getPositionX() + 20);
		label1->setPositionY(quest->getPositionY() - 20);
		label1->setTextColor(Color4B::BLACK);
		label1->setVisible(false);
		this->addChild(label1, 97 + i);
		vlabel1.push_back(label1);
	}
	//Quest 2 of Solo

	for (int i = 0; i <= 6; i++)
	{
		label2 = Label::createWithSystemFont("Danh 6 con quai Goblin (" + std::to_string(i) + " / 6)", "Arial", 16);
		label2->setAnchorPoint(Vec2(0, 1));
		label2->setPositionX(quest->getPositionX() + 20);
		label2->setPositionY(label1->getPositionY() - 30);
		label2->setTextColor(Color4B::BLACK);
		label2->setVisible(false);
		this->addChild(label2, 102 + i);
		vlabel2.push_back(label2);
	}


	auto buttonQuest = ui::Button::create("Button/buttons/normal/records.png", "Button/buttons/click/records.png", "Button/buttons/hover/records.png");
	
	buttonQuest->setAnchorPoint(Vec2(1, 1));
	buttonQuest->setPosition(Vec2(visibleSize)-Size(0,100));
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
				if (QuestYolo == 1) {
					for (int i = 0; i < 4; i++)
					{
						if (d == i)
						{
							if(i==0) vlabel1[i]->setVisible(true);
							else {
								vlabel1[i - 1]->setVisible(false);
								vlabel1[i]->setVisible(true);
								
							}
						}
						
					}


				}
				if (QuestSolo == 2) {
					for (int i = 0; i < 7; i++)
					{
						if (c == i)
						{
							if (i == 0) vlabel2[i]->setVisible(true);
							else {
								vlabel2[i - 1]->setVisible(false);
								vlabel2[i]->setVisible(true);

							}
						}
					}

				}
			}
			else {

				quest->runAction(fadeOut);
				for (int i = 0; i <= 6; i++)
				{

					vlabel2[i]->setVisible(false);
				}
				for (int i = 0; i <= 3; i++)
				{

					vlabel1[i]->setVisible(false);
				}
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

void MenuLayer::setQuestSolo(int x)
{
	QuestSolo = x;
}

void MenuLayer::setQuestYolo(int x)
{
	QuestYolo = x;
}

void MenuLayer::setD(int x)
{
	d = x;
}

void MenuLayer::setC(int x)
{
	c = x;
}

//end nhan