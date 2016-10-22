#pragma once
class PrototypeScene :public Layer
{
public:
	static Scene* scene();
	CREATE_FUNC(PrototypeScene);
	virtual bool init();

private:
	PrototypeScene();
	~PrototypeScene();
};
