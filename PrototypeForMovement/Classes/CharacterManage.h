#pragma once
class Character;

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
	Vec2 m_CharacterPosition;
	Vec2 m_CharacterAttackDirection;
	Vec2 m_CharacterAttackRange;
	Vec2 m_CharacterBeAttackedBox;
	Vec2 m_TargetPosition;
	Vec2 m_TargetBeAttackefBox
};