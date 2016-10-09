#pragma once

class KeyboardLayer;

class UserClass :public Node
{
public:
	
	static cocos2d::Scene* scene();
	virtual bool init();
	CREATE_FUNC(UserClass);
	void SetDirection(const unsigned int &keyboardDirection);
	void MoveUserClass(float dt);
private:
	//애니메이션을 위한 멤버변수
	Sprite *m_archBishop;
	SpriteFrameCache *m_frame;
	Animation *m_animation;
	Animate *m_animate;
	MoveBy *m_move;
	Spawn *m_spawn;
	char buffer[100];
	
	//방향변수
	int m_currentDirection;

	enum direction {
		//앞은 키보드의 방향 뒤의 숫자는 캐릭터의 방향
		NO = 0,
		UP_1200 = 1,
		DOWN_0600 = 2,
		RIGHT_0900 = 4,
		UP_RIGHT_0130 = 5,
		DOWN_RIGHT_0430 = 6,
		LEFT_0300 = 8,
		UP_LEFT_1030 = 9,
		DOWN_LEFT_0730 = 10
		
	};
};

