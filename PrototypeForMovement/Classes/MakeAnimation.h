#pragma once

class MakeAnimation //:public Node
{
public:

	//virtual bool init();
	//CREATE_FUNC(MakeAnimation);
	//�̵� �ִϸ��̼��� ����� ��ȯ�Ѵ�.
	Animate* AnimationMove(int direction);
	//���������� �ؽ��ĸ� ��ȯ�Ѵ�.
	Animate* AnimationStop(int direction);
	//���� �ִϸ��̼��� ��ȯ�Ѵ�.
	Animate* AnimationAttack(int direction);
	MakeAnimation(const char const *fileName, const char const * fileNameExtention);
	~MakeAnimation();
private:
	//����Ȯ����
	char m_FileNameExtention[10];
	//�����̸�
	char m_FrameName[100];
	//�������� �ҷ��ö� ����ϴ� ����
	char m_Buffer[256];

	Animation        *m_pAnimation;
	Animate          *m_pAnimate;
	//void AttackAnimationEnd();
	//void MoveAnimationEnd();
};