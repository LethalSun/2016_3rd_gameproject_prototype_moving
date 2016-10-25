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
	m_pMakeAnimation = new MakeAnimation(BFE_IDCA_DEFINE::ARCH_BISHOP_FILE_NAME, BFE_IDCA_DEFINE::SPRITE_FRAME_FILE_EXTENTION);
	//����,�̵�,���� ���¸� ��Ÿ���� ���� �ʱ�ȭ
//	m_IsActionState = false;
//	m_IsMoveState = false;
//	m_IsStopState = true;
	//�ִϸ��̼������� �ƴ����� ��Ÿ���� ����
	m_ActionAnimationOn = false;
	m_MoveAnimationOn = false;
	m_StopAnimationOn = true;
	//�Է��÷��׸� ó���ϱ� ���� ���� �ʱ�ȭ
	m_Input = 0;
	m_ActionInput = 0;
	m_MoveInput = 0;
	m_CurDirection = BFE_IDCA_DEFINE::ACTIONS::NO_MOVE;
	m_BeforeDirection = BFE_IDCA_DEFINE::ACTIONS::NO_MOVE;
	m_UnitVector[0] = 0;
	m_UnitVector[1] = 0;
	//this->addChild(m_pMakeAnimation);
}
//Ű���� �Էº�Ʈ �÷��׸� �׼Ǻκа�,�����Ӻκ����� ������ ������ ������ �ش�. �����ÿ� ����� ���� ���⿡ ���� ó���� ������.
void Character::SetInput(int inputFromScene)
{
	m_Input = inputFromScene;
	m_ActionInput = m_Input & BFE_IDCA_DEFINE::ACTIONS::GET_ACTION_BIT;
	m_MoveInput = m_Input & BFE_IDCA_DEFINE::ACTIONS::DIRECTION_BIT;
	switch (m_MoveInput)
	{
	case BFE_IDCA_DEFINE::ACTIONS::TOP:
	{
		m_UnitVector[0] = 0;
		m_UnitVector[1] = 1;
		m_BeforeDirection = m_CurDirection;
		m_CurDirection = BFE_IDCA_DEFINE::ACTIONS::TOP;
		break;
	}
	case BFE_IDCA_DEFINE::ACTIONS::TOP_RIGTH:
	{
		m_UnitVector[0] = 1;
		m_UnitVector[1] = 1;
		m_BeforeDirection = m_CurDirection;
		m_CurDirection = BFE_IDCA_DEFINE::ACTIONS::TOP_RIGTH;
		break;
	}
	case BFE_IDCA_DEFINE::ACTIONS::RIGHT:
	{
		m_UnitVector[0] = 1;
		m_UnitVector[1] = 0;
		m_BeforeDirection = m_CurDirection;
		m_CurDirection = BFE_IDCA_DEFINE::ACTIONS::RIGHT;
		break;
	}
	case BFE_IDCA_DEFINE::ACTIONS::BOTTOM_RIGHT:
	{
		m_UnitVector[0] = 1;
		m_UnitVector[1] = -1;
		m_BeforeDirection = m_CurDirection;
		m_CurDirection = BFE_IDCA_DEFINE::ACTIONS::BOTTOM_RIGHT;
		break;
	}
	case BFE_IDCA_DEFINE::ACTIONS::BOTTOM:
	{
		m_UnitVector[0] = 0;
		m_UnitVector[1] = -1;
		m_BeforeDirection = m_CurDirection;
		m_CurDirection = BFE_IDCA_DEFINE::ACTIONS::BOTTOM;
		break;
	}
	case BFE_IDCA_DEFINE::ACTIONS::BOTTOM_LEFT:
	{
		m_UnitVector[0] = -1;
		m_UnitVector[1] = -1;
		m_BeforeDirection = m_CurDirection;
		m_CurDirection = BFE_IDCA_DEFINE::ACTIONS::BOTTOM_LEFT;
		break;
	}
	case BFE_IDCA_DEFINE::ACTIONS::LEFT:
	{
		m_UnitVector[0] = -1;
		m_UnitVector[1] = 0;
		m_BeforeDirection = m_CurDirection;
		m_CurDirection = BFE_IDCA_DEFINE::ACTIONS::LEFT;
		break;
	}
	case BFE_IDCA_DEFINE::ACTIONS::TOP_LEFT:
	{
		m_UnitVector[0] = -1;
		m_UnitVector[1] = 1;
		m_BeforeDirection = m_CurDirection;
		m_CurDirection = BFE_IDCA_DEFINE::ACTIONS::TOP_LEFT;
		break;
	}
	default:
	{
		m_MoveInput = BFE_IDCA_DEFINE::ACTIONS::NO_MOVE;
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
//�Է¿� ���� ������ ���¸� �ľ��Ѵ�.
void Character::CheckCharacterState()
{
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
	//if (isAttack)
	//	aTTACK();
	//	return;
	//
	//	if (isInputBykey)
	//	{
	//		Move();
	//	}
	//	else
	//		Idle();

	//	if ((m_IsActionState == false) && (m_ActionInput != 0))
	//	{
	//		m_IsActionState = true;
	//		m_IsMoveState = false;
	//		m_IsStopState = false;
	//	}
	//	else if ((m_IsActionState == false) && (m_IsMoveState == false) && (m_MoveInput != BE_IDCA_ACTIONS::ACTIONS::NO_MOVE))
	//	{
	//		m_IsActionState = false;
	//		m_IsMoveState = true;
	//		m_IsStopState = false;
	//
	//		m_BeforeDirection = m_CurDirection;
	//	}
	//	else if ((m_IsActionState == false) && (m_IsStopState == false) && (m_MoveInput == BE_IDCA_ACTIONS::ACTIONS::NO_MOVE))
	//	{
	//		m_IsActionState = false;
	//		m_IsMoveState = false;
	//		m_IsStopState = true;
	//	}
		//	char buffer[256];
		//	sprintf(buffer, "inputKeyboard: %d,%d,%d", m_IsActionState, m_IsMoveState, m_IsStopState);
		//	cocos2d::log(buffer);
}
//���ݸ���� ��������Ʈ�� ��ӹ��� ��Ŭ������ �־��ش�.
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
//�̵������ ��������Ʈ�� ��ӹ��� ��Ŭ������ �־��ش�.
void Character::Move(float dt)
{
	if (m_MoveAnimationOn == true && m_BeforeDirection == m_CurDirection)
	{
		return;
	}
	//BeepThread();
	stopAllActions();
	auto animate = m_pMakeAnimation->AnimationMove(m_CurDirection);
	auto moveOn = CallFunc::create(CC_CALLBACK_0(Character::MoveOn, this));
	auto moveOff = CallFunc::create(CC_CALLBACK_0(Character::MoveOff, this));
	auto sequence = Sequence::create(moveOn, animate, moveOff, NULL);
	cocos2d::log("�ȱ����");
	runAction(sequence);
}
//��������� ��������Ʈ�� ��ӹ��� ��Ŭ������ �־��ش�.
void Character::Stop(float dt)
{
	stopAllActions();
	auto animate = m_pMakeAnimation->AnimationStop(m_CurDirection);
	auto stopOn = CallFunc::create(CC_CALLBACK_0(Character::StopOn, this));
	auto stopOff = CallFunc::create(CC_CALLBACK_0(Character::StopOff, this));
	auto sequence = Sequence::create(stopOn, animate, stopOff, NULL);
	runAction(sequence);
}
//�������Ӹ��� �̽�������Ʈ�� ������ �͵��� �����Ѵ�. ���� �ľ�->���
void Character::update(float dt)
{
	//���� �ľ�
	CheckCharacterState();
	//���
	if (m_State == BFE_IDCA_DEFINE::CHARACTER_STATE::STATE_ATTACK)
	{
		Attack(dt);
	}
	else if (m_State == BFE_IDCA_DEFINE::CHARACTER_STATE::STATE_MOVE)
	{
		Move(dt);
	}
	else if (m_State == BFE_IDCA_DEFINE::CHARACTER_STATE::STATE_STOP)
	{
		Stop(dt);
	}
}
//��������Ʈ ĳ���� �̹����� �ø���.
void Character::AddSpriteFramesWithFile(const char * filename)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(filename);
}
void Character::AttackOff()
{
	m_ActionAnimationOn = false;
	m_State = BFE_IDCA_DEFINE::CHARACTER_STATE::STATE_STOP;
	//	m_IsActionState = false;
	//	m_IsMoveState = false;
	//	m_IsStopState = true;
}
void Character::MoveOff()
{
	m_MoveAnimationOn = false;
	m_State = BFE_IDCA_DEFINE::CHARACTER_STATE::STATE_STOP;
	//	m_IsActionState = false;
	//	m_IsMoveState = false;
	//	m_IsStopState = true;
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