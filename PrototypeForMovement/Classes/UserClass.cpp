#include "pch.h"
#include "UserClass.h"

#include<string>

Scene * UserClass::scene()
{
	Scene* scene = Scene::create();
	UserClass* layer = UserClass::create();
	scene->addChild(layer);
	return scene;
}

bool UserClass::init()
{
	if (!Node::init())
	{
		return false;
	}

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("spriteArchBishop.plist");

	m_pArchBishop = Sprite::createWithSpriteFrameName("stopSprite2.png");

	m_pArchBishop->setPosition(Vec2(100, 100));
	this->addChild(m_pArchBishop);
	this->scheduleUpdate();
	return true;
}

void UserClass::SetDirection(const unsigned int &keyboardDirection)
{
	m_currentDirection = keyboardDirection;
	switch (m_currentDirection)
	{
	case TOP:
	{
		m_unitVec[0] = 0;
		m_unitVec[1] = 1;
		break;
	}
	case TOP_RIGTH:
	{
		m_unitVec[0] = 1;
		m_unitVec[1] = 1;
		break;
	}
	case RIGHT:
	{
		m_unitVec[0] = 1;
		m_unitVec[1] = 0;
		break;
	}
	case BOTTOM_RIGHT:
	{
		m_unitVec[0] = 1;
		m_unitVec[1] = -1;
		break;
	}
	case BOTTOM:
	{
		m_unitVec[0] = 0;
		m_unitVec[1] = -1;
		break;
	}
	case BOTTOM_LEFT:
	{
		m_unitVec[0] = -1;
		m_unitVec[1] = -1;
		break;
	}
	case LEFT:
	{
		m_unitVec[0] = -1;
		m_unitVec[1] = 0;
		break;
	}
	case TOP_LEFT:
	{
		m_unitVec[0] = -1;
		m_unitVec[1] = 1;
		break;
	}
	default:
	{
		m_unitVec[0] = 0;
		m_unitVec[1] = 0;
		m_pArchBishop->stopAllActions();
		break;
	}
	}
}

void UserClass::MakeAnimation()
{
	if (m_beforeDirection == m_currentDirection ||
		m_currentDirection == ERROR_INPUT1 ||
		m_currentDirection == ERROR_INPUT2 ||
		m_currentDirection == ERROR_INPUT3 ||
		m_currentDirection == ERROR_INPUT4 ||
		m_currentDirection == ERROR_INPUT5 ||
		m_currentDirection == ERROR_INPUT6 ||
		m_currentDirection == ERROR_INPUT7)
	{
		//m_archBishop->stopAllActions();
		return;
	}

	int imageStartNumber = m_currentDirection * SPRITE_FILE_NUMBER;

	if (m_currentDirection == NO_MOVE)
	{
		m_pArchBishop->stopAllActions();
		int stopImageNumber = m_beforeDirection % 10;
		sprintf(m_buffer, "stopSprite%d.png", stopImageNumber);
		m_pArchBishop->initWithSpriteFrameName(m_buffer);
		//m_archBishop->setTexture(SpriteFrameCache::getInstance()->getSpriteFrameByName(buffer)->getTexture());
		m_beforeDirection = m_currentDirection;
		return;
	}

	m_pArchBishop->stopAllActions();
	Vector<SpriteFrame*> animFrame;
	for (int i = imageStartNumber; i < imageStartNumber + 8; i++)
	{
		sprintf(m_buffer, "moveSpright%d.png", i);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(m_buffer);
		animFrame.pushBack(frame);
	}
	m_pAnimation = Animation::createWithSpriteFrames(animFrame, 0.1f);
	m_pAnimate = Animate::create(m_pAnimation);
	m_pArchBishop->runAction(RepeatForever::create(m_pAnimate));

	m_beforeDirection = m_currentDirection;
}

void UserClass::MoveUserClass(float dt)
{
	MakeAnimation();

	auto currentposition = m_pArchBishop->getPosition();

	auto deltaX = (m_unitVec[0] * (PIXEL_PER_SECOND)*dt);
	auto deltaY = (m_unitVec[1] * (PIXEL_PER_SECOND)*dt);

	m_pArchBishop->setPositionX(currentposition.x + deltaX);
	m_pArchBishop->setPositionY(currentposition.y + deltaY);
}