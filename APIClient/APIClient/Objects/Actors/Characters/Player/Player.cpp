#include "Framework/Framework.h"
#include "Player.h"

#include "Objects/Actors/Weapon/Weapon.h"

Player::Player()
{
	Init();
}

Player::Player(Vector2 Location)
	: Character(Location)
{
	Init();
}

Player::~Player()
{
	delete Key;
	delete Sword;
}

void Player::Init()
{
	Key = new Keyboard();
	Sword = new Weapon(this);
	

	Location = Vector2(WIN_CENTER_X, WIN_CENTER_Y);

	KeyboardSetting();
	CollisionSetting();
	AnimationSetting();
	AnimStateSetting();

	CurState = Idle_R;
	Anim->Play(CurState);

	//{
	//	HDC hdc = GetDC(hWnd);
	//	hMemDC = CreateCompatibleDC(hdc);
	//	ReleaseDC(hWnd, hdc);
	//
	//	wstring str = L"Resource/Player/Knight/000.bmp";
	//	hTest = (HBITMAP)LoadImage(hInst, str.c_str(), IMAGE_BITMAP, 303, 243, LR_LOADFROMFILE);
	//	SelectObject(hMemDC, hTest);
	//}
}

void Player::Update()
{
	Super::Update();

	InputKey();
	Anim->Update();
	GetGravity();

	//CurState = Idle;

	AnimationPlay();
}

void Player::Render(HDC hdc)
{
	Super::Render(hdc);
	Anim->Render(hdc);
}

void Player::InputKey()
{
	Key->Update();
	MoveInput();
}

void Player::GetGravity()
{
	if (bJump == false) return;
	Velocity.y += GRAVITY * DELTA_TIME;

	if (Location.y >= TempLocation.y)
	{
		bJump = false;
		IsChangeState = true;
		Velocity.y = 0.0f;
		CurState = Idle_R;
	}
}

#pragma region Input Function
void Player::MoveInput()
{
	if (IsMove == false) return;

	Location += Velocity * DELTA_TIME;
	if(bJump == false)
		Velocity = {0, 0};
}
#pragma endregion

#pragma region Bind key function
void Player::MoveLeft()
{
	CurDir = Left;
	if (Velocity.x != 0)
		Velocity.x = 0;
	else if (Location.x > SIZE.x * 0.5f)
		Velocity.x = -Speed * AccelMagnifi;

	if (IsChangeState == false) return;
	CurState = Move_L;
}

void Player::MoveRight()
{
	CurDir = Right;
	if (Velocity.x != 0)
		Velocity.x = 0;
	else if (Location.x < WIN_WIDTH - SIZE.x * 0.5f)
		Velocity.x = Speed * AccelMagnifi;

	if (IsChangeState == false) return;
	CurState = Move_R;
}

void Player::MoveUp()
{
	if (bJump == true) return;

	if (Velocity.y != 0)
		Velocity.y = 0;
	else if (Location.y > SIZE.y * 0.5f)
		Velocity.y = -Speed * AccelMagnifi;

	if (IsChangeState == false) return;
	
	if (CurDir == Right)
		CurState = Move_R;
	else if (CurDir == Left)
		CurState = Move_L;
}

void Player::MoveDown()
{
	if (bJump == true) return;

	if (Velocity.y != 0)
		Velocity.y = 0;
	else if (Location.y < WIN_HEIGHT - SIZE.x * 0.5f)
		Velocity.y = Speed * AccelMagnifi;

	if (IsChangeState == false) return;
	
	if (CurDir == Right)
		CurState = Move_R;
	else if (CurDir == Left)
		CurState = Move_L;
}

void Player::ReleaseMoveHorizontal()
{
	if (IsChangeState == false) return;

	Velocity.x = 0;

	if (CurState == Jump_R || CurState == Jump_L) return;
	
	if (CurDir == Right)
		CurState = Idle_R;
	else if (CurDir == Left)
		CurState = Idle_L;
}

