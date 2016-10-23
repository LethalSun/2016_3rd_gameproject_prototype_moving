#include "pch.h"
#include "Character.h"
#include "MakeAnimation.h"
#include "EnumDefines.h"
Character * Character::create()
{
	auto pSprite = new Character();
	if (!(pSprite))
	{
		CC_SAFE_DELETE(pSprite);
		return nullptr;
	}

	pSprite->autorelease();

	pSprite->initOptions();
}
void Character::initOptions()
{
	AddSpriteFramesWithFile(BE_IDCA_DEFINES::PLIST_FILE_NAME);
}
//Ű���� �Էº�Ʈ �÷��׸� �׼Ǻκа�,�����Ӻκ����� ������ ������ ������ �ش�. �����ÿ� ����� ���� ���⿡ ���� ó���� ������.
void Character::SetInput(int inputFromScene)
{
	m_Input = inputFromScene;
	m_ActionInput = m_Input & BE_IDCA_ACTIONS::ACTIONS::GET_ACTION_BIT;
	m_MoveInput = m_Input & BE_IDCA_ACTIONS::ACTIONS::DIRECTION_BIT;
	switch (m_MoveInput)
	{
	case BE_IDCA_ACTIONS::ACTIONS::TOP:
	{
		m_UnitVector[0] = 0;
		m_UnitVector[1] = 1;
		m_CurDirection = BE_IDCA_ACTIONS::ACTIONS::TOP;
		break;
	}
	case BE_IDCA_ACTIONS::ACTIONS::TOP_RIGTH:
	{
		m_UnitVector[0] = 1;
		m_UnitVector[1] = 1;
		m_CurDirection = BE_IDCA_ACTIONS::ACTIONS::TOP_RIGTH;
		break;
	}
	case BE_IDCA_ACTIONS::ACTIONS::RIGHT:
	{
		m_UnitVector[0] = 1;
		m_UnitVector[1] = 0;
		m_CurDirection = BE_IDCA_ACTIONS::ACTIONS::RIGHT;
		break;
	}
	case BE_IDCA_ACTIONS::ACTIONS::BOTTOM_RIGHT:
	{
		m_UnitVector[0] = 1;
		m_UnitVector[1] = -1;
		m_CurDirection = BE_IDCA_ACTIONS::ACTIONS::BOTTOM_RIGHT;
		break;
	}
	case BE_IDCA_ACTIONS::ACTIONS::BOTTOM:
	{
		m_UnitVector[0] = 0;
		m_UnitVector[1] = -1;
		m_CurDirection = BE_IDCA_ACTIONS::ACTIONS::BOTTOM;
		break;
	}
	case BE_IDCA_ACTIONS::ACTIONS::BOTTOM_LEFT:
	{
		m_UnitVector[0] = -1;
		m_UnitVector[1] = -1;
		m_CurDirection = BE_IDCA_ACTIONS::ACTIONS::BOTTOM_LEFT;
		break;
	}
	case BE_IDCA_ACTIONS::ACTIONS::LEFT:
	{
		m_UnitVector[0] = -1;
		m_UnitVector[1] = 0;
		m_CurDirection = BE_IDCA_ACTIONS::ACTIONS::LEFT;
		break;
	}
	case BE_IDCA_ACTIONS::ACTIONS::TOP_LEFT:
	{
		m_UnitVector[0] = -1;
		m_UnitVector[1] = 1;
		m_CurDirection = BE_IDCA_ACTIONS::ACTIONS::TOP_LEFT;
		break;
	}
	default:
	{	m_MoveInput = BE_IDCA_ACTIONS::ACTIONS::NO_MOVE;
	m_CurDirection = m_BeforeDirection;
	m_UnitVector[0] = 0;
	m_UnitVector[1] = 0;
	break;
	}
	}
}
//�Է¿� ���� ������ ���¸� �ľ��Ѵ�.
void Character::CheckCharacterState()
{
	if ((m_IsActionState == false) && (!(m_ActionInput)))
	{
		m_IsActionState = true;
		m_IsMoveState = false;
		m_IsStopState = false;
	}
	else if ((m_IsActionState == false) && (m_MoveInput != BE_IDCA_ACTIONS::ACTIONS::NO_MOVE))
	{
		m_IsActionState = false;
		m_IsMoveState = true;
		m_IsStopState = false;

		m_BeforeDirection = m_CurDirection;
	}
	else if ((m_IsActionState == false) && (m_MoveInput == BE_IDCA_ACTIONS::ACTIONS::NO_MOVE))
	{
		m_IsActionState = false;
		m_IsMoveState = false;
		m_IsStopState = true;
	}
}
//���ݸ���� ��������Ʈ�� ��ӹ��� ��Ŭ������ �־��ش�.
void Character::Attack(float dt)
{
	if (m_IsActionState == false)
	{
		return;
	}
}
//�̵������ ��������Ʈ�� ��ӹ��� ��Ŭ������ �־��ش�.
void Character::Move(float dt)
{
	if (m_IsMoveState == false)
	{
		return;
	}
}
//��������� ��������Ʈ�� ��ӹ��� ��Ŭ������ �־��ش�.
void Character::Stop(float dt)
{
	if (m_IsStopState == false)
	{
		return;
	}
}
//�������Ӹ��� �̽�������Ʈ�� ������ �͵��� �����Ѵ�. ���� �ľ�->���
void Character::update(float dt)
{
	//���� �ľ�
	CheckCharacterState();
	//���
	if (m_IsActionState == true)
	{
		Attack(dt);
	}
	if (m_IsMoveState == true)
	{
		Move(dt);
	}
	if (m_IsStopState == true)
	{
		Stop(dt);
	}
}
//��������Ʈ ĳ���� �̹����� �ø���.
void Character::AddSpriteFramesWithFile(const char * filename)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(filename);
}
Character::Character()
{
}

Character::~Character()
{
}