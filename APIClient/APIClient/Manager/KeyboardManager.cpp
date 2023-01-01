#include "Framework/Framework.h"
#include "KeyboardManager.h"

void KeyboardManager::Update()
{
	memcpy(BeforeState, CurState, sizeof(BeforeState));

	GetKeyboardState(CurState);

	for (UINT i = 0; i < KEY_MAX; ++i)
	{
		BYTE key = CurState[i] & 0x80;
		CurState[i] = key ? 1 : 0;

		BYTE before = BeforeState[i];
		BYTE current = CurState[i];

		if (before == 0 && current == 1)
			MapState[i] = KeyState::Down;
		else if (before == 1 && current == 0)
			MapState[i] = KeyState::Up;
		else if (before == 1 && current == 1)
			MapState[i] = KeyState::Press;
		else
			MapState[i] = KeyState::None;
	}
}
