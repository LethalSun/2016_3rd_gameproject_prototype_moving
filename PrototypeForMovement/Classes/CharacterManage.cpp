#include "pch.h"
#include "CharacterManage.h"
#include "UserClass.h"

Scene* CharacterManage::createScene()
{
	auto scene = Scene::create();

	CharacterManage* node = CharacterManage::create();
	node->addChild(node);
	return scene;
}

bool CharacterManage::init()
{
	if (!Node::init())
	{
		return false;
	}
	m_archBishop = UserClass::create();
	this->addChild(m_archBishop);
	m_monster = UserClass::create();
	m_monster->IAmMonster();
	m_monster->setPosition(Vec2(500, 500));
	addChild(m_monster);
	return true;
}

void CharacterManage::SetKeyboardInput(const unsigned int &keyboardDirection)
{
	m_keyboardDirection = keyboardDirection;
}

void CharacterManage::CheckHit()
{
	//if(((m_archBishopInfo.x+15)<(m_monsterInfo.x-15))&&((m_archBishopInfo.x+m_archBishopInfo.z)>()))
}

void CharacterManage::Update(float delta)
{
	m_archBishop->InterpretKeyboardInput(m_keyboardDirection);
	m_archBishopInfo = m_archBishop->GetActionInfo();
	m_monsterInfo = m_monster->GetActionInfo();
	m_archBishop->MoveUserClass(delta);
}