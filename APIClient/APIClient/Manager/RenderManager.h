#pragma once

class RenderManager : public Singleton<RenderManager>
{
private:
	friend class Singleton;

	RenderManager();
	~RenderManager();

public:
	void Update();
	void Render(HDC hdc);

private:

};