#include "pch.h"
#include "PrototypeScene.h"
#include "Character.h"
#include "CharacterManage.h"
#include "EnumDefines.h"
#include <bitset>

Scene * PrototypeScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	auto layer = PrototypeScene::create();
	scene->addChild(layer);

	return scene;
}

bool PrototypeScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//변수 초기화
	m_keyboardInput = 0;
	m_pCharacterManage = CharacterManage::create();
	addChild(m_pCharacterManage);
	//캐릭터 애드차일드
	m_pCharacter = Character::create(BFE_IDCA_DEFINE::ARCH_BISHOP_FILE_NAME, BFE_IDCA_DEFINE::SPRITE_FRAME_FILE_EXTENTION);
	m_pCharacter->setPosition(Vec2(100, 100));
	addChild(m_pCharacter);
	//이성경 애드차일드
	m_pMonster = Sprite::create("lSG.png");
	m_pMonster->setPosition(Vec2(900, 600));
	auto action1 = MoveTo::create(20, Vec2(100, 600));
	auto action2 = MoveTo::create(20, Vec2(900, 600));
	auto seq = Sequence::create(action1, action2, nullptr);
	auto repeat = RepeatForever::create(seq);
	m_pMonster->runAction(repeat);
	addChild(m_pMonster);
	//몬스터1 애드차일드
	m_pMonster1 = Sprite::create("monster.png");
	m_pMonster1->setPosition(Vec2(900, 100));
	auto action3 = MoveTo::create(8, Vec2(500, 100));
	auto action4 = MoveTo::create(8, Vec2(900, 100));
	auto seq1 = Sequence::create(action3, action4, nullptr);
	auto repeat1 = RepeatForever::create(seq1);
	m_pMonster1->runAction(repeat1);
	addChild(m_pMonster1);
	//이벤트 리스너
	auto eventListener = EventListenerKeyboard::create();
	eventListener->onKeyPressed = CC_CALLBACK_2(PrototypeScene::onKeyPressed, this);
	eventListener->onKeyReleased = CC_CALLBACK_2(PrototypeScene::onKeyReleased, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);
	//업데이트 함수 등록
	this->scheduleUpdate();
	return true;
}

void PrototypeScene::update(float delta)
{
	m_pCharacter->SetInput(m_keyboardInput);
	m_pCharacterManage->GetCharacterInfo(m_pCharacter);
	if (m_pMonster != nullptr)
	{
		m_pCharacterManage->GetSpriteInfo(m_pMonster);
		bool hit = false;

		hit = m_pCharacterManage->GetHitInfo();

		char buffer[100];
		sprintf(buffer, "hit = %d", hit);
		cocos2d::log(buffer);

		if (hit == true)
		{
			m_pMonster->removeFromParent();
			m_pMonster = nullptr;
		}
	}
}

void PrototypeScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
	{
		m_keyboardInput |= BFE_IDCA_DEFINE::INPUT::KEY_UP;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	{
		m_keyboardInput |= BFE_IDCA_DEFINE::INPUT::KEY_DOWN;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		m_keyboardInput |= BFE_IDCA_DEFINE::INPUT::KEY_RIGHT;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		m_keyboardInput |= BFE_IDCA_DEFINE::INPUT::KEY_LEFT;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_A)
	{
		m_keyboardInput |= BFE_IDCA_DEFINE::INPUT::KEY_A;
	}
}

void PrototypeScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
	{
		m_keyboardInput &= ~(BFE_IDCA_DEFINE::INPUT::KEY_UP);
	}

	else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	{
		m_keyboardInput &= ~(BFE_IDCA_DEFINE::INPUT::KEY_DOWN);
	}

	else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		m_keyboardInput &= ~(BFE_IDCA_DEFINE::INPUT::KEY_RIGHT);
	}

	else if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		m_keyboardInput &= ~(BFE_IDCA_DEFINE::INPUT::KEY_LEFT);
	}

	else if (keyCode == EventKeyboard::KeyCode::KEY_A)
	{
		m_keyboardInput &= ~(BFE_IDCA_DEFINE::INPUT::KEY_A);
	}
}

PrototypeScene::PrototypeScene()
{
}

PrototypeScene::~PrototypeScene()
{
}