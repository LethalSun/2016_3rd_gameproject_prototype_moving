#include "pch.h"
#include "PrototypeScene.h"
#include "Character.h"
#include "EnumDefines.h"
#include <bitset>

Scene * PrototypeScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
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

	m_pCharacter->setPosition(Vec2(100.0f, 100.0f));
	addChild(m_pCharacter);
	//
	char buffer[256];
	sprintf(buffer, "%sstop%d%s", BFE_IDCA_DEFINE::ARCH_BISHOP_FILE_NAME, 2, BFE_IDCA_DEFINE::SPRITE_FRAME_FILE_EXTENTION);
	m_pMonster = Sprite::createWithSpriteFrameName(buffer);
	m_pMonster->setPosition(Vec2(1000.0f, 600.0f));
	addChild(m_pMonster);
	//PhysicsBody character
	auto physicsbody = PhysicsBody::createBox(Size(90.0f, 50.0f), PhysicsMaterial(0.1f, 1.0f, 0.0f));
	physicsbody->setDynamic(false);
	physicsbody->setPositionOffset(Vec2(50.0f, 10.0f));
	m_pCharacter->setPhysicsBody(physicsbody);

	//physicsbody = PhysicsBody::createBox(Size(90.0f, 50.0f), PhysicsMaterial(0.1f, 1.0f, 0.0f));
	//physicsbody->setDynamic(false);
	//physicsbody->setPositionOffset(Vec2(-50.0f, 10.0f));
	//m_pCharacter->setPhysicsBody(physicsbody);

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