#pragma once

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
};