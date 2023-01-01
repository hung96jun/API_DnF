#include "Framework/Framework.h"
#include "Animation.h"


Animation::Animation(Actor* Owner)
	:Owner(Owner)
{
	HDC hdc = GetDC(hWnd);
	hMemDC = CreateCompatibleDC(hdc);
	ReleaseDC(hWnd, hdc);
}

Animation::~Animation()
{
	Destroy();

	DeleteObject(hMemDC);
	DeleteObject(hBitMap);

	delete Info;
}

void Animation::Add(const WSTR& FileName, SpriteInfo Sprite)
{
	if (Animations.count(FileName) > 0) return;

	SpriteInfo* info = new SpriteInfo(Sprite);
	Animations[FileName] = info;
}

void Animation::SetFrame(const WSTR& FileName, const int& Key, const Vector2& Start, const Vector2& End, const LoopType::Type& Loop, const float& Speed)
{
	// 저장된 스프라이트 정보가 없을 경우
	if (Animations.count(FileName) == 0) return;
	// 입력된 행동 key값이 있을 경우
	if (KeySet.count(Key) > 0) return;

	SpriteInfo* sprite = Animations[FileName];
	KeySet[Key] = FileName;
	sprite->SetCutFrame(Key, Start, End, Loop, Speed);
}

void Animation::AddFrameFunction(const WSTR& FileName, const int& Key, const int& Frame, std::function<void()> Func)
{
	Animations[FileName]->SetFrameFunction(Key, Frame, Func);
}

void Animation::SetEndFunction(const WSTR& FileName, const int& Key, std::function<void()> Func)
{
	Animations[FileName]->SetEndFunction(Key, Func);
}

void Animation::Remove(const WSTR& FileName)
{
	if (Animations.count(FileName) == 0) return;

	delete Animations[FileName];
	Animations.erase(FileName);
}

void Animation::Destroy()
{
	for(pair<std::wstring, SpriteInfo*> animation : Animations)
	{
		delete animation.second;
	}
	Animations.clear();
}

void Animation::Play(const int& Key)
{
	if (KeySet.count(Key) == 0) return;

	SelectKey = Key;
	std::wstring file = KeySet[Key];
	CurAnim = Animations[file];

	bPlay = true;
	SelectObject(hMemDC, CurAnim->GetTexture());
	CurFrame = CurAnim->GetCutInfo(SelectKey).Start;
}

void Animation::ReversePlay(const int& Key)
{
}

void Animation::Update()
{
	if (bPlay == false) return;

	CurAnim->SetLocation(Owner->GetLocation());

	if (CurFrame == CurAnim->GetCutInfo(SelectKey).End)
	{
		ResetFrame();

		if (CurAnim->GetCutInfo(SelectKey).Loop == LoopType::Delay)
			return;
	}

	if (CurTime > CurAnim->GetCutInfo(SelectKey).Speed)
	{
		++CurFrame.x;
		++CountFrame;
	
		if (CurFrame.x == CurAnim->GetMaxIndex().x)
		{
			CurFrame.x = CurAnim->GetCutInfo(SelectKey).Start.x;
			
			if (CurFrame.y == CurAnim->GetMaxIndex().y ||
				CurFrame.y == CurAnim->GetCutInfo(SelectKey).End.y)
			{
				ResetFrame();
			}

			else
				++CurFrame.y;
		}

		if (CurAnim->GetCutInfo(SelectKey).FrameFunction.size() > 0)
		{
			CurAnim->CallFrameFunction(SelectKey, CountFrame);
		}

		CurTime = 0.0f;
	}
	
	CurTime += DELTA_TIME;
}

void Animation::Render(HDC hdc)
{
	if (bPlay == false) return;

	Vector2 location = CurAnim->GetLocation();
	Vector2 size = CurAnim->GetCutsize();

	bool check = GdiTransparentBlt(
		hdc,
		location.x, location.y,
		size.x, size.y,
		hMemDC,
		size.x * (CurFrame.x),
		size.y * (CurFrame.y),
		size.x, size.y,
		MAGENTA
	);

	wstring str;
	if (check == true)
	{
		str = L"Success";
		TextOut(hdc, WIN_CENTER_X, 0, str.c_str(), str.length());
	}
	else
	{
		str = L"Failed";
		TextOut(hdc, WIN_CENTER_Y, 0, str.c_str(), str.length());
	}
}

void Animation::ResetFrame()
{
	switch (CurAnim->GetCutInfo(SelectKey).Loop)
	{
	case LoopType::Loop:
	{
		CurFrame = CurAnim->GetCutInfo(SelectKey).Start;
		CountFrame = 0;
	}
		break;
	//case LoopType::Delay:
	//{
	//	CurTime = 0.0f;
	//	CurFrame.x = CurAnim->GetCutInfo(SelectKey).End.x - 1;
	//	CurFrame.y = CurAnim->GetCutInfo(SelectKey).End.y;
	//}
	//	break;
	case LoopType::Stop:
	{
		if (CurAnim->GetCutInfo(SelectKey).EndFunction != nullptr)
			CurAnim->GetCutInfo(SelectKey).EndFunction();

		bPlay = false;
		CountFrame = 0;
	}
		break;
	default:
		break;
	}
}