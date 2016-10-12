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
	m_archBishop = UserClass::create();
	this->addChild(m_archBishop);

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
		m_keyboardArrow |= KEY_BOARD_ARROW::UP;
	}

	else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	{
		m_keyboardArrow |= KEY_BOARD_ARROW::DOWN;
	}

	else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		m_keyboardArrow |= KEY_BOARD_ARROW::RIGHT;
	}

	else if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		m_keyboardArrow |= KEY_BOARD_ARROW::LEFT;
	}

}

void KeyboardLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
	{
		m_keyboardArrow &= (!KEY_BOARD_ARROW::UP);
	}

	else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	{
		m_keyboardArrow &= (!KEY_BOARD_ARROW::DOWN);
	}

	else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		m_keyboardArrow &= (!KEY_BOARD_ARROW::RIGHT);
	}

	else if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		m_keyboardArrow &= (!KEY_BOARD_ARROW::LEFT);
	}

	
}

const unsigned int  KeyboardLayer::GetKeyboardInput()
{
	// TODO: insert return statement here
	return m_keyboardArrow;
}


void KeyboardLayer::update(float delta) 
{
	char logBuffer[100];
	sprintf(logBuffer, "m_keyboardArrow:%d ", m_keyboardArrow);
	cocos2d::log(logBuffer);
	m_archBishop->SetDirection(GetKeyboardInput());
	m_archBishop->MoveUserClass(delta);
}

