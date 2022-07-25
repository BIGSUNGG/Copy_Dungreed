#include "framework.h"
#include "BinaryWriter.h"

BinaryWriter::BinaryWriter(wstring path)
: _size(0)
{
	_file = CreateFile(path.c_str(), GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
}

BinaryWriter::~BinaryWriter()
{
	CloseHandle(_file);
}

void BinaryWriter::Int(int data)
{
	WriteFile(_file, &data, sizeof(int), OUT &_size, nullptr);
}

void BinaryWriter::Uint(UINT data)
{
	WriteFile(_file, &data, sizeof(UINT), OUT & _size, nullptr);
}

void BinaryWriter::Float(float data)
{
	WriteFile(_file, &data, sizeof(float), OUT &_size, nullptr);
}

void BinaryWriter::String(string data)
{
	Uint(data.size());

	const char* str = data.c_str();
	WriteFile(_file, str, data.size(), OUT &_size, nullptr);
}

void BinaryWriter::Byte(void* data, UINT dataSize)
{
	WriteFile(_file, data, dataSize,OUT &_size, nullptr);
}
