#pragma once

class UserClass;

class KeyboardLayer:public Layer
{
public:

	static cocos2d::Scene* createScene();
	virtual bool init();

	CREATE_FUNC(KeyboardLayer);
	virtual void update(float delta) override;
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event) override;
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event) override;
	const unsigned int & GetKeyboardInput();
private:

	enum KeyboardArrow {
		UP = 1,
		DOWN = 2,
		RIGHT = 4,
		LEFT = 8
	};

	unsigned int m_keyboardArrow;
	//bool m_keyboardArrow[4];
	UserClass *m_archBishop;
};

