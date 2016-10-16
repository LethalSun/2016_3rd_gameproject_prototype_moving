#pragma once
class UserClass;

class CharacterManage :public Node
{
public:

	static cocos2d::Scene* createScene();
	virtual bool init();

	CREATE_FUNC(CharacterManage);

	void SetKeyboardInput(const unsigned int &keyboardDirection);
	void CheckHit();
	void Update(float delta);

private:
	Vec4 m_archBishopInfo;
	Vec4 m_monsterInfo;
	UserClass *m_archBishop;
	UserClass *m_monster;
	unsigned int m_keyboardDirection;
};