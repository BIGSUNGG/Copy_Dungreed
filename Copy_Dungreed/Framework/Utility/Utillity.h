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

static string CharToStr(char* value, int size)
{
	string result;

	for (int i = 0; i < size; i++)
	{
		if (value[i] == '\0')
			break;

		result.push_back(value[i]);
	}

	return result;
}

static wstring CharToWstr(char* value, int size = 1000)
{
	wstring result;

	for (int i = 0; i < size; i++)
	{
		if (value[i] == '\0')
			break;

		result.push_back(value[i]);
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
