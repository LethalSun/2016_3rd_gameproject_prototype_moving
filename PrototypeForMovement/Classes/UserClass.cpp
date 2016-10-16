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

	m_currentDirection = 0;
	m_beforeDirection = 0;
	m_unitVec[1] = { 0 };
	m_unitVec[0] = { 0 };
	amIMonster = 0;

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("spriteArchBishop.plist");

	m_pArchBishop = Sprite::createWithSpriteFrameName("stopSprite2.png");

	m_pArchBishop->setPosition(Vec2(100, 100));
	this->addChild(m_pArchBishop);
	this->scheduleUpdate();
	return true;
}

void UserClass::InterpretKeyboardInput(const unsigned int & keyboardDirection)
{
	m_currentDirection = keyboardDirection /*& GET_DIRECTION_BIT*/;
	m_currentAction = keyboardDirection & GET_ACTION_BIT;
}

Vec4 UserClass::GetActionInfo()
{
	auto currentPosition = m_pArchBishop->getPosition();
	auto xRange = m_unitVec[0] * ATTACK_RANGE_X;
	auto yRange = m_unitVec[1] * ATTACK_RANGE_Y;
	return Vec4(currentPosition.x, currentPosition.y, xRange, yRange);
}

void UserClass::IAmMonster()
{
	amIMonster = 1;
}

void UserClass::SetDirection()
{
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
		m_currentDirection = NO_MOVE;
		m_unitVec[0] = 0;
		m_unitVec[1] = 0;
		break;
	}
	}
}

void UserClass::MakeMoveAnimation()
{
	if (m_beforeDirection == m_currentDirection)
	{
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
	m_pAnimation = Animation::createWithSpriteFrames(animFrame, ANIMATION_SPEED);
	m_pAnimate = Animate::create(m_pAnimation);
	m_pArchBishop->runAction(RepeatForever::create(m_pAnimate));

	m_beforeDirection = m_currentDirection;
}

void UserClass::MakeActionAnimation()
{
	int imageStartNumber = (m_currentAction | m_beforeDirection)* SPRITE_FILE_NUMBER;
	char logBuffer1[100];
	sprintf(logBuffer1, "keyCode: %d ,%d ,%d ", imageStartNumber, m_currentAction, m_beforeDirection);
	cocos2d::log(logBuffer1);
	if (imageStartNumber < 170)
	{
		return;
	}
	m_pArchBishop->stopAllActions();
	Vector<SpriteFrame*> animFrame;
	for (int i = imageStartNumber; i < imageStartNumber + 7; i++)
	{
		sprintf(m_buffer, "hit%d.png", i);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(m_buffer);
		animFrame.pushBack(frame);
	}
	m_pAnimation = Animation::createWithSpriteFrames(animFrame, HIT_ANIMATION_SPEED);
	m_pAnimate = Animate::create(m_pAnimation);
	m_pArchBishop->runAction(m_pAnimate);

	m_beforeAction = m_currentAction;
}

void UserClass::MoveUserClass(float dt)
{
	if (amIMonster == 1)
	{
		return;
	}
	SetDirection();

	if (m_currentAction == 0 && !(m_currentAction))
	{
		MakeMoveAnimation();

		auto currentposition = m_pArchBishop->getPosition();

		auto deltaX = (m_unitVec[0] * (PIXEL_PER_SECOND)*dt);
		auto deltaY = (m_unitVec[1] * (PIXEL_PER_SECOND)*dt);

		m_pArchBishop->setPositionX(currentposition.x + deltaX);
		m_pArchBishop->setPositionY(currentposition.y + deltaY);
	}
	else
	{
		MakeActionAnimation();
	}
}