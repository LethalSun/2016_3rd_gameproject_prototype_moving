#include "pch.h"
#include "MakeAnimation.h"
#include "EnumDefines.h"

//bool MakeAnimation::init()
//{
//	if (!Node::init())
//	{
//		return false;
//	}
//
//	return true;
//}
//
//이동 애니메이션을 만든다.
Animate* MakeAnimation::AnimationMove(int direction)
{
	int imageStartNumber = direction * BE_IDCA_DEFINES::NUM_OF_SPRITE_FILE_PER_ACTIONS;
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
	m_pAnimation = Animation::createWithSpriteFrames(animFrame, BE_IDCA_DEFINES::ANIMATION_SPEED);
	m_pAnimate = Animate::create(m_pAnimation);
	//auto AnimationOff = CallFunc::create(CC_CALLBACK_0(MakeAnimation::MoveAnimationEnd, this));
	//auto sequenceAnimation = Sequence::create(m_pAnimate, AnimationOff, NULL);
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
	m_pAnimation = Animation::createWithSpriteFrames(animFrame, BE_IDCA_DEFINES::ANIMATION_SPEED);
	m_pAnimate = Animate::create(m_pAnimation);
	//sprintf(m_Buffer, "%sstop%d%s", m_FrameName, direction, m_FileNameExtention);
	return m_pAnimate;
}

//공격 애니메이션을 만든다.
Animate* MakeAnimation::AnimationAttack(int direction)
{
	int imageStartNumber = (direction | BE_IDCA_ACTIONS::ACTIONS::ATTACK) * BE_IDCA_DEFINES::NUM_OF_SPRITE_FILE_PER_ACTIONS;

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

	m_pAnimation = Animation::createWithSpriteFrames(animFrame, BE_IDCA_DEFINES::HIT_ANIMATION_SPEED);
	m_pAnimate = Animate::create(m_pAnimation);
	//auto AnimationOff = CallFunc::create(CC_CALLBACK_0(MakeAnimation::AttackAnimationEnd, this));
//	auto sequenceAnimation = Sequence::create(m_pAnimate, AnimationOff, NULL);

	return m_pAnimate;
}

Animate * MakeAnimation::GetAttackAnimation(int direction)
{
	*m_pAttackUpUpLeft;
	*m_pAttackLeftDownLeft;
	*m_pAttackDownDownRight;
	*m_pAttackRightUpRight;

	return nullptr;
}

Animate * MakeAnimation::GetMoveAnimation(int direction)
{
	*m_pMoveUp;
	*m_pMoveDown;
	*m_pMoveRight;
	*m_pMoveLeft;
	*m_pMoveUpLeft;
	*m_pMoveUpRight;
	*m_pMoveDownRight;
	*m_pMoveDownLeft;
	return nullptr;
}

Animate * MakeAnimation::GetStopAnimation(int direction)
{
	*m_pStopUp;
	*m_pStopDown;
	*m_pStopRight;
	*m_pStopLeft;
	*m_pStopUpLeft;
	*m_pStopUpRight;
	*m_pStopDownRight;
	*m_pStopDownLeft;
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
	m_pStopDownLeft = AnimationStop(10);
}

MakeAnimation::~MakeAnimation()
{
}

//void MakeAnimation::AttackAnimationEnd()
//{
//	m_AttackOn = false;
//}
//
//void MakeAnimation::MoveAnimationEnd()
//{
//	m_MoveOn = false;
//}