#pragma once

class KeyboardLayer;

class UserClass //:public Layer
{
public:
	UserClass();
	~UserClass();
	void SetDirection(const unsigned int &keyboardDirection);
	void MoveUserClass();
private:
	Sprite m_archBishop;
	int m_checkCurrentDirection;
	//bool m_checkCurrentDirection[8];
	
	enum directionIndex {
		UP = 1,
		DOWN = 2,
		RIGHT = 4,
		LEFT = 8
	};

	enum direction {
		NO = 0,
		UP_1200 = 1,
		DOWN_0600 = 2,
		RIGHT_0900 = 4,
		UP_RIGHT_0130 = 5,
		DOWN_RIGHT_0430 = 6,
		LEFT_0300 = 8,
		UP_LEFT_1030 = 9,
		DOUN_LEFT_0730 = 10
		
	};
};

