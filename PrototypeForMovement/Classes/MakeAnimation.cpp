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
//�̵� �ִϸ��̼��� ����� ��ȯ�Ѵ�.
Animate* MakeAnimation::AnimationMove(int direction)
{
	int imageStartNumber = direction * BE_IDCA_DEFINES::NUM_OF_SPRITE_FILE_PER_ACTIONS;
	Vector<SpriteFrame*> animFrame;
	for (int i = imageStartNumber; i < imageStartNumber + 8; i++)
	{
		sprintf(m_Buffer, "%smove%d%s", m_FrameName, i, m_FileNameExtention);

		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(m_Buffer);
		animFrame.pushBack(frame);
	}
	m_pAnimation = Animation::createWithSpriteFrames(animFrame, BE_IDCA_DEFINES::ANIMATION_SPEED);
	m_pAnimate = Animate::create(m_pAnimation);
	//auto AnimationOff = CallFunc::create(CC_CALLBACK_0(MakeAnimation::MoveAnimationEnd, this));
	//auto sequenceAnimation = Sequence::create(m_pAnimate, AnimationOff, NULL);
	return m_pAnimate;
}

//���������� �ؽ��ĸ� ��ȯ�Ѵ�.
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

//���� �ִϸ��̼��� ��ȯ�Ѵ�.
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
		sprintf(m_Buffer, "%shit%d%s", m_FrameName, direction, m_FileNameExtention);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(m_Buffer);
		animFrame.pushBack(frame);
	}

	m_pAnimation = Animation::createWithSpriteFrames(animFrame, BE_IDCA_DEFINES::HIT_ANIMATION_SPEED);
	m_pAnimate = Animate::create(m_pAnimation);
	//auto AnimationOff = CallFunc::create(CC_CALLBACK_0(MakeAnimation::AttackAnimationEnd, this));
//	auto sequenceAnimation = Sequence::create(m_pAnimate, AnimationOff, NULL);

	return m_pAnimate;
}

MakeAnimation::MakeAnimation(const char const *fileName, const char const * fileNameExtention)
{
	sprintf(m_FileNameExtention, "%s", fileNameExtention);
	sprintf(m_FrameName, "%s", fileName);
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