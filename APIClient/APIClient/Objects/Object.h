#pragma once

class Object
{
public:
	Object();
	~Object();

	virtual void Render(HDC hdc) = 0;

private:

};