void Player::ReleaseMoveVertiacal()
{
	if (IsChangeState == false) return;

	Velocity.y = 0;

	if (CurState == Jump_R || CurState == Jump_L) return;

	if (CurDir == Right)
		CurState = Idle_R;
	else if (CurDir == Left)
		CurState = Idle_L;
}

/**
* CurState 변경을 별도로 처리
*/
void Player::OnAttacking()
{
	if (bJump == true) return;
	if (IsAttack == true) return;

	//if(CurState != Attack1)
	//	CurState = Attack1;
	
	/// 공격중이 아닐 경우
	if (CurState < FIRST_ATTACK)
	{
		if (CurDir == Right)
			CurState = Attack1_R;
		else if (CurDir == Left)
			CurState = Attack1_L;
	}

	else if (CurState >= FIRST_ATTACK || CurState < LAST_ATTACK)
	{
		int temp = static_cast<int>(CurState);
		temp += 2;
		CurState = static_cast<CharacterState>(temp);
	}

	IsChangeState = false;
	IsMove = false;
	IsAttack = true;
}

void Player::OnSmashing()
{
	if (CurDir == Right)
		CurState = Smash_R;
	else if (CurDir == Left)
		CurState = Smash_L;

	IsChangeState = false;
	IsMove = false;
	IsAttack = true;
}

void Player::OnJump()
{
	if (bJump == true) return;
	if (IsChangeState == false) return;
	if (IsMove == false) return;

	IsChangeState = false;
	
	if (CurDir == Right)
		CurState = Jump_R;
	else if (CurDir == Left)
		CurState = Jump_L;

	if(bJump == false)
		TempLocation = Location;

	bJump = true;

	Velocity.y = -JUMP_POWER;
}

void Player::EndAttacking()
{
	if (CurDir == Right)
		CurState = Idle_R;
	else if (CurDir == Left)
		CurState = Idle_L;

	IsMove = true;
	IsChangeState = true;
	IsAttack = false;
}
#pragma endregion

void Player::SaveAttacking()
{
	IsAttack = false;
	//IsChangeState = true;
	
	//OnAttacking();
}

void Player::OnBegin(RectCollision* Other)
{
	if (Other == nullptr) return;

	//hdc = GetDC(hWnd);

	//if (hdc == nullptr) return;

	//wstring str = L"Player OnBegin";
	//TextOut(hdc, (int)(WIN_CENTER_X), (int)10, str.c_str(), (int)(str.length()));
}

void Player::AnimationSetting()
{
	std::wstring str;
	SpriteInfo sprite;
	// Right Motion
	{
		str = L"Resource/Player/Knight/Movement_R.bmp";
		sprite = SpriteInfo(str, Vector2(1818, 1458), Vector2(6, 6), 35, Vector2(15, -17));
		Anim->Add(L"Movement_R", sprite);

		str = L"Resource/Player/Knight/NormalAttack_R.bmp";
		sprite = SpriteInfo(str, Vector2(1818, 972), Vector2(6, 4), 22, Vector2(15, -17));
		Anim->Add(L"NormalAttack_R", sprite);

		str = L"Resource/Player/Knight/Skill1_R.bmp";
		sprite = SpriteInfo(str, Vector2(1818, 1701), Vector2(6, 7), 37, Vector2(15, -17));
		Anim->Add(L"Skill1_R", sprite);

		str = L"Resource/Player/Knight/Skill2_R.bmp";
		sprite = SpriteInfo(str, Vector2(1818, 2430), Vector2(6, 10), 61, Vector2(15, -17));
		Anim->Add(L"Skill2_R", sprite);
	}

	// Left Motion
	{
		str = L"Resource/Player/Knight/Movement_L.bmp";
		sprite = SpriteInfo(str, Vector2(1818, 1458), Vector2(6, 6), 35, Vector2(-15, -17), 0.1f);
		Anim->Add(L"Movement_L", sprite);

		str = L"Resource/Player/Knight/NormalAttack_L.bmp";
		sprite = SpriteInfo(str, Vector2(1818, 972), Vector2(6, 4), 22, Vector2(-15, -17));
		Anim->Add(L"NormalAttack_L", sprite);

		str = L"Resource/Player/Knight/Skill1_L.bmp";
		sprite = SpriteInfo(str, Vector2(1818, 1701), Vector2(6, 7), 37, Vector2(-15, -17));
		Anim->Add(L"Skill1_L", sprite);

		str = L"Resource/Player/Knight/Skill2_L.bmp";
		sprite = SpriteInfo(str, Vector2(1818, 2430), Vector2(6, 10), 61, Vector2(-15, -17));
		Anim->Add(L"Skill2_L", sprite);
	}
}

