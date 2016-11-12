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
	//���� �ʱ�ȭ
	m_keyboardInput = 0;
	//ĳ���� �ֵ����ϵ�

	m_pCharacter = Character::create(BFE_IDCA_DEFINE::ARCH_BISHOP_FILE_NAME, BFE_IDCA_DEFINE::SPRITE_FRAME_FILE_EXTENTION);
<<<<<<< HEAD

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

=======
	m_pCharacter->setPosition(Vec2(100, 100));
	addChild(m_pCharacter);
	//���� �ֵ����ϵ�
	m_pMonster = Sprite::create("lSG.png");
	m_pMonster->setPosition(Vec2(900, 600));
	auto action1 = MoveTo::create(20, Vec2(100, 600));
	auto action2 = MoveTo::create(20, Vec2(900, 600));
	auto seq = Sequence::create(action1, action2, nullptr);
	auto repeat = RepeatForever::create(seq);
	m_pMonster->runAction(repeat);
	addChild(m_pMonster);
	//����1 �ֵ����ϵ�
	m_pMonster1 = Sprite::create("monster.png");
	m_pMonster1->setPosition(Vec2(900, 100));
	auto action3 = MoveTo::create(8, Vec2(500, 100));
	auto action4 = MoveTo::create(8, Vec2(900, 100));
	auto seq1 = Sequence::create(action3, action4, nullptr);
	auto repeat1 = RepeatForever::create(seq1);
	m_pMonster1->runAction(repeat1);
	addChild(m_pMonster1);
>>>>>>> 7ab9e4018567d5c7a764ebcbff1934aa7166a1de
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