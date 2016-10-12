#pragma once

class KeyboardLayer;

class UserClass :public Node
{
private:
	enum direction {
		NO_MOVE = 0,
		TOP = 1,
		BOTTOM = 2,
		ERROR_INPUT1 = 3,
		LEFT = 8,
		TOP_RIGTH = 5,
		BOTTOM_RIGHT = 6,
		RIGHT = 4,
		TOP_LEFT = 9,
		BOTTOM_LEFT = 10,
		ERROR_INPUT2 = 12,
		ERROR_INPUT3 = 7,
		ERROR_INPUT4 = 11,
		ERROR_INPUT5 = 13,
		ERROR_INPUT6 = 14,
		ERROR_INPUT7 = 15,
	};

	const int PIXEL_PER_SECOND = 100;
	const int SPRITE_FILE_NUMBER = 10;

public:
	
	static cocos2d::Scene* scene();
	virtual bool init();
	CREATE_FUNC(UserClass);
	void SetDirection(const unsigned int &keyboardDirection);
	void MoveUserClass(float dt);
private:
	//�ִϸ��̼��� ���� �������
	Sprite *m_pArchBishop;
	SpriteFrameCache *m_pFrame;
	Animation *m_pAnimation;
	Animate *m_pAnimate;
	char m_buffer[100];
	void MakeAnimation();

	//���⺯��
	int m_currentDirection;
	int m_beforeDirection;
	int m_unitVec[2];
};

