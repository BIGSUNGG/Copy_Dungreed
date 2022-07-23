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