void Player::AnimStateSetting()
{
	// Right Motion
	{
		Anim->SetFrame(L"Movement_R", CharacterState::Idle_R, Vector2(0, 1), Vector2(5, 1), LoopType::Loop, 0.1f);
		Anim->SetFrame(L"Movement_R", CharacterState::Move_R, Vector2(0, 2), Vector2(3, 3), LoopType::Loop, 0.1f);
		Anim->SetFrame(L"Movement_R", CharacterState::Jump_R, Vector2(0, 5), Vector2(5, 5), LoopType::Delay, 0.19f);
		//Anim->SetEndFunction(L"Movement", CharacterState::Jump, bind(&Player::EndJump, this));

		Anim->SetFrame(L"NormalAttack_R", CharacterState::Attack1_R, Vector2(0, 0), Vector2(2, 1), LoopType::Delay, 0.07f);
		Anim->SetEndFunction(L"NormalAttack_R", CharacterState::Attack1_R, bind(&Player::EndAttacking, this));
		Anim->AddFrameFunction(L"NormalAttack_R", CharacterState::Attack1_R, 6, bind(&Player::SaveAttacking, this));
		Anim->SetDelayTime(L"NormalAttack_R", CharacterState::Attack1_R, 0.02f);

		Anim->SetFrame(L"NormalAttack_R", CharacterState::Attack2_R, Vector2(3, 1), Vector2(2, 2), LoopType::Delay, 0.07f);
		Anim->SetEndFunction(L"NormalAttack_R", CharacterState::Attack2_R, bind(&Player::EndAttacking, this));
		Anim->AddFrameFunction(L"NormalAttack_R", CharacterState::Attack2_R, 4, bind(&Player::SaveAttacking, this));
		Anim->SetDelayTime(L"NormalAttack_R", CharacterState::Attack2_R, 0.02f);

		Anim->SetFrame(L"NormalAttack_R", CharacterState::Attack3_R, Vector2(3, 2), Vector2(4, 3), LoopType::Delay, 0.07f);
		Anim->SetEndFunction(L"NormalAttack_R", CharacterState::Attack3_R, bind(&Player::EndAttacking, this));
		Anim->SetDelayTime(L"NormalAttack_R", CharacterState::Attack3_R, 0.02f);

		Anim->SetFrame(L"Skill2_R", CharacterState::Smash_R, Vector2(0, 4), Vector2(3, 5), LoopType::Delay, 0.07f);
		Anim->SetEndFunction(L"Skill2_R", CharacterState::Smash_R, bind(&Player::EndAttacking, this));
		Anim->SetDelayTime(L"Skill2_R", CharacterState::Smash_R, 0.02f);
	}

	// Left Motion
	{
		Anim->SetFrame(L"Movement_L", CharacterState::Idle_L, Vector2(0, 1), Vector2(5, 1), LoopType::Loop, 0.1f);
		Anim->SetFrame(L"Movement_L", CharacterState::Move_L, Vector2(0, 2), Vector2(3, 3), LoopType::Loop, 0.1f);
		Anim->SetFrame(L"Movement_L", CharacterState::Jump_L, Vector2(0, 5), Vector2(5, 5), LoopType::Stop, 0.19f);
		//Anim->SetEndFunction(L"Movement", CharacterState::Jump, bind(&Player::EndJump, this));

		Anim->SetFrame(L"NormalAttack_L", CharacterState::Attack1_L, Vector2(0, 0), Vector2(2, 1), LoopType::Delay, 0.07f);
		Anim->SetEndFunction(L"NormalAttack_L", CharacterState::Attack1_L, bind(&Player::EndAttacking, this));
		Anim->AddFrameFunction(L"NormalAttack_L", CharacterState::Attack1_L, 6, bind(&Player::SaveAttacking, this));
		Anim->SetDelayTime(L"NormalAttack_L", CharacterState::Attack1_L, 0.02f);

		Anim->SetFrame(L"NormalAttack_L", CharacterState::Attack2_L, Vector2(3, 1), Vector2(2, 2), LoopType::Delay, 0.07f);
		Anim->SetEndFunction(L"NormalAttack_L", CharacterState::Attack2_L, bind(&Player::EndAttacking, this));
		Anim->AddFrameFunction(L"NormalAttack_L", CharacterState::Attack2_L, 4, bind(&Player::SaveAttacking, this));
		Anim->SetDelayTime(L"NormalAttack_L", CharacterState::Attack2_L, 0.02f);

		Anim->SetFrame(L"NormalAttack_L", CharacterState::Attack3_L, Vector2(3, 2), Vector2(4, 3), LoopType::Delay, 0.07f);
		Anim->SetEndFunction(L"NormalAttack_L", CharacterState::Attack3_L, bind(&Player::EndAttacking, this));
		Anim->SetDelayTime(L"NormalAttack_L", CharacterState::Attack3_L, 0.02f);

		Anim->SetFrame(L"Skill2_L", CharacterState::Smash_L, Vector2(0, 4), Vector2(3, 5), LoopType::Delay, 0.07f);
		Anim->SetEndFunction(L"Skill2_L", CharacterState::Smash_L, bind(&Player::EndAttacking, this));
		Anim->SetDelayTime(L"Skill2_L", CharacterState::Smash_L, 0.02f);
	}
}

