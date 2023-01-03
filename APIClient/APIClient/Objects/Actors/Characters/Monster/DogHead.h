#pragma once

class DogHead
{
private:
	const float MOVE_SPEED = 200.0f;

	enum State
	{
		Idle,
		Sting,
		Sting2,
		Swing,
		Swing2,

		SpearStand,
		TakeDown,

		DownCharge,
		ThrowCharge,

		Domerta,		// 3 consecutive charge skill
		Pendeta,		// Jump and doiwn sting

		Canaria,		// 100 stack Holding

		Groggy,
		Death,
	};
public:
	DogHead();
	~DogHead();

private:

};
