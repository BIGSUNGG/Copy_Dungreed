#pragma once
class Texture
{
public:
	static shared_ptr<Texture>& Add(wstring file);
	void Set(UINT slot);
	Vector2 GetSize();
	const wstring& GetFile() { return _file; }

public:
	Texture(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv, ScratchImage& image);
	~Texture();

	static unordered_map<wstring, shared_ptr<Texture>> _texturesMap;

	wstring _file;
	ScratchImage _image;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> _srv;
};

