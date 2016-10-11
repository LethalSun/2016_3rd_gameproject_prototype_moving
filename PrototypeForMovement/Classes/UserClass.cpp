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

	m_archBishop = Sprite::createWithSpriteFrameName("stopSprite2.png");

	m_archBishop->setPosition(Vec2(100, 100));
	this->addChild(m_archBishop);
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
		unitVec[0] = 0;
		unitVec[1] = 1;
		break;
	}
	case TOP_RIGTH:
	{
		unitVec[0] = 1;
		unitVec[1] = 1;
		break;
	}
	case RIGHT:
	{
		unitVec[0] = 1;
		unitVec[1] = 0;
		break;
	}
	case BOTTOM_RIGHT:
	{
		unitVec[0] = 1;
		unitVec[1] = -1;
		break;
	}
	case BOTTOM:
	{
		unitVec[0] = 0;
		unitVec[1] = -1;
		break;
	}
	case BOTTOM_LEFT:
	{
		unitVec[0] = -1;
		unitVec[1] = -1;
		break;
	}
	case LEFT:
	{
		unitVec[0] = -1;
		unitVec[1] = 0;
		break;
	}
	case TOP_LEFT:
	{
		unitVec[0] = -1;
		unitVec[1] = 1;
		break;
	}
	default:
	{
		unitVec[0] = 0;
		unitVec[1] = 0;
		m_archBishop->stopAllActions();
		break;
	}
	}
}

void UserClass::MoveUserClass(float dt)
{
	MakeAnimation();

	auto currentposition = m_archBishop->getPosition();

	m_archBishop->setPositionX(currentposition.x + 
								(unitVec[0] * (PixelPerSecond)*dt));
	m_archBishop->setPositionY(currentposition.y + 
								(unitVec[1] * (PixelPerSecond)*dt));
	auto currentDir = std::string{ "current dir : " };
	currentDir.append( std::to_string( m_currentDirection));
	if (m_currentDirection == 13)
		int a = 0;
	cocos2d::log(currentDir.c_str());
}

void UserClass::MakeAnimation()
{

	if (m_beforeDirection == m_currentDirection || 
		m_currentDirection == ERROR_INPUT1		|| 
		m_currentDirection == ERROR_INPUT2		|| 
		m_currentDirection == ERROR_INPUT3		|| 
		m_currentDirection == ERROR_INPUT4		|| 
		m_currentDirection == ERROR_INPUT5		|| 
		m_currentDirection == ERROR_INPUT6		|| 
		m_currentDirection == ERROR_INPUT7)
	{
		//m_archBishop->stopAllActions();
		return;
	}

	

		
	
	
	int imageStartNumber = m_currentDirection * spriteFileNumber;

	m_archBishop->stopAllActions();


	if (m_currentDirection == NO_MOVE )
	{
		m_archBishop->stopAllActions();
		int stopImageNumber = m_beforeDirection % 10;
		sprintf(buffer, "stopSprite%d.png", stopImageNumber);
		m_archBishop->initWithSpriteFrameName(buffer);
		//m_archBishop->setTexture(SpriteFrameCache::getInstance()->getSpriteFrameByName(buffer)->getTexture());
		m_beforeDirection = m_currentDirection;
		return;
	}

	//auto spriteCache = SpriteFrameCache::getInstance();

	Vector<SpriteFrame*> animFrame;
	for (int i = imageStartNumber; i < imageStartNumber + 8; i++)
	{
		sprintf(buffer, "moveSpright%d.png", i);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(buffer);
		animFrame.pushBack(frame);
	}
	m_animation = Animation::createWithSpriteFrames(animFrame, 0.1f);
	m_animate = Animate::create(m_animation);
	m_archBishop->runAction(RepeatForever::create(m_animate));

	m_beforeDirection = m_currentDirection;
}

/*
switch (m_currentDirection)
{
case TOP:
{
break;
}
case TOP_RIGTH:
{
break;
}
case RIGHT:
{
break;
}
case BOTTOM_RIGHT:
{
break;
}
case BOTTOM:
{
break;
}
case BOTTOM_LEFT:
{
break;
}
case LEFT:
{
break;
}
case TOP_LEFT:
{
break;
}
default:
{
break;
}
}
*/