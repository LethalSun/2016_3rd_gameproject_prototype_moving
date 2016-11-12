#pragma once
<<<<<<< HEAD
=======
class Character;
>>>>>>> 7ab9e4018567d5c7a764ebcbff1934aa7166a1de

class CharacterManage :public Node
{
public:

	static cocos2d::Scene* createScene();
	virtual bool init();

	CREATE_FUNC(CharacterManage);

	void Update(float delta);
	void GetCharacterInfo(Character* character);
	void GetSpriteInfo(Sprite* sprite);
	void CheckHit();
private:
<<<<<<< HEAD
=======
	Vec2 m_CharacterPosition;
	Vec2 m_CharacterAttackDirection;
	Vec2 m_CharacterAttackRange;
	Vec2 m_CharacterBeAttackedBox;
	Vec2 m_TargetPosition;
	Vec2 m_TargetBeAttackefBox
>>>>>>> 7ab9e4018567d5c7a764ebcbff1934aa7166a1de
};