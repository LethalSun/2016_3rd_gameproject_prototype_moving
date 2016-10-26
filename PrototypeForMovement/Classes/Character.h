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
private:
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
