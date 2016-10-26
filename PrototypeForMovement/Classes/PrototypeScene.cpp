#include "pch.h"
#include "PrototypeScene.h"
#include "Character.h"
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
	//캐릭터 애드차일드

	m_pCharacter = Character::create(BFE_IDCA_DEFINE::ARCH_BISHOP_FILE_NAME, BFE_IDCA_DEFINE::SPRITE_FRAME_FILE_EXTENTION);

	m_pCharacter->setPosition(Vec2(100, 100));
	this->addChild(m_pCharacter);
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