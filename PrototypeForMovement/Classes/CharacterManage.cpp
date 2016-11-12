#include "pch.h"
#include "CharacterManage.h"
#include "character.h"

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
	m_CharacterPosition = Vec2(0, 0);
	m_CharacterAttackDirection = Vec2(0, 0);
	m_CharacterAttackRange = Vec2(0, 0);
	m_TargetPosition = Vec2(0, 0);
	return true;
}

void CharacterManage::Update(float delta)
{
}

void CharacterManage::GetCharacterInfo(Character * character)
{
	m_CharacterPosition = character->getPosition();
	m_CharacterAttackDirection = character->GetCurrentDitection();
	m_CharacterAttackRange = character->GetAttackRange();
}

void CharacterManage::GetSpriteInfo(Sprite * sprite)
{
	m_TargetPosition = sprite->getPosition();
}

void CharacterManage::CheckHit()
{
}