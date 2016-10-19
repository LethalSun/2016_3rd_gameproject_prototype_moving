#include "pch.h"
#include "MakeAnimation.h"

const float ANIMATION_SPEED = 0.1f;
const float HIT_ANIMATION_SPEED = 0.1f;

void MakeAnimation::AnimationMove()
{
	m_Character->stopAllActions();
	Vector<SpriteFrame*> animFrame;
	for (int i = imageStartNumber; i < imageStartNumber + 8; i++)
	{
		sprintf(m_buffer, "%s%d%s", m_FrameName,i,m_FileNameExtention);

		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(m_buffer);
		animFrame.pushBack(frame);
	}
	m_pAnimation = Animation::createWithSpriteFrames(animFrame, ANIMATION_SPEED);
	m_pAnimate = Animate::create(m_pAnimation);
	m_pArchBishop->runAction(RepeatForever::create(m_pAnimate));
}

void MakeAnimation::AnimationStop()
{
}

void MakeAnimation::AnimationAttack()
{
}

void MakeAnimation::MakeAnimationWithFrameName(const char & plistName, const char & frameName, Sprite * character)
{
	sprintf(m_FileNameExtention,"%s", plistName);
	sprintf(m_FrameName, "%s", frameName);
	m_Character = character;
}

