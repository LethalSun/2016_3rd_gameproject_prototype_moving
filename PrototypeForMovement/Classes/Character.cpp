#include "pch.h"
#include "Character.h"
#include "MakeAnimation.h"
#include "EnumDefines.h"
#include <bitset>

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
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(BFE_IDCA_DEFINE::PLIST_FILE_NAME);
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
	m_pMakeAnimation = MakeAnimation::create(BFE_IDCA_DEFINE::ARCH_BISHOP_FILE_NAME, BFE_IDCA_DEFINE::SPRITE_FRAME_FILE_EXTENTION);
	addChild(m_pMakeAnimation);
	//공격,이동,정지 상태를 나타내는 변수 초기화
	m_State = 0;
	//애니메이션중인지 아닌지를 나타내는 변수
	m_ActionAnimationOn = false;
	m_MoveAnimationOn = false;
	m_StopAnimationOn = true;
	//입력플래그를 처리하기 위한 변수 초기화
	m_Input = 0;
	m_ActionInput = 0;
	m_MoveInput = 0;
	m_CurDirection = BFE_IDCA_DEFINE::ACTIONS::NO_MOVE;
	m_BeforeDirection = BFE_IDCA_DEFINE::ACTIONS::NO_MOVE;
	m_UnitVector[0] = 0;
	m_UnitVector[1] = 0;
}
//키보드 입력비트 플래그를 액션부분과,움직임부분으로 나누고 방향을 설정해 준다. 정지시에 사용할 이전 방향에 대한 처리도 같이함.
void Character::SetInput(int inputFromScene)
{
	m_Input = inputFromScene;
	m_ActionInput = m_Input & BFE_IDCA_DEFINE::ACTIONS::GET_ACTION_BIT;
	m_MoveInput = m_Input & BFE_IDCA_DEFINE::ACTIONS::GET_DIRECTION_BIT;

	if (IsErrorInput(m_MoveInput))
	{
		m_MoveInput = BFE_IDCA_DEFINE::ACTIONS::NO_MOVE;
		m_CurDirection = m_BeforeDirection;

		m_UnitVector[0] = 0;
		m_UnitVector[1] = 0;

		return;
	}

	m_BeforeDirection = m_CurDirection;
	m_CurDirection = m_MoveInput;

	if (IsTopOn(m_MoveInput))
	{
		m_UnitVector[1] = 1;
	}
	else if (IsBottomOn(m_MoveInput))
	{
		m_UnitVector[1] = -1;
	}
	else
	{
		m_UnitVector[1] = 0;
	}

	if (IsLeftOn(m_MoveInput))
	{
		m_UnitVector[0] = -1;
	}
	else if (IsRightOn(m_MoveInput))
	{
		m_UnitVector[0] = 1;
	}
	else
	{
		m_UnitVector[0] = 0;
	}
}
//입력에 따라서 현재의 상태를 파악한다.
void Character::CheckCharacterState()
{
	log("state");
	if (m_ActionAnimationOn == false)
	{
		if (m_ActionInput == BFE_IDCA_DEFINE::ACTIONS::ATTACK)
		{
			m_State = BFE_IDCA_DEFINE::CHARACTER_STATE::STATE_ATTACK;
		}
		else
		{
			if (m_MoveInput == BFE_IDCA_DEFINE::ACTIONS::NO_MOVE)
			{
				m_State = BFE_IDCA_DEFINE::CHARACTER_STATE::STATE_STOP;
			}
			else
			{
				m_State = BFE_IDCA_DEFINE::CHARACTER_STATE::STATE_MOVE;
			}
		}
	}
	else
	{
		return;
	}
	char logBuffer[100];
	sprintf(logBuffer, "m_CHARACTERSTATE:%d ", m_State);
	cocos2d::log(logBuffer);
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
	if (m_MoveAnimationOn == true && m_BeforeDirection == m_CurDirection && m_BeforeState == m_State)
	{
		return;
	}

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
	cocos2d::log("UPDATE");
	//상태 파악
	CheckCharacterState();
	//모션
	if (m_State == BFE_IDCA_DEFINE::CHARACTER_STATE::STATE_ATTACK)
	{
		Attack(dt);
		m_BeforeState = m_State;
	}
	else if (m_State == BFE_IDCA_DEFINE::CHARACTER_STATE::STATE_MOVE)
	{
		Move(dt);
		auto currentposition = getPosition();

		auto deltaX = (m_UnitVector[0] * (BFE_IDCA_DEFINE::VELOCITY)*dt);
		auto deltaY = (m_UnitVector[1] * (BFE_IDCA_DEFINE::VELOCITY)*dt);

		setPositionX(currentposition.x + deltaX);
		setPositionY(currentposition.y + deltaY);
		m_BeforeState = m_State;
	}
	else if (m_State == BFE_IDCA_DEFINE::CHARACTER_STATE::STATE_STOP)
	{
		Stop(dt);
		m_BeforeState = m_State;
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
	m_State = BFE_IDCA_DEFINE::CHARACTER_STATE::STATE_STOP;
}
void Character::MoveOff()
{
	m_MoveAnimationOn = false;
	m_State = BFE_IDCA_DEFINE::CHARACTER_STATE::STATE_STOP;
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

bool Character::IsTopOn(int m_MoveInput)
{
	return m_MoveInput & BFE_IDCA_DEFINE::ACTIONS::TOP;
}

bool Character::IsBottomOn(int m_MoveInput)
{
	return m_MoveInput & BFE_IDCA_DEFINE::ACTIONS::BOTTOM;
}

bool Character::IsLeftOn(int m_MoveInput)
{
	return m_MoveInput & BFE_IDCA_DEFINE::ACTIONS::LEFT;
}

bool Character::IsRightOn(int m_MoveInput)
{
	return m_MoveInput & BFE_IDCA_DEFINE::ACTIONS::RIGHT;
}

bool Character::IsErrorInput(int m_MoveInput)
{
	bool isError = false;
	if (m_MoveInput == 0)
	{
		isError = true;
	}
	else if (m_MoveInput == 3)
	{
		isError = true;
	}
	else if (m_MoveInput == 7)
	{
		isError = true;
	}
	else if (m_MoveInput >= 11 && m_MoveInput <= 15)
	{
		isError = true;
	}

	return isError;
}