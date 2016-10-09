#include "pch.h"
#include "KeyboardLayer.h"
#include "UserClass.h" 

Scene* KeyboardLayer::createScene()
{
	auto scene = Scene::create();

	KeyboardLayer* layer = KeyboardLayer::create();
	scene->addChild(layer);
	return scene;
}

bool KeyboardLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("spriteArchBishop.plist");
	
	auto spr = Sprite::createWithSpriteFrameName("stopFront.png");

	spr->setPosition(Vec2(100, 100));
	this->addChild(spr);

	//m_archBishop.

	auto eventListener = EventListenerKeyboard::create();

	eventListener->onKeyPressed = CC_CALLBACK_2(KeyboardLayer::onKeyPressed, this);
	eventListener->onKeyReleased = CC_CALLBACK_2(KeyboardLayer::onKeyReleased, this);

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);

	this->scheduleUpdate();
	return true;
}

void KeyboardLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
	{
		m_keyboardArrow = m_keyboardArrow | KeyboardArrow::UP;
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	{
		m_keyboardArrow = m_keyboardArrow | KeyboardArrow::DOWN;
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		m_keyboardArrow = m_keyboardArrow | KeyboardArrow::RIGHT;
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		m_keyboardArrow = m_keyboardArrow | KeyboardArrow::LEFT;
	}

}

void KeyboardLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
	{
		m_keyboardArrow = m_keyboardArrow & (!KeyboardArrow::UP);
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	{
		m_keyboardArrow = m_keyboardArrow & (!KeyboardArrow::DOWN);
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		m_keyboardArrow = m_keyboardArrow & (!KeyboardArrow::RIGHT);
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		m_keyboardArrow = m_keyboardArrow & (!KeyboardArrow::LEFT);
	}
}

unsigned int & KeyboardLayer::GetKeyboardInput()
{
	// TODO: insert return statement here
	return m_keyboardArrow;
}


void KeyboardLayer::update(float delta) 
{
	//if()
	//m_archBishop.SetDirection(GetKeyboardInput());
}

