#pragma once

static string WstrToStr(wstring wStr)
{
	string result;
	result.reserve(wStr.length());

	for (auto w : wStr)
		result.push_back(w);

	return result;
}

static wstring StrToWstr(string str)
{
	wstring result;
	result.reserve(str.length());

	for (auto s : str)
	{
		result.push_back(s);
	}

	return result;
}

static void SwitchBool(bool& value)
{
	if (value == true)
		value = false;
	else
		value = true;
}

static void CursurOn()
{
	int temp = ShowCursor(true);

	if (temp < 0)
	{
		for (int i = 0; i < -temp; i++)
		{
			ShowCursor(true);
		}
	}
}

static void CursurOff()
{
	int temp = ShowCursor(false);

	if (temp > -1)
	{
		for (int i = 0; i < temp + 1; i++)
		{
			ShowCursor(false);
		}
	}
}