#pragma once

class MakeAnimation
{
public:
	//�̵� �ִϸ��̼��� ����� ��ȯ�Ѵ�.
	Animate* AnimationMove(int direction);
	//���������� �ؽ��ĸ� ��ȯ�Ѵ�.
	Animate* AnimationStop(int direction);
	//���� �ִϸ��̼��� ��ȯ�Ѵ�.
	Animate* AnimationAttack(int direction);

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

	MakeAnimation();
	~MakeAnimation();
};