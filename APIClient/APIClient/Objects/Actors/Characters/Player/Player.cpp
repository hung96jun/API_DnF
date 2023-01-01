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
	delete Anim;
}

void Player::Init()
{
	Key = new Keyboard();

	Location = Vector2(WIN_CENTER_X, WIN_CENTER_Y);

	KeyboardSetting();
	CollisionSetting();
	AnimationSetting();
	AnimStateSetting();

	CurState = Idle;
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
		CurState = Idle;
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
	if (Velocity.x != 0)
		Velocity.x = 0;
	else if (Location.x > SIZE.x * 0.5f)
		Velocity.x = -Speed * AccelMagnifi;

	if (IsChangeState == false) return;
	CurState = Move;
}

void Player::MoveRight()
{
	if (Velocity.x != 0)
		Velocity.x = 0;
	else if (Location.x < WIN_WIDTH - SIZE.x * 0.5f)
		Velocity.x = Speed * AccelMagnifi;

	if (IsChangeState == false) return;
	CurState = Move;
}

void Player::MoveUp()
{
	if (bJump == true) return;

	if (Velocity.y != 0)
		Velocity.y = 0;
	else if (Location.y > SIZE.y * 0.5f)
		Velocity.y = -Speed * AccelMagnifi;

	if (IsChangeState == false) return;
	CurState = Move;
}

void Player::MoveDown()
{
	if (bJump == true) return;

	if (Velocity.y != 0)
		Velocity.y = 0;
	else if (Location.y < WIN_HEIGHT - SIZE.x * 0.5f)
		Velocity.y = Speed * AccelMagnifi;

	if (IsChangeState == false) return;
	CurState = Move;
}

void Player::ReleaseMoveHorizontal()
{
	if (IsChangeState == false) return;

	Velocity.x = 0;

	if (CurState == Jump) return;
	CurState = Idle;
}

void Player::ReleaseMoveVertiacal()
{
	if (IsChangeState == false) return;

	Velocity.y = 0;

	if (CurState == Jump) return;
	CurState = Idle;
}

void Player::OnAttacking()
{
	if (IsChangeState == false) return;
	if (IsAttack == true) return;

	//if(CurState != Attack1)
	//	CurState = Attack1;
	
	/// 공격중이 아닐 경우
	if (CurState < FIRST_ATTACK)
	{
		CurState = Attack1;
	}

	else if (CurState >= FIRST_ATTACK || CurState < LAST_ATTACK)
	{
		int temp = static_cast<int>(CurState);
		++temp;
		CurState = static_cast<CharacterState>(temp);
	}

	IsChangeState = false;
	IsMove = false;
	IsAttack = true;
}

void Player::OnSmashing()
{
}

void Player::OnJump()
{
	if (bJump == true) return;
	if (IsChangeState == false) return;
	if (IsMove == false) return;

	IsChangeState = false;
	CurState = Jump;
	
	if(bJump == false)
		TempLocation = Location;

	bJump = true;

	Velocity.y = -JUMP_POWER;
}

void Player::EndAttacking()
{
	CurState = Idle;
	IsMove = true;
	IsChangeState = true;
	IsAttack = false;
}
#pragma endregion

void Player::SaveAttacking()
{
	IsAttack = false;
	IsChangeState = true;
	
	OnAttacking();
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
	Anim = new Animation(this);

	std::wstring str = L"Resource/Player/Knight/Movement.bmp";
	SpriteInfo sprite = SpriteInfo(str, Vector2(1818, 1458), Vector2(6, 6), Vector2(15, -17), 0.1f);
	Anim->Add(L"Movement", sprite);

	str = L"Resource/Player/Knight/NormalAttack.bmp";
	sprite = SpriteInfo(str, Vector2(1818, 972), Vector2(6, 4), Vector2(15, -17), 0.1f);
	Anim->Add(L"NormalAttack", sprite);
}

void Player::AnimStateSetting()
{
	Anim->SetFrame(L"Movement", CharacterState::Idle, Vector2(0, 1), Vector2(5, 1), LoopType::Loop);
	Anim->SetFrame(L"Movement", CharacterState::Move, Vector2(0, 2), Vector2(3, 3), LoopType::Loop);
	Anim->SetFrame(L"Movement", CharacterState::Jump, Vector2(0, 5), Vector2(5, 5), LoopType::Stop, 0.19f);
	//Anim->SetEndFunction(L"Movement", CharacterState::Jump, bind(&Player::EndJump, this));

	/**
	* 현재 프레임값을 받아서 바인딩 함수를 호출하는 시스템을 만들었지만, 프레임이 튈 경우 호출이 안되는 문제가 발생
	* 
	*/
	Anim->SetFrame(L"NormalAttack", CharacterState::Attack1, Vector2(0, 0), Vector2(2, 1), LoopType::Stop);
	Anim->SetEndFunction(L"NormalAttack", CharacterState::Attack1, bind(&Player::EndAttacking, this));
	Anim->AddFrameFunction(L"NormalAttack", CharacterState::Attack1, 10, bind(&Player::SaveAttacking, this));

	Anim->SetFrame(L"NormalAttack", CharacterState::Attack2, Vector2(3, 2), Vector2(2, 3), LoopType::Stop);
	Anim->SetEndFunction(L"NormalAttack", CharacterState::Attack2, bind(&Player::EndAttacking, this));
	//Anim->SetFrame(L"NormalAttack", CharacterState::Attack2, Vector2(0, 0), Vector2(2, 1), LoopType::Stop);
	//Anim->SetEndFunction(L"NormalAttack", CharacterState::Attack2, bind(&Player::EndAttacking, this));
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
