#include "pch.h"
#include "UserClass.h"

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

	m_archBishop = Sprite::createWithSpriteFrameName("stopFront.png");

	m_archBishop->setPosition(Vec2(100, 100));
	this->addChild(m_archBishop);

	return true;
}



void UserClass::SetDirection(const unsigned int &keyboardDirection)
{
	m_currentDirection = keyboardDirection;
}

void UserClass::MoveUserClass(float dt)
{
	switch (m_currentDirection)
	{
		case UP_1200:
		{
			auto spriteCache = SpriteFrameCache::getInstance();
			Vector<SpriteFrame*> animFrame;
			for (int i = 0; i < 8; i++)
			{
				sprintf(buffer, "goBack%d.png", (i + 1));
				auto frame = spriteCache->getSpriteFrameByName(buffer);
				animFrame.pushBack(frame);
			}
			m_animation = Animation::createWithSpriteFrames(animFrame, dt);
			m_animate = Animate::create(m_animation);
			m_move = MoveBy::create(dt, Vec2(0, 10));
			m_spawn = Spawn::create(m_animate, m_move,NULL);
			m_archBishop->runAction(m_spawn);
			
			break;
		}
		case UP_RIGHT_0130:
		{
			break;
		}
		case LEFT_0300:
		{
			break;
		}
		case DOWN_RIGHT_0430:
		{
			break;
		}
		case DOWN_0600:
		{
			break;
		}
		case DOWN_LEFT_0730:
		{
			break;
		}
		case RIGHT_0900:
		{
			break;
		}
		case UP_LEFT_1030:
		{
			break;
		}
		default:
		{
			break;
		}
	}
}