void Player::KeyboardSetting()
{
	Key->AddPressKey(KeyValue::Up, bind(&Player::MoveUp, this));
	Key->AddPressKey(KeyValue::Down, bind(&Player::MoveDown, this));
	Key->AddPressKey(KeyValue::Left, bind(&Player::MoveLeft, this));
	Key->AddPressKey(KeyValue::Right, bind(&Player::MoveRight, this));

	Key->AddUpKey(KeyValue::Left, bind(&Player::ReleaseMoveHorizontal, this));
	Key->AddUpKey(KeyValue::Right, bind(&Player::ReleaseMoveHorizontal, this));
	Key->AddUpKey(KeyValue::Up, bind(&Player::ReleaseMoveVertiacal, this));
	Key->AddUpKey(KeyValue::Down, bind(&Player::ReleaseMoveVertiacal, this));

	Key->AddDownKey(KeyValue::Jump, bind(&Player::OnJump, this));
	Key->AddDownKey(KeyValue::Attack, bind(&Player::OnAttacking, this));
	Key->AddDownKey(KeyValue::Smash, bind(&Player::OnSmashing, this));
}

void Player::CollisionSetting()
{
	CollisionManager::Get()->ChangeCollisionChannel(Collision, CollisionChannel::Channel1);
	Collision->SetHidden(false);

	Collision->SetLocation(Vector2(WIN_CENTER_X, WIN_CENTER_Y));
	Collision->SetSize(Vector2(50.0f, 50.0f));

	Collision->AddFunction(Implement<Player>(this, &Player::OnBegin));
}

void Player::AnimationPlay()
{
	if (CurState != BeforeState)
		Anim->Play(CurState);

	BeforeState = CurState;
}
