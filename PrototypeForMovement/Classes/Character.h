#pragma once
class MakeAnimation;

class Character :public Sprite
{
public:
	static Character *create(const char const* filename, const char const* extention);
	void initOptions(const char const* filename, const char const* extention);
	//키보드 입력비트 플래그를 액션부분과,움직임부분으로 나누고 방향을 설정해 준다. 정지시에 사용할 이전 방향에 대한 처리도 같이함.
	void SetInput(int inputFromScene);
	//입력에 따라서 현재의 상태를 파악한다.
	void CheckCharacterState();
	//공격모션을 스프라이트를 상속받은 이클래스에 넣어준다.
	void Attack(float dt);
	//이동모션을 스프라이트를 상속받은 이클래스에 넣어준다.
	void Move(float dt);
	//정지모션을 스프라이트를 상속받은 이클래스에 넣어준다.
	void Stop(float dt);
	//매프레임마다 이스프라이트에 관련한 것들을 갱신한다. 상태 파악->모션
	void update(float dt);
	//스프라이트 캐쉬에 이미지를 올린다.
	void AddSpriteFramesWithFile(const char * filename);
	void AttackOff();
	void MoveOff();
	void StopOff();
	void AttackOn();
	void MoveOn();
	void StopOn();
	Vec2 GetCurrentDitection();
	Vec2 GetAttackRange();
private:
<<<<<<< HEAD
	//상태를 확인 하는함수
=======
	//공격범위
	Vec2 m_AttackRange;
	//방향을 정할때 쓰는 변수
>>>>>>> 7ab9e4018567d5c7a764ebcbff1934aa7166a1de
	bool IsTopOn(int m_MoveInput);
	bool IsBottomOn(int m_MoveInput);
	bool IsLeftOn(int m_MoveInput);
	bool IsRightOn(int m_MoveInput);
	bool IsErrorInput(int m_MoveInput);
	//PHYSICSBODY를 설정하는 함수
	void SetPhysicsBody();
	void DeletePhysicsBody();

	//공격,이동,정지 상태를 나타내는 변수
	int m_State;
	int m_BeforeState;
	//애니메이션중인지 아닌지를 나타내는 변수
	bool m_ActionAnimationOn;
	bool m_MoveAnimationOn;
	bool m_StopAnimationOn;
	//입력플래그를 처리하기 위한 변수
	int m_Input;
	int m_ActionInput;
	int m_MoveInput;
	int m_CurDirection;
	int m_BeforeDirection;
	int m_UnitVector[2];
	//애니메이션을 만들어주는 멤버
	MakeAnimation *m_pMakeAnimation;

	Character();
	~Character();
};

/*
옆 w28,h91
뒤 w37,h88
앞 w38,h90
앞대각공 w77,h81
뒤 대각공 w80,h83
대각위 w36,h93
대각아래 w40,h92
*/