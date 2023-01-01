#pragma once

class SpriteImage
{
public:
	SpriteImage() = default;
	SpriteImage(SpriteInfo Sprite);
	~SpriteImage();

	void Play();
	
	//void Render()



private:
	int Index = -1;
	SpriteInfo Info;
	std::function<void()> EndFunction;
};