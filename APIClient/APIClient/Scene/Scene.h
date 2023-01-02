#pragma once

class Scene
{
public:
	Scene() = default;
	virtual ~Scene() = default;

	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;
	virtual void AfterRender(HDC hdc) = 0;
};
