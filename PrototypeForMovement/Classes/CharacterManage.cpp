#include "pch.h"
#include "CharacterManage.h"
<<<<<<< HEAD
=======
#include "character.h"
>>>>>>> 7ab9e4018567d5c7a764ebcbff1934aa7166a1de

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
<<<<<<< HEAD
=======
	m_CharacterPosition = Vec2(0, 0);
	m_CharacterAttackDirection = Vec2(0, 0);
	m_CharacterAttackRange = Vec2(0, 0);
	m_TargetPosition = Vec2(0, 0);
>>>>>>> 7ab9e4018567d5c7a764ebcbff1934aa7166a1de
	return true;
}

void CharacterManage::Update(float delta)
{
}

void CharacterManage::GetCharacterInfo(Character * character)
{
<<<<<<< HEAD
=======
	m_CharacterPosition = character->getPosition();
	m_CharacterAttackDirection = character->GetCurrentDitection();
	m_CharacterAttackRange = character->GetAttackRange();
>>>>>>> 7ab9e4018567d5c7a764ebcbff1934aa7166a1de
}

void CharacterManage::GetSpriteInfo(Sprite * sprite)
{
	m_TargetPosition = sprite->getPosition();
}

void CharacterManage::CheckHit()
{
}