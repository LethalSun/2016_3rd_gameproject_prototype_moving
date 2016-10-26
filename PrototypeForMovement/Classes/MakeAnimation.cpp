#include "pch.h"
#include "MakeAnimation.h"
#include "EnumDefines.h"

//이동 애니메이션을 만든다.
Animate* MakeAnimation::AnimationMove(int direction)
{
	int imageStartNumber = direction * BFE_IDCA_DEFINE::NUM_OF_SPRITE_FILE_PER_ACTIONS;
	Vector<SpriteFrame*> animFrame;
	for (int i = imageStartNumber; i < imageStartNumber + 8; i++)
	{
		sprintf(m_Buffer, "%smove%d%s", m_FrameName, i, m_FileNameExtention);
		char buffer[256];
		sprintf(buffer, "inputKeyboard: %s", m_Buffer);
		cocos2d::log(buffer);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(m_Buffer);
		animFrame.pushBack(frame);
	}
	m_pAnimation = Animation::createWithSpriteFrames(animFrame, BFE_IDCA_DEFINE::ANIMATION_SPEED);
	m_pAnimate = Animate::create(m_pAnimation);
	return m_pAnimate;
}

//정지상태의 텍스쳐를 만든다.
Animate* MakeAnimation::AnimationStop(int direction)
{
	int imageStartNumber = direction;
	Vector<SpriteFrame*> animFrame;
	sprintf(m_Buffer, "%sstop%d%s", m_FrameName, direction, m_FileNameExtention);
	auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(m_Buffer);
	animFrame.pushBack(frame);
	m_pAnimation = Animation::createWithSpriteFrames(animFrame, BFE_IDCA_DEFINE::STOP_ANIMATION_SPEED);
	m_pAnimate = Animate::create(m_pAnimation);
	return m_pAnimate;
}

//공격 애니메이션을 만든다.
Animate* MakeAnimation::AnimationAttack(int direction)
{
	int imageStartNumber = (direction | BFE_IDCA_DEFINE::ACTIONS::ATTACK) * BFE_IDCA_DEFINE::NUM_OF_SPRITE_FILE_PER_ACTIONS;

	if (imageStartNumber < 170)
	{
		return nullptr;
	}

	Vector<SpriteFrame*> animFrame;
	for (int i = imageStartNumber; i < imageStartNumber + 7; i++)
	{
		sprintf(m_Buffer, "%shit%d%s", m_FrameName, i, m_FileNameExtention);
		char buffer[256];
		sprintf(buffer, "inputKeyboard: %s", m_Buffer);
		cocos2d::log(buffer);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(m_Buffer);
		animFrame.pushBack(frame);
	}

	m_pAnimation = Animation::createWithSpriteFrames(animFrame, BFE_IDCA_DEFINE::HIT_ANIMATION_SPEED);
	m_pAnimate = Animate::create(m_pAnimation);
	return m_pAnimate;
}

Animate * MakeAnimation::GetAttackAnimation(int direction)
{
	if (direction == BFE_IDCA_DEFINE::ACTIONS::TOP || direction == BFE_IDCA_DEFINE::ACTIONS::TOP_LEFT)
	{
		return m_pAttackUpUpLeft;
	}
	else if (direction == BFE_IDCA_DEFINE::ACTIONS::LEFT || direction == BFE_IDCA_DEFINE::ACTIONS::BOTTOM_LEFT)
	{
		return m_pAttackLeftDownLeft;
	}
	else if (direction == BFE_IDCA_DEFINE::ACTIONS::BOTTOM || direction == BFE_IDCA_DEFINE::ACTIONS::BOTTOM_RIGHT)
	{
		return m_pAttackDownDownRight;
	}
	else if (direction == BFE_IDCA_DEFINE::ACTIONS::RIGHT || direction == BFE_IDCA_DEFINE::ACTIONS::TOP_RIGTH)
	{
		return m_pAttackRightUpRight;
	}

	return nullptr;
}

