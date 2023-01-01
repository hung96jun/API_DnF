#include "Framework/Framework.h"
#include "Keyboard.h"

Keyboard::Keyboard()
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

Keyboard::~Keyboard()
{
}

void Keyboard::Update()
{
	UpKeyUpdate();
	DownKeyUpdate();
	PressKeyUpdate();
}

void Keyboard::AddPressKey(KeyValue::Type Type, std::function<void()> function)
{
	PressFuncSet[Type] = function;
}

void Keyboard::AddDownKey(KeyValue::Type Type, std::function<void()> function)
{
	DownFuncSet[Type] = function;
}

void Keyboard::AddUpKey(KeyValue::Type Type, std::function<void()> function)
{
	UpFuncSet[Type] = function;
}

void Keyboard::ChangeKey(KeyValue::Type Type, int Key)
{
	map<InputType::Type, std::vector<KeyInfo>>::iterator it = KeySet.begin();
	
	for (; it != KeySet.end(); ++it)
	{
		for (KeyInfo& info : (*it).second)
		{
			if (info.Type == Type)
			{
				info.KeyValue = Key;
				break;
			}
		}
	}
}

void Keyboard::DownKeyUpdate()
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

void Keyboard::UpKeyUpdate()
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

void Keyboard::PressKeyUpdate()
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
