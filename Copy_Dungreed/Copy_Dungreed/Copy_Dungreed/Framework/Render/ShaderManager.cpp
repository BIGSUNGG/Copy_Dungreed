#include "framework.h"
#include "ShaderManager.h"

ShaderManager* ShaderManager::_instance = nullptr;

ShaderManager::ShaderManager()
{
}

ShaderManager::~ShaderManager()
{
}

shared_ptr<VertexShader> ShaderManager::AddVS(wstring file)
{
	if (_shaders.count(file) > 0)
	{
		shared_ptr<VertexShader> vs = dynamic_pointer_cast<VertexShader>(_shaders[file]);
		return vs;
	}

	shared_ptr<VertexShader> shader = make_shared<VertexShader>(file);
	_shaders[file] = shader;

	return shader;
}

shared_ptr<PixelShader> ShaderManager::AddPS(wstring file)
{
	if (_shaders.count(file) > 0)
	{
		shared_ptr<PixelShader> ps = dynamic_pointer_cast<PixelShader>(_shaders[file]);
		return ps;
	}

	shared_ptr<PixelShader> shader = make_shared<PixelShader>(file);
	_shaders[file] = shader;

	return shader;
}
