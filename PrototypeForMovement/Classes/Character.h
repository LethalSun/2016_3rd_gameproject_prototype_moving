#pragma once
class MakeAnimation;

class Character :public Sprite
{
public:
	static Character *create();
	void initOptions();
	//Ű���� �Էº�Ʈ �÷��׸� �׼Ǻκа�,�����Ӻκ����� ������ ������ ������ �ش�. �����ÿ� ����� ���� ���⿡ ���� ó���� ������.
	void SetInput(int inputFromScene);
	//�Է¿� ���� ������ ���¸� �ľ��Ѵ�.
	void CheckCharacterState();
	//���ݸ���� ��������Ʈ�� ��ӹ��� ��Ŭ������ �־��ش�.
	void Attack(float dt);
	//�̵������ ��������Ʈ�� ��ӹ��� ��Ŭ������ �־��ش�.
	void Move(float dt);
	//��������� ��������Ʈ�� ��ӹ��� ��Ŭ������ �־��ش�.
	void Stop(float dt);
	//�������Ӹ��� �̽�������Ʈ�� ������ �͵��� �����Ѵ�. ���� �ľ�->���
	void update(float dt);
	//��������Ʈ ĳ���� �̹����� �ø���.
	void AddSpriteFramesWithFile(const char * filename);
private:
	//����,�̵�,���� ���¸� ��Ÿ���� ����
	bool m_IsActionState;
	bool m_IsMoveState;
	bool m_IsStopState;
	//�Է��÷��׸� ó���ϱ� ���� ����
	int m_Input;
	int m_ActionInput;
	int m_MoveInput;
	int m_CurDirection;
	int m_BeforeDirection;
	int m_UnitVector[2];
	//�ִϸ��̼��� ������ִ� ���
	MakeAnimation *m_pMakeAnimation;

	Character();
	~Character();
};
