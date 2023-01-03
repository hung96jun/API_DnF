#include "Framework/Framework.h"
#include "Camera.h"

#include "Objects/Actors/Characters/Player/Player.h"

Camera::Camera()
{
	Key = new Keyboard();

	Key->AddPressKey(KeyValue::Temp1, bind(&Camera::OnRightClick, this));
	Key->AddUpKey(KeyValue::Temp1, bind(&Camera::EndRightClick, this));

	Key->AddPressKey(KeyValue::Temp2, bind(&Camera::OnTop, this));
	Key->AddPressKey(KeyValue::Temp3, bind(&Camera::OnLeft, this));
	Key->AddPressKey(KeyValue::Temp4, bind(&Camera::OnBottom, this));
	Key->AddPressKey(KeyValue::Temp5, bind(&Camera::OnRight, this));

	//Location = Vector2(WIN_WIDTH, WIN_HEIGHT) * 0.5f;
	Location = {};
	
}

Camera::~Camera()
{
	delete Key;
}

void Camera::Update()
{
	//Velocity = Target->GetVelocity();
	//
	//Rect->Right();
	//if (Target->GetLocation().x >= WIN_WIDTH)
	//{
	//	Target->AdditionalLocationX(-Velocity.x);
	//}
	//
	//if (Target->GetLocation().y >= WIN_HEIGHT)
	//{
	//	Target->AdditionalLocationY(-Velocity.y);
	//}
	Key->Update();
	SetTargetLocation();
	SetRenderRectLocation();
}

void Camera::Render(HDC hdc)
{

}

void Camera::SetBackgroundRect(RectCollision* RenderRect)
{
	Rect = RenderRect;
	Rect->SetLocation({ WIN_CENTER_X, WIN_CENTER_Y });
	Rect->SetSize({ WIN_WIDTH, WIN_HEIGHT });
}

void Camera::SetTargetLocation()
{
	if (Target == nullptr) return;

	Vector2 location = Target->GetLocation();
	//Velocity = Target->GetVelocity();
	//
	//// 왼쪽으로 이동
	//if (Velocity.x < 0.0f)
	//{
	//	if (Rect->Left() <= 0.0f)
	//		Velocity.x = 0.0f;
	//}
	//
	//if (Velocity.x > 0.0f)
	//{
	//	if (Rect->Right() >= Bitmap.bmWidth)
	//		Velocity.x = 0.0f;
	//}
	//
	//if (Velocity.y < 0.0f)
	//{
	//	if (Rect->Top() <= 0.0f)
	//		Velocity.y = 0.0f;
	//}
	//
	//if (Velocity.y > 0.0f)
	//{
	//	if (Rect->Bottom() >= Bitmap.bmHeight)
	//		Velocity.y = 0.0f;
	//}

	if (location.x > WIN_CENTER_X)
	{
		if (Rect->Right() >= Bitmap.bmWidth)
		{
			Velocity.x = 0.0f;
		}
		else
		{
			Velocity.x = MAX_SPEED * DELTA_TIME;
			Target->SetLocationX(WIN_CENTER_X);
			//Target->ControlMoveX(false);
		}
	}

	if (location.x < WIN_CENTER_X)
	{
		if (Rect->Left() <= 0)
		{
			Velocity.x = 0.0f;
		}
		else
		{
			Velocity.x = -MAX_SPEED * DELTA_TIME;
			Target->SetLocationX(WIN_CENTER_X);
		}
	}

	if (location.y > WIN_CENTER_Y)
	{
		if (Target->IsJump() == true)
			return;

		if (Rect->Bottom() >= Bitmap.bmHeight)
		{
			Velocity.y = 0.0f;
		}
		else
		{
			Velocity.y = MAX_SPEED * DELTA_TIME;
			Target->SetLocationY(WIN_CENTER_Y);
			//Target->ControlMoveX(false);
		}
	}

	if (location.y < WIN_CENTER_Y)
	{
		if (Target->IsJump() == true)
			return;

		if (Rect->Top() <= 0)
		{
			Velocity.y = 0.0f;
		}
		else
		{
			Velocity.y = -MAX_SPEED * DELTA_TIME;
			Target->SetLocationY(WIN_CENTER_Y);
		}
	}
}

void Camera::SetRenderRectLocation()
{
	//if (Rect->Left() <= 0.0f)
	//	bCameraMoveX = false;
	//
	//if (Rect->Right() >= Bitmap.bmWidth)
	//	bCameraMoveX = false;
	//
	//if (Rect->Top() <= 0.0f)
	//	bCameraMoveY = false;
	//
	//if (Rect->Bottom() >= Bitmap.bmHeight)
	//	bCameraMoveY = false;

	Location += Velocity;

	bCameraMoveX = true;
	bCameraMoveY = true;

	if (bCameraMoveX == true)
		Rect->AdditionalLocation(Vector2(Velocity.x, 0.0f));
	if (bCameraMoveY == true)
		Rect->AdditionalLocation(Vector2(0.0f, Velocity.y));

	Velocity = {};
}

void Camera::OnRightClick()
{
	bFreeMove = true;
}

void Camera::EndRightClick()
{
	//bFreeMove = false;
}

void Camera::OnLeft()
{
	//if (bCameraMoveX == true)
	//{
	if (!(Rect->Left() <= 0.0f))
		Velocity.x -= MAX_SPEED * DELTA_TIME;
	//}
}

void Camera::OnRight()
{
	//if (bCameraMoveX == true)
	//{

	float test = Rect->Right();
	if (!(Rect->Right() >= Bitmap.bmWidth))
		Velocity.x += MAX_SPEED * DELTA_TIME;
	//}
}

void Camera::OnTop()
{
	//if (bCameraMoveY == true)
	//{
	if (!(Rect->Top() <= 0.0f))
		Velocity.y -= MAX_SPEED * DELTA_TIME;
	//}
}

void Camera::OnBottom()
{
	//if (bCameraMoveY == true)
	//{
	float test = Rect->Bottom();
	if (!(Rect->Bottom() >= Bitmap.bmHeight))
		Velocity.y += MAX_SPEED * DELTA_TIME;
	//}
}
