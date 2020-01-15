#include<MenuLayer.h>
#include<SimpleAudioEngine.h>
using namespace CocosDenshion;
std::vector<Label*> vlabel1, vlabel2 , vlabel3;
int count1 = 0;//nhan
MenuLayer::MenuLayer(Player* mainPlayer) {
	this->mainPlayer = mainPlayer;
	if (!(vlabel1.empty() || vlabel2.empty()|| vlabel3.empty())) {
		vlabel1.clear();
		vlabel2.clear();
		vlabel3.clear();
	}

	init();
}

MenuLayer::~MenuLayer() {}

bool MenuLayer::init() {
	if (!Layer::init())
	{
		return false;
	}
	createButtonLayer();
	createUpLevelLayer();
	createSkillFire();
	createSkillIce();

	createFlood();

	createJoyStickLayer();
	createPlayerDie(false);
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
	mainPlayer->SetFace(leftJoystick->getVelocity());
	timeCount += deltaTime;
	if (mainPlayer->Exp >= mainPlayer->MaxExp) {
		ButtonUpLevel->setVisible(true);
	}

	loadhelth->setPercent(mainPlayer->setHealth());
	loaddame->setPercent(mainPlayer->setDame());
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
		//item->showItemBlood();
		this->addChild(item);
		//pause
		//pause
		auto btnPause = ui::Button::create("settings/pause.png");
		btnPause->setPosition(Vec2(visibleSize));
		btnPause->setAnchorPoint(Vec2(1, 1));
		btnPause->setOpacity(-50);
		btnPause->setScale(0.2);
		btnPause->addClickEventListener([](Ref* event) {
			auto turn = GameSetting::getInstance()->isSound();
			if (turn == true)
			{
				auto audio = SimpleAudioEngine::getInstance();
				audio->playEffect("sounds/212.mp3", false);
			}
			Director::getInstance()->pause();
			mPauseLayer->setVisible(true);
		});
		addChild(btnPause, 10);
		mPauseLayer = Sprite::create("settings/bg.png");
		//mPauseLayer->setAnchorPoint(Vec2(0.5, 0.5));
		//mPauseLayer->setOpacity(-125);
		mPauseLayer->setScale(0.4);
		mPauseLayer->setPosition(visibleSize / 2);
		mPauseLayer->setVisible(false);
		addChild(mPauseLayer, 50);
		auto paulb = Sprite::create("settings/header.png");
		//paulb->setAnchorPoint(Vec2(0.5, 0.5));
		paulb->setScale(0.6);
		paulb->setPosition(mPauseLayer->getPosition() + Vec2(200, 380));
		mPauseLayer->addChild(paulb, 1);
		auto paubg = Sprite::create("settings/tablepause.png");
		//paubg->setAnchorPoint(Vec2(0.5, 0.5));
		paubg->setScale(1.4);
		paubg->setPosition(Vec2(visibleSize / 2) + Vec2(170, 230));
		mPauseLayer->addChild(paubg);

		auto btnHome = ui::Button::create("settings/menu.png");
		btnHome->setPosition(mPauseLayer->getPosition() + Vec2(150, 50));
		//btnHome->setScale(0.5);
		btnHome->addClickEventListener([](Ref* event) {

			auto turn = GameSetting::getInstance()->isSound();
			if (turn == true)
			{
				auto audio = SimpleAudioEngine::getInstance();
				audio->playEffect("sounds/212.mp3", false);
			}
			Director::getInstance()->resume();
			Director::getInstance()->replaceScene(MainMenuScene::createScene());
		});
		mPauseLayer->addChild(btnHome);

		auto btnResume = ui::Button::create("settings/restart.png");
		btnResume->setPosition(mPauseLayer->getPosition() + Vec2(mPauseLayer->getContentSize().width * 1 / 3 + 50, 50));
		//btnResume->setScale(0.5);
		btnResume->addClickEventListener([](Ref* event) {
			auto turn = GameSetting::getInstance()->isSound();
			if (turn == true)
			{
				auto audio = SimpleAudioEngine::getInstance();
				audio->playEffect("sounds/212.mp3", false);
			}
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
				audio->playEffect("sounds/212.mp3", false);
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
		auto turn = GameSetting::getInstance()->isSound();
		if (turn == true)
		{
			auto audio = SimpleAudioEngine::getInstance();
			audio->playEffect("sounds/dam.wav", false);
		}
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
void MenuLayer::createUpLevelLayer()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	ButtonUpLevel = ResourceManager::GetInstance()->GetButtonById(6);
	ButtonUpLevel->setPosition(Vec2(visibleSize.width/2, visibleSize.height / 2));
	ButtonUpLevel->setAnchorPoint(Vec2(1, 0));
	ButtonUpLevel->setScale(0.3f);
	ButtonUpLevel->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			mainPlayer->Level++;
			mainPlayer->updateLevel();
			ButtonUpLevel->setVisible(false);
			break;
		case ui::Widget::TouchEventType::ENDED:
			break;
		default:
			break;
		}

	});
	ButtonUpLevel->removeFromParent();
	addChild(ButtonUpLevel, 1);
	ButtonUpLevel->setVisible(false);
}
void MenuLayer::createPlayerDie(bool a)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	//pause
	

	mPauseLayer1 = Sprite::create("settings/bg.png");
	mPauseLayer1->setScale(0.4);
	mPauseLayer1->setPosition(visibleSize / 2);
	mPauseLayer1->setVisible(a);
	addChild(mPauseLayer1, 50);
	auto paulb = Sprite::create("settings/header.png");
	paulb->setScale(0.6);
	paulb->setPosition(mPauseLayer1->getPosition() + Vec2(200, 380));
	mPauseLayer1->addChild(paulb, 1);
	auto paubg = Sprite::create("settings/tablepause.png");
	paubg->setScale(1.4);
	paubg->setPosition(Vec2(visibleSize / 2) + Vec2(170, 230));
	mPauseLayer1->addChild(paubg);

	auto btnHome = ui::Button::create("settings/menu.png");
	btnHome->setPosition(mPauseLayer1->getPosition() + Vec2(150, 50));
	btnHome->addClickEventListener([](Ref* event) {

		Director::getInstance()->resume();
		Director::getInstance()->replaceScene(MainMenuScene::createScene());
	});
	mPauseLayer1->addChild(btnHome);

	auto btnResume = ui::Button::create("settings/restart.png");
	btnResume->setPosition(mPauseLayer1->getPosition() + Vec2(mPauseLayer->getContentSize().width * 1 / 3 + 50, 50));
	btnResume->addClickEventListener([](Ref* event) {

		Director::getInstance()->resume();
		Director::getInstance()->replaceScene(MainMenuScene::createScene());
	});
	mPauseLayer1->addChild(btnResume);

	auto btnSetting = ui::Button::create("settings/settings.png");
	btnSetting->setPosition(mPauseLayer1->getPosition() + Vec2(-210, 50));
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
	mPauseLayer1->addChild(btnSetting);
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
	icon_ice = ui::Button::create("Sprites/Item/icon-bang.png");
	icon_ice->setScale(0.25);
	//icon_ice->setOpacity(-150);
	icon_ice->setRotation(-25);
	icon_ice->setEnabled(false);
	icon_ice->setAnchorPoint(Vec2(1, 0));
	icon_ice->setPosition(Vec2(visibleSize.width + 30, 100));
	this->addChild(icon_ice);
	icon_ice->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		auto turn = GameSetting::getInstance()->isSound();
		if (turn == true)
		{
			auto audio = SimpleAudioEngine::getInstance();
			audio->playEffect("sounds/bang.wav", false);
		}
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

}
void MenuLayer::createSkillFire() {

	auto visibleSize = Director::getInstance()->getVisibleSize();
	icon_fire = ui::Button::create("Sprites/Item/icon-lua.png");
	icon_fire->setScale(0.25);
	//icon_fire->setOpacity(-150);
	icon_fire->setEnabled(false);
	icon_fire->setRotation(-45);
	icon_fire->setAnchorPoint(Vec2(1, 0));
	icon_fire->setPosition(Vec2(visibleSize.width - 40, 90));
	this->addChild(icon_fire); 
	icon_fire->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		auto turn = GameSetting::getInstance()->isSound();
		if (turn == true)
		{
			auto audio = SimpleAudioEngine::getInstance();
			audio->playEffect("sounds/lua.wav", false);
		}
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
}
/////////////////////////begin nhan

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

	//Quest 3 of man 2 
	for (int i = 0; i <= 15; i++)
	{
		label3 = Label::createWithSystemFont("con quai Goblin (" + std::to_string(i) + " / 15)", "Arial", 16);
		label3->setAnchorPoint(Vec2(0, 1));
		label3->setPositionX(quest->getPositionX() + 20);
		label3->setPositionY(label1->getPositionY() - 20);
		label3->setTextColor(Color4B::BLACK);
		label3->setVisible(false);
		this->addChild(label3, 102 + i);
		vlabel3.push_back(label3);
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
					for (int i = 0; i <= 3; i++)
					{
						if (d == i)
						{
							if(i==0) vlabel1[i]->setVisible(true);
							else {
								if (i <= 3) {
									vlabel1[i - 1]->setVisible(false);
									vlabel1[i]->setVisible(true);
								}
								
								
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
								if (i <= 6) {
									vlabel2[i - 1]->setVisible(false);
									vlabel2[i]->setVisible(true);
								}
								
							}
						}
					}

				}
				if (questman2 == 2) {
					for (int i = 0; i < 16; i++)
					{
						if (c == i)
						{
							if (i == 0) vlabel3[i]->setVisible(true);
							else {
								if (i <= 15) {
									vlabel3[i - 1]->setVisible(false);
									vlabel3[i]->setVisible(true);
								}

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
				for (int i = 0; i <= 15; i++)
				{

					vlabel3[i]->setVisible(false);
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

void MenuLayer::setQuestMan2(int x)
{
	questman2 = x;
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
void MenuLayer::showItemSword(Vec2 a)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto item_kiem = Sprite::create("Sprites/Item/Sword.png");
	item_kiem->setPosition(a);
	addChild(item_kiem, 80);
	item_kiem->setScale(0.2); item_kiem->setRotation(45);
	auto moveby = MoveBy::create(0.5, Vec2(20, 20));
	auto move_ease_out = EaseBackOut::create(moveby->clone());
	auto move = MoveBy::create(0.5, Vec2(20, -60));
	auto move_ease_in = EaseBounceOut::create(move->clone());
	auto scaleBy = ScaleBy::create(2.0f, 3.0f);
	auto scaleBy1 = ScaleBy::create(2.0f, 0.1f);
	auto remove = RemoveSelf::create();
	auto sequence = Sequence::create(scaleBy, scaleBy1,remove, nullptr);
	item_kiem->runAction(sequence);
}

ui::Button * MenuLayer::getIcon_Ice()
{
	return icon_ice;
}

ui::Button * MenuLayer::getIcon_Fire()
{
	return icon_fire;
}

void MenuLayer::createFlood()
{
	/*auto inftable = Sprite::create("settings/table2.png");
	inftable->setScaleX(1.6);
	inftable->setOpacity(-100);
	inftable->setPosition(Vec2(Director::getInstance()->getVisibleSize().width*0.75, Director::getInstance()->getVisibleSize().height - 32));
	addChild(inftable);*/
	/*auto infface = Sprite::create("settings/Face_01.png");
	infface->setScaleX(1.5);
	infface->setPosition(inftable->getPosition() - Vec2(150, 0));
	addChild(infface);*/
	auto loadingbgheath = Sprite::create("settings/healthbg.png");
	loadingbgheath->setPosition(Vec2(Director::getInstance()->getVisibleSize().width*0.75, Director::getInstance()->getVisibleSize().height - 32) + Vec2(30, 15));
	loadingbgheath->setScale(0.3f);
	loadingbgheath->setScaleY(0.2f);
	addChild(loadingbgheath, 1);
	loadhelth = ui::LoadingBar::create("settings/health.png");
	loadhelth->setScale(0.3f);
	loadhelth->setScaleY(0.2f);
	loadhelth->setPosition(loadingbgheath->getPosition() +Vec2(18, 1));
	addChild(loadhelth, 2);
	loadhelth->setDirection(ui::LoadingBar::Direction::LEFT);
	auto loadingbgdame = Sprite::create("settings/manabg.png");
	loadingbgdame->setPosition(Vec2(Director::getInstance()->getVisibleSize().width*0.75, Director::getInstance()->getVisibleSize().height - 32) - Vec2(-30, 10));
	loadingbgdame->setScale(0.3f);
	loadingbgdame->setScaleY(0.2f);
	addChild(loadingbgdame, 1);
	loaddame = ui::LoadingBar::create("settings/mana.png");
	loaddame->setScale(0.3f);
	loaddame->setScaleY(0.2f);
	loaddame->setPosition(loadingbgdame->getPosition() + Vec2(18, -4));
	addChild(loaddame, 2);
	loaddame->setDirection(ui::LoadingBar::Direction::LEFT);
}