Animate * MakeAnimation::GetMoveAnimation(int direction)
{
	switch (direction)
	{
	case BFE_IDCA_DEFINE::ACTIONS::TOP:
	{
		return m_pMoveUp;
	}
	case BFE_IDCA_DEFINE::ACTIONS::TOP_LEFT:
	{
		return m_pMoveUpLeft;
	}
	case BFE_IDCA_DEFINE::ACTIONS::TOP_RIGTH:
	{
		return m_pMoveUpRight;
	}
	case BFE_IDCA_DEFINE::ACTIONS::RIGHT:
	{
		return m_pMoveRight;
	}
	case BFE_IDCA_DEFINE::ACTIONS::BOTTOM_RIGHT:
	{
		return m_pMoveDownRight;
	}
	case BFE_IDCA_DEFINE::ACTIONS::BOTTOM:
	{
		return m_pMoveDown;
	}
	case BFE_IDCA_DEFINE::ACTIONS::BOTTOM_LEFT:
	{
		return m_pMoveDownLeft;
	}
	case BFE_IDCA_DEFINE::ACTIONS::LEFT:
	{
		return m_pMoveLeft;
	}
	default:
	{
		return nullptr;
	}
	}
}

Animate * MakeAnimation::GetStopAnimation(int direction)
{
	switch (direction)
	{
	case BFE_IDCA_DEFINE::ACTIONS::TOP:
	{
		return m_pStopUp;
	}
	case BFE_IDCA_DEFINE::ACTIONS::TOP_LEFT:
	{
		return m_pStopUpLeft;
	}
	case BFE_IDCA_DEFINE::ACTIONS::TOP_RIGTH:
	{
		return m_pStopUpRight;
	}
	case BFE_IDCA_DEFINE::ACTIONS::RIGHT:
	{
		return m_pStopRight;
	}
	case BFE_IDCA_DEFINE::ACTIONS::BOTTOM_RIGHT:
	{
		return m_pStopDownRight;
	}
	case BFE_IDCA_DEFINE::ACTIONS::BOTTOM:
	{
		return m_pStopDown;
	}
	case BFE_IDCA_DEFINE::ACTIONS::BOTTOM_LEFT:
	{
		return m_pStopDownLeft;
	}
	case BFE_IDCA_DEFINE::ACTIONS::LEFT:
	{
		return m_pStopLeft;
	}
	default:
	{
		return nullptr;
	}
	}
	return nullptr;
}

MakeAnimation::MakeAnimation(const char const *fileName, const char const * fileNameExtention)
{
	sprintf(m_FileNameExtention, "%s", fileNameExtention);
	sprintf(m_FrameName, "%s", fileName);
	m_pMoveUp = AnimationMove(1);
	m_pMoveDown = AnimationMove(2);
	m_pMoveRight = AnimationMove(4);
	m_pMoveLeft = AnimationMove(8);
	m_pMoveUpLeft = AnimationMove(9);
	m_pMoveUpRight = AnimationMove(5);
	m_pMoveDownRight = AnimationMove(6);
	m_pMoveDownLeft = AnimationMove(10);
	m_pAttackUpUpLeft = AnimationAttack(1);
	m_pAttackLeftDownLeft = AnimationAttack(8);
	m_pAttackDownDownRight = AnimationAttack(2);
	m_pAttackRightUpRight = AnimationAttack(4);
	m_pStopUp = AnimationStop(1);
	m_pStopDown = AnimationStop(2);
	m_pStopRight = AnimationStop(4);
	m_pStopLeft = AnimationStop(8);
	m_pStopUpLeft = AnimationStop(9);
	m_pStopUpRight = AnimationStop(5);
	m_pStopDownRight = AnimationStop(6);
	m_pStopDownLeft = AnimationStop(0);
}

MakeAnimation::~MakeAnimation()
{
}