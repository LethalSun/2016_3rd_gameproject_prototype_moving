#include "pch.h"
#include "Character.h"
#include "MakeAnimation.h"
#include "EnumDefines.h"
#include <bitset>

void BeepThread()
{
	auto beepThread = std::thread([]() {Beep(1000, 100); });
	beepThread.detach();
}

Character::Character()
{
}

Character::~Character()
{
	delete m_pMakeAnimation;
}
Character * Character::create(const char const* filename, const char const* extention)
{
	auto pSprite = new Character();
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(BE_IDCA_DEFINES::PLIST_FILE_NAME);
	char buffer[256];
	sprintf(buffer, "%sstop%d%s", filename, 2, extention);
	if (!(pSprite->initWithSpriteFrameName(buffer)))
	{
		CC_SAFE_DELETE(pSprite);
		return nullptr;
	}

	pSprite->autorelease();

	pSprite->initOptions(filename, extention);

	return pSprite;
}
void Character::initOptions(const char const* filename, const char const* extention)
{
	this->scheduleUpdate();
	m_pMakeAnimation = new MakeAnimation(BE_IDCA_DEFINES::ARCH_BISHOP_FILE_NAME, BE_IDCA_DEFINES::SPRITE_FRAME_FILE_EXTENTION);
	//공격,이동,정지 상태를 나타내는 변수 초기화
	m_IsActionState = false;
	m_IsMoveState = false;
	m_IsStopState = true;
	//애니메이션중인지 아닌지를 나타내는 변수
	m_ActionAnimationOn = false;
	m_MoveAnimationOn = false;
	m_StopAnimationOn = true;
	//입력플래그를 처리하기 위한 변수 초기화
	m_Input = 0;
	m_ActionInput = 0;
	m_MoveInput = 0;
	m_CurDirection = BE_IDCA_ACTIONS::ACTIONS::NO_MOVE;
	m_BeforeDirection = BE_IDCA_ACTIONS::ACTIONS::NO_MOVE;
	m_UnitVector[0] = 0;
	m_UnitVector[1] = 0;
	//this->addChild(m_pMakeAnimation);
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
		m_BeforeDirection = m_CurDirection;
		m_CurDirection = BE_IDCA_ACTIONS::ACTIONS::TOP;
		break;
	}
	case BE_IDCA_ACTIONS::ACTIONS::TOP_RIGTH:
	{
		m_UnitVector[0] = 1;
		m_UnitVector[1] = 1;
		m_BeforeDirection = m_CurDirection;
		m_CurDirection = BE_IDCA_ACTIONS::ACTIONS::TOP_RIGTH;
		break;
	}
	case BE_IDCA_ACTIONS::ACTIONS::RIGHT:
	{
		m_UnitVector[0] = 1;
		m_UnitVector[1] = 0;
		m_BeforeDirection = m_CurDirection;
		m_CurDirection = BE_IDCA_ACTIONS::ACTIONS::RIGHT;
		break;
	}
	case BE_IDCA_ACTIONS::ACTIONS::BOTTOM_RIGHT:
	{
		m_UnitVector[0] = 1;
		m_UnitVector[1] = -1;
		m_BeforeDirection = m_CurDirection;
		m_CurDirection = BE_IDCA_ACTIONS::ACTIONS::BOTTOM_RIGHT;
		break;
	}
	case BE_IDCA_ACTIONS::ACTIONS::BOTTOM:
	{
		m_UnitVector[0] = 0;
		m_UnitVector[1] = -1;
		m_BeforeDirection = m_CurDirection;
		m_CurDirection = BE_IDCA_ACTIONS::ACTIONS::BOTTOM;
		break;
	}
	case BE_IDCA_ACTIONS::ACTIONS::BOTTOM_LEFT:
	{
		m_UnitVector[0] = -1;
		m_UnitVector[1] = -1;
		m_BeforeDirection = m_CurDirection;
		m_CurDirection = BE_IDCA_ACTIONS::ACTIONS::BOTTOM_LEFT;
		break;
	}
	case BE_IDCA_ACTIONS::ACTIONS::LEFT:
	{
		m_UnitVector[0] = -1;
		m_UnitVector[1] = 0;
		m_BeforeDirection = m_CurDirection;
		m_CurDirection = BE_IDCA_ACTIONS::ACTIONS::LEFT;
		break;
	}
	case BE_IDCA_ACTIONS::ACTIONS::TOP_LEFT:
	{
		m_UnitVector[0] = -1;
		m_UnitVector[1] = 1;
		m_BeforeDirection = m_CurDirection;
		m_CurDirection = BE_IDCA_ACTIONS::ACTIONS::TOP_LEFT;
		break;
	}
	default:
	{
		m_MoveInput = BE_IDCA_ACTIONS::ACTIONS::NO_MOVE;
		m_CurDirection = m_BeforeDirection;
		m_UnitVector[0] = 0;
		m_UnitVector[1] = 0;
		break;
	}
	}
	//	char buffer[256];
	//	sprintf(buffer, "inputCharacter: %d,%d", m_CurDirection, m_MoveInput);
	//	cocos2d::log(buffer);
}
//입력에 따라서 현재의 상태를 파악한다.
void Character::CheckCharacterState()
{
	if ((m_IsActionState == false) && (m_ActionInput != 0))
	{
		m_IsActionState = true;
		m_IsMoveState = false;
		m_IsStopState = false;
	}
	else if ((m_IsActionState == false) && (m_IsMoveState == false) && (m_MoveInput != BE_IDCA_ACTIONS::ACTIONS::NO_MOVE))
	{
		m_IsActionState = false;
		m_IsMoveState = true;
		m_IsStopState = false;

		m_BeforeDirection = m_CurDirection;
	}
	else if ((m_IsActionState == false) && (m_IsStopState == false) && (m_MoveInput == BE_IDCA_ACTIONS::ACTIONS::NO_MOVE))
	{
		m_IsActionState = false;
		m_IsMoveState = false;
		m_IsStopState = true;
	}
	//	char buffer[256];
	//	sprintf(buffer, "inputKeyboard: %d,%d,%d", m_IsActionState, m_IsMoveState, m_IsStopState);
	//	cocos2d::log(buffer);
}
//공격모션을 스프라이트를 상속받은 이클래스에 넣어준다.
void Character::Attack(float dt)
{
	if (m_ActionAnimationOn == true)
	{
		return;
	}
	stopAllActions();
	auto animate = m_pMakeAnimation->AnimationAttack(m_CurDirection);
	auto attackOn = CallFunc::create(CC_CALLBACK_0(Character::AttackOn, this));
	auto attackOff = CallFunc::create(CC_CALLBACK_0(Character::AttackOff, this));
	auto sequence = Sequence::create(attackOn, animate, attackOff, NULL);
	runAction(sequence);
}
//이동모션을 스프라이트를 상속받은 이클래스에 넣어준다.
void Character::Move(float dt)
{
	if (m_MoveAnimationOn == true)
	{
		return;
	}
	//BeepThread();
	stopAllActions();
	auto animate = m_pMakeAnimation->AnimationMove(m_CurDirection);
	auto moveOn = CallFunc::create(CC_CALLBACK_0(Character::MoveOn, this));
	auto moveOff = CallFunc::create(CC_CALLBACK_0(Character::MoveOff, this));
	auto sequence = Sequence::create(moveOn, animate, moveOff, NULL);
	cocos2d::log("걷기시작");
	runAction(sequence);
}
//정지모션을 스프라이트를 상속받은 이클래스에 넣어준다.
void Character::Stop(float dt)
{
	if (m_StopAnimationOn == true)
	{
		return;
	}
	stopAllActions();
	auto animate = m_pMakeAnimation->AnimationStop(m_CurDirection);
	auto stopOn = CallFunc::create(CC_CALLBACK_0(Character::StopOn, this));
	auto stopOff = CallFunc::create(CC_CALLBACK_0(Character::StopOff, this));
	auto sequence = Sequence::create(stopOn, animate, stopOff, NULL);
	runAction(sequence);
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
	else if (m_IsMoveState == true)
	{
		Move(dt);
	}
	else if (m_IsStopState == true)
	{
		Stop(dt);
	}
}
//스프라이트 캐쉬에 이미지를 올린다.
void Character::AddSpriteFramesWithFile(const char * filename)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(filename);
}
void Character::AttackOff()
{
	m_ActionAnimationOn = false;
	m_IsActionState = false;
	m_IsMoveState = false;
	m_IsStopState = true;
}
void Character::MoveOff()
{
	m_MoveAnimationOn = false;
	m_IsActionState = false;
	m_IsMoveState = false;
	m_IsStopState = true;
}
void Character::StopOff()
{
	m_StopAnimationOn = false;
}

void Character::AttackOn()
{
	m_ActionAnimationOn = true;
}

void Character::MoveOn()
{
	m_MoveAnimationOn = true;
}

void Character::StopOn()
{
	m_StopAnimationOn = true;
}