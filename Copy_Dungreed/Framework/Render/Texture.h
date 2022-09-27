#pragma once
class Texture
{
public:
	static shared_ptr<Texture>& Add(wstring file);
	static shared_ptr<Texture>& Add(wstring file, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv);
	void Set(UINT slot);
	void SetSrv(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv) { _srv = srv; }
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

