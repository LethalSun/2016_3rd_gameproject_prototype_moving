#include "pch.h"
#include "CharacterManage.h"

Scene* CharacterManage::createScene()
{
	auto scene = Scene::create();

	CharacterManage* node = CharacterManage::create();
	node->addChild(node);
	return scene;
}

bool CharacterManage::init()
{
	if (!Node::init())
	{
		return false;
	}
	return true;
}

void CharacterManage::SetKeyboardInput(const unsigned int &keyboardDirection)
{
}

void CharacterManage::CheckHit()
{
}

void CharacterManage::Update(float delta)
{
}