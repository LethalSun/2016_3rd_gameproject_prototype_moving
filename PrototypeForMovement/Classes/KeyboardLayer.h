#pragma once

class UserClass;

class KeyboardLayer:public Layer
{
private:
	enum KEY_BOARD_ARROW {
		UP = 1,
		DOWN = 2,
		RIGHT = 4,
		LEFT = 8
	};

public:

	static cocos2d::Scene* createScene();
	virtual bool init();

	CREATE_FUNC(KeyboardLayer);
	virtual void update(float delta) override;
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event) override;
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event) override;
	const unsigned int  GetKeyboardInput();
private:
	unsigned int m_keyboardArrow;
	//bool m_keyboardArrow[4];
	UserClass *m_archBishop;
};

