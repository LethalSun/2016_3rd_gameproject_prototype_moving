#include "pch.h"
#include "Character.h"
#include "MakeAnimation.h"
#include "EnumDefines.h"
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
	//����,�̵�,���� ���¸� ��Ÿ���� ���� �ʱ�ȭ
	m_IsActionState = false;
	m_IsMoveState = false;
	m_IsStopState = true;
	//�Է��÷��׸� ó���ϱ� ���� ���� �ʱ�ȭ
	m_Input = 0;
	m_ActionInput = 0;
	m_MoveInput = 0;
	m_CurDirection = BE_IDCA_ACTIONS::ACTIONS::NO_MOVE;
	m_BeforeDirection = BE_IDCA_ACTIONS::ACTIONS::NO_MOVE;
	m_UnitVector[0] = 0;
	m_UnitVector[1] = 0;
	//this->addChild(m_pMakeAnimation);
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
	char buffer[256];
	sprintf(buffer, "inputCharacter: %d,%d", m_CurDirection, m_MoveInput);
	cocos2d::log(buffer);
}
//�Է¿� ���� ������ ���¸� �ľ��Ѵ�.
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
}
//���ݸ���� ��������Ʈ�� ��ӹ��� ��Ŭ������ �־��ش�.
void Character::Attack(float dt)
{
	if (m_IsActionState == false)
	{
		return;
	}
	auto animate = m_pMakeAnimation->AnimationAttack(m_CurDirection);
	auto attackOff = CallFunc::create(CC_CALLBACK_0(Character::AttackOff, this));
	auto sequence = Sequence::create(animate, attackOff, NULL);
	this->runAction(sequence);
}
//�̵������ ��������Ʈ�� ��ӹ��� ��Ŭ������ �־��ش�.
void Character::Move(float dt)
{
	if (m_IsMoveState == false)
	{
		return;
	}

	auto animate = m_pMakeAnimation->AnimationMove(m_CurDirection);
	auto moveOff = CallFunc::create(CC_CALLBACK_0(Character::MoveOff, this));
	auto sequence = Sequence::create(animate, moveOff, NULL);
	this->runAction(sequence);
}
//��������� ��������Ʈ�� ��ӹ��� ��Ŭ������ �־��ش�.
void Character::Stop(float dt)
{
	if (m_IsStopState == false)
	{
		return;
	}

	auto animate = m_pMakeAnimation->AnimationStop(m_CurDirection);
	auto stopOff = CallFunc::create(CC_CALLBACK_0(Character::StopOff, this));
	auto sequence = Sequence::create(animate, stopOff, NULL);
	this->runAction(sequence);
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
	else if (m_IsMoveState == true)
	{
		Move(dt);
	}
	else if (m_IsStopState == true)
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
	m_IsActionState = false;
}
void Character::MoveOff()
{
	m_IsMoveState = false;
}
void Character::StopOff()
{
	m_IsStopState = false;
}