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
//키보드 입력비트 플래그를 액션부분과,움직임부분으로 나누고 방향을 설정해 준다. 정지시에 사용할 이전 방향에 대한 처리도 같이함.
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
//입력에 따라서 현재의 상태를 파악한다.
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
//공격모션을 스프라이트를 상속받은 이클래스에 넣어준다.
void Character::Attack(float dt)
{
	if (m_IsActionState == false)
	{
		return;
	}
}
//이동모션을 스프라이트를 상속받은 이클래스에 넣어준다.
void Character::Move(float dt)
{
	if (m_IsMoveState == false)
	{
		return;
	}
}
//정지모션을 스프라이트를 상속받은 이클래스에 넣어준다.
void Character::Stop(float dt)
{
	if (m_IsStopState == false)
	{
		return;
	}
}
//매프레임마다 이스프라이트에 관련한 것들을 갱신한다. 상태 파악->모션
void Character::update(float dt)
{
	//상태 파악
	CheckCharacterState();
	//모션
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
//스프라이트 캐쉬에 이미지를 올린다.
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