#pragma once 

class MakeAnimation
{
public:
	void AnimationMove();
	void AnimationStop();
	void AnimationAttack();
	void MakeAnimationWithFrameName(const char &fileNameExtention, const char &frameNameWithOutNumber, Sprite * character);

private:
	char m_FileNameExtention[10];
	char m_FrameName[100];
	char m_buffer[256];
	Sprite *m_Character;
	SpriteFrameCache *m_pFrame;
	Animation        *m_pAnimation;
	Animate          *m_pAnimate;

	enum ANIMATION_STATE
	{
		STOP_ON = 0,
		STOP_OFF = 1,
		MOVE_ON = 2,
		MOVE_OFF = 3,
		ATTACK_ON = 4,
		ATTACK_OFF = 5
	};

	MakeAnimation();
	~MakeAnimation();
};