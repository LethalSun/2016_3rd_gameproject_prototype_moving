#include "pch.h"
#include "CharacterManage.h"
#include "character.h"
#include "EnumDefines.h"

//Scene* CharacterManage::createScene()
//{
//	auto scene = Scene::create();
//
//	CharacterManage* node = CharacterManage::create();
//	node->addChild(node);
//	return scene;
//}

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
	m_HitHit = false;
	scheduleUpdate();
	return true;
}

void CharacterManage::update(float delta)
{
	char buffer[100];
	sprintf(buffer, "state = %d", m_CharacterState);
	cocos2d::log(buffer);
	if (m_CharacterState == BFE_IDCA_DEFINE::CHARACTER_STATE::STATE_ATTACK)
	{
		m_HitHit = CheckHit();
	}
}

void CharacterManage::GetCharacterInfo(Character * character)
{
	m_CharacterPosition = character->getPosition();
	m_CharacterAttackDirection = character->GetCurrentDitection();
	m_CharacterAttackRange = character->GetAttackRange();
	m_CharacterState = character->GetCharacterState();
	m_CharacterBeAttackedBox.x = character->getContentSize().width;
	m_CharacterBeAttackedBox.y = character->getContentSize().height;
}

void CharacterManage::GetSpriteInfo(Sprite * sprite)
{
	m_TargetPosition = sprite->getPosition();
	char buffer[100];
	sprintf(buffer, "%f,%f", m_TargetPosition.x, m_TargetPosition.y);
	cocos2d::log(buffer);
	m_TargetBeAttackefBox.x = sprite->getContentSize().width;
	m_TargetBeAttackefBox.y = sprite->getContentSize().height;
}

bool CharacterManage::CheckHit()
{
	auto attackAnchorPoint = AttackAnchorPoint();
	auto checkingDistance = Distance(attackAnchorPoint, m_TargetPosition);
	bool hit = true;

	if (checkingDistance.x > (m_CharacterAttackRange.x / 2 + m_TargetBeAttackefBox.x / 2))
	{
		hit = false;
		return hit;
	}

	if (checkingDistance.y > (m_CharacterAttackRange.y / 2 + m_TargetBeAttackefBox.y / 2))
	{
		hit = false;
		return hit;
	}

	return hit;
}

bool CharacterManage::GetHitInfo()
{
	bool result = m_HitHit;

	return result;
}

Vec2 CharacterManage::Distance(Vec2 a, Vec2 b)
{
	auto x = ((a.x - b.x) < 0) ? -(a.x - b.x) : (a.x - b.x);
	auto y = ((a.y - b.y) < 0) ? -(a.y - b.y) : (a.y - b.y);
	return Vec2(x,y);
}

Vec2 CharacterManage::AttackAnchorPoint()
{
	auto x = m_CharacterPosition.x +
		m_CharacterAttackDirection.x*(m_CharacterBeAttackedBox.x / 2 + m_CharacterAttackRange.x / 2);
	auto y = m_CharacterPosition.y;
		   
	return Vec2(x,y);
}
