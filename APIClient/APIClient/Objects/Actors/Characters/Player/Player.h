#pragma once

class Weapon;

class Player : public Character
{
private:
	const float JUMP_POWER = 800.0f;
	const float GRAVITY = 2000.0f;
	const float Accel_SPEED = 1.7f;

	enum CharacterState
	{
		Idle,
		Move,
		Jump,
		Attack,
		Smash,
	};

public:
	Player();
	Player(Vector2 Location);
	~Player();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

protected:
	virtual void OnBegin(RectCollision* Other) override;
	void GetGravity();
	
private:
	void InputKey();
	virtual void Init() override;

	void MoveInput();

	void AnimationSetting();
	void AnimStateSetting();

	void KeyboardSetting();
	void CollisionSetting();

	void AnimationPlay();

	//////////////////////////////////////////////////////////////////////////////
	/// Bind key function
	//////////////////////////////////////////////////////////////////////////////
	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();

	void ReleaseMoveHorizontal();
	void ReleaseMoveVertiacal();
	
	void OnAttacking();
	void OnSmashing();
	void OnJump();

	void EndAttacking();
	//////////////////////////////////////////////////////////////////////////////

private:
	//Weapon* weapon = nullptr;
	//Keyboard* Key = nullptr;
	TestKeyboard* Key = nullptr;
	Animation* Anim = nullptr;

	Vector2 Size = {};
	Vector2 Velocity = {};
	Vector2 TempLocation = {};

	float AccelMagnifi = 1.0f;
	bool bJump = false;

	CharacterState CurState = CharacterState::Idle;
	CharacterState BeforeState = CharacterState::Idle;
};