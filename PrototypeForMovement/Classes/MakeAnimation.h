#pragma once

class MakeAnimation
{
public:
	Sequence* AnimationMove(int direction, int speed);
	Texture2D* AnimationStop(int direction);
	Sequence* AnimationAttack(int direction, int speed);
	void AddSpriteFramesWithFile(char * filename);

private:
	char m_FileNameExtention[10];
	char m_FrameName[100];
	char m_Buffer[256];
	bool m_AttackOn;
	bool m_MoveOn;
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

	void AttackAnimationEnd();
	void MoveAnimationEnd();

	MakeAnimation();
	~MakeAnimation();
};