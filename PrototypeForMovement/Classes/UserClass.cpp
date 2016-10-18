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
	m_currentDirection = keyboardDirection & GET_DIRECTION_BIT;

	if (m_currentAction = keyboardDirection & GET_ACTION_BIT)
	{
		AnimationOn();
	}
}

Vec4 UserClass::GetActionInfo()
{
	auto currentPosition = m_pArchBishop->getPosition();
	auto xRange = m_unitVec[0] * ATTACK_RANGE_X;
	auto yRange = m_unitVec[1] * ATTACK_RANGE_Y;
	return Vec4(currentPosition.x, currentPosition.y, xRange, yRange);
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
	int imageStartNumber = (m_currentAction | m_attackDirection)* SPRITE_FILE_NUMBER;

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
	auto AnimationOff = CallFunc::create(CC_CALLBACK_0(UserClass::AnimationOff, this));
	//auto AnimationOn = CallFunc::create(CC_CALLBACK_0(UserClass::AnimationOn, this));
	auto sequenceAnimation = Sequence::create(m_pAnimate, AnimationOff, NULL);
	m_pArchBishop->runAction(sequenceAnimation);

	m_beforeAction = m_currentAction;
	m_beforeDirection = 3;
}
void UserClass::MoveUserClass(float dt)
{
	if (amIMonster == 1)
	{
		return;
	}

	SetDirection();
	if (m_isAnimationOn == 1)
	{
		MakeActionAnimation();
	}
	else
	{
		MakeMoveAnimation();

		auto currentposition = m_pArchBishop->getPosition();

		auto deltaX = (m_unitVec[0] * (PIXEL_PER_SECOND)*dt);
		auto deltaY = (m_unitVec[1] * (PIXEL_PER_SECOND)*dt);

		m_pArchBishop->setPositionX(currentposition.x + deltaX);
		m_pArchBishop->setPositionY(currentposition.y + deltaY);
	}
}

void UserClass::AnimationOff()
{
	m_isAnimationOn = 0;

	char logBuffer1[100];
	sprintf(logBuffer1, "m_isAnimationOn:%d 0000000000", m_isAnimationOn);
	cocos2d::log(logBuffer1);
}

void UserClass::AnimationOn()
{
	m_isAnimationOn = 1;

	char logBuffer1[100];
	sprintf(logBuffer1, "m_isAnimationOn:%d111111 ", m_isAnimationOn);
	cocos2d::log(logBuffer1);
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
		m_attackDirection = TOP;
		break;
	}
	case TOP_RIGTH:
	{
		m_unitVec[0] = 1;
		m_unitVec[1] = 1;
		m_attackDirection = TOP_RIGTH;
		break;
	}
	case RIGHT:
	{
		m_unitVec[0] = 1;
		m_unitVec[1] = 0;
		m_attackDirection = RIGHT;
		break;
	}
	case BOTTOM_RIGHT:
	{
		m_unitVec[0] = 1;
		m_unitVec[1] = -1;
		m_attackDirection = BOTTOM_RIGHT;
		break;
	}
	case BOTTOM:
	{
		m_unitVec[0] = 0;
		m_unitVec[1] = -1;
		m_attackDirection = BOTTOM;
		break;
	}
	case BOTTOM_LEFT:
	{
		m_unitVec[0] = -1;
		m_unitVec[1] = -1;
		m_attackDirection = BOTTOM_LEFT;
		break;
	}
	case LEFT:
	{
		m_unitVec[0] = -1;
		m_unitVec[1] = 0;
		m_attackDirection = LEFT;
		break;
	}
	case TOP_LEFT:
	{
		m_unitVec[0] = -1;
		m_unitVec[1] = 1;
		m_attackDirection = TOP_LEFT;
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