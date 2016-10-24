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
	//���� �ʱ�ȭ
	m_keyboardInput = 0;
	//ĳ���� �ֵ����ϵ�

	m_pCharacter = Character::create(BE_IDCA_DEFINES::ARCH_BISHOP_FILE_NAME, BE_IDCA_DEFINES::SPRITE_FRAME_FILE_EXTENTION);

	m_pCharacter->setPosition(Vec2(100, 100));
	this->addChild(m_pCharacter);
	//�̺�Ʈ ������
	auto eventListener = EventListenerKeyboard::create();

	eventListener->onKeyPressed = CC_CALLBACK_2(PrototypeScene::onKeyPressed, this);
	eventListener->onKeyReleased = CC_CALLBACK_2(PrototypeScene::onKeyReleased, this);

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);
	//������Ʈ �Լ� ���
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
		m_keyboardInput |= BE_IDCA_KEY_BOARD::INPUT::UP;
	}

	else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	{
		m_keyboardInput |= BE_IDCA_KEY_BOARD::INPUT::DOWN;
	}

	else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		m_keyboardInput |= BE_IDCA_KEY_BOARD::INPUT::RIGHT;
	}

	else if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		m_keyboardInput |= BE_IDCA_KEY_BOARD::INPUT::LEFT;
	}

	else if (keyCode == EventKeyboard::KeyCode::KEY_A)
	{
		m_keyboardInput |= BE_IDCA_KEY_BOARD::INPUT::A;
	}

	char buffer[256];
	sprintf(buffer, "inputKeyboard: %d", m_keyboardInput);
	cocos2d::log(buffer);
}

void PrototypeScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
	{
		m_keyboardInput &= ~(KEY_BOARD_INPUT::UP);
	}

	else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	{
		m_keyboardInput &= ~(KEY_BOARD_INPUT::DOWN);
	}

	else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		m_keyboardInput &= ~(KEY_BOARD_INPUT::RIGHT);
	}

	else if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		m_keyboardInput &= ~(KEY_BOARD_INPUT::LEFT);
	}

	else if (keyCode == EventKeyboard::KeyCode::KEY_A)
	{
		m_keyboardInput &= ~(KEY_BOARD_INPUT::A);
	}
}

PrototypeScene::PrototypeScene()
{
}

PrototypeScene::~PrototypeScene()
{
}