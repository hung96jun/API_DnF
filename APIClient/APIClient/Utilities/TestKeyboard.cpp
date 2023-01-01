#include "Framework/Framework.h"
#include "TestKeyboard.h"

TestKeyboard::TestKeyboard()
{
	pair<InputType::Type, std::vector<KeyInfo>> keyPair;
	KeyInfo info;

	{
		keyPair.first = InputType::Down;
		std::vector<KeyInfo> infos;
		info = { KeyValue::Attack, 'X' };
		infos.push_back(info);
		info = { KeyValue::Smash, 'Z' };
		infos.push_back(info);
		info = { KeyValue::Jump, 'C' };
		infos.push_back(info);
		info = { KeyValue::Skill1, 'A' };
		infos.push_back(info);
		info = { KeyValue::Skill2, 'S' };
		infos.push_back(info);
		info = { KeyValue::Skill3, 'D' };
		infos.push_back(info);
		info = { KeyValue::Skill4, 'F' };
		infos.push_back(info);
		info = { KeyValue::Skill5, 'G' };
		infos.push_back(info);
		info = { KeyValue::Skill6, 'H' };
		infos.push_back(info);
		info = { KeyValue::Item1, '1' };
		infos.push_back(info);
		info = { KeyValue::Item2, '2' };
		infos.push_back(info);
		info = { KeyValue::Item3, '3' };
		infos.push_back(info);
		info = { KeyValue::Item4, '4' };
		infos.push_back(info);
		info = { KeyValue::Item5, '5' };
		infos.push_back(info);
		info = { KeyValue::Itme6, '6' };
		infos.push_back(info);
		info = { KeyValue::Escape, VK_ESCAPE };
		infos.push_back(info);

		keyPair.second = infos;
		KeySet.insert(keyPair);
	}

	{
		keyPair.first = InputType::Up;
		std::vector<KeyInfo> infos;
		info = { KeyValue::Left, VK_LEFT };
		infos.push_back(info);
		info = { KeyValue::Right, VK_RIGHT };
		infos.push_back(info);
		info = { KeyValue::Up, VK_UP };
		infos.push_back(info);
		info = { KeyValue::Down, VK_DOWN };
		infos.push_back(info);

		keyPair.second = infos;
		KeySet.insert(keyPair);
	}

	{
		keyPair.first = InputType::Press;
		std::vector<KeyInfo> infos;
		info = { KeyValue::Left, VK_LEFT };
		infos.push_back(info);
		info = { KeyValue::Right, VK_RIGHT };
		infos.push_back(info);
		info = { KeyValue::Up, VK_UP };
		infos.push_back(info);
		info = { KeyValue::Down, VK_DOWN };
		infos.push_back(info);

		keyPair.second = infos;
		KeySet.insert(keyPair);
	}
}

TestKeyboard::~TestKeyboard()
{
}

void TestKeyboard::Update()
{
	UpKeyUpdate();
	DownKeyUpdate();
	PressKeyUpdate();
}

void TestKeyboard::AddPressKey(KeyValue::Type Type, std::function<void()> function)
{
	PressFuncSet[Type] = function;
}

void TestKeyboard::AddDownKey(KeyValue::Type Type, std::function<void()> function)
{
	DownFuncSet[Type] = function;
}

void TestKeyboard::AddUpKey(KeyValue::Type Type, std::function<void()> function)
{
	UpFuncSet[Type] = function;
}

void TestKeyboard::ChangeKey(KeyValue::Type Type, int Key)
{
	//KeySet[Type] = Key;
	for (pair<InputType::Type, std::vector<KeyInfo>> keyPair : KeySet)
	{
		for (KeyInfo info : keyPair.second)
		{
			if (info.Type == Type)
			{
				info.KeyValue = Key;
				break;
			}
		}
	}
}

void TestKeyboard::DownKeyUpdate()
{
	vector<KeyInfo> infos = KeySet[InputType::Down];
	for (KeyInfo info : infos)
	{
		if (KEY_DOWN(info.KeyValue))
		{
			if (DownFuncSet[info.Type] != nullptr)
				DownFuncSet[info.Type]();
		}
	}
}

void TestKeyboard::UpKeyUpdate()
{
	vector<KeyInfo> infos = KeySet[InputType::Up];
	for (KeyInfo info : infos)
	{
		if (KEY_UP(info.KeyValue))
		{
			if (UpFuncSet[info.Type] != nullptr)
				UpFuncSet[info.Type]();
		}
	}
}

void TestKeyboard::PressKeyUpdate()
{
	vector<KeyInfo> infos = KeySet[InputType::Press];
	for (KeyInfo info : infos)
	{
		if (KEY_PRESS(info.KeyValue))
		{
			if(PressFuncSet[info.Type] != nullptr)
				PressFuncSet[info.Type]();
		}
	}
}
