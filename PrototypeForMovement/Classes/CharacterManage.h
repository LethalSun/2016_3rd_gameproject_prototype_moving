#pragma once
class Character;

class CharacterManage :public Node
{
public:

	//static cocos2d::Scene* createScene();
	virtual bool init();

	CREATE_FUNC(CharacterManage);

	void update(float delta);
	void GetCharacterInfo(Character* character);
	void GetSpriteInfo(Sprite* sprite);
	bool CheckHit();
	bool GetHitInfo();
	Vec2 Distance(Vec2 a, Vec2 b);
	Vec2 AttackAnchorPoint();

private:
	bool m_HitHit;
	int m_CharacterState;
	Vec2 m_CharacterPosition;
	Vec2 m_CharacterAttackDirection;
	Vec2 m_CharacterAttackRange;
	Vec2 m_CharacterBeAttackedBox;
	Vec2 m_TargetPosition;
	Vec2 m_TargetBeAttackefBox;
	
};