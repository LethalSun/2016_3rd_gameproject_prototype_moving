#include "pch.h"
#include "PrototypeScene.h"

Scene * PrototypeScene::scene()
{
	auto scene = Scene::createWithPhysics();
	auto layer = PrototypeScene::create();
	scene->addChild(layer);

	return scene;
}

bool PrototypeScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	return true;
}

PrototypeScene::PrototypeScene()
{
}

PrototypeScene::~PrototypeScene()
{
}