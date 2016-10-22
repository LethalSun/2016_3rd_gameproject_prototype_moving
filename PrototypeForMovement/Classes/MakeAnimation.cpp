#include "pch.h"
#include "MakeAnimation.h"
#include "EnumDefines.h"

const float ANIMATION_SPEED = 0.1f;
const float HIT_ANIMATION_SPEED = 0.1f;

//이동 애니메이션을 만들어 반환한다.
Sequence* MakeAnimation::AnimationMove(int direction, int speed)
{
	int imageStartNumber = direction * BE_IDCA_DEFINES::NUM_OF_SPRITE_FILE_PER_ACTIONS;
	Vector<SpriteFrame*> animFrame;
	for (int i = imageStartNumber; i < imageStartNumber + 8; i++)
	{
		sprintf(m_Buffer, "%smove%d%s", m_FrameName, i, m_FileNameExtention);

		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(m_Buffer);
		animFrame.pushBack(frame);
	}
	m_pAnimation = Animation::createWithSpriteFrames(animFrame, ANIMATION_SPEED);
	m_pAnimate = Animate::create(m_pAnimation);
	auto AnimationOff = CallFunc::create(CC_CALLBACK_0(MakeAnimation::MoveAnimationEnd, this));
	auto sequenceAnimation = Sequence::create(m_pAnimate, AnimationOff, NULL);
	return sequenceAnimation;
}

//정지상태의 텍스쳐를 반환한다.
Texture2D* MakeAnimation::AnimationStop(int direction)
{
	//int imageStartNumber = direction * BE_IDCA_DEFINES::NUM_OF_SPRITE_FILE_PER_ACTIONS;
	//Vector<SpriteFrame*> animFrame;

	//sprintf(m_Buffer, "%sstop%d%s", m_FrameName, direction, m_FileNameExtention);
	//auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(m_Buffer);
	//animFrame.pushBack(frame);
	//m_pAnimation = Animation::createWithSpriteFrames(animFrame, ANIMATION_SPEED);
	//m_pAnimate = Animate::create(m_pAnimation);
	sprintf(m_Buffer, "%sstop%d%s", m_FrameName, direction, m_FileNameExtention);
	return SpriteFrameCache::getInstance()->getSpriteFrameByName(m_Buffer)->getTexture();
}

//공격 애니메이션을 반환한다.
Sequence* MakeAnimation::AnimationAttack(int direction, int speed)
{
	int imageStartNumber = direction * BE_IDCA_DEFINES::NUM_OF_SPRITE_FILE_PER_ACTIONS;

	if (imageStartNumber < 170)
	{
		return;
	}

	Vector<SpriteFrame*> animFrame;
	for (int i = imageStartNumber; i < imageStartNumber + 7; i++)
	{
		sprintf(m_Buffer, "%shit%d%s", m_FrameName, direction, m_FileNameExtention);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(m_Buffer);
		animFrame.pushBack(frame);
	}

	m_pAnimation = Animation::createWithSpriteFrames(animFrame, HIT_ANIMATION_SPEED);
	m_pAnimate = Animate::create(m_pAnimation);
	auto AnimationOff = CallFunc::create(CC_CALLBACK_0(MakeAnimation::AttackAnimationEnd, this));
	auto sequenceAnimation = Sequence::create(m_pAnimate, AnimationOff, NULL);

	return sequenceAnimation;
}

void MakeAnimation::AddSpriteFramesWithFile(char * filename)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(filename);
}

void MakeAnimation::AttackAnimationEnd()
{
	m_AttackOn = false;
}

void MakeAnimation::MoveAnimationEnd()
{
	m_MoveOn = false;